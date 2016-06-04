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
	
	Eigen::MatrixXd sig = *signal_handler.getNextSegment();
	
	Hermite Herm(sig.cols());

	//Eigen::MatrixXd sig = Herm.get_ort_fun_sys()->col(10).transpose();
	
	OrtCompresser OC(Herm, 20);
	
	Compressed* p;
	p = OC.compressBeat(sig);
	
	Eigen::MatrixXd apr = OC.decompress( p );
	
	std::cout<<"apr:"<<std::endl;
	std::cout<<apr.transpose()<<std::endl;
	std::cout<<"****************"<<std::endl;
	
	
	
	
	return 0;
}
