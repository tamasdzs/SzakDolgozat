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
 *   - own class for Compressed and OrtCompressed!
 * */
struct Compressed {
	Compressed* next;
	Eigen::MatrixXd compressed_sig; 
	Compressed(): next(0) { }
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
 *  - TODO: Make class truly abstract (get rid of OrtCompressed*s)
 */

class Compresser {
	protected:
		
	public:
		Compresser() {}
		virtual ~Compresser() {}
		
		virtual Eigen::MatrixXd compressBeat(Eigen::MatrixXd& signal) = 0;
		virtual const Eigen::MatrixXd decompress(const OrtCompressed* compr) = 0;
};

#endif
