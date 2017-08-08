/*--------------------/
ALH
MSSP with output of solution.
17/07/2017
/--------------------*/

#include <iostream>
#include <vector>
#include <time.h>
#include <algorithm>
#include <iomanip> //header providing parametric manipulators
using namespace std;

void resetVectors(int vacant, int numScores, int numComp,  vector<vector<int> > &adjMatrix, vector<int> &allScores, vector<int> &checked, vector<int> &cycleVertex, vector<int> &matchList, vector<int> &mates, vector<int> &QSet, vector<vector<int> > &S, vector<int> &patchCycle, vector<int> &patchVertex){
	int i, j;

	for(i = 0; i < numScores; ++i){
		allScores[i] = 0;
		matchList[i] = vacant;
		cycleVertex[i] = 1;
		mates[i] = 0;
		checked[i] = 0;
        patchVertex[i] = vacant;
	}

	for(i = 0; i < numScores; ++i){
		for(j = 0; j < numScores; ++j){
			adjMatrix[i][j] = 0;
		}
	}

	for(i = 0; i < numComp; ++i){
		QSet[i] = 0;
        patchCycle[i] = vacant;
	}

	for(i = 0; i < numComp; ++i){
		for(j = 0; j < numComp; ++j){
			S[i][j] = 0;
		}
	}

}

void clearVectors(vector<int> &cycle, vector<int> &edge, vector<int> &lengthMateInduced, vector<vector<int> > &mateInduced, vector<int> &randOrder, vector<int> &t, vector<vector<int> > &T, vector<int> &SSet, vector<int> &fullCycle, vector<vector<int> > &Tpatch, vector<int> &temp){
	cycle.clear();
	edge.clear();
	lengthMateInduced.clear();
	mateInduced.clear();
	randOrder.clear();
	t.clear();
	T.clear();
	SSet.clear();
    fullCycle.clear();
    Tpatch.clear();
    temp.clear();

}

void loopCycle(int v, int full, int save, vector<int> &matchList, vector<int> &cycleVertex, vector<int> &fullCycle, vector<vector<int> > &mateInduced, vector<vector<int> > &T){

    int i;


    //CASE ONE: if element matchList[T[full][v]] is before element T[full][v] in the mateInduced cycle
    //i.e. if the element at position 'save' in the cycle is matchList[T[full][v]] and the element at position "save + 1" is T[full][v]
    if(mateInduced[cycleVertex[T[full][v]]][save + 1] == T[full][v]){
        for(i = save + 1; i-- > 0;){ //from element at position 'save' to the first element in the cycle
            fullCycle.push_back(mateInduced[cycleVertex[T[full][v]]][i]);
        }
        for(i = mateInduced[cycleVertex[T[full][v]]].size(); i-- > save +1;){ //from end of cycle to element at position save+1
            fullCycle.push_back(mateInduced[cycleVertex[T[full][v]]][i]);
        }
    }

    //CASE TWO: if element matchList[T[full][v]] is after element T[full][v] in the mateInduced cycle
    //i.e. if the element at position 'save' in the cycle is matchList[T[full][v]] and the element at position "save - 1" is T[full][v]
    else if (mateInduced[cycleVertex[T[full][v]]][save - 1] == T[full][v]){
        for(i = save; i < mateInduced[cycleVertex[T[full][v]]].size(); ++i){
            fullCycle.push_back(mateInduced[cycleVertex[T[full][v]]][i]);
        }
        for(i = 0; i < save; ++i){
            fullCycle.push_back(mateInduced[cycleVertex[T[full][v]]][i]);
        }
    }

    //CASE THREE: if element matchList[T[full][v]] is the first element in the cycle, and T[full][v] is the last element in the cycle
    //i.e. if save = 0 and T[full][v] is at position mateInduced[cycleVertex[T[full][v]]].size()-1
    else if (save == 0 && mateInduced[cycleVertex[T[full][v]]][mateInduced[cycleVertex[T[full][v]]].size()-1] == T[full][v]){
        for(i = 0; i < mateInduced[cycleVertex[T[full][v]]].size(); ++i){
            fullCycle.push_back(mateInduced[cycleVertex[T[full][v]]][i]);
        }
    }

    //CASE FOUR: if element matchList[T[full][v]] is the last element in the cycle, and T[full][v] is the first element in the cycle
    //i.e. if save = mateInduced[cycleVertex[T[full][v]]].size()-1 and T[full][v] is at position 0
    else if(save == mateInduced[cycleVertex[T[full][v]]].size()-1 && mateInduced[cycleVertex[T[full][v]]][0] == T[full][v]){
        for(i = mateInduced[cycleVertex[T[full][v]]].size(); i-- > 0; ){
            fullCycle.push_back(mateInduced[cycleVertex[T[full][v]]][i]);
        }
    }

}

