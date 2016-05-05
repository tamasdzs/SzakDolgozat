#ifndef __COMPRESSER_H__
#define __COMPRESSER_H__

#include <Eigen/Dense>
#include "EcgSigPrep.h"
#include <vector>

struct Compressed {
	Compressed* next;
	std::vector<Eigen::MatrixXd> FCOEFFS; // Initialize in costructor?
	double sig_first_val;
	double sig_last_val;
	double sig_max_val;
	Compressed(): next(0), sig_first_val(0), sig_last_val(0), sig_max_val(0) { }
};

struct OrtCompressed: public Compressed {
	double dilat;
	double trans;
	OrtCompressed(): Compressed(), dilat(1), trans(0) {}
};

class Compresser {
	protected:
		EcgSigPrep* signal_handler;
		
	public:
		Compresser(char* RECORD, const int n_of_leads, const int n_of_samples);
		virtual ~Compresser();
		
		virtual OrtCompressed compressBeat(const std::vector<int>& rounds) = 0;
		//virtual const OrtCompressed compressRec(const std::vector<int>& rounds) = 0;
		virtual const Eigen::MatrixXd decompress(const OrtCompressed compr) = 0;
		virtual const double getPRD(const Eigen::MatrixXd& APR) = 0;
		
		const Eigen::MatrixXd* getSignal();
};

#endif
