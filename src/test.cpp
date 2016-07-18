#include <iostream>
#include <Eigen/Dense>
#include <typeinfo>
#include <string>
#include <vector>
#include "Hermite.h"
#include "EcgSigPrep.h"
#include "OrtCompresser.h"
#include "NelderMead.h"
#include "MatchingPursuit.h"
#include <math.h>

int main () {
	//COMPRESS WITHOUT MP TEST
	
	EcgSigPrep signal_handler("103", 2, 950);
	
	Eigen::MatrixXd sig = *signal_handler.getNextSegment();
	Hermite Herm(sig.cols());
	std::cout<<"HERM INIT DONE"<<std::endl;
	OrtCompresser OC(Herm, 50);
	std::cout<<"OC INIT DONE"<<std::endl;
	OrtCompressed* p = new OrtCompressed;
	
	
	Eigen::MatrixXd osig = sig;
	sig = signal_handler.setDilatTrans(0.155274, 50.5818, Herm.get_ort_fun_roots(), sig); 
	
	std::cout<<"SIG SETUP DONE"<<std::endl;
	
	std::cout<<osig.transpose()<<std::endl;
	std::cout<<" "<<std::endl;
	
	p = OC.compressBeat(sig);
	
	p->trans = 50.5818;
	p->dilat = 0.155274;
	
	Eigen::MatrixXd apr = OC.decompress( p );
	
	//std::cout<<apr.transpose()<<std::endl;
	
	delete p;
	
	//MP TEST
	/*
	EcgSigPrep* signal_handler = new EcgSigPrep("103", 2, 950);
	
	MatchingPursuit MP(signal_handler);
	
	std::vector<int> rounds_deg;
	rounds_deg.push_back(25);
	rounds_deg.push_back(10);
	rounds_deg.push_back(7);
	
	MP.CompressBeat(rounds_deg);
	
	delete signal_handler;
	*/
	return 0;
}