void loopCyclePatch(int &u, int v, int save, int vacant, vector<int> &matchList, vector<int> &cycleVertex, vector<int> &fullCycle, vector<vector<int> > &mateInduced, vector<vector<int> > &Tpatch, vector<int> &patchVertex){

    int i;
    int x = 0;

    //CASE ONE: if the current value is matchList[Tpatch[u][v]] and the previous value is Tpatch[u][v]
    if (mateInduced[cycleVertex[Tpatch[u][v]]][save - 1] == Tpatch[u][v]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = save + 1; i < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++i){
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                x = 1;
                break;
            }
        }
        if(x == 0) {
            for (i = 0; i < save; ++i) {
                if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                }
                else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                    u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                    break;
                }
            }
        }
    }

    //CASE TWO: if the current value is Tpatch[u][v] and the previous value is matchList[Tpatch[u][v]]
    else if (mateInduced[cycleVertex[Tpatch[u][v]]][save - 1] == matchList[Tpatch[u][v]]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = save + 1; i < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++i){
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                x = 1;
                break;
            }
        }
        if(x == 0) {
            for (i = 0; i < save; ++i) {
                if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                }
                else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                    u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                    break;
                }
            }
        }
    }

    //CASE THREE: if the current vertex is Tpatch[u][v] and the next element is matchList[Tpatch[u][v]]
    else if(mateInduced[cycleVertex[Tpatch[u][v]]][save + 1] == matchList[Tpatch[u][v]]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = save; i-- > 0;){ //from element at position 'save' to the first element in the cycle
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                x = 1;
                break;
            }
        }
        if(x == 0) {
            for (i = mateInduced[cycleVertex[Tpatch[u][v]]].size(); i-- > save + 1;) { //from end of cycle to element at position save+1
                if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                }
                else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                    u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                    break;
                }
            }
        }
    }

    //CASE FOUR: if the current vertex is matchList[Tpatch[u][v]] and the next element is Tpatch[u][v]
    else if(mateInduced[cycleVertex[Tpatch[u][v]]][save + 1] == Tpatch[u][v]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = save; i-- > 0;){ //from element at position 'save' to the first element in the cycle
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                x = 1;
                break;
            }
        }
        if(x == 0) {
            for (i = mateInduced[cycleVertex[Tpatch[u][v]]].size(); i-- > save + 1;) { //from end of cycle to element at position save+1
                if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                }
                else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                    fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                    u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                    break;
                }
            }
        }
    }

    //CASE FIVE: if the current vertex is matchList[Tpatch[u][v]] and is the first element in the cycle, and
    //the last element in the cycle is Tpatch[u][v]
    else if(save == 0 && mateInduced[cycleVertex[Tpatch[u][v]]][mateInduced[cycleVertex[Tpatch[u][v]]].size()-1] == Tpatch[u][v]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = 1; i < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++i){
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                break;
            }
        }
    }

    //CASE SIX: if the current vertex is matchList[Tpatch[u][v]] and is last element in the cycle, and
    //the first element in the cycle is Tpatch[u][v]
    else if(save == mateInduced[cycleVertex[Tpatch[u][v]]].size()-1 && mateInduced[cycleVertex[Tpatch[u][v]]][0] == Tpatch[u][v]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = mateInduced[cycleVertex[Tpatch[u][v]]].size()-1; i-- > 0; ){
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                break;
            }
        }
    }

    //CASE SEVEN: if the current vertex is Tpatch[u][v] and is the first element in the cycle, and
    //and the last element in the cycle is matchList[Tpatch[u][v]]
    else if(save == 0 && mateInduced[cycleVertex[Tpatch[u][v]]][mateInduced[cycleVertex[Tpatch[u][v]]].size()-1] == matchList[Tpatch[u][v]]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = 1; i < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++i){
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                break;
            }
        }
    }

    //CASE EIGHT: if the current vertex is Tpatch[u][v] and is last element in the cycle, and
    //the first element in the cycle is matchList[Tpatch[u][v]]
    else if(save == mateInduced[cycleVertex[Tpatch[u][v]]].size()-1 && mateInduced[cycleVertex[Tpatch[u][v]]][0] == matchList[Tpatch[u][v]]){
        fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][save]);
        for(i = mateInduced[cycleVertex[Tpatch[u][v]]].size()-1; i-- > 0; ){
            if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] == vacant) {
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
            }
            else if(patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]] != vacant){
                fullCycle.push_back(mateInduced[cycleVertex[Tpatch[u][v]]][i]);
                u = patchVertex[mateInduced[cycleVertex[Tpatch[u][v]]][i]];
                break;
            }
        }
    }



}

