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
	//Orthogonality TEST
	/*
	Hermite Herm(200);
	Eigen::MatrixXd sig = Herm.get_ort_fun_sys()->col(5);
	OrtCompresser OC(Herm, 20);
	
	Eigen::MatrixXd Herm_sys;
	Herm_sys.resize(Herm.get_ort_fun_sys()->rows(), 20);
			
	for ( int i = 0; i < 20; ++i ) {
		Herm_sys.col(i) = Herm.get_ort_fun_sys()->col(i);
	}
	
	std::cout<<(Herm_sys.transpose()*(Herm.get_ort_fun_lamb()->inverse()*sig))<<std::endl;
	*/
	
///////////////////////////////////////////////////////////////////////////////////////////	
	
	//COMPRESS WITHOUT MP TEST
	
/*
	EcgSigPrep signal_handler("103", 2, 950);
	Eigen::MatrixXd sig = *signal_handler.getNextSegment();
	
	Hermite Herm(sig.cols());
	
	std::cout<<"HERM INIT DONE"<<std::endl;
	OrtCompresser OC(Herm, 7);
	std::cout<<"OC INIT DONE"<<std::endl;
	OrtCompressed* p = new OrtCompressed;
	
	Eigen::MatrixXd osig = sig;
	sig = signal_handler.setDilatTrans(0.154, 155.0, Herm.get_ort_fun_roots(), sig); 
	
	std::cout<<"SIG SETUP DONE"<<std::endl;
	
	std::cout<<osig.transpose()<<std::endl;
	std::cout<<" "<<std::endl;
	
	p = OC.compressBeat(sig);
	
	p->trans = 155.0;
	p->dilat = 0.154;
	
	Eigen::MatrixXd apr = OC.decompress( p );
	
	std::cout<<apr.transpose()<<std::endl;
	
	
	osig = osig - apr;
	sig = osig;
	
	std::cout<<"*****ROUND 2:*****"<<std::endl;
	std::cout<<osig.transpose()<<std::endl<<"********"<<std::endl;
	
	sig = signal_handler.setDilatTrans(0.154, 252.0, Herm.get_ort_fun_roots(), osig);
	
	p = OC.compressBeat( sig );
	p->trans = 252.0;
	p->dilat = 0.154;
	
	apr = OC.decompress( p );
	
	std::cout<<apr.transpose()<<std::endl;
	
	std::cout<<"PRD: "<<OC.getPRD( p, osig)<<std::endl;
	
	delete p;
*/	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////	
	
	//MP TEST
	EcgSigPrep* signal_handler = new EcgSigPrep("103", 2, 950);
	
	MatchingPursuit MP(signal_handler, "/var/www/html/medical/results/s.csv", "/var/www/html/medical/results/a.csv", "/var/www/html/medical/results/a.csv");
	
	std::vector<int> rounds_deg;
	rounds_deg.push_back(7);
	rounds_deg.push_back(6);
	rounds_deg.push_back(2);
	
	MP.CompressBeat(rounds_deg);
	
	delete signal_handler;
	
	return 0;
}
