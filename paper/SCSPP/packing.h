/*--------------/
ALH
packing.h
12/10/17
/--------------*/
#ifndef PACKING_H
#define PACKING_H

#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b);

int lowerBound(int maxStripWidth, double totalBoxWidth);

void packStripsFFDApprox(int numScores, int numBox, int maxBoxWidth, int maxStripWidth, double totalBoxWidth, vector<int> &allScores, vector<int> &mates,
                         vector<vector<int> > &adjMatrix, vector<vector<int> > &boxWidths, vector<int> &stripSum, vector<vector<int> > &strip);

void packStripsFFDSmallest(int numScores, int numBox, int maxBoxWidth, int maxStripWidth, double totalBoxWidth, vector<int> &allScores, vector<int> &mates,
                         vector<vector<int> > &adjMatrix, vector<vector<int> > &boxWidths, vector<int> &stripSum, vector<vector<int> > &strip);

void packStripsFFDExact(int numScores, int numBox, int maxBoxWidth, int maxStripWidth, double totalBoxWidth, vector<int> &allScores, vector<int> &mates,
                   vector<vector<int> > &adjMatrix, vector<vector<int> > &boxWidths, vector<int> &stripSum, vector<vector<int> > &strip);

void MBAHRA(int i1, int j1, int &feasible, vector<int> &allScores, vector<int> &mates, vector<vector<int> > &adjMatrix,
            vector<vector<int> > &boxWidths, vector<int> &boxDecrease, vector<int> &stripSum, vector<vector<int> > &strip);

#endif