void MTGMA(int vacant, int threshold, int numScores, int &matchSize, vector<int> &allScores, vector<vector<int> > &adjMatrix, vector<int> &cycleVertex, vector<int> &matchList){

	int i, j, k;
	int lastMatch = vacant;
	int mateMatch = vacant;
	int vacantFlag = 0;

	for (i = 0; i < numScores; ++i) { //check all vertices
		vacantFlag = 0;
		if (matchList[i] == vacant) { //if vertex has not yet been matched
			for (j = numScores - 1; j > i; --j) { //try match vertex i with largest unmatched vertex, start from largest vertex j, go down list of vertices in decreasing order of size
				if (adjMatrix[i][j] == 1 && matchList[j] == vacant) { //if vertices i and j are adjacent, and if vertex j has not yet been matched
					matchList[i] = j;
					matchList[j] = i;
					lastMatch = i;
					++matchSize;
					if (vacantFlag == 1) { //delete edge for FCA if matching was not with highest vertex due to the highest vertex being its mate
						cycleVertex[i] = vacant;
						cycleVertex[j] = vacant;
					}
					break;
				} else if (adjMatrix[i][j] == 2 && matchList[j] == vacant) { //if potential match == mate
					vacantFlag = 1;
				}
			}//end for j
			if (matchList[i] == vacant) { //if vertex has still not been matched
				for (k = 0; k < numScores; ++k) {
					if (adjMatrix[i][k] == 2) { //if vertex i and vertex k are mates
						mateMatch = k;
						break;
					}
				}
				if ((allScores[i] + allScores[mateMatch] >= threshold) //match with mate?
					&& (matchList[mateMatch] == vacant) //is mate unmatched?
					&& (lastMatch != vacant) //has the previous vertex been matched?
					&& (mateMatch > i) //is the mate larger? (sorted in increasing order of vertex weight, so index will be higher if vertex has larger value)
					&& (allScores[lastMatch] + allScores[mateMatch] >= threshold)) { //can mate be matched with last matched vertex?
					// if so, then swap mates
					matchList[i] = matchList[lastMatch];
					matchList[lastMatch] = mateMatch;
					matchList[mateMatch] = lastMatch;
					matchList[matchList[i]] = i;
					cycleVertex[lastMatch] = vacant; //edge from mate swap will not count for FCA
					cycleVertex[mateMatch] = vacant; //edge from mate swap will not count for FCA
					lastMatch = i;
					++matchSize;
				}
			}//end if matchList == vacant
		}//end if matchList[i] == i
	}//end for i


}

void MIS(int numScores, int &numCycles, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<int> &matchList, vector<vector<int> > &mateInduced, vector<int> &lengthMateInduced){
	int i, j;
	int smallestVertex;
	int currentVertex;
	vector<int> cycle;
	vector<int> checked(numScores, 0);

	for (i = 0; i < numScores; ++i) {
		for (j = 0; j < numScores; ++j) {
			if (adjMatrix[i][j] == 2) {
				mates[i] = j;
				break;
			}
		}
	}

	/*cout << "Mates Vector:\n";*/

	//find the smallest vertex not yet checked for mate-induced structure - start with this vertex
	for (i = 0; i < numScores; ++i) {
		if (checked[i] == 0) {
			smallestVertex = i;
			break;
		}
	}

	//Building the mate-induced structure
	do {
		currentVertex = smallestVertex;
		do {
			cycle.push_back(currentVertex);
			checked[currentVertex] = 1;
			cycle.push_back(mates[currentVertex]);
			checked[mates[currentVertex]] = 1;
			currentVertex = matchList[mates[currentVertex]];
		} while (currentVertex != smallestVertex);

		mateInduced.push_back(cycle);
		cycle.clear();

		for (i = 0; i < numScores; ++i) {
			if (checked[i] == 0) {
				smallestVertex = i;
				break;
			}
		}


	} while (smallestVertex != currentVertex);

	cycle.clear(); //clear cycle vector again for next instance

	numCycles = mateInduced.size(); //number of cycles in the mate-induced structure

	/*cout << "Mate-Induced Structure:\n";*/
	/*cout << "Number of cycles in mate-induced structure: " << numCycles << endl;*/

	for (i = 0; i < mateInduced.size(); ++i) {
		lengthMateInduced.push_back(mateInduced[i].size());
	}


}

