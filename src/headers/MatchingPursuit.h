#infndef __MATCHING_PURSUIT_INCLUDED__
#define __MATHCING_PURSUIT_INCLUDED__

#include <functional>
#include <iostream>

#include "NelderMead.h"
#include "Hermite.h"
#include "OrtCompresser.h"
#include "EcgSigPrep.h"

class MatchinPursuit {
	private:
		 EcgSigPrep* sig_handler;
		 OrtFunSys* ort_sys;
		 Compresser* compresser;
		 Optimizer* opter;
		 
		 std::function<double (Coord &)> costfun;
		 
		 void set_costfun(std::function<double (Coord &)> cfun);
		 void get_next_beat();
	public:
		MatchingPursuit();
		~MatchingPursuit();
		
		OrtCompressed CompressBeat();
		
		
};

#endif
