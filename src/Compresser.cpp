#include "Compresser.h"
#include <iostream>

Compresser::Compresser(char* RECORD, const int n_of_leads, const int n_of_samples) {
	signal_handler = new EcgSigPrep(RECORD, n_of_leads, n_of_samples);
	std::cout<<"ECGCOMPRESSER: signal_handler initalized"<<std::endl;
}


Compresser::~Compresser() {
	delete signal_handler;
}

const Eigen::MatrixXd* Compresser::getSignal() {
	return signal_handler->getSignal();
}


