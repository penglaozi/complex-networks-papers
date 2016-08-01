/*******************************************************************************
BoundingDiameters v0.4
@author Frank Takes - ftakes@liacs.nl
@website http://www.liacs.nl/~ftakes/diameter
**************** consult the README.txt file before using *********************/

#include "graph.h"

// Constructor: set all variables to zero / false
Graph::Graph() {
	clear();
} // Graph constructor

// Erase the current Graph object
void Graph::clear() {
	for(int i=0; i<MAXN; i++) {
		E[i].clear();
		//rE[i].clear();		
		revNodeMapping[i] = -1;
		pruned[i] = -1; // -1 indicates a node is not pruned by any other node		
	}
	memset(inDeg, 0, sizeof(inDeg));	
	memset(WCC, 0, sizeof(WCC));
	memset(WCCNodes, 0, sizeof(WCCNodes));
	memset(WCCEdges, 0, sizeof(WCCEdges));	
	nodeMapping.clear();
	n = m = selfm = nexti = 0;
	loaded = sorted = undirected = doneWCC = false;
	largestWCC = wccs = 0;
}

// Map original node node number to id
int Graph::mapNode(const int i) {
	if(nodeMapping.find(i) == nodeMapping.end()) {
		nodeMapping[i] = nexti;
		revNodeMapping[nexti] = i;
		nexti++;
	} // if
	return nodeMapping[i]; 
} // mapNode

// Reverse map node id to original node number
int Graph::revMapNode(const int i) {
	return revNodeMapping[i]; 
} // revMapNode

// Check if a node is in the largest WCC
bool Graph::inLargestWCC(const int u) {
	return (WCC[u] == largestWCC);
} // inLargestWCC

// Add an undirected edge to the graph 
bool Graph::addUndirEdge(const int u, const int v) {
	if(!addEdge(u, v))
		return false;
	else if(!addEdge(v, u))
		return false;
	return true;
} // addUndirEdge

// Add an edge to the graph and update the neccessary statistics
bool Graph::addEdge(const int u, const int v) {
	if(u < 0 || u >= MAXN || v < 0 || v >= MAXN) {// || edgeSlow(u,v)) {// uncomment to disallow parallel edges || u == v) { // uncomment to disallow self-edges
		cerr << "OUT OF BOUNDS: (" << u << "," << v << ")" << endl;
		return false;
	}
	
	m++;
	if(u == v)
		selfm++;
	
	if(inDeg[v] == 0 && E[v].size() == 0)
		n++;
	if(v != u && inDeg[u] == 0 && E[u].size() == 0)
		n++;		
	
	E[u].push_back(v);
	//rE[v].push_back(u);	
	inDeg[v]++;

	sorted = false;
	undirected = false;
	doneWCC = false;	
	
	return true;	
} // addEdge


// Load a graph from a file in edge list format: [u v]
bool Graph::load(const string filename) {
	int u, v, edgesAdded = 0, edgesSkipped = 0;
	FILE * fin;
	
	// load the file
	if(!(fin = fopen (filename.c_str(),"r")))
		return false;
	cerr << "Loading graph from " << filename << " ..." << endl;

	// ignore lines that do not start with an integer character
	char c = getc (fin);
	while(c < '0' || c > '9') {
		while(c != '\n')
			c = getc (fin);	
		c = getc (fin);
	}	
    ungetc (c, fin);	
    
	while(fscanf(fin, "%d %d", &u, &v) > 0) {
		if(addEdge(mapNode(u), mapNode(v))) 
			edgesAdded++;
		else
			edgesSkipped++;		
		if(m % 100000000 == 0)
			cerr << "- " << m << " edges loaded." << endl;
	}
	cerr << "Done, " << edgesAdded << " edges added (m = " << m << "), " 
		 << edgesSkipped << " edges skipped (out-of-bounds), " << selfm 
		 << " self-edges." << endl << endl;
	loaded = true;
	//makeUndirected();	
	//nodeMapping.clear(); // free memory (actually does not free it =/)
	if(edgesSkipped == 0)
		return true;
	return false;
} // load


