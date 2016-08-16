#include "MatchingPursuit.h"

MatchingPursuit::MatchingPursuit( EcgSigPrep *SH): sig_handler(SH) {
	
}

MatchingPursuit::~MatchingPursuit() {
	
}

void MatchingPursuit::set_costfun(std::function<double (Coord &)> cfun) {
	costfun = cfun;
}

OrtCompressed* MatchingPursuit::CompressBeat(std::vector<int> rounds_deg) {
	OrtCompressed* ret;
	
	Eigen::MatrixXd sig = *(sig_handler->getNextSegment());
	Eigen::MatrixXd osig = sig;
	Hermite Herm(sig.cols());
	std::cout<<"HERM INIT DONE"<<std::endl;
	
	
	for (unsigned int i = 0; i < rounds_deg.size(); ++i) {
		
		std::cout<<"MP HERE, round: "<<i<<std::endl;
		
		OrtCompresser OC(Herm, rounds_deg[i]);
		
		std::cout<<"OC init done \n";
		
		OrtCompressed* p = new OrtCompressed;
		
		//OPTIMIZATION
		// 1. Set anonymus function
		
		set_costfun( 
			[&osig, &OC, &Herm, this ] (Coord & pos) -> double {
				double dilat = pos[0];
				double trans = pos[1];
				
				std::cout<<"COSTFUN: dilat: "<<dilat<<" trans: "<<trans<<std::endl;
				
				Eigen::MatrixXd s = osig;
				s = sig_handler->setDilatTrans( dilat, trans, Herm.get_ort_fun_roots(), s );
				OrtCompressed* a_compression = OC.compressBeat( s );
				a_compression->dilat = dilat; a_compression->trans = trans;
				double ret = OC.getPRD( a_compression, osig ); 
				delete a_compression;
				std::cout<<"COSTFUN: RET VAL: "<<ret<<std::endl;
				return ret;
			}
		);
		
		std::cout<<"costfun set \n";
		
		//2. NelderMead (vagy mas) -->o legyen jo -> harmadik kor
		
		//Initial values for NM optimization
		std::vector<Coord> pop;
		pop.resize(3);
	
		pop[0][0] = 0.16; 
		pop[1][0] = 0.14; 
		pop[2][0] = 0.154; 
		
		Eigen::MatrixXd::Index maxRow;
		Eigen::MatrixXd::Index maxCol; 
		
		Eigen::MatrixXd absSig = osig;
		for( unsigned int i = 0; i < absSig.cols(); ++i ) {
				absSig(0, i) = fabs(absSig(0, i));
		}
		
		absSig.maxCoeff(&maxRow, &maxCol);
		
		pop[0][1] = maxCol - 5;
		pop[1][1] = maxCol + 5;
		pop[2][1] = (double)(maxCol);
		
		
		std::cout<<"MAX COL NOW IS: "<<maxCol<<std::endl;
		
		std::cout<<"Starting positions for population initaliazed \n";
		
		
		Coord optimized_coords;
		
		NelderMead opter(20, 0.2, pop);
		
		std::cout<<"Nelder Mead optimizer init done \n";
		
		optimized_coords = opter.Optimize(costfun);
		
		std::cout<<"Optimization done \n";
		std::cout<<"D: "<<optimized_coords[0]<<" T: "<<optimized_coords[1]<<std::endl;
		
		sig = sig_handler->setDilatTrans(optimized_coords[0], optimized_coords[1], Herm.get_ort_fun_roots(), sig);
		
		char c; std::cin>>c;
		
		std::cout<<"signal set up \n";
		
		
		p = OC.compressBeat(sig);
		p->dilat = optimized_coords[0];
		p->trans = optimized_coords[1];
		std::cout<<"Final compression done \n";
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		std::cout<<"Apprixmation acquired \n";
		
		std::cout<<"sig: "<<std::endl;
		std::cout<<osig.transpose()<<std::endl;
		std::cout<<"***************"<<std::endl;
		
		std::cin>>c;
		
		std::cout<<"apr:"<<std::endl;
		std::cout<<apr.transpose()<<std::endl;
		std::cout<<"****************"<<std::endl;
		
		std::cin>>c;
		
		osig = osig - apr;
		ret = p;
		delete p;
		sig = osig;
	}
	
	return ret;
}

