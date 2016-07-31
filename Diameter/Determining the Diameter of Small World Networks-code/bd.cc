/*******************************************************************************
BoundingDiameters v0.4
@author Frank Takes - ftakes@liacs.nl
@website http://www.liacs.nl/~ftakes/diameter
**************** consult the README.txt file before using *********************/

#include "graph.h"

// Pruning strategy
int Graph::pruning() {
	int z, count = 0, prunee = -1;
	for(int i=0; i<n; i++) {
		pruned[i] = -1; // -1 indicates a node is not pruned by any other node
	}

	// pruned[i] is going to contain the node number that i has identical ecc to
	for(int i=0; i<n; i++) {
		if(!inLargestWCC(i))
			continue;
		
		z = E[i].size();
		prunee = -1;
		
		for(int j=0; j<z; j++) {
			if(inDeg[E[i][j]] == 1 && pruned[E[i][j]] == -1) {
				if(prunee == -1) { // prune all but this one
					prunee = E[i][j]; 
				}
				else {
					pruned[E[i][j]] = prunee; // [0...n] indicates that the node was pruned as it is identical to prunee
					count++;		
					pruned[prunee] = -2; // -2 indicates that its neighbors have been pruned			
				}
			}
		}
	}

	cerr << "Pruning cleared a total of " << count << " nodes." << endl << endl;			
	return count;
} // pruning

// Compute the graph's diameter using BoundingDiameters
int Graph::diameterBD() {
	const bool PRUNE = true;
	return extremaBounding(1, PRUNE);
} // diameterBD

// Compute the graph's radius using BoundingDiameters
int Graph::radiusBD() {
	const bool PRUNE = true;
	return extremaBounding(2, PRUNE);
} // radiusBD

// Get the eccentricities of each of the nodes in the graph
int * Graph::eccentricitiesBD() {
	const bool PRUNE = true;
	extremaBounding(3, PRUNE);
	int * eccs = ecc_lower;	
	// count (and optionally print) eccentricity values to form the distribution
	memset(d, 0, sizeof(d));
	for(int i=0; i<n; i++) {
		d[ecc_lower[i]]++;
		if(inLargestWCC(i)) {
//			cout << E[i].size() << "\t" << ecc_lower[i] << endl; // degree/ecc
			cout << revMapNode(i) << "\t" << ecc_lower[i] << endl; // id/ecc
		}
	}
	cerr << endl;
	// print eccentricity distribution
	double total = 0, count = 0;
	for(int i=1; i<n; i++) 
		if(d[i] > 0) {
			cerr << i << "\t" << d[i] << endl;	// cout if ecc result matters
			total += (d[i]*i);
			count += d[i];
		}
	cerr << "Average: " << total/count << endl;
	return eccs;
} // eccentricitiesBD

// Compute the graph's periphery using BoundingDiameters
int Graph::peripheryBD() {
	const bool PRUNE = true;
	return extremaBounding(4, PRUNE);
} // peripheryBD

// Compute the graph's center using BoundingDiameters
int Graph::centerBD() {
	const bool PRUNE = true;
	return extremaBounding(5, PRUNE);
} // centerBD

