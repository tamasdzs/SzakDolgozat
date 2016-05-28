#ifndef __COMPRESSER_H__
#define __COMPRESSER_H__

#include <Eigen/Dense>
#include "EcgSigPrep.h"
#include <vector>
/* 
 * STRUCT: COMPRESSED
 *	Used to store a compressed heartbeat. Stores data needed to reconstruct
 * 	compressed hearbeat. Contains a pointer to the next compressed heartbeat. 
 * 
 * 	TODO:
 * 	 - rename FCOEFFS to fourier_coefficients
 * */
struct Compressed {
	Compressed* next;
	std::vector<Eigen::MatrixXd> FCOEFFS; // Initialize in costructor?
	double sig_first_val;
	double sig_last_val;
	double sig_max_val;
	Compressed(): next(0), sig_first_val(0), sig_last_val(0), sig_max_val(0) { }
};

/*
 * STRUCT: OrtCompressed
 * Used to store a compressed heartbeat, where compression was done via some
 * orthonormal system. 
 * */
struct OrtCompressed: public Compressed {
	double dilat;
	double trans;
	OrtCompressed(): Compressed(), dilat(1), trans(0) {}
};

/*
 * CLASS: Compresser 
 * Class contains basic methods for signal compression. Contains as a member, 
 * a signal handler. Methods include compression of a single heartbeat, decompression of 
 * a single heatbeat (orthonormal).
 * 
 * TODO: 
 * 	- Decompression method for non orthonormal 
 */

class Compresser {
	protected:
		
		
	public:
		Compresser() {}
		virtual ~Compresser() {}
		
		virtual OrtCompressed compressBeat(Eigen::MatrixXd& signal) = 0;
		virtual const Eigen::MatrixXd decompress(const OrtCompressed compr) = 0;
		virtual const double costfun(const Eigen::MatrixXd& APR) = 0; //std::function 
};

#endif
