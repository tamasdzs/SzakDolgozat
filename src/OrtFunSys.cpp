#include "OrtFunSys.h"

OrtFunSys::OrtFunSys(int N, int M) {
	rootNum = N;
	degNum = M;
	domain = new Eigen::MatrixXd;
	bigSys = new Eigen::MatrixXd;
	lambda = new Eigen::MatrixXd;
	
	*domain = Eigen::MatrixXd::Zero(1,N);
	*bigSys = Eigen::MatrixXd::Zero(N,N);
	*lambda = Eigen::MatrixXd::Zero(N,N);
}

OrtFunSys::~OrtFunSys() {
	delete domain;
	delete bigSys;
	delete lambda;
}
