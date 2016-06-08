#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit(char* REC) {
	 signal_handler = new EcgSigPrep(REC, 2, 950);
	 ort_sys = new Hermite(signal_handler->get_ort_fun_sys()->rows);
}

MatchingPursuit::~MatchingPursuit() {
	delete signal_handler;
	delete ort_sys;
	delete compresser;
	delete opter;
}

void MatchingPursuit::set_costfun(std::function<double (Coord &)>) {
	costfun = cfun;
}

OrtCompressed MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	
	OrtCompressed* next;
	OrtCompressed* curr;
	OrtCompressed* ret;
	Eigen::MatrixXd sig = signal_handler->getSignal();
	
	for ( unsigned int i = 0; i < rounds_deg.size(); ++i ) {
		compresser = new OrtCompresser(sig.cols(), rounds_deg[i]);
		
		//OPTIMIZATION HERE
		
		if ( i == 0 ) {
			
			//set pointers
			next = compreser->compressBeat(sig);
			curr = next;
			curr->next = nullptr;
			ret = curr;
		} else {
			
			//set pointers
			next = compreser->compressBeat(sig);
			curr->next = next;
			curr = next;
			curr->next = nullptr; 
		}
		
		Eigen::MatrixXd apr = compresser->decompress(curr);
		sig = sig - apr;
	}
	
	return ret;
}

void MatchingPursuit::get_next_beat() {
	signal_handler->getNextSegment();
}
