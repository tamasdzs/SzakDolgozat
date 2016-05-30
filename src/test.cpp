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
	
	Hermite Herm(sig.cols(), 20);
	
	OrtCompresser OC(Herm, 20);
	
	Compressed* p;
	p = OC.compressBeat(sig);
	
	Eigen::MatrixXd apr = OC.decompress( p );
	
	std::cout<<Herm.get_ort_fun_sys()->col(0)<<std::endl;
	
	return 0;
}
