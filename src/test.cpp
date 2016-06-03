#include <iostream>
#include <Eigen/Dense>
#include <typeinfo>
#include <string>
#include <vector>
#include "Hermite.h"
#include "EcgSigPrep.h"
#include "OrtCompresser.h"
#include "NelderMead.h"

int main () {
	EcgSigPrep signal_handler("103", 2, 950);
	
	//Eigen::MatrixXd sig = *signal_handler.getNextSegment();
	
	Hermite Herm(150, 20);

	Eigen::MatrixXd sig = Herm.get_ort_fun_sys()->col(10).transpose();
	
	OrtCompresser OC(Herm, 20);
	
	Compressed* p;
	p = OC.compressBeat(sig);
	
	
	std::cout<<"HERM DIM:"<<std::endl;
	std::cout<<Herm.get_ort_fun_sys()->rows()<<" "<<Herm.get_ort_fun_sys()->cols()<<std::endl;
	std::cout<<"****************"<<std::endl;
	
	
	
	std::cout<<"FOURIER COEFFS:"<<std::endl;
	std::cout<<p->compressed_sig<<std::endl;
	std::cout<<"****************"<<std::endl;
	
	Eigen::MatrixXd apr = OC.decompress( p );

	
	return 0;
}
