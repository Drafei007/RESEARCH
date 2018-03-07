/*--------------/
ALH
packing.h
Evolutionary Algorithm with Local Search
05/12/2017
06/03/2018
/--------------*/
#ifndef PACKING_H
#define PACKING_H

#include <iostream>
#include <vector>
using namespace std;

void swap(int &a, int &b);

int lowerBound(double totalItemWidth, int maxStripWidth);

double fitness (int maxStripWidth, vector<int> &stripSum, vector<vector<int> > &strip);

void FFDecreasing(int numScores, int numItem, int maxItemWidth, vector<int> &partners, vector<vector<int> > &itemWidths, vector<int> &itemOrder);

void FFRandom(int numScores, int numItem, vector<int> &partners, vector<vector<int> > &itemWidths, vector<int> &itemOrder);

void FFShell(int numScores, int numItem, int maxItemWidth, int maxStripWidth, vector<int> &partners,
         vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths, vector<int> &stripSum, vector<vector<int> > &strip, bool decrease);


void partialFFD(int numScores, int maxItemWidth, int maxStripWidth, vector<int> &partners, vector<vector<int> > &adjMatrix,
                vector<vector<int> > &itemWidths, vector<int> &partialItem, vector<int> &partialSum, vector<vector<int> > &partialSol);


void createInitialPopulation(int tau, int numScores, int numItem, int maxItemWidth, int maxStripWidth, vector<int> &allScores,
                             vector<int> &partners, vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths,
                             vector<vector<int> > &populationSum, vector<vector<vector<int> > > &population);


void mutation(int tau, int numScores, int maxItemWidth, int maxStripWidth, vector<int> &allScores, vector<int> &partners,
              vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths, vector<int> &stripSum, vector<vector<int> > &strip);


void localSearch(int tau, int numScores, int maxItemWidth, int maxStripWidth, vector<int> &allScores, vector<int> &partners, vector<vector<int> > &adjMatrix,
                 vector<vector<int> > &itemWidths, vector<int> &stripSum, vector<vector<int> > &strip, vector<int> &stripSumX, vector<vector<int> > &stripX, vector<int> &stripSumY, vector<vector<int> > &stripY);


void initAHCA(int tau, int swapType, int moveType, int &feasible, int i1, int a1, int b1, int j1, int c1, int d1, vector<int> &allScores,
              vector<vector<int> > &itemWidths, vector<int> &stripSumX, vector<vector<int> > &stripX, vector<int> &stripSumY, vector<vector<int> > &stripY);


void AHCA(int tau, int &feasible, vector<int> &scores, vector<int> &original, vector<int> &final);


void initializeInstance(int tau, int nScores, vector<vector<int> > &adjMat, vector<int> &scores, vector<int> &order, vector<int> &partnersX);


void MMCM(int nScores, int &matchSize, vector<vector<int> > &adjMat, vector<int> &partnersX, vector<int> &matchList, vector<int> &cycleVertex);


void MPS(int nScores, int &nCycles, vector<int> &partnersX, vector<int> &matchList, vector<vector<int> > &mpStructure);


void BR(int &qstar, int matchSize, vector<vector<int> > &adjMat, vector<int> &matchList, vector<int> &cycleVertex, vector<int> &edge,
        vector<vector<int> > &mpStructure, vector<vector<int> > &C, vector<vector<int> > &S);

void CP(int nScores, int nComp, int &feasible, int qstar, int nCycles, vector<int> &partnersX, vector<int> &matchList,
        vector<int> &cycleVertex, vector<int> &edge, vector<vector<int> > &adjMat, vector<vector<int> > &C, vector<vector<int> > &S, vector<int> &altHam);


void EA(int tau, int numScores, int maxItemWidth, int maxStripWidth, double &parent1cost, double &parent2cost, vector<int> &allScores, vector<int> &partners, vector<vector<int> > &adjMatrix,
        vector<vector<int> > &itemWidths, vector<vector<int> > &populationSum, vector<vector<vector<int> > > &population);

void GGA(int tau, int numScores, int maxItemWidth, int maxStripWidth, vector<int> &allScores, vector<int> &partners, vector<vector<int> > &adjMatrix,
         vector<vector<int> > &itemWidths, vector<int> &stripSumX, vector<vector<int> > &stripX, vector<int> &stripSumY, vector<vector<int> > &stripY);


void AHCA1(int tau, int swapType, int moveType, int &feasible, int i1, int a1, int b1, int j1, int c1, int d1, vector<int> &allScores,
           vector<vector<int> > &itemWidths, vector<int> &stripSumX, vector<vector<int> > &stripX,
           vector<int> &stripSumY, vector<vector<int> > &stripY);

#endif

