#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit(char* REC) {
	 signal_handler = new EcgSigPrep("103", 2, 950);
	 ort_sys = new Hermite(signal_handler->getSignal()->cols());
	 //std::cout<<signal_handler->getSignal()->cols()<<std::endl;
	 compresser = nullptr;
	 opter = nullptr;
	 
}

MatchingPursuit::~MatchingPursuit() {
	if ( signal_handler != nullptr ) delete signal_handler;
	if ( ort_sys != nullptr )delete ort_sys;
	if ( compresser != nullptr ) delete compresser;
	if ( opter != nullptr ) delete opter;
}

void MatchingPursuit::set_costfun(std::function<double (Coord &)> cfun) {
	costfun = cfun;
}

Compressed* MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	Compressed* ret;
	
	EcgSigPrep sig_handler("103", 2, 950);
	Eigen::MatrixXd sig = *sig_handler.getNextSegment();
	Hermite Herm(sig.cols());
	std::cout<<"HERM INIT DONE"<<std::endl;
	
	
	for (int i = 0; i < 3; ++i) {
		
		OrtCompresser OC(Herm, 50);
		
		Compressed* p;
		
		p = OC.compressBeat(sig);
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		std::cout<<"sig:"<<std::endl;
		std::cout<<sig.transpose()<<std::endl;
		std::cout<<"***************"<<std::endl;
		
		char c; std::cin>>c;
		
		std::cout<<"apr:"<<std::endl;
		std::cout<<apr.transpose()<<std::endl;
		std::cout<<"****************"<<std::endl;
		
		std::cin>>c;
		
		sig = sig - apr;
	
	}
	
	return ret;
}

void MatchingPursuit::get_next_beat() {
	signal_handler->getNextSegment();
}
