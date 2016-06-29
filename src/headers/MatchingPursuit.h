#ifndef __MATCHING_PURSUIT_INCLUDED__
#define __MATHCING_PURSUIT_INCLUDED__

#include <functional>
#include <iostream>

#include "NelderMead.h"
#include "Hermite.h"
#include "OrtCompresser.h"
#include "EcgSigPrep.h"

class MatchingPursuit {
	private:
		 OrtFunSys* ort_sys;
		 Compresser* compresser;
		 Optimizer* opter;
		 EcgSigPrep* signal_handler;
		 
		 std::function<double (Coord &)> costfun;
		 
		 void set_costfun(std::function<double (Coord &)> cfun);
		 void get_next_beat();
	public:
		MatchingPursuit(char* REC);
		~MatchingPursuit();
		
		Compressed* CompressBeat(std::vector<int> rounds_deg);
		
		
};

#endif