void FCA(int &qstar, int vacant, int matchSize, vector<vector<int> > &adjMatrix, vector<int> &cycleVertex, vector<int> &matchList, vector<vector<int> > &mateInduced, vector<vector<int> > &S, vector<vector<int> > &T){
	int i, j, k;
	int numEdges;
	vector<int> edge;
	vector<int> t;

	//FCA
	//create list cycleVertex that contains for each vertex the cycle that each edge belongs to
	for (i = 0; i < mateInduced.size(); ++i) {
		for (j = 0; j < mateInduced[i].size(); ++j) {
			if (cycleVertex[mateInduced[i][j]] != vacant) { //if edge is not deleted for FCA
				cycleVertex[mateInduced[i][j]] = i;
			}
		}
	}
	/*cout << "Cycle Vertex:\n";*/
	//create list of edges without empty edges (those generated by mate swap)
	for (i = 0; i < matchSize; ++i) {
		while (cycleVertex[i] == vacant) {
			++i;
		}
		edge.push_back(i);
	}
	numEdges = edge.size();
	/*cout << "Edges vector:\n";*/
	//cout << "Number of Edges: " << numEdges << endl;
	//FCA Algorithm
	qstar = -1;
	k = 0; //edge from matching that is under consideration

	do {
		while (k < numEdges - 2 && (adjMatrix[edge[k]][matchList[edge[k + 1]]] != 1 || cycleVertex[edge[k]] == cycleVertex[edge[k + 1]])) {
			++k;
		}
		if (adjMatrix[edge[k]][matchList[edge[k + 1]]] == 1 && cycleVertex[edge[k]] != cycleVertex[edge[k + 1]]) {
			++qstar;
			t.push_back(edge[k]);
			S[qstar][cycleVertex[edge[k]]] = 1;
			while (k < numEdges - 1 && adjMatrix[edge[k]][matchList[edge[k + 1]]] == 1 && S[qstar][cycleVertex[edge[k + 1]]] == 0) { //add more edges to current T-cycle
				++k;
				t.push_back(edge[k]);
				S[qstar][cycleVertex[edge[k]]] = 1;
			}
			T.push_back(t);
			t.clear();
		} // end if
		++k;
	} while (k < numEdges - 1);

	t.clear();



}

