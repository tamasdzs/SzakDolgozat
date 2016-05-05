#ifndef __NELDER_MEAD_H__
#define __NELDER_MEAD_H__  

#include "Optimizer.h"
#include "OrtCompresser.h"

class NelderMead: public Optimizer{
	protected:
		unsigned int rounds;
		void IterStep(Eigen::MatrixXd &H, Eigen::MatrixXd &sig, OrtCompresser* compr);
		
	public:
		NelderMead(const double beg_dilat, const double beg_trans, unsigned int r);
		~NelderMead() {}
		Coord Optimize(Eigen::MatrixXd &H, Eigen::MatrixXd &sig, OrtCompresser* compr);
};

#endif

