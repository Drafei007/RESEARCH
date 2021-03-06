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

void Swap(int &a, int &b);

int LowerBound(int stripLength, double totalItemWidth);

double Fitness(int stripLength, vector<int> &stripSum, vector<vector<int> > &strip);

void FFD(int numScores, int numItem, int maxItemWidth, vector<int> &partners, vector<vector<int> > &itemWidths,
         vector<int> &itemOrder);

void FFR(int numScores, int numItem, vector<int> &partners, vector<vector<int> > &itemWidths, vector<int> &itemOrder);

void FFShell(int numScores, int numItem, int maxItemWidth, int stripLength, vector<int> &partners,
             vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths, vector<int> &stripSum, vector<vector<int> > &strip, bool decrease);


void PartialFFD(int numScores, int maxItemWidth, int stripLength, vector<int> &partners, vector<vector<int> > &adjMatrix,
                vector<vector<int> > &itemWidths, vector<int> &partialItem, vector<int> &partialSum, vector<vector<int> > &partialSol);


void CreateInitPop(int tau, int numPop, int numScores, int numItem, int maxItemWidth, int stripLength, vector<int> &allScores, vector<int> &partners,
                   vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths, vector<vector<int> > &populationSum, vector<vector<vector<int> > > &population);


void Mutation(int tau, int numScores, int maxItemWidth, int stripLength, vector<int> &allScores, vector<int> &partners,
              vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths, vector<int> &stripSum,
              vector<vector<int> > &strip);


void LocalSearch(int tau, int numScores, int maxItemWidth, int stripLength, vector<int> &allScores, vector<int> &partners, vector<vector<int> > &adjMatrix,
                 vector<vector<int> > &itemWidths, vector<int> &stripSum, vector<vector<int> > &strip, vector<int> &stripSumX, vector<vector<int> > &stripX,
                 vector<int> &stripSumY, vector<vector<int> > &stripY);


void InitAHCA(int tau, int swapType, int moveType, int &feasible, int i1, int a1, int b1, int j1, int c1, int d1, vector<int> &allScores,
              vector<vector<int> > &itemWidths, vector<int> &stripSumX, vector<vector<int> > &stripX, vector<int> &stripSumY, vector<vector<int> > &stripY);


void AHCA(int tau, int &feasible, vector<int> &scores, vector<int> &original, vector<int> &final);


void InitInstance(int tau, int nScores, vector<vector<int> > &adjMat, vector<int> &scores, vector<int> &order,
                  vector<int> &partnersX);


void MMCM(int nScores, int &matchSize, vector<vector<int> > &adjMat, vector<int> &partnersX, vector<int> &matchList, vector<int> &cycleVertex);


void MPS(int nScores, int &nCycles, vector<int> &partnersX, vector<int> &matchList, vector<vector<int> > &mpStructure);


void BR(int &qstar, int matchSize, vector<vector<int> > &adjMat, vector<int> &matchList, vector<int> &cycleVertex, vector<int> &edge,
        vector<vector<int> > &mpStructure, vector<vector<int> > &C, vector<vector<int> > &S);

void CP(int nScores, int nComp, int &feasible, int qstar, int nCycles, vector<int> &partnersX, vector<int> &matchList,
        vector<int> &cycleVertex, vector<int> &edge, vector<vector<int> > &adjMat, vector<vector<int> > &C, vector<vector<int> > &S, vector<int> &altHam);


void EA(int tau, int recomb, int numScores, int maxItemWidth, int stripLength, int &bestEnd, double &bestFitness, vector<int> &allScores, vector<int> &partners,
        vector<vector<int> > &adjMatrix, vector<vector<int> > &itemWidths, vector<vector<int> > &populationSum, vector<vector<vector<int> > > &population);

void GGA(int tau, int numScores, int maxItemWidth, int stripLength, vector<int> &allScores, vector<int> &partners, vector<vector<int> > &adjMatrix,
         vector<vector<int> > &itemWidths, vector<int> &offspringSum, vector<vector<int> > &offspring,
         vector<int> &stripSumX, vector<vector<int> > &stripX, vector<int> &stripSumY, vector<vector<int> > &stripY);

void GPX(int tau, int numScores, int maxItemWidth, int stripLength, vector<int> &allScores, vector<int> &partners, vector<vector<int> > &adjMatrix,
         vector<vector<int> > &itemWidths, vector<int> &offspringSum, vector<vector<int> > &offspring, vector<int> &stripSumX, vector<vector<int> > &stripX,
         vector<int> &stripSumY, vector<vector<int> > &stripY);

#endif

