#ifndef __OPTIMIZER_H__
#define __OPTIMIZER_H__

#include <limits>
#include <vector>
#include <Eigen/Dense>
#include "OrtCompresser.h"

/* 
 *	STRUCT: Coord 
 * 	This struct defines the coordinate of a given particle.
 * 	These coordinates will be used to locate particles in the search
 * 	space for optimization algorithms. (Nelder-Mead, PSO, steepest descent)
*/
struct Coord{
	double l;
	double t;
	Coord(): l(0.0), t(0.0) {}
	Coord operator+(const Coord a){
		Coord ans;
		ans.l = this->l + a.l;
		ans.t = this->t + a.t;
		return ans;
	}
	Coord operator-(const Coord a){
		Coord ans;
		ans.l = this->l - a.l;
		ans.t = this->t - a.t;
		return ans;
	}
	Coord operator*(const double a){
		Coord ans;
		ans.l = this->l*a;
		ans.t = this->t*a;
		return ans;
	}
	Coord operator/(const double a){
		
		Coord ans;
		ans.l = this->l/a;
		ans.t = this->t/a;
		return ans;
	}
	void operator=(const Coord a) {
		this->l = a.l;
		this->t = a.t;
	}
};

/*
 *	STRUCT: Particle 
 * 	This struct defines a particle, which are used by the optimization
 * 	algorithms. 
*/

struct Particle{
	double PRD;
	double velocity;
	Coord location;
	Eigen::MatrixXd co; 
	Particle(): PRD(std::numeric_limits<double>::max()), velocity(0.0) {}
};

#endif
