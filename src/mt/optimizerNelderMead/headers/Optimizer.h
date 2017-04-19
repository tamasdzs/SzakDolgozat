#ifndef __OPTIMIZER_H__
#define __OPTIMIZER_H__

#include <limits>
#include <vector>
#include <functional>
#include <Eigen/Dense>

/* 
 *	Class: Coord 
 * 	This class inherits from Eigen::MatrixXd, and serves as
 * 	a parameter of the function to be optimized. If the dimension of
 *  the vector is not given, it initaliaizes itself to 2.
*/
class Coord: public std::vector<double> {
	private:
		
	public:
		Coord() {
			this->resize(2);
		}

		Coord(int n) {
			this->resize(n);
		}
		~Coord() {}
		
		Coord operator+(const Coord a) {
			Coord ret(this->size());
			
			if ( this->size() != a.size() ) {
				//HANDLE ERROR
			}
			
			for ( unsigned int i = 0; i < ret.size(); ++i ) {
				ret[i] = (*this)[i] + a[i];
			}
			
			return ret;
		}
		Coord operator-(const Coord a) {
			Coord ret(this->size());
			
			if ( this->size() != a.size() ) {
				//HANDLE ERROR
			}
			
			for ( unsigned int i = 0; i < ret.size(); ++i ) {
				ret[i] = (*this)[i] - a[i];
			}
			
			return ret;
		}
		Coord operator*(const double a) {
			Coord ret(this->size());
			
			for ( unsigned int i = 0; i < ret.size(); ++i ) {
				ret[i] = (*this)[i] * a;
			}
			
			return ret;
		}
		Coord operator/(const double a) {
			Coord ret(this->size());
			
			for ( unsigned int i = 0; i < ret.size(); ++i ) {
				ret[i] = (*this)[i] / a;
			}
			
			return ret;
		}
};


/*
 *  CLASS: Optimizer:
 * 	Parent class of all optimization classes. Pure virtual function optimize 
 * 	is responsible of the execution of the desired optimization algorithm.
 * 	It returns a Coord, and takes as a parameter an anonymus function.
 *  The class also includes protected member generations, which determines the 
 * 	number of times the optimization algorithm runs. In addition the maximum error 
 * 	can be given.
*/

class Optimizer {
	protected:
		const unsigned int generations;
		const double max_err;
	public:
		Optimizer( const unsigned int gen, const double merr ) : generations(gen), max_err(merr) {}
		~Optimizer() {}
		virtual Coord Optimize( std::function<double (Coord &)> costfun ) = 0;
};

#endif
