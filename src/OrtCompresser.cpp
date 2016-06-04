#include "OrtCompresser.h"
#include <iostream>
#include <math.h>

OrtCompresser::OrtCompresser(OrtFunSys& H, const int dim) {
			big_ort_sys = &H;
			
			Herm_sys = new Eigen::MatrixXd;
			Herm_sys->resize(H.get_ort_fun_sys()->rows(), dim);
			
			for ( int i = 0; i < dim; ++i ) {
				Herm_sys->col(i) = H.get_ort_fun_sys()->col(i);
			}
			
}

OrtCompresser::~OrtCompresser() {
	delete Herm_sys;
}

Compressed* OrtCompresser::compressBeat( Eigen::MatrixXd& signal ) {
	OrtCompressed *ret = new OrtCompressed;
	ret->compressed_sig = (Herm_sys->transpose()*(big_ort_sys->get_ort_fun_lamb()->inverse()*signal.transpose()));
	return ret;
}

const Eigen::MatrixXd OrtCompresser::decompress(const Compressed* compr) {
	return compr->compressed_sig.transpose() * Herm_sys->transpose();
}

double OrtCompresser::get_err( Eigen::MatrixXd& signal ) {
	//TODO: local variables to speed up the process
	Eigen::MatrixXd fourier_coeffs = (Herm_sys->transpose()*(big_ort_sys->get_ort_fun_lamb()->inverse()*signal.transpose()));
	Eigen::MatrixXd APR = fourier_coeffs.transpose() * Herm_sys->transpose();
	return ((signal - APR).norm() / (signal.array() - signal.mean()).matrix().norm()); 
}


