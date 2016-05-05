#ifndef __ORTCOMPRESSER_H__
#define __ORTCOMPRESSER_H__

#include "Compresser.h"
#include "Hermite.h"
//#include "NelderMead.h"

class OrtCompresser: public Compresser {
	protected:
		OrtFunSys* ort_sys;
		
		
		Eigen::MatrixXd calcAprx(const Eigen::MatrixXd& Coeffs, const Eigen::MatrixXd& H);
		
	public:
		OrtCompresser(char* RECORD, const int n_of_leads, const int n_of_samples);
		~OrtCompresser();
		
		Eigen::MatrixXd calcFourier(const Eigen::MatrixXd& H, Eigen::MatrixXd& sig, const double lambda, const double trans);
		
		OrtCompressed compressBeat(const std::vector<int>& rounds);
		//const OrtCompressed compressRec(std::vector<int>& rounds);
		const Eigen::MatrixXd decompress(const OrtCompressed compr);
		const double getPRD(const Eigen::MatrixXd& APR); 
		const double getErr(const Eigen::MatrixXd& Coeffs);
		
};

#endif
