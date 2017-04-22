#ifndef __MATCHING_PURSUIT_INCLUDED__
#define __MATHCING_PURSUIT_INCLUDED__

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
#define CN_MATCHING_PURSUIT_IN_ACTION_SIG_STR "/var/www/html/medical/results/in_action/s.csv"
#define CN_MATCHING_PURSUIT_IN_ACTION_APR_STR "/var/www/html/medical/results/in_action/a.csv"

#define CN_MATCHING_PURSUIT_QRS_SIG_STR "/var/www/html/medical/results/qrs/s.csv"
#define CN_MATCHING_PURSUIT_QRS_APR_STR "/var/www/html/medical/results/qrs/a.csv"
           
#define CN_MATCHING_PURSUIT_T_SIG_STR "/var/www/html/medical/results/t/s.csv"
#define CN_MATCHING_PURSUIT_T_APR_STR "/var/www/html/medical/results/t/a.csv"

#define CN_MATHCING_PURSUIT_P_SIG_STR "/var/www/html/medical/results/p/s.csv"
#define CN_MATHCING_PURSUIT_P_APR_STR "/var/www/html/medical/results/p/a.csv"
           
#define CN_MATHCING_PURSUIT_COMBINED_SIG_STR "/var/www/html/medical/results/combined/s.csv"
#define CN_MATHCING_PURSUIT_COMBINED_APR_STR "/var/www/html/medical/results/combined/a.csv"
/* END DEFINES FOR ANIMATION OUTPUT */

/* DEFINES FOR OPTIMIZATION INITIALIZATION */
#define CN_MATCHING_PURSUIT_INIT_SIMPLEX_LOW_DILAT_DB  (double)0.14
#define CN_MATCHING_PURSUIT_INIT_SIMPLEX_MID_DILAT_DB  (double)0.154
#define CN_MATCHING_PURSUIT_INIT_SIMPLEX_HIGH_DILAT_DB (double)0.16

#define CN_MATCHING_PURSUIT_POPULATION_SIZE_INT (unsigned int)3

#define CN_MATCHING_PURSUIT_NELDER_ROUNDS_INT (int)20
#define CN_MATCHING_PURSUIT_NELDER_MAXERR_DB  (double)0.2

/* END DEFINES FOR OPTIMIZATION INITIALIZATION */

/* END DEFINE CONSTANTS FOR MP MODULE */

class MatchingPursuit {
	private:
		 EcgSigPrep* sig_handler;
		 std::map<std::string, std::string> file_dirs;
		 std::function<double (Coord &)> costfun;
		 
		 void set_costfun(std::function<double (Coord &)> cfun);
		 std::vector<Coord> set_optimizer_init_values(Eigen::MatrixXd curr_sig);
	public:
		MatchingPursuit(EcgSigPrep *SH, std::map<std::string, std::string> fdirs);
		MatchingPursuit(EcgSigPrep *SH);
		~MatchingPursuit();
		
		OrtCompressed* CompressBeat(std::vector<int> rounds_deg);
};

#endif
