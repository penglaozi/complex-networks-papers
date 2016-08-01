/*******************************************************************************
BoundingDiameters v0.4
@author Frank Takes - ftakes@liacs.nl
@website http://www.liacs.nl/~ftakes/diameter
**************** consult the README.txt file before using *********************/

#include "graph.h"

// all workflow should be arranged in the main()-function below
int main(int argc, char ** argv) {
	
	// check if we have sufficient arguments
 	if(argc < 2) {
		cerr << "\nCorrect usage: ./bd [file] [optional measure = d/r/p/c/e]\n" 
			 << " d = diameter (default)\n r = radius\n p = periphery size\n"
			 << " c = center size\n e = all eccentricities\n" 
			 << "(multiple measures can be computed by concatenating options)\n" << endl;
		return 1;
	}

	// create empty Graph object
	static Graph G;
	
	// load & immediately undirect a complete graph from file
	//if(!G.loadUndirected(argv[1])) {
	//	cerr << "File " << argv[1] << " not found." << endl;
	//	return 1;
	//}
	
	// load a complete graph from file, and then 	make it undirected
	// (uses more RAM than loadUndirected but is much faster for larger graphs)
	if(!G.load(argv[1])) {
		cerr << "File " << argv[1] << " not found." << endl;
		return 1;
	}
	G.makeUndirected(); // not needed if loadUndirected() is used
		
	// compute WCC and show some stats
	G.calcWCC();	
	G.stats();
	
	// print filename and number of nodes
	cerr << "\nFilename and number of nodes: "; 	
	cout << argv[1] << "\t" << G.getn();
	cerr << endl << endl;
	
	// keep track of clock time
	int begin = clock();
	
	// compute either one or multiple of the five measures
	if(argc <= 2)
		cout << "\t" << G.diameterBD(); 
	else {
		int i = 0;
		while(argv[2][i] != '\0') { // process multiple measures if needed
			if(argc > 2 && argv[2][i] == 'e') 
				G.eccentricitiesBD();
			else if(argc > 2 && argv[2][i]  == 'r') 
				cout << "\t" << G.radiusBD();
			else if(argc > 2 && argv[2][i]  == 'c') 
				cout << "\t" << G.centerBD(); 	
			else if(argc > 2 && argv[2][i]  == 'p') 
				cout << "\t" << G.peripheryBD(); 								 			
			else if(argc > 2 && argv[2][i]  == 'd') 
				cout << "\t" << G.diameterBD(); 
			
			i++;
			cerr << endl << endl;				
		} // while
	} // else	
	
	cout << endl;
	
	// display passed clock time
	cerr << endl << "Running time: " << 
	((double)(clock()-begin))/((double)CLOCKS_PER_SEC) << " sec" << endl;
	
	return 0;
}

