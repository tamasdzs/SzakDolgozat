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
 * */
struct Compressed {
	Eigen::MatrixXd compressed_sig; 
	Compressed() { }
};

/*
 * STRUCT: OrtCompressed
 * Used to store a compressed heartbeat, where compression was done via some
 * orthonormal system. 
 * */
struct OrtCompressed: public Compressed {
	OrtCompressed* next;
	double dilat;
	double trans;
	OrtCompressed(): Compressed(), next(0), dilat(1), trans(0) {}
};

/*
 * CLASS: Compresser 
 * Class contains basic methods for signal compression. Contains as a member, 
 * a signal handler. Methods include compression of a single heartbeat, decompression of 
 * a single heatbeat (orthonormal).  
 * 
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