void patchGraph(int vacant, int instance, int numCycles, int &feasible, int &fullT, int qstar, int numScores, int &splitT, int &noPatch, int &infeasible, int &problemInstance, vector<int> &matchList, vector<int> &cycleVertex, vector<vector<int> > &mateInduced, vector<vector<int> > &T, vector<vector<int> > &S){
	int i, j, q, u, v, save, SSum, SqIntS;
	int full = vacant;
	vector<int> QSet(qstar, 0);
	vector<int> SSet;
	vector<int> patchCycle(qstar, vacant);
	vector<int> temp;
	vector<int> patchVertex(numScores, vacant);
	vector<vector<int> > Tpatch;
	vector<int> fullCycle;

	for (i = 0; i < T.size(); ++i) {
		if (T[i].size() == numCycles) {
			full = i;
			break;
		}
	}

	if(full != vacant){
		save = 0;
		//cout << "Full: " << full << endl;
		for (v = 0; v < T[full].size(); ++v) {
			for (j = 0; j < mateInduced[cycleVertex[T[full][v]]].size(); ++j) {
				if (mateInduced[cycleVertex[T[full][v]]][j] == matchList[T[full][v]]) {
					save = j;
					break;
				}
			}
			loopCycle(v, full, save, matchList, cycleVertex, fullCycle, mateInduced, T);

		}
		cout << instance << ": Full cycle after T-cycle analysis:\n";
		for (i = 0; i < fullCycle.size(); ++i) {
			cout << fullCycle[i] << " ";
		}
		cout << endl << endl;
		++feasible;
		++fullT;

	}

	else {
		q = 0; //Start with first Tq-cycle
		QSet[0] = 1;
		SSum = 0; //number of MIS-cycles that have been included
		for (i = 0; i < numCycles; ++i) {
			SSet.push_back(S[q][i]); // ==1 if MIS cycle i has been included
		}
		for (i = 0; i < numCycles; ++i) {
			SSum = SSum + SSet[i];
		}

		if (SSum >= 1) {
			patchCycle[q] = 1;
		}

		//Start connectivity check
		while (q <= qstar && SSum < numCycles) {
			do {
				++q;
				SqIntS = vacant;
				if (q <= qstar) {
					for (j = 0; j < numCycles; ++j) { //is there a j such that S[q][j] = 1 and SSet[j] = 1?
						if (S[q][j] == 1 && SSet[j] == 1) {
							SqIntS = 1;
							//break here? no need to check all other j indices once one has been found such that S[q][j] =1 and SSet[j] = 1
						}
					}
				}
			} while (q < qstar + 1 && (QSet[q] == 1 || SqIntS == vacant));

			if (q <= qstar) { //if Tq-cyce for enlargement has been found
				for (i = 0; i < numCycles; ++i) {
					if (SSet[i] == 0 && S[q][i] == 1) {
						SSet[i] = 1;
						++SSum;
						patchCycle[q] = 1;
					}
				}
				QSet[q] = 1;
				q = 0;
			}
		}//end while


		//If patching graph is connected, then instance is feasible, else infeasible
		if (SSum == numCycles) {
			for (i = 0; i < patchCycle.size(); ++i) {
				if (patchCycle[i] == 1) {
					for (j = 0; j < T[i].size(); ++j) {
						temp.push_back(T[i][j]);
					}
					Tpatch.push_back(temp);
					temp.clear();
				}
			}
			temp.clear();

			for (i = 0; i < Tpatch.size(); ++i) {
				for (j = 0; j < Tpatch[i].size(); ++j) {
					patchVertex[Tpatch[i][j]] = i;
					patchVertex[matchList[Tpatch[i][j]]] = i;
				}
			}

			u = 0;
			v = 0;
			save = 0;
			for (j = 0; j < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++j) {
				if (mateInduced[cycleVertex[Tpatch[u][v]]][j] == matchList[Tpatch[u][v]]) {
					save = j;
					break;
				}
			}
			loopCyclePatch(u, v, save, vacant, matchList, cycleVertex, fullCycle, mateInduced, Tpatch, patchVertex);

			while (fullCycle.size() < numScores) {
				save = 0;
				for (i = 0; i < Tpatch[u].size(); ++i) {
					if (Tpatch[u][i] == fullCycle.back()) {
						if (i == Tpatch[u].size() - 1) {
							v = 0;
						} else {
							v = ++i;
						}
						for (j = 0; j < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++j) {
							if (mateInduced[cycleVertex[Tpatch[u][v]]][j] == matchList[Tpatch[u][v]]) {
								save = j;
								break;
							}
						}
						break;
					} else if (matchList[Tpatch[u][i]] == fullCycle.back()) {
						if (i == 0) {
							v = Tpatch[u].size() - 1;
						} else {
							v = --i;
						}
						for (j = 0; j < mateInduced[cycleVertex[Tpatch[u][v]]].size(); ++j) {
							if (mateInduced[cycleVertex[Tpatch[u][v]]][j] == Tpatch[u][v]) {
								save = j;
								break;
							}
						}
						break;
					}
				}
				loopCyclePatch(u, v, save, vacant, matchList, cycleVertex, fullCycle, mateInduced, Tpatch, patchVertex);
			}

			cout << instance << ": full cycle SPLIT:\n";
			for (i = 0; i < fullCycle.size(); ++i) {
				cout << fullCycle[i] << " ";
			}
			cout << endl;
			++feasible;
			++splitT;
		}
		else if (SSum < numCycles) {
			//cout << instance << ": Infeasible SSum < numCycles\n\n";
			++noPatch;
			++infeasible;
		}
		else {
			//cout << instance << ": Problem.\n\n";
			++problemInstance;
		}


	}





}


