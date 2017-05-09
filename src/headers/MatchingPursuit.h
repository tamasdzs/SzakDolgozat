#ifndef __MATCHING_PURSUIT_INCLUDED__
#define __MATHCING_PURSUIT_INCLUDED__

#include <unistd.h>
#include <functional>
#include <iostream>
#include <fstream>
#include <string>
#include <map>

#include "NelderMead.h"
#include "Hermite.h"
#include "OrtCompresser.h"
#include "EcgSigPrep.h"

/* DEFINE CONSTANTS FOR MP MODULE */

/* DEFINES FOR ANIMATION OUTPUT */

#define CN_MATCHING_PURSUIT_PRD_STR "../results/prd/prd.txt"
#define CN_MATCHING_PURSUIT_QS_STR "../results/qs/qs.txt"
#define CN_MATCHING_PURSUIT_CR_STR "../results/cr/cr.txt"

#define CN_MATCHING_PURSUIT_IN_ACTION_SIG_STR "../results/in_action/s.csv"
#define CN_MATCHING_PURSUIT_IN_ACTION_APR_STR "../results/in_action/a.csv"

#define CN_MATCHING_PURSUIT_QRS_SIG_STR "../results/qrs/s.csv"
#define CN_MATCHING_PURSUIT_QRS_APR_STR "../results/qrs/a.csv"
           
#define CN_MATCHING_PURSUIT_T_SIG_STR "../results/t/s.csv"
#define CN_MATCHING_PURSUIT_T_APR_STR "../results/t/a.csv"

#define CN_MATHCING_PURSUIT_P_SIG_STR "../results/p/s.csv"
#define CN_MATHCING_PURSUIT_P_APR_STR "../results/p/a.csv"
           
#define CN_MATHCING_PURSUIT_COMBINED_SIG_STR "../results/combined/s.csv"
#define CN_MATHCING_PURSUIT_COMBINED_APR_STR "../results/combined/a.csv"

const unsigned int CN_SLEEP_FOR_ANIMATION = 20000;

/* END DEFINES FOR ANIMATION OUTPUT */

/* DEFINES FOR OPTIMIZATION INITIALIZATION */
#define CN_MATCHING_PURSUIT_INIT_SIMPLEX_LOW_DILAT_DB  (double)0.14
#define CN_MATCHING_PURSUIT_INIT_SIMPLEX_MID_DILAT_DB  (double)0.154
#define CN_MATCHING_PURSUIT_INIT_SIMPLEX_HIGH_DILAT_DB (double)0.16

#define CN_MATCHING_PURSUIT_POPULATION_SIZE_INT (unsigned int)3

#define CN_MATCHING_PURSUIT_NELDER_ROUNDS_INT (int)30
#define CN_MATCHING_PURSUIT_NELDER_MAXERR_DB  (double)0.2

/* END DEFINES FOR OPTIMIZATION INITIALIZATION */

/* END DEFINE CONSTANTS FOR MP MODULE */

class MatchingPursuit {
	private:
		 EcgSigPrep* sig_handler;
		 std::function<double (Coord &)> costfun;
		 
		 void set_costfun(std::function<double (Coord &)> cfun);
		 std::vector<Coord> set_optimizer_init_values(Eigen::MatrixXd curr_sig);
	public:
		MatchingPursuit(EcgSigPrep *SH);
		~MatchingPursuit();
		
		OrtCompressed* CompressBeat(std::vector<int> rounds_deg, bool animation);
};

#endif