// Load a graph from a file in edge list format: [u v]
bool Graph::loadUndirected(const string filename) {
	int u, v, u2, v2, edgesAdded = 0, edgesSkipped = 0;
	FILE * fin;
	
	// load the file
	if(!(fin = fopen (filename.c_str(),"r")))
		return false;
	cerr << "Loading graph from " << filename << " ..." << endl;
	
	// ignore lines that do not start with an integer character
	char c = getc (fin);
	while(c < '0' || c > '9') {
		while(c != '\n')
			c = getc (fin);	
		c = getc (fin);
	}	
    ungetc (c, fin);	
    
	while(fscanf(fin, "%d %d", &u, &v) > 0) {
		// always add if either one of the nodes are new
		if(nodeMapping.find(u) == nodeMapping.end() || nodeMapping.find(v) == nodeMapping.end()) {	
			if(addUndirEdge(mapNode(u), mapNode(v))) 
				edgesAdded++;
			else
				edgesSkipped++;			
		}
		// only add if u is smaller than v if both are known
		else {
			u2 = mapNode(u);
			v2 = mapNode(v);
			if(!edgeSlow(u2, v2)) {
				if(addUndirEdge(u2, v2)) 
					edgesAdded++;
				else
					edgesSkipped++;		
			}
		}
	
		if(m % 100000000 == 0)
			cerr << "- " << m << " edges loaded." << endl;			
	}
	cerr << "Done, " << edgesAdded << " edges added (m = " << m << "), " 
		 << edgesSkipped << " edges skipped (out-of-bounds), " << selfm 
		 << " self-edges." << endl << endl;
	loaded = true;
	undirected = true;
	nodeMapping.clear(); // free memory
	return true;
} // loadUndirected

// see if there is an edge from a to b
bool Graph::edge(const int a, const int b) { 
	if(!sorted)
		sortEdgeList();
	int first = 0, last = E[a].size() - 1;
    while (first <= last) {
		int mid = (first + last) / 2;		
		if (b > E[a][mid]) 
			first = mid + 1;             	
		else if (b < E[a][mid]) 
			last = mid - 1; 				
		else
			return true;     				
	}
	return false;
} // edge

// see if there is an edge from a to b without first sorting the list - SLOW !
bool Graph::edgeSlow(const int a, const int b) { 
	const int z = E[a].size();
	for(int j=0; j<z; j++)
		if(E[a][j] == b)
			return true;     				
	return false;
} // edgeSlow

// sort edge list so that O(log n) edge queries are possible
void Graph::sortEdgeList() {
	cerr << "Sorting edge list..." << endl;
	if(!sorted) {
		for(int i=0; i<n; i++) {
			sort(E[i].begin(), E[i].end());	
			/*if(i % (n/5) == 0)
				cerr << "- " << i << " node lists sorted (" << setprecision(4) 
					 << (double)(i*100)/(double)n << "%)." << endl;*/
		}
		sorted = true;		
		cerr << "Done." << endl;		 			
	}
	else
		cerr << "Was already done." << endl;		 
} // sortEdgeList

// Print some statistics about the graph.
void Graph::stats() {
	cerr << setw(40) << "Nodes n: " << n << endl;
	cerr << setw(40) << "Links m: " << m;
	if(undirected)
		cerr << " (" << m/2 << " edges)";
	cerr << endl;
	cerr << setw(40) << "Self-links: " << selfm << endl;	
	cerr << setw(40) << "Density m / (n*(n-1)): " << (((double)m)/((double)n))/(((double)(n-1))) << endl;
	cerr << endl;
	//cerr << setw(40) << "Global clustering coefficient: " << globalCluscoef() << endl;	
	cerr << setw(40) << "WCC computed: " << doneWCC << endl;			
	cerr << setw(40) << "Sorted edge lists: " << sorted << endl;		
	cerr << setw(40) << "Undirected edges: " << undirected << endl;			
	cerr << endl;	
 	if(doneWCC) {
		cerr << setw(40) << "Weakly connected components: " << wccs << endl;
		cerr << setw(40) << "Largest weakly connected component #: " << largestWCC << endl;
		cerr << setw(40) << "Largest weakly connected comp. size: " << WCCNodes[largestWCC] << " nodes ("
		  	 << setprecision(8) 
		  	 << (double)WCCNodes[largestWCC]/(double)n << ")" << endl
			 << setw(40) << " " << WCCEdges[largestWCC] << " links / "
			 << ((WCCEdges[largestWCC]-selfm)/2)+selfm << " edges (" 
			 << setprecision(8) 
			 << (double)WCCEdges[largestWCC]/(double)m << ")" << endl
			 ;
		//cerr << setw(40) << "WCC's clustering coefficient: " << wccCluscoef() << endl; 
	}
	cerr << endl;
} // stats