int main(int argc, char **argv){
    if(argc < 5){
		cout << "Minimum Score Separation Problem: MBAHRA.\n";
		cout << "Arguments are the following:\n";
		cout << "- Number of instances (integer)\n";
		cout << "- Number of boxes (integer)\n";
		cout << "- Minimum width of scores (millimeters, min = 1)\n";
		cout << "- Maximum width of scores (millimeters, max = 70)\n";
		cout << "- Random Seed (integer)\n";
		exit(1);
	}

    //VARIABLES FROM ARGUMENTS
	int numInstances = atoi(argv[1]); //number of instances of mssp, use in main for loop
	int numBox = atoi(argv[2]) + 1; //number of boxes in mssp plus 1 extra box (scores on either side of extra box will be dominating vertices, score widths = 71)
	int minWidth = atoi(argv[3]); //minimum width of scores (millimeters)
	int maxWidth = atoi(argv[4]); //maximum width of scores (millimeters)
	int randomSeed = atoi(argv[5]); //random seed

	//VARIABLES
	int i, j, k, q;
	int instance; //counter for instances loop
	int numScores = numBox * 2; //number of scores, 2 per box (1 either side), last two scores are dominating vertices
	int numComp = (numBox + (numBox % 2)) / 2;
	int threshold = 70; //adjacency threshold of scores, minimum knife distance
	int vacant = 999; //large empty value
	int feasible = 0; //number of feasible instances
	int infeasible = 0; //number of infeasible instances

	//Creating scores and forming adjacency matrix:
	vector<int> allScores(numScores, 0); //vector containing all score widths
	vector<int> randOrder; //vector used to shuffle and assign mates
	vector<vector<int> > adjMatrix(numScores, vector<int>(numScores ,0)); //adjacency matrix, 0 if width sum < threshold, 1 if width sum >= threshold, 2 if scores are mates (either side of same box)

	//Modified Threshold Graph Matching Algorithm (MTGMA)
	int matchSize = 0; //size/cardinality of the matching list
	int noMatch = 0; //counter for number of instances with |M| < n (matchSize < numBox)
	vector<int> cycleVertex(numScores, 1); //contains the number of the cycle of the mate-induced structure that the vertex i belongs to
	//(e.g. if vertex 4 is in the first cycle of the MIS, then cycleVertex[4] = 0 (0 = first cycle, 1 = second cycle etc))
	vector<int> matchList(numScores, vacant); //contains vertex index for matching vertices, e.g. if vertex 0 is matched with vertex 9, then matchList[0] = 9

	//Mate-Induced Structure (MIS)
	int numCycles; //number of cycles in the mate-induced structure, i.e mateInduced.size() (each row in the mate-induced structure matrix represents a cycle)
	int oneCycle = 0; //counter for the number of instances where the MIS consists of one one cycle (therefore immediately feasible)
	vector<int> mates(numScores, 0); //contains vertex index for mates, e.g if vertex 0 is mates with vertex 4, then mates[0] = 4
	vector<vector<int> > mateInduced; //size numscore by noComp, i.e. number of rows = numScores, number of columns = noComp
	vector<int> lengthMateInduced; //each element holds the value corresponding to the length of the relative cycle in the mate-induced structure

	//Familty Construction Algorithm (FCA)
	int qstar; //number of T-cycle families found (i.e T.size())
	int noFam = 0; //counter for number of instances where no family of T-cycles has been found
	vector<vector<int> > T; //holds set of edges in T-cycles
	vector<vector<int> > S(numComp, vector<int>(numComp, 0)); // set of indices of cycles of MIS that have an edge in T, == 1 if edge from cycle j is used in T-cycle q (T[q][j])
	//FCA also uses the vector cycleVertex from MTGMA

	//Patching Graph Connectivity
	int problemInstance = 0; //counter for number of instances with issues (SSum > numCycles)
	int noPatch = 0;

	//Building solution output
    int splitT = 0;
    int fullT = 0;
	srand(randomSeed); //seed

	cout << "Minimum Score Separation Problem - Matching-Based Alternating Hamiltonicity Recognition Algorithm\n\n";

	time_t startTime, endTime; //start clock
	startTime = clock();

	for(instance = 0; instance < numInstances; ++instance) {

		resetVectors(vacant, numScores, numComp, adjMatrix, allScores, checked, cycleVertex, matchList, mates, QSet, S, patchCycle, patchVertex);
		clearVectors(cycle, edge, lengthMateInduced, mateInduced, randOrder, t, T, SSet, fullCycle, Tpatch, temp);

		//Create random values to be used as score widths, put in allScores vector (except last two elements)
		for (i = 0; i < numScores - 2; ++i) {
			allScores[i] = rand() % (maxWidth - minWidth + 1) + minWidth;
		}
		//add two dominating vertices with score widths = 71 (these scores will be either side of same box, mates)
		allScores[numScores - 2] = 70;
		allScores[numScores - 1] = 70;

		//Sort all of the scores in the allScores vector in ascending order
		sort(allScores.begin(), allScores.end()); //sorts elements of vector in ascending order

		//Filling in adjacency matrix - if sum of two scores >= threshold (70), then insert 1 into the matrix, else leave as 0
		for (i = 0; i < allScores.size() - 1; ++i) {
			for (j = i + 1; j < allScores.size(); ++j) {
				if (allScores[i] + allScores[j] >= threshold) {
					adjMatrix[i][j] = 1;
					adjMatrix[j][i] = 1;
				}
			}

		}

		//Initially, randOrder vector will contain elements in the order 0, ..., numScores -2, numScores -1
		for (i = 0; i < numScores; ++i) {
			randOrder.push_back(i);
		}

		//Randomly shuffle all values in randOrder vector EXCEPT the last two values (dominating vertices, must stay as mates)
		random_shuffle(randOrder.begin(), randOrder.begin() + (numScores - 2));

		//Assign mates to each score (i.e. pair up scores to define which scores are either side of the same box)
		//In the adjacency matrix, this will be represented by value 2
		//Therefore there will be a value of 2 in every row and every column, non repeating
		for (i = 0; i < numBox; ++i) {
			adjMatrix[randOrder[2 * i]][randOrder[2 * i + 1]] = 2;
			adjMatrix[randOrder[2 * i + 1]][randOrder[2 * i]] = 2;
		}

		//MATCHING ALGORITHM MTGMA
		MTGMA(vacant, threshold, numScores, matchSize, allScores, adjMatrix, cycleVertex, matchList);


		/*cout << "Cycle Vertex vector after MTGMA:\n";*/
        /*cout << "Matching List:\n";*/

		//If the number of matches (i.e. the size of the matching list M) is less than the number of boxes (n), then instance is infeasible ( |M| < n )
		if (matchSize < numBox) {
            cout << instance << ": Not enough matching edges.\n\n";
			++infeasible;
			++noMatch;
			//cout << "Instance is infeasible, not enough matching edges available (|M| < n)." << endl;
			continue;
		}

		MIS(numScores, numCycles, adjMatrix, mates, matchList, mateInduced, lengthMateInduced);


		//If the mate-induced structure only consists of one cycle, then the problem has been solved and is feasible (just remove one matching edge to find feasible path)
		if (lengthMateInduced[0] == numScores) { //if all of the vertices are in the first (and only) cycle of the mate-induced structure
			++feasible;
			++oneCycle;
            cout << instance << ": Full cycle (MIS):\n";
            for(j = 0; j < mateInduced[0].size(); ++j){
                cout << mateInduced[0][j] << " ";

            }
            cout << endl << endl;
			continue;
		}

		FCA(qstar, vacant, matchSize, adjMatrix, cycleVertex, matchList, mateInduced, S, T);


		//No family of T-cycle found
		if (qstar == -1) {
            //cout << instance << ": Infeasible, qstar = -1\n\n";
			++infeasible;
			++noFam;
			continue;
		}


		//CHECK IF PATCHING GRAPH IS CONNECTED
		patchGraph(vacant, instance, numCycles, feasible, fullT, qstar, numScores, splitT, noPatch, infeasible, problemInstance, matchList, cycleVertex, mateInduced, T, S);

	} //end of for loop instances


    cout << "\n------------------------------------------------------------------\n\n";
	cout << "Number of feasible instances: " << feasible << endl;
	cout << "Number of infeasible instances: " << infeasible << endl;
    cout << "Number of full T cycles: " << fullT << endl;
    cout << "Number of split T cycles: " << splitT << endl;
    cout << "Number of poor matchings: " << noMatch << endl;
    cout << "Number of single cycles: " << oneCycle << endl;
	cout << "Number of no T-cycles: " << noFam << endl;
	cout << "Number of unconnected patching: " << noPatch << endl;

	endTime = clock();
	double totalTime = (((endTime - startTime) / double(CLOCKS_PER_SEC)) * 1000);
	cout << "CPU Time = " << totalTime << " milliseconds.\n";



}//END INT MAIN

