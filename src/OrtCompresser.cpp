#include "OrtCompresser.h"
#include <iostream>
#include <math.h>

OrtCompresser::OrtCompresser(OrtFunSys& H, const int dim) {
			n = dim;
			ort_sys = &H;
}

OrtCompresser::~OrtCompresser() {
	
}

Compressed* OrtCompresser::compressBeat( Eigen::MatrixXd& signal ) {
	OrtCompressed *ret = new OrtCompressed;
	ret->compressed_sig = (ort_sys->get_ort_fun_sys()->transpose()*(ort_sys->get_ort_fun_lamb()->inverse()*signal.transpose()));
	return ret;
}

const Eigen::MatrixXd OrtCompresser::decompress(const Compressed* compr) {
	return compr->compressed_sig.transpose() * ort_sys->get_ort_fun_sys()->transpose();
}

double OrtCompresser::get_err( Eigen::MatrixXd& signal ) {
	//TODO: local variables to speed up the process
	Eigen::MatrixXd fourier_coeffs = (ort_sys->get_ort_fun_sys()->transpose()*(ort_sys->get_ort_fun_lamb()->inverse()*signal.transpose()));
	Eigen::MatrixXd APR = fourier_coeffs.transpose() * ort_sys->get_ort_fun_sys()->transpose();
	return ((signal - APR).norm() / (signal.array() - signal.mean()).matrix().norm()); 
}