// Compute to which WCC each node belongs.
void Graph::calcWCC() {

	if(!undirected) {
		return;
		//makeUndirected();
	}

	int c, current, z;
	queue<int> q;	
	c = 1;
	
	for(int i=0; i<n; i++) {
		if(WCC[i] > 0)
			continue;
		while(!q.empty()) 
			q.pop();
		WCC[i] = c;
		WCCNodes[c]++;
		WCCEdges[c] += E[i].size();
		q.push(i);		
		while(!q.empty()) {
			current = q.front();
			q.pop();
			z = E[current].size();
			for(int i=0; i<z; i++) {
				if(WCC[E[current][i]] == 0) {
					WCC[E[current][i]] = c;
					WCCNodes[c]++;
					WCCEdges[c] += E[E[current][i]].size();
					q.push(E[current][i]);
				}
			}
		}

		if(WCCNodes[c] > WCCNodes[largestWCC])
			largestWCC = c;
		c++;
	}
	wccs = c-1;
	doneWCC = true;
} // calcWCC

// Get the number of nodes n
int Graph::getn() {
	return n;
} // getn

// Compute the eccentricity of node u - O(m)
int Graph::eccentricity(const int u) {
	int current, z, ecc = 0;
	queue<int> q;
	for(int i=0; i<n; i++)
		d[i] = -1;

	d[u] = 0;
	q.push(u);
	while(!q.empty()) {
		current = q.front();
		q.pop();
		z = E[current].size();
		for(int j=0; j<z; j++) {
			if(d[E[current][j]] == -1 && pruned[E[current][j]] < 0) {
				d[E[current][j]] = d[current] + 1;
				q.push(E[current][j]);
				ecc = max(ecc, d[E[current][j]]);
			}
		}
	}
	return ecc;
} // eccentricity

// compute the distance between node u and v - O(m)
int Graph::distance(const int u, const int v) {
	int current, z, ecc = 0;
	queue<int> q;
	for(int i=0; i<n; i++)
		d[i] = -1;
		
	d[u] = 0;
	q.push(u);
	while(!q.empty()) {
		current = q.front();
		q.pop();
		z = E[current].size();
		for(int j=0; j<z; j++) {
			if(d[E[current][j]] == -1) {
				d[E[current][j]] = d[current] + 1;
				if(E[current][j] == v)
					return d[v];
				q.push(E[current][j]);
				ecc = max(ecc, d[E[current][j]]);
			}
		}
	}
	return d[v];
} // distance

// compute the diameter of the graph, brute-force (APSP) - O(mn)
int Graph::diameterAPSP() {
	if(!doneWCC)
		calcWCC();
	int diameter = 0;
	cerr << "Computing graph diameter using APSP..." << endl;	
	for(int i=0; i<n; i++)
		if(inLargestWCC(i))
			diameter = max(diameter, eccentricity(i));
	cerr << "Done." << endl;
	return diameter;
} // diameterAPSP

// compute the radius of the graph, brute-force (APSP) - O(mn)
int Graph::radiusAPSP() {
	if(!doneWCC)
		calcWCC();
	int rad = n;
	cerr << "Computing graph radius using APSP..." << endl;	
	for(int i=0; i<n; i++)
		if(inLargestWCC(i))
			rad = min(rad, eccentricity(i));
	cerr << "Done." << endl;
	return rad;
} // radiusAPSP

// Make graph undirected (i.e., if (u,v) and !(v,u), then add (u,v))
void Graph::makeUndirected() {
	int z, j;

	static vector<int> templist[MAXN]; // memory-consumer

	sortEdgeList();
	
	for(int i=0; i<n; i++) { 
		templist[i].clear();
	}

	cerr << "Making graph undirected..." << endl;

	// find links that should be added
	for(int i=0; i<n; i++) { 
		z = E[i].size();
		for(j=0; j<z; j++) 
			if(!edge(E[i][j], i)) {
				templist[E[i][j]].push_back(i);				
			}
		/*if(i % (n/5) == 0)
			cerr << "- " << i << " node lists made undirected (" << 
			setprecision(4) << (double)(i*100)/(double)n << "%)." << endl;	 */
	} // for
	
	// actually add these new links
	for(j=0; j<n; j++) {
		z = (signed)templist[j].size();
		for(int i=0; i<z; i++)
			addEdge(j, templist[j][i]);
		vector<int>().swap(templist[j]); // empty the memory-consuming list
		/*if(j % (n/5) == 0)		
			cerr << "- " << j << " node lists cleaned up (" << setprecision(4) 
				 << (double)(j*100)/(double)n << "%)." << endl;		*/
	}
	
	sortEdgeList();		
	
	undirected = true;
	cerr << "Done." << endl;
} // makeUndirected





