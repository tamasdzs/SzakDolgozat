#include <iostream>
#include <Eigen/Dense>
#include <typeinfo>
#include <string>
#include <vector>
#include <map>
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

	// MAP helyett define
	std::map<std::string, std::string> files_dirs;
	files_dirs.insert( std::pair<std::string, std::string>("in_action_sig", "/var/www/html/medical/results/in_action/s.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("in_action_apr", "/var/www/html/medical/results/in_action/a.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("QRS_sig", "/var/www/html/medical/results/qrs/s.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("QRS_apr", "/var/www/html/medical/results/qrs/a.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("T_sig", "/var/www/html/medical/results/t/s.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("T_apr", "/var/www/html/medical/results/t/a.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("P_sig", "/var/www/html/medical/results/p/s.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("P_apr", "/var/www/html/medical/results/p/a.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("combined_sig", "/var/www/html/medical/results/combined/s.csv") );
	files_dirs.insert( std::pair<std::string, std::string>("combined_apr", "/var/www/html/medical/results/combined/a.csv") );
	
	MatchingPursuit MP(signal_handler, files_dirs);
	
	std::vector<int> rounds_deg;
	rounds_deg.push_back(7);
	rounds_deg.push_back(6);
	rounds_deg.push_back(2);
	
	MP.CompressBeat(rounds_deg);
	
	delete signal_handler;
	
	return 0;
}
