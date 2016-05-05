#include "NelderMead.h"
#include <algorithm>

NelderMead::NelderMead(const double beg_dilat, const double beg_trans, unsigned int r): rounds(r) {
	Particle initpart;
	initpart.location.l = beg_dilat;
	initpart.location.t = beg_trans;
	population.push_back(initpart);
	
	initpart.location.l = beg_dilat+0.5;
	initpart.location.t = beg_trans+1;
	population.push_back(initpart);
	
	initpart.location.l = beg_dilat+1;
	initpart.location.t = beg_trans+2;
	population.push_back(initpart);
}

bool lt(Particle i, Particle j) {
		return (i.PRD < j.PRD);
}

Coord NelderMead::Optimize(Eigen::MatrixXd &H, Eigen::MatrixXd &sig, OrtCompresser* compr) {
	//init population
	const double maxErr = 0.3;
	
	for(unsigned int i = 0; i < population.size(); ++i) {
		population[i].co = compr->calcFourier(H, sig, population[i].location.l, population[i].location.t);
		population[i].PRD = compr->getErr(population[i].co);
	}
	
	std::sort(population.begin(), population.end(), lt);
	
	bool over = population[0].PRD < maxErr;
	unsigned int curr_round = 0;
	
	while(!over && curr_round < rounds) {
		
		Coord x4 = population[0].location + ((population[0].location + population[1].location)/2.0 - population[0].location) * 2.0;
		Eigen::MatrixXd co = compr->calcFourier(H, sig, x4.l, x4.t);
		double y4 = compr->getErr(co); 
		
		if( population[2].PRD <= y4 && y4 < population[1].PRD ) {
			population[0].location = x4;
			population[0].co = co;
			population[0].PRD = y4;
		}
		else if( y4 < population[2].PRD ) {
			Coord x5 = population[0].location +((population[1].location + population[2].location)/2.0 - population[0].location)*2.5;
			co = compr->calcFourier(H, sig, x5.l, x5.t);
			double y5 = compr->getErr(co);
			
			if( y5 < y4 ) {
				population[0].location = x5;
				population[0].co = co;
				population[0].PRD = y5;	
			}
			else {
				population[0].location = x4; 			
				population[0].co = compr->calcFourier(H, sig, population[0].location.l, population[0].location.t);
				population[0].PRD = y4;
			}
		}
		else if( y4 >= population[1].PRD ) {
				if ( y4 < population[0].PRD ) {
					Coord x6 = population[0].location + ((population[0].location + population[1].location)/2.0 - population[0].location)*1.5;
					Eigen::MatrixXd co = compr->calcFourier(H, sig, x6.l, x6.t);
					double y6 = compr->getErr(co); 
					
					if( y6 <= y4 ) {
						population[0].location = x6;
						population[0].co = co;
						population[0].PRD = y6;
					}
					else {
						IterStep(H, sig, compr);
					}
				}
				else if( y4 >= population[0].PRD ) {
					Coord x7 = population[0].location - ((population[0].location + population[1].location)/2.0 - population[0].location)*0.5;
					Eigen::MatrixXd co = compr->calcFourier(H, sig, x7.l, x7.t);
					double y7 = compr->getErr(co);
					
					if( y7 < population[2].PRD ) {
						population[0].location = x7;
						population[0].co = co;
						population[0].PRD = y7;
					}
					else {
						IterStep(H, sig, compr);
					} 
				}		
		} 
		
		std::sort(population.begin(), population.end(), lt);
		curr_round++;
		over = population[0].PRD < maxErr;
	}
	
	return population[0].location;
}

void NelderMead::IterStep(Eigen::MatrixXd &H, Eigen::MatrixXd &sig, OrtCompresser* compr) {
	
	std::sort(population.begin(), population.end(), lt);
	
	population[0].location = (population[0].location + population[2].location)*0.5;
	population[0].co = compr->calcFourier(H, sig, population[0].location.l, population[0].location.t);
	population[0].PRD = compr->getErr(population[0].co);
		
	population[1].location = (population[1].location + population[2].location)*0.5;
	population[1].co = compr->calcFourier(H, sig, population[1].location.l, population[1].location.t);
	population[1].PRD = compr->getErr(population[1].co);
}
