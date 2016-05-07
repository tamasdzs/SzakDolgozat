#ifndef __ORTCOMPRESSER_H__
#define __ORTCOMPRESSER_H__

#include "Compresser.h"
#include "Hermite.h"

/* 
 * CLASS: OrtCompresser
 * Child class of compresser, the puropose of this class is to compress
 * RECORD using some orthonormal polynomial based approach. 
 * 
 * TODO:
 * 		-ERROR: The compression algorithm uses optimization to calculate the
 * 				best possible dilatation and translation parameters for the heartbeat.
 * 				The problem is, that the optimization algorithms themselves need to compress
 * 				and decompress the heartbeat, and this means that while the optimizer 
 * 				class is part of OrtCompresser, OrtCompresser needs also be part of
 * 				the optimizer -> include CONFLICT
 * 				
 * 				POSSIBLE SOLUTION:  Create inbetween class, that is responsible for 
 * 									compression with optimizitation. This class can 
 * 									contain as members both an instance of the OrtCompresser	
 * 									class AND and instance of the optimizer class
 */

class OrtCompresser: public Compresser {
	protected:
		OrtFunSys* ort_sys;
		Eigen::MatrixXd calcAprx(const Eigen::MatrixXd& Coeffs, const Eigen::MatrixXd& H);
		
	public:
		OrtCompresser(char* RECORD, const int n_of_leads, const int n_of_samples);
		~OrtCompresser();
		
		Eigen::MatrixXd calcFourier(const Eigen::MatrixXd& H, Eigen::MatrixXd& sig, const double lambda, const double trans);
		
		OrtCompressed compressBeat(const std::vector<int>& rounds);
		const Eigen::MatrixXd decompress(const OrtCompressed compr);
		const double getPRD(const Eigen::MatrixXd& APR); 
		const double getErr(const Eigen::MatrixXd& Coeffs);
		
};

#endif