// Compuate extreme distance values using a Bounding technique
int Graph::extremaBounding(const int TYPE = 1, const int PRUNE = false) {
	// compute wcc if this wasnt done yet
	if(!doneWCC)
		calcWCC();
	
	// initialize some values
	int it = 0, current_ecc, current = -1, // n-1 for random
		minupper = -2, maxupper = -1, minlower = -4, maxlower = -3,
		minlowernode = -1, maxuppernode = -1, 
		candidates = WCCNodes[largestWCC];
		
	for(int i=0; i<n; i++) {
		ecc_lower[i] = 0;
		ecc_upper[i] = WCCNodes[largestWCC];
		candidate[i] = true;
	}
	
	// set to false in first iteration so that at iteration 2, we take the highest upper bound
	bool high = true;
		
	// perform pruning
	if(PRUNE)
		candidates -= pruning();
	
	// start the main loop
	while(candidates > 0) {
		++it;
		
		// select the next node to be investigated
		
		// select a random node (slower, serves as baseline)
		/*do {
			current = rand() % n;
		} while(!candidate[current] || !inLargestWCC(current) || pruned[current] >= 0);
		*/
		
		//selectFrom(); // this function has been unrolled here
		high = !high;	
		if(current == -1) { // select node with highest degree
			current = 0;
			for(int i=1; i<n; i++) {
				if(d[i] == -1 || !inLargestWCC(i) || pruned[i] >= 0)
					continue;
				if(E[i].size() > E[current].size()) {
					current = i;
				}
			} // for
		} // if
		else if(high) // select node with highest upper bound
			current = maxuppernode;
		else // select node with lowest lower bound
			current = minlowernode;
		
		// determine the eccentricity of the current node
		current_ecc = eccentricity(current);

		// output some status info (1)			
		cerr << setw(3) << it 
		     << ". Current: " << setw(8) << current 
		     << " (" << ecc_lower[current] << "/" 
		     << ecc_upper[current] << ") -> ";
		
		// initialize min/max values
		minlower = WCCNodes[largestWCC];
		maxlower = 0;
		minupper = WCCNodes[largestWCC];
		maxupper = 0;
		maxuppernode = -1;
		minlowernode = -1;
		
		// update bounds
		for(int i=0; i<n; i++) {
			if(d[i] == -1 || !inLargestWCC(i) || pruned[i] >= 0)
				continue;

			// update eccentricity bounds
			ecc_lower[i] = max(ecc_lower[i], max(d[i], current_ecc - d[i]));
			ecc_upper[i] = min(ecc_upper[i], current_ecc + d[i]);	
			
			// update min/max values of lower and upper bounds
			minlower = min(ecc_lower[i], minlower);
			minupper = min(ecc_upper[i], minupper);
			maxlower = max(ecc_lower[i], maxlower);
			maxupper = max(ecc_upper[i], maxupper); 
		} 
		
		// update candidate set
		for(int i=0; i<n; i++) {
			if(!candidate[i] || d[i] == -1 || !inLargestWCC(i) || pruned[i] >= 0)
				continue; 
		
			// disregard nodes that can no longer contribute
			if(candidate[i] && (
			  (ecc_lower[i] == ecc_upper[i]) || (  
			     (TYPE == 1 && ecc_upper[i] <= maxlower &&  ecc_lower[i]*2 >= maxupper)	// diameter
			  || (TYPE == 2 && ecc_lower[i] >= minupper && (ecc_upper[i]+1)/2 <= minlower)// radius
			  || (TYPE == 4 && ecc_upper[i] < maxlower &&  ((maxlower == maxupper) || (ecc_lower[i]*2 > maxupper)))	// periphery
			  || (TYPE == 5 && ecc_lower[i] > minupper &&  ((minlower == minupper) || ((ecc_upper[i]+1)/2 < minlower)))  // center
			  || (TYPE == 3 && ecc_lower[i] == ecc_upper[i]) 			// eccentricity distribution			
			  )))	{
				candidate[i] = false;
				candidates--;	
			}
			
			// updating maxuppernode and minlowernode for selection in next round
			if(candidate[i]) {
				if(minlowernode == -1)
					minlowernode = i; 
				else if (ecc_lower[i] == ecc_lower[minlowernode] && E[i].size() > E[minlowernode].size())
					minlowernode = i;
				else if(ecc_lower[i] < ecc_lower[minlowernode]) 
					minlowernode = i;						
				if(maxuppernode == -1) 
					maxuppernode = i;			
				else if(ecc_upper[i] == ecc_upper[maxuppernode]	&& E[i].size() > E[maxuppernode].size())
					maxuppernode = i;								
				else if(ecc_upper[i] > ecc_upper[maxuppernode]) 
					maxuppernode = i;			
			}
		}
		
		// output some status info (2)
		cerr << setw(3) << current_ecc << " - Bounds range: min=" 
			 << minlower << "/" << minupper << " max=" << maxlower << "/" << maxupper
			 << " - Candidates: " << candidates << endl;
	}
	
	// display number of iterations
	cerr << "\nIterations: "; 
	cout << "\t" << it;
	cerr << "\nMeasure value: "; 

	// return the diameter
	if(TYPE == 1)
		return maxlower;	

	// return the radius
	if(TYPE == 2)
		return minupper;
		
	// process ecc values for pruned nodes
	if(PRUNE) {
		for(int i=0; i<n; i++) 
			if(pruned[i] >= 0)
				ecc_lower[i] = ecc_lower[(int)pruned[i]];
	}
	
	// return the periphery
	if(TYPE == 4) {
		int periphery = 0;
		for(int i=0; i<n; i++) {
			if(ecc_lower[i] == maxlower)
				periphery++;
		}
		return periphery;
	}		
	
	// return the center
	if(TYPE == 5) {
		int center = 0;
		for(int i=0; i<n; i++) {
			if(ecc_upper[i] == minupper)
				center++;
		}
		return center;
	}
	
	// return 0 with the eccentricity distribution in ecc_lower
		return 0;
} // extremaBounding

