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
 * 	- Compression method for entire record
 * 	- Decompression method for non orthonormal 
 */

class Compresser {
	protected:
		EcgSigPrep* signal_handler;
		
	public:
		Compresser(char* RECORD, const int n_of_leads, const int n_of_samples);
		virtual ~Compresser();
		
		virtual OrtCompressed compressBeat(const std::vector<int>& rounds) = 0;
		virtual const Eigen::MatrixXd decompress(const OrtCompressed compr) = 0;
		virtual const double getPRD(const Eigen::MatrixXd& APR) = 0;
		
		const Eigen::MatrixXd* getSignal();
};

#endif
