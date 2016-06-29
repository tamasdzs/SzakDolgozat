#include <iostream>
#include <Eigen/Dense>
#include <typeinfo>
#include <string>
#include <vector>
#include "Hermite.h"
#include "EcgSigPrep.h"
#include "OrtCompresser.h"
#include "NelderMead.h"
#include <math.h>

#include "MatchingPursuit.h"

int main () {
	
	EcgSigPrep signal_handler("103", 2, 950);
	
	Eigen::MatrixXd sig = *signal_handler.getNextSegment();
	
	Hermite Herm(sig.cols());
	
	std::cout<<"HERM INIT DONE"<<std::endl;
	
	OrtCompresser OC(Herm, 20);
	
	Compressed* p;
	
	// sig = signal_handler.setDilatTrans(1.0, 0.0, Herm.get_ort_fun_roots(), sig); 
	
	p = OC.compressBeat(sig);
	
	Eigen::MatrixXd apr = OC.decompress( p );
	
	std::cout<<"apr:"<<std::endl;
	std::cout<<apr<<std::endl;
	std::cout<<"****************"<<std::endl;
	
	char c;
	std::cin>>c;
	
	std::cout<<"sig:"<<std::endl;
	std::cout<<sig.transpose()<<std::endl;
	std::cout<<"****************"<<std::endl;
	
	return 0;
}
