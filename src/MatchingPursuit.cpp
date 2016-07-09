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
			[&sig, &OC, &Herm, this ] (Coord & pos) -> double {
				double dilat = pos[0];
				double trans = pos[1];
				Eigen::MatrixXd s = sig;
				s = sig_handler->setDilatTrans( dilat, trans, Herm.get_ort_fun_roots(), s );
				OrtCompressed* a_compression = OC.compressBeat( s );
				return OC.getPRD( a_compression, s ); 
			}
		);
		
		std::cout<<"costfun set \n";
		
		//2. NelderMead (vagy mas) -->o legyen jo -> harmadik kor
		
		//Initial values for NM optimization
		std::vector<Coord> pop;
		pop.resize(3);
		pop[0][0] = 1; pop[0][1] = sig.cols()/2.0;
		pop[1][0] = 0.5; pop[1][1] = 100.0;
		pop[2][0] = 1.0/4.5; 
		
		Eigen::MatrixXd::Index maxRow;
		Eigen::MatrixXd::Index maxCol; 
		
		Eigen::MatrixXd absSig = sig;
		for( unsigned int i = 0; i < absSig.cols(); ++i ) {
				absSig(0, i) = abs(absSig(0, i));
		}
		
		absSig.maxCoeff(&maxRow, &maxCol);
		
		pop[2][2] = (double)(maxCol);
		
		std::cout<<"Starting positions for population initaliazed \n";
		
		
		Coord optimized_coords;
		
		NelderMead opter(50, 0.2, pop);
		
		std::cout<<"Nelder Mead optimizer init done \n";
		
		optimized_coords = opter.Optimize(costfun);
		
		std::cout<<"Optimization done \n";
		std::cout<<"D: "<<optimized_coords[0]<<" T: "<<optimized_coords[1]<<std::endl;
		
		sig = sig_handler->setDilatTrans(optimized_coords[0], optimized_coords[1], Herm.get_ort_fun_roots(), sig);
		
		char c; std::cin>>c;
		
		std::cout<<"signal set up \n";
		
		//3. Csinald meg a jokkal
		
		p = OC.compressBeat(sig);
		p->dilat = optimized_coords[0];
		p->trans = optimized_coords[1];
		std::cout<<"Final compression done \n";
		
		Eigen::MatrixXd apr = OC.decompress( p );
		
		std::cout<<"Apprixmation acquired \n";
		
		std::cout<<"sig: "<<std::endl;
		std::cout<<sig.transpose()<<std::endl;
		std::cout<<"***************"<<std::endl;
		
		std::cin>>c;
		
		std::cout<<"apr:"<<std::endl;
		std::cout<<apr.transpose()<<std::endl;
		std::cout<<"****************"<<std::endl;
		
		std::cin>>c;
		
		sig = sig - apr;
		ret = p;
		delete p;
	}
	
	return ret;
}

