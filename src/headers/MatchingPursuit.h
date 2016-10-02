#ifndef __MATCHING_PURSUIT_INCLUDED__
#define __MATHCING_PURSUIT_INCLUDED__

#include <functional>
#include <iostream>
#include <fstream>
#include <string>

#include "NelderMead.h"
#include "Hermite.h"
#include "OrtCompresser.h"
#include "EcgSigPrep.h"

class MatchingPursuit {
	private:
		 EcgSigPrep* sig_handler;
		 std::string sig_out;
		 std::string nm_out;
		 std::string apr_out;
		 std::function<double (Coord &)> costfun;
		 
		 void set_costfun(std::function<double (Coord &)> cfun);
	public:
		MatchingPursuit(EcgSigPrep *SH, std::string s, std::string nm, std::string apr);
		MatchingPursuit(EcgSigPrep *SH);
		~MatchingPursuit();
		
		OrtCompressed* CompressBeat(std::vector<int> rounds_deg);
};

#endif
