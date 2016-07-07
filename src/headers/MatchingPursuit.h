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
		 OrtFunSys ort_sys;
		 Optimizer opter;
		 EcgSigPrep signal_handler;
		 
		 std::function<double (Coord &)> costfun;
		 
		 void set_costfun(std::function<double (Coord &)> cfun);
	public:
		MatchingPursuit(char* REC, OrtFunSys& OS, EcgSigPrep &SH);
		~MatchingPursuit();
		
		Compressed* CompressBeat(std::vector<int> rounds_deg);
};

#endif
