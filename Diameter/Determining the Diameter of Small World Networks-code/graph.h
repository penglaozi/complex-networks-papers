/*******************************************************************************
BoundingDiameters v0.4
@author Frank Takes - ftakes@liacs.nl
@website http://www.liacs.nl/~ftakes/diameter
**************** consult the README.txt file before using *********************/

#ifndef __types_h__
#define __types_h__

// maximum node number (IMPORTANT, see README)
#define MAXN 1000000

#include <algorithm>	// min,max
#include <cstring> 		// memset
#include <fstream> 		// files
#include <iostream> 	// cin,cout
#include <iomanip> 		// setw
#include <vector>		// edge array
#include <queue> 		// bfs
#include <map>			// node mapping

using namespace std;

// Graph: main class which represents the graph
class Graph {
	public:
		// Graph functions:
		Graph();
		~Graph() {}	
		void calcWCC();
		void clear();
		int diameterAPSP();
		int distance(const int, const int);		
		int eccentricity(const int);	
		int getn();
		bool load(const string);
		bool loadUndirected(const string);	
		void makeUndirected();
		int mapNode(const int);
		int radiusAPSP();		
		int revMapNode(const int);	
		void stats(); 

		// bd.cc functions
		int centerBD();				
		int diameterBD();		
		int* eccentricitiesBD();
		int peripheryBD();				
		int radiusBD();		

	private:
		// Graph functions:
		bool addEdge(const int, const int);
		bool addUndirEdge(const int, const int);		
		bool edge(const int, const int);
		bool edgeSlow(const int, const int);		
		bool inLargestWCC(const int);
		void sortEdgeList();

		// bd.cc functions:
		int extremaBounding(const int, const int);
		int pruning();		
		
		// Graph data:
		long				n;						// number of nodes
		unsigned int		m;						// number of directed edges
		unsigned int		selfm;					// number of loops (self-edges)
		int					nexti; 					// next "empty" node id
		bool 				loaded;					// is a graph loaded?
		bool 				sorted;					// are the edge lists sorted?
		bool				undirected;				// is the graph undirected?
		bool 				doneWCC;				// have we computed the WCCs?
		int 				largestWCC;				// id of largest WCC 
		int					wccs;					// number of WCCs
		map<int,int>		nodeMapping;			// mapping of actual nodenumbers s to 0, .., n			
		int 				revNodeMapping[MAXN];	// mapping of 0, ..., n to actual node numbers
		vector<int>			E[MAXN];				// outdegrees (size) & list of neighbors of i 		
		//vector<int>		rE[MAXN];				// indegrees (size) & list of in-neighbors of i
		int 				inDeg[MAXN];			// indegrees
		int 				WCC[MAXN];				// wcc # of node i
		long 				WCCNodes[MAXN];			// nr. of nodes in WCC i
		int 				WCCEdges[MAXN];			// nr. of edges in WCC i		

		// helpers:
		int 				d[MAXN];				// used to hold the last distance matrix

		// bd.cc data:
		int 				pruned[MAXN];			// -1 if not pruned, 0 or larger value if pruned by that particular node
		int 				ecc_lower[MAXN];		// lower eccentricity bounds
		int 				ecc_upper[MAXN];		// upper eccentricity bounds
		bool 				candidate[MAXN];		// candidate set for contributing to the extreme measures
		
}; // Graph class

#endif // __types_h__

