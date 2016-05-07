#include <iostream>
#include <Eigen/Dense>
#include <typeinfo>
#include <string>
#include <vector>
#include "Hermite.h"
#include "EcgSigPrep.h"
#include "OrtCompresser.h"

int main () {
	OrtCompresser OC("103", 2, 900);
	Hermite H(OC.getSignal()->cols());
	Eigen::MatrixXd Hsys = H.get_ort_fun_sys()->block(0, 0, OC.getSignal()->cols(), 20);
	 
    OrtCompressed result;
    
    std::vector<int> rounds;
    rounds.push_back(7);
    rounds.push_back(10);
    rounds.push_back(17);
    
    result = OC.compressBeat(rounds); 
     
	const Eigen::MatrixXd res = OC.decompress(result);
	std::cout<<res.transpose()<<std::endl;
	
	return 0;
}
