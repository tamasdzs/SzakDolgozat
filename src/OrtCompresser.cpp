#include "OrtCompresser.h"
#include <iostream>
#include <math.h>

OrtCompresser::OrtCompresser(char* RECORD, const int n_of_leads, const int n_of_samples): 
					Compresser(RECORD, n_of_leads, n_of_samples) {
			ort_sys = new Hermite(getSignal()->cols());
			std::cout<<"ECGCOMPRESSER: Orthonormal Hermite System initalized"<<std::endl;
}

OrtCompresser::~OrtCompresser() {
	delete ort_sys;
}

Eigen::MatrixXd OrtCompresser::calcAprx(const Eigen::MatrixXd& Coeffs, const Eigen::MatrixXd& H) {
	 return (Coeffs.transpose() * H.transpose());
}

Eigen::MatrixXd OrtCompresser::calcFourier(const Eigen::MatrixXd& H, Eigen::MatrixXd& sig, const double lambda, const double trans) {
	
	signal_handler->setDilatTrans(lambda, trans, ort_sys->get_ort_fun_roots(), sig);
	return (H.transpose()*(ort_sys->get_ort_fun_lamb()->inverse()*sig.transpose()));
}

const double OrtCompresser::getPRD(const Eigen::MatrixXd& APR) {
	const Eigen::MatrixXd* sig = signal_handler->getSignal();
	return (((*sig) - APR).norm() / ((*sig).array() - (*sig).mean()).matrix().norm());
}

const double OrtCompresser::getErr(const Eigen::MatrixXd &Coeffs) {
		return -1.0 * Coeffs.sum();
}

OrtCompressed OrtCompresser::compressBeat(const std::vector<int>& rounds) {
	
	const Eigen::MatrixXd* BH = ort_sys->get_ort_fun_sys();
	Eigen::MatrixXd sig = *(getSignal());
	
	double lambda = 1;
	double trans = 0;
	
	OrtCompressed result;
	Eigen::MatrixXd H;

	for(unsigned int i = 0; i < rounds.size(); ++i) {
		H = BH->block(0, 0, BH->rows(), rounds[i]);

		//Calculate best dilat/trans here
		
		
		
		result.FCOEFFS.push_back(calcFourier(H, sig, lambda, trans));
		
		result.dilat = 1;
		result.trans = 0;
		
		sig = sig - calcAprx(result.FCOEFFS[i], H);	
	}
	
	result.sig_first_val = signal_handler->getSigFirstVal();
	result.sig_last_val = signal_handler->getSigLastVal();
	result.sig_max_val = signal_handler->getSigMaxVal();
	
	return result;
}

const Eigen::MatrixXd OrtCompresser::decompress(const OrtCompressed compr) {
	Eigen::MatrixXd result(1, signal_handler->getSignal()->cols()); 
	result = Eigen::MatrixXd::Zero(1, signal_handler->getSignal()->cols());
	
	for(unsigned int i = 0; i < compr.FCOEFFS.size(); ++i) {
		Eigen::MatrixXd H = ort_sys->get_ort_fun_sys()->block(0, 0, ort_sys->get_ort_fun_sys()->rows(), compr.FCOEFFS[i].rows());
		result = result + calcAprx(compr.FCOEFFS[i], H);
	}
	
	return result;
}
