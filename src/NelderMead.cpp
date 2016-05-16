#include "NelderMead.h"
#include <algorithm>
#include <random>

NelderMead::NelderMead(const unsigned int gen, const double merr, std::vector<Coord> pop): Optimizer(gen, merr) {
	if ( pop.size() != 3 ) {
		//handle error
		std::cout<<"WARNING: NELDER-MEAD OPTIMIZATION STARTED WITHOUT THREE POINTS"<<std::endl;
	} 
	
	for (unsigned int i = 0; i < pop.size(); ++i) {
		 population.insert(std::pair<double, Coord>(std::numeric_limits<double>::max(), pop[i]));
	}	
}

std::vector<std::multimap<double, Coord>::reverse_iterator> NelderMead::set_pointers() {
	std::vector<std::multimap<double, Coord>::reverse_iterator> ret;
	std::multimap<double, Coord>::reverse_iterator access_x = population.rend();
	
	ret.push_back(access_x);
	std::advance(access_x, 1);
	ret.push_back(access_x);
	std::advance(access_x, 1);
	ret.push_back(access_x);
	
	return ret;
}

Coord NelderMead::Optimize( std::function<double (Coord &)> costfun ) {
	
	std::multimap<double, Coord> sort_pop;
	std::vector<std::multimap<double, Coord>::reverse_iterator> access_x = set_pointers();
	
	bool over = false;
	unsigned int curr_round = 0;
	
	if (!costfun) {
		//handle error
	}
	
	//Get initial values of positions. (Y1, Y2, Y3)
	double err;
	for (std::multimap<double, Coord>::iterator it = population.begin(); it != population.end(); ++it ) {
		err = costfun(it->second);
		sort_pop.insert(std::pair<double, Coord>(err, it->second));
		
	}
	
	population = sort_pop;
	sort_pop.clear();
	over = population.begin()->first < max_err;

	//Main loop begins
	while ( !over && curr_round < generations ) {	
		curr_round++;
		access_x = set_pointers();		
		
		Coord x4 = access_x[0]->second + ((access_x[0]->second + access_x[1]->second)/2.0 - access_x[0]->second)*2.0;
		double y4 = costfun(x4);
		
		if ( access_x[2]->first <= y4 && access_x[1]->first <= y4) {
			sort_pop.insert(std::pair<double, Coord>(y4, x4));
			sort_pop.insert(std::pair<double, Coord>(access_x[1]->first, access_x[1]->second));
			sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
			
			population = sort_pop;
			sort_pop.clear();
		}
		else if ( y4 < access_x[2]->first ) {
			Coord x5 = access_x[0]->second +((access_x[1]->second + access_x[2]->second)/2.0 - access_x[0]->second)*2.5;
			double y5 = costfun(x5);
			
			if ( y4 < y5 ) {
				sort_pop.insert(std::pair<double, Coord>(y5, x5));
				sort_pop.insert(std::pair<double, Coord>(access_x[1]->first, access_x[1]->second));
				sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
				
				population = sort_pop;
				sort_pop.clear();
			}
			else {
				sort_pop.insert(std::pair<double, Coord>(y4, x4));
				sort_pop.insert(std::pair<double, Coord>(access_x[1]->first, access_x[1]->second));
				sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
				
				population = sort_pop;
				sort_pop.clear();
			}
		}
		else if ( y4 >= access_x[1]->first ) {
			if ( y4 < access_x[0]->first ) {
				Coord x6 = access_x[0]->second + ((access_x[0]->second + access_x[1]->second)/2.0 - access_x[0]->second)*1.5;
				double y6 = costfun(x6);
				
				if ( y6 <= y4 ) {
					sort_pop.insert(std::pair<double, Coord>(y6, x6));
					sort_pop.insert(std::pair<double, Coord>(access_x[1]->first, access_x[1]->second));
					sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
					
					population = sort_pop;
					sort_pop.clear();
				}
				else {
					//ITER_STEP
					Coord x0 = (access_x[0]->second + access_x[2]->second)*0.5;
					Coord x1 = (access_x[1]->second + access_x[2]->second)*0.5;
					
					double y0 = costfun(x0);
					double y1 = costfun(x1);
					
					sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
					sort_pop.insert(std::pair<double, Coord>(y0, x0));
					sort_pop.insert(std::pair<double, Coord>(y1, x1));
					
					population = sort_pop;
					sort_pop.clear();
				}
			}
			else if ( y4 >= access_x[0]->first ) {
				Coord x7 = access_x[0]->second - ((access_x[0]->second + access_x[1]->second)/2.0 - access_x[0]->second)*0.5;
				double y7 = costfun(x7);
				
				if ( y7 < access_x[2]->first ) {
					sort_pop.insert(std::pair<double, Coord>(y7, x7));
					sort_pop.insert(std::pair<double, Coord>(access_x[1]->first, access_x[1]->second));
					sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
					
					population = sort_pop;
					sort_pop.clear();
				}
				else {
					//ITER_STEP
					Coord x0 = (access_x[0]->second + access_x[2]->second)*0.5;
					Coord x1 = (access_x[1]->second + access_x[2]->second)*0.5;
		
					double y0 = costfun(x0);
					double y1 = costfun(x1);
		
					sort_pop.insert(std::pair<double, Coord>(access_x[2]->first, access_x[2]->second));
					sort_pop.insert(std::pair<double, Coord>(y0, x0));
					sort_pop.insert(std::pair<double, Coord>(y1, x1));
		
					population = sort_pop;
					sort_pop.clear();
				}
			} 
		}
	}	
	
	return access_x[2]->second;
}

int main() {
	
	std::vector<Coord> X;
	Coord t;
	X.resize(3);
	X[0] = t;
	X[1] = t;
	X[2] = t; 
	NelderMead a(3, 4.0, X);
	
	auto cfunc = [] (Coord &t) { double f = (double)rand() / RAND_MAX;
								 return 1.0 + f * (10.0 - 1.0);};
	
	a.Optimize(cfunc);
	
	return 0;
}
