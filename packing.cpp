/*--------------------/
ALH
packing.cpp
18/08/2017
/--------------------*/
#include <algorithm>
#include "packing.h"
using namespace std;

void packStripsSmallest(int numScores, int numBox, int maxStripWidth, vector<int> &mates, vector<vector<int> > &adjMatrix, vector<vector<int> > &boxWidths){

    // USE WITH NUMSCORES - 2
    int i, j, x, k;
    vector<int> stripSum(numBox, 0);
    vector<vector<int> > strip(numBox);
    int numStrips = 0;

    strip[0].push_back(0);
    strip[0].push_back(mates[0]);
    stripSum[0] += boxWidths[0][mates[0]];
    for(k = 0; k < adjMatrix.size(); ++k){
        adjMatrix[k][0] = 0;
        adjMatrix[k][mates[0]] = 0;
    }
    x = 0;

    for(j = 0; j < numScores - 2; ++j){
        for(i = 0; i < strip.size(); ++i){
            if(!strip[i].empty()){
                if(adjMatrix[strip[i].back()][j] == 1){
                    if(stripSum[i] + boxWidths[j][mates[j]] <= maxStripWidth){
                        strip[i].push_back(j);
                        strip[i].push_back(mates[j]);
                        stripSum[i] += boxWidths[j][mates[j]];
                        for(k = 0; k < adjMatrix.size(); ++k){
                            adjMatrix[k][j] = 0;
                            adjMatrix[k][mates[j]] = 0;
                        }
                        x = 1;
                        break;
                    }
                }
                else {
                    break;
                }
            }
            else if (strip[i].empty()){
                strip[i].push_back(j);
                strip[i].push_back(mates[j]);
                stripSum[i] += boxWidths[j][mates[j]];
                for(k = 0; k < adjMatrix.size(); ++k){
                    adjMatrix[k][j] = 0;
                    adjMatrix[k][mates[j]] = 0;
                }
                x = 1;
                break;
            }

        }
        if(x == 1) {
            x = 0;
            j = -1;
        }
    }

    cout << "Strips:\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
            ++numStrips;
        }
    }
    cout << endl;

    cout << "Total number of strips required: " << numStrips << endl << endl;

    cout << "Number of boxes per strip:\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": " << strip[i].size() << endl;

        }
    }
    cout << endl;

    cout << "Strip Widths(mm):\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] != 0){
            cout << "Strip " << i << ": " << stripSum[i] << endl;
        }
    }
    cout << endl;

    cout << "Strip Waste(mm):\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] != 0){
            cout << "Strip " << i << ": " << maxStripWidth - stripSum[i] << endl;
        }
    }
    cout << endl;



}

void packStripsMIS(int numBox, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<vector<int> > &mateInduced, vector<vector<int> > &boxWidths){

    int i, j, k;
    int numStrips = 0;
    vector<int> stripSum(numBox, 0);
    vector<vector<int> > strip(numBox);

    i = 0;
    for(j = 0; j < mateInduced[0].size()-1; j+=2){
        if(stripSum[i] + boxWidths[mateInduced[0][j]][mateInduced[0][j+1]] <= maxStripWidth){
            strip[i].push_back(mateInduced[0][j]);
            strip[i].push_back(mateInduced[0][j+1]);
            stripSum[i] += boxWidths[mateInduced[0][j]][mateInduced[0][j+1]];
        }
        else{
            ++i;
            strip[i].push_back(mateInduced[0][j]);
            strip[i].push_back(mateInduced[0][j+1]);
            stripSum[i] += boxWidths[mateInduced[0][j]][mateInduced[0][j+1]];
        }
    }

    if(mateInduced.size() > 1){
        for(k = 1; k < mateInduced.size(); ++k){
            for(j = 0; j < mateInduced[k].size()-1; j+=2){
                for(i = 0; i < strip.size(); ++i){
                    if(!strip[i].empty()){
                        if(adjMatrix[strip[i].back()][mateInduced[k][j]] == 1){
                            if(stripSum[i] + boxWidths[mateInduced[k][j]][mateInduced[k][j+1]] <= maxStripWidth){
                                strip[i].push_back(mateInduced[k][j]);
                                strip[i].push_back(mateInduced[k][j+1]);
                                stripSum[i] += boxWidths[mateInduced[k][j]][mateInduced[k][j+1]];
                                break;
                            }
                            else{
                                continue;
                            }
                        }
                        else{
                            continue;
                        }
                    }
                    else if(strip[i].empty()){
                        strip[i].push_back(mateInduced[k][j]);
                        strip[i].push_back(mateInduced[k][j+1]);
                        stripSum[i] += boxWidths[mateInduced[k][j]][mateInduced[k][j+1]];
                        break;
                    }
                }
            }
        }
    }



    cout << "Strips:\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
            ++numStrips;
        }
    }
    cout << endl;

    cout << "Total number of strips required: " << numStrips << endl << endl;

    cout << "Number of boxes per strip:\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": " << strip[i].size()/2 << endl;

        }
    }
    cout << endl;

    cout << "Strip Widths(mm):\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] != 0){
            cout << "Strip " << i << ": " << stripSum[i] << endl;
        }
    }
    cout << endl;

    cout << "Strip Waste(mm):\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] != 0){
            cout << "Strip " << i << ": " << maxStripWidth - stripSum[i] << endl;
        }
    }
    cout << endl;

}

void weakMatchPath(int vacant, int numScores, vector<int> &matchList, vector<int> &mates){

    int i, j;
    int startPath = vacant;
    int endPath = vacant;
    int currentVertex;
    int smallestVertex;
    vector<int> checked(numScores, 0);
    vector<int> tempWMP;
    vector<vector<int> > weakPaths;


    for(i = 0; i < matchList.size(); ++i){
        if(matchList[i] == vacant){
            if(startPath == vacant){
                startPath = i;
                continue;
            }
            else if(startPath != vacant){
                endPath = i;
                break;
            }
        }
    }

    cout << "startPath: " << startPath << endl;
    cout << "endPath: " << endPath << endl;

    currentVertex = startPath;

    do {
        tempWMP.push_back(currentVertex);
        checked[currentVertex] = 1;
        tempWMP.push_back(mates[currentVertex]);
        checked[mates[currentVertex]] = 1;
        currentVertex = matchList[mates[currentVertex]];
    } while(currentVertex != mates[endPath]);

    tempWMP.push_back(currentVertex);
    checked[currentVertex] = 1;
    tempWMP.push_back(mates[currentVertex]);
    checked[mates[currentVertex]] = 1;

    weakPaths.push_back(tempWMP);
    tempWMP.clear();

    for(i = 0; i < numScores; ++i){
        if(checked[i] == 0){
            smallestVertex = i;
            break;
        }
    }

    do {
        currentVertex = smallestVertex;
        do {
            tempWMP.push_back(currentVertex);
            checked[currentVertex] = 1;
            tempWMP.push_back(mates[currentVertex]);
            checked[mates[currentVertex]] = 1;
            currentVertex = matchList[mates[currentVertex]];
        } while (currentVertex != smallestVertex);

        weakPaths.push_back(tempWMP);
        tempWMP.clear();

        for (i = 0; i < numScores; ++i) {
            if (checked[i] == 0) {
                smallestVertex = i;
                break;
            }
        }


    } while (smallestVertex != currentVertex);


    for(i = 0; i < weakPaths.size(); ++i){
        for(j = 0; j < weakPaths[i].size(); ++j){
            cout << weakPaths[i][j] << " ";
        }
        cout << endl;
    }
    cout << endl;


}

void packStripsBFD(int numBox, int maxBoxWidth, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<vector<int> > &boxWidths){

    int i, j, k, mini;
    int min = 0;
    int max = maxBoxWidth;
    int numStrips = 0;
    vector<int> stripResidual(numBox, maxStripWidth);
    vector<vector<int> > strip(numBox);
    vector<int> boxDecrease; //contains the score number of the smallest score of the boxes in decreasing order
    vector<vector<int> > stripWidth(numBox);
    vector<int> stripNumBoxes(numBox, 0);
    /* i.e if mates 0-4 have boxwidth 536, mates 1-3 have BW 494, mates 2-5 have BW 940
     * then boxDecrease will contain the numbers: 2 0 1 (in that specific order)
     */

    while(boxDecrease.size() < numBox -1) { //numBox -1, doesn't include dominating vertices
        for (i = 0; i < mates.size(); ++i) {
            if (boxWidths[i][mates[i]] > min && boxWidths[i][mates[i]] < max) { //what happens if two boxes have the same width?
                min = boxWidths[i][mates[i]];
                mini = i;
            }
        }
        boxDecrease.push_back(mini);
        max = min;
        min = 0;
    }

    cout << "\nBox Decrease:\n";
    for(i = 0; i < boxDecrease.size(); ++i){
        cout << boxDecrease[i] << " ";
    }
    cout << endl << endl;

    int minRes;
    int minResj;
    int minResk;
    int maxRes;
    int x;

    strip[0].push_back(boxDecrease[0]);
    strip[0].push_back(mates[boxDecrease[0]]);
    stripResidual[0] -= boxWidths[boxDecrease[0]][mates[boxDecrease[0]]];
    stripWidth[0].push_back(boxWidths[boxDecrease[0]][mates[boxDecrease[0]]]);


    for(i = 1; i < boxDecrease.size(); ++i){
        minRes = maxStripWidth + 1;
        for(j = 0; j < stripResidual.size(); ++j){
            if(stripResidual[j] < minRes){
                minRes = stripResidual[j];
                minResj = j;
            }
        }

        x = 0;
        do {
            if(!strip[minResj].empty()) {
                if (stripResidual[minResj] - boxWidths[boxDecrease[i]][mates[boxDecrease[i]]] >= 0) {
                    if (adjMatrix[strip[minResj].back()][boxDecrease[i]] == 1) {
                        strip[minResj].push_back(boxDecrease[i]);
                        strip[minResj].push_back(mates[boxDecrease[i]]);
                        stripResidual[minResj] -= boxWidths[boxDecrease[i]][mates[boxDecrease[i]]];
                        stripWidth[minResj].push_back(boxWidths[boxDecrease[i]][mates[boxDecrease[i]]]);
                        x = 1;
                        continue;
                    }

                    else if (adjMatrix[strip[minResj].back()][mates[boxDecrease[i]]] == 1) {
                        strip[minResj].push_back(mates[boxDecrease[i]]);
                        strip[minResj].push_back(boxDecrease[i]);
                        stripResidual[minResj] -= boxWidths[boxDecrease[i]][mates[boxDecrease[i]]];
                        stripWidth[minResj].push_back(boxWidths[boxDecrease[i]][mates[boxDecrease[i]]]);
                        x = 1;
                        continue;
                    }

                    else { //if neither score is adjacent, try next strip
                        maxRes = maxStripWidth + 1;
                        for (k = 0; k < stripResidual.size(); ++k) {
                            if (stripResidual[k] > minRes && stripResidual[k] < maxRes) {
                                maxRes = stripResidual[k];
                                minResk = k;
                            }

                            else if (stripResidual[k] == minRes) {
                                if (minResj != k) {
                                    maxRes = stripResidual[k];
                                    minResk = k;
                                    break;
                                }
                            }
                        }
                        minRes = maxRes;
                        minResj = minResk;
                        continue;
                    }
                }

                else { //if box doesn't fit in strip, try next strip
                    maxRes = maxStripWidth + 1;
                    for (k = 0; k < stripResidual.size(); ++k) {
                        if (stripResidual[k] > minRes && stripResidual[k] < maxRes) {
                            maxRes = stripResidual[k];
                            minResk = k;
                        }
                        else if (stripResidual[k] == minRes) {
                            if (minResj != k) {
                                maxRes = stripResidual[k];
                                minResk = k;
                                break;
                            }
                        }
                    }
                    minRes = maxRes;
                    minResj = minResk;
                    continue;
                }
            }

            else if(strip[minResj].empty()){
                strip[minResj].push_back(boxDecrease[i]);
                strip[minResj].push_back(mates[boxDecrease[i]]);
                stripResidual[minResj] -= boxWidths[boxDecrease[i]][mates[boxDecrease[i]]];
                stripWidth[minResj].push_back(boxWidths[boxDecrease[i]][mates[boxDecrease[i]]]);
                x = 1;
            }

        } while (x == 0); //end while loop


    } //end for loop

    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            stripNumBoxes[i] = strip[i].size() / 2;
            ++numStrips;
        }
    }

    cout << "BFD: " << numStrips << " strips\n-----------------------\n";

    cout << "Strips BFD (Scores):\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strips BFD (boxWidths):\n";
    for(i = 0; i < stripWidth.size(); ++i){
        if(!stripWidth[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < stripWidth[i].size(); ++j){
                cout << stripWidth[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strip Widths BFD:\n";
    cout << "Strip\t#Boxes\tWidth\tResidual\n";
    for(i = 0; i < stripResidual.size(); ++i){
        if(stripResidual[i] != maxStripWidth) {
            cout << i << "\t" << stripNumBoxes[i] <<"\t" << maxStripWidth - stripResidual[i] << "\t" << stripResidual[i] << endl;
        }
    }
    cout << endl << endl;

}

void packStripsFFD(int numBox, int maxBoxWidth, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<vector<int> > &boxWidths){

    int i, j, mini;
    int min = 0;
    int max = maxBoxWidth;
    int numStrips = 0;
    vector<int> stripSum(numBox, 0);
    vector<vector<int> > strip(numBox);
    vector<int> boxDecrease;
    vector<vector<int> > stripWidth(numBox);
    vector<int> stripNumBoxes(numBox, 0);

    while(boxDecrease.size() < numBox -1) { //numBox -1, doesn't include dominating vertices
        for (i = 0; i < mates.size(); ++i) {
            if (boxWidths[i][mates[i]] > min && boxWidths[i][mates[i]] < max) { //what happens if two boxes have the same width?
                min = boxWidths[i][mates[i]];
                mini = i;
            }
        }
        boxDecrease.push_back(mini);
        max = min;
        min = 0;
    }

    /*cout << "Box decrease:\n";
    for(i = 0; i < boxDecrease.size(); ++i){
        cout << boxDecrease[i] << " ";
    }
    cout << endl;*/

    strip[0].push_back(boxDecrease[0]);
    strip[0].push_back(mates[boxDecrease[0]]);
    stripSum[0] += boxWidths[boxDecrease[0]][mates[boxDecrease[0]]];
    stripWidth[0].push_back(boxWidths[boxDecrease[0]][mates[boxDecrease[0]]]);


    for(j = 1; j < boxDecrease.size(); ++j){
        for(i = 0; i < strip.size(); ++i){
            if(!strip[i].empty()){
                if(stripSum[i] + boxWidths[boxDecrease[j]][mates[boxDecrease[j]]] <= maxStripWidth){
                    if(adjMatrix[strip[i].back()][boxDecrease[j]] == 1){
                        strip[i].push_back(boxDecrease[j]);
                        strip[i].push_back(mates[boxDecrease[j]]);
                        stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                        stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                        break;
                    }
                    else if (adjMatrix[strip[i].back()][mates[boxDecrease[j]]] == 1){
                        strip[i].push_back(mates[boxDecrease[j]]);
                        strip[i].push_back(boxDecrease[j]);
                        stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                        stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                        break;
                    }
                    else{
                        continue;
                    }
                }
                else{
                    continue;
                }
            }
            else if (strip[i].empty()){
                strip[i].push_back(boxDecrease[j]);
                strip[i].push_back(mates[boxDecrease[j]]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                break;
            }
        }
    }
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            stripNumBoxes[i] = strip[i].size() / 2;
            ++numStrips;
        }
    }

    cout << "FFD: " << numStrips << " strips\n-----------------------\n";

    cout << "Strips FFD (scores):\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strips FFD (boxWidths):\n";
    for(i = 0; i < stripWidth.size(); ++i){
        if(!stripWidth[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < stripWidth[i].size(); ++j){
                cout << stripWidth[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strip Widths FFD:\n";
    cout << "Strip\t#Boxes\tWidth\tResidual\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] !=0) {
            cout << i << "\t" << stripNumBoxes[i] << "\t" <<  stripSum[i] << "\t" << maxStripWidth - stripSum[i] << endl;
        }
    }
    cout << endl << endl;



}

void packStripsNFD(int numBox, int maxBoxWidth, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<vector<int> > &boxWidths){

    int i, j, mini;
    int min = 0;
    int max = maxBoxWidth;
    int numStrips = 0;
    vector<int> stripSum(numBox, 0);
    vector<vector<int> > strip(numBox);
    vector<int> boxDecrease;
    vector<vector<int> > stripWidth(numBox);
    vector<int> stripNumBoxes(numBox, 0);

    while(boxDecrease.size() < numBox -1) { //numBox -1, doesn't include dominating vertices
        for (i = 0; i < mates.size(); ++i) {
            if (boxWidths[i][mates[i]] > min && boxWidths[i][mates[i]] < max) { //what happens if two boxes have the same width?
                min = boxWidths[i][mates[i]];
                mini = i;
            }
        }
        boxDecrease.push_back(mini);
        max = min;
        min = 0;
    }

    strip[0].push_back(boxDecrease[0]);
    strip[0].push_back(mates[boxDecrease[0]]);
    stripSum[0] += boxWidths[boxDecrease[0]][mates[boxDecrease[0]]];
    stripWidth[0].push_back(boxWidths[boxDecrease[0]][mates[boxDecrease[0]]]);

    i = 0;
    for(j = 1; j < boxDecrease.size(); ++j){
        if(stripSum[i] + boxWidths[boxDecrease[j]][mates[boxDecrease[j]]] <= maxStripWidth){
            if(adjMatrix[strip[i].back()][boxDecrease[j]] == 1){
                strip[i].push_back(boxDecrease[j]);
                strip[i].push_back(mates[boxDecrease[j]]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                continue;
            }
            else if (adjMatrix[strip[i].back()][mates[boxDecrease[j]]] == 1){
                strip[i].push_back(mates[boxDecrease[j]]);
                strip[i].push_back(boxDecrease[j]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                continue;
            }
            else{
                ++i;
                strip[i].push_back(boxDecrease[j]);
                strip[i].push_back(mates[boxDecrease[j]]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                continue;

            }
        }
        else{
            ++i;
            strip[i].push_back(boxDecrease[j]);
            strip[i].push_back(mates[boxDecrease[j]]);
            stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
            stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
            continue;
        }
    }

    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            stripNumBoxes[i] = strip[i].size() / 2;
            ++numStrips;
        }
    }

    cout << "NFD: " << numStrips << " strips\n-----------------------\n";

    cout << "Strips NFD (scores):\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strips NFD (boxWidths):\n";
    for(i = 0; i < stripWidth.size(); ++i){
        if(!stripWidth[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < stripWidth[i].size(); ++j){
                cout << stripWidth[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strip Widths NFD:\n";
    cout << "Strip\t#Boxes\tWidth\tResidual\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] !=0) {
            cout << i << "\t" <<stripNumBoxes[i] << "\t" << stripSum[i] << "\t" << maxStripWidth - stripSum[i] << endl;
        }
    }
    cout << endl << endl;





}

void packStripsBFI(int numBox, int maxBoxWidth, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<vector<int> > &boxWidths){
    int i, j, k, mini;
    int min = 0;
    int max = maxBoxWidth;
    int numStrips = 0;
    vector<int> stripResidual(numBox, maxStripWidth);
    vector<vector<int> > strip(numBox);
    vector<int> boxDecrease; //contains the score number of the smallest score of the boxes in decreasing order
    vector<vector<int> > stripWidth(numBox);
    vector<int> stripNumBoxes(numBox, 0);
    /* i.e if mates 0-4 have boxwidth 536, mates 1-3 have BW 494, mates 2-5 have BW 940
     * then boxDecrease will contain the numbers: 2 0 1 (in that specific order)
     */

    while(boxDecrease.size() < numBox -1) { //numBox -1, doesn't include dominating vertices
        for (i = 0; i < mates.size(); ++i) {
            if (boxWidths[i][mates[i]] > min && boxWidths[i][mates[i]] < max) { //what happens if two boxes have the same width?
                max = boxWidths[i][mates[i]];
                mini = i;
            }
        }
        boxDecrease.push_back(mini);
        min = max;
        max = maxBoxWidth;
    }

    cout << "\nBox Increase:\n";
    for(i = 0; i < boxDecrease.size(); ++i){
        cout << boxDecrease[i] << " ";
    }
    cout << endl << endl;

    int minRes;
    int minResj;
    int minResk;
    int maxRes;
    int x;

    strip[0].push_back(boxDecrease[0]);
    strip[0].push_back(mates[boxDecrease[0]]);
    stripResidual[0] -= boxWidths[boxDecrease[0]][mates[boxDecrease[0]]];
    stripWidth[0].push_back(boxWidths[boxDecrease[0]][mates[boxDecrease[0]]]);


    for(i = 1; i < boxDecrease.size(); ++i){
        minRes = maxStripWidth + 1;
        for(j = 0; j < stripResidual.size(); ++j){
            if(stripResidual[j] < minRes){
                minRes = stripResidual[j];
                minResj = j;
            }
        }

        x = 0;
        do {
            if(!strip[minResj].empty()) {
                if (stripResidual[minResj] - boxWidths[boxDecrease[i]][mates[boxDecrease[i]]] >= 0) {
                    if (adjMatrix[strip[minResj].back()][boxDecrease[i]] == 1) {
                        strip[minResj].push_back(boxDecrease[i]);
                        strip[minResj].push_back(mates[boxDecrease[i]]);
                        stripResidual[minResj] -= boxWidths[boxDecrease[i]][mates[boxDecrease[i]]];
                        stripWidth[minResj].push_back(boxWidths[boxDecrease[i]][mates[boxDecrease[i]]]);
                        x = 1;
                        continue;
                    }

                    else if (adjMatrix[strip[minResj].back()][mates[boxDecrease[i]]] == 1) {
                        strip[minResj].push_back(mates[boxDecrease[i]]);
                        strip[minResj].push_back(boxDecrease[i]);
                        stripResidual[minResj] -= boxWidths[boxDecrease[i]][mates[boxDecrease[i]]];
                        stripWidth[minResj].push_back(boxWidths[boxDecrease[i]][mates[boxDecrease[i]]]);
                        x = 1;
                        continue;
                    }

                    else { //if neither score is adjacent, try next strip
                        maxRes = maxStripWidth + 1;
                        for (k = 0; k < stripResidual.size(); ++k) {
                            if (stripResidual[k] > minRes && stripResidual[k] < maxRes) {
                                maxRes = stripResidual[k];
                                minResk = k;
                            }

                            else if (stripResidual[k] == minRes) {
                                if (minResj != k) {
                                    maxRes = stripResidual[k];
                                    minResk = k;
                                    break;
                                }
                            }
                        }
                        minRes = maxRes;
                        minResj = minResk;
                        continue;
                    }
                }

                else { //if box doesn't fit in strip, try next strip
                    maxRes = maxStripWidth + 1;
                    for (k = 0; k < stripResidual.size(); ++k) {
                        if (stripResidual[k] > minRes && stripResidual[k] < maxRes) {
                            maxRes = stripResidual[k];
                            minResk = k;
                        }
                        else if (stripResidual[k] == minRes) {
                            if (minResj != k) {
                                maxRes = stripResidual[k];
                                minResk = k;
                                break;
                            }
                        }
                    }
                    minRes = maxRes;
                    minResj = minResk;
                    continue;
                }
            }

            else if(strip[minResj].empty()){
                strip[minResj].push_back(boxDecrease[i]);
                strip[minResj].push_back(mates[boxDecrease[i]]);
                stripResidual[minResj] -= boxWidths[boxDecrease[i]][mates[boxDecrease[i]]];
                stripWidth[minResj].push_back(boxWidths[boxDecrease[i]][mates[boxDecrease[i]]]);
                x = 1;
            }

        } while (x == 0); //end while loop


    } //end for loop

    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            stripNumBoxes[i] = strip[i].size() / 2;
            ++numStrips;
        }
    }

    cout << "BFI: " << numStrips << " strips\n-----------------------\n";

    cout << "Strips BFI (Scores):\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strips BFI (boxWidths):\n";
    for(i = 0; i < stripWidth.size(); ++i){
        if(!stripWidth[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < stripWidth[i].size(); ++j){
                cout << stripWidth[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strip Widths BFI:\n";
    cout << "Strip\t#Boxes\tWidth\tResidual\n";
    for(i = 0; i < stripResidual.size(); ++i){
        if(stripResidual[i] != maxStripWidth) {
            cout << i << "\t" << stripNumBoxes[i] << "\t" << maxStripWidth - stripResidual[i] << "\t" << stripResidual[i] << endl;
        }
    }
    cout << endl << endl;

}

void packStripsFFI(int numBox, int maxBoxWidth, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<vector<int> > &boxWidths){

    int i, j, mini;
    int min = 0;
    int max = maxBoxWidth;
    int numStrips = 0;
    vector<int> stripSum(numBox, 0);
    vector<vector<int> > strip(numBox);
    vector<int> boxDecrease;
    vector<vector<int> > stripWidth(numBox);
    vector<int> stripNumBoxes(numBox, 0);

    while(boxDecrease.size() < numBox -1) { //numBox -1, doesn't include dominating vertices
        for (i = 0; i < mates.size(); ++i) {
            if (boxWidths[i][mates[i]] > min && boxWidths[i][mates[i]] < max) { //what happens if two boxes have the same width?
                max = boxWidths[i][mates[i]];
                mini = i;
            }
        }
        boxDecrease.push_back(mini);
        min = max;
        max = maxBoxWidth;
    }

    /*cout << "\nBox Increase:\n";
    for(i = 0; i < boxDecrease.size(); ++i){
        cout << boxDecrease[i] << " ";
    }
    cout << endl << endl;*/

    strip[0].push_back(boxDecrease[0]);
    strip[0].push_back(mates[boxDecrease[0]]);
    stripSum[0] += boxWidths[boxDecrease[0]][mates[boxDecrease[0]]];
    stripWidth[0].push_back(boxWidths[boxDecrease[0]][mates[boxDecrease[0]]]);


    for(j = 1; j < boxDecrease.size(); ++j){
        for(i = 0; i < strip.size(); ++i){
            if(!strip[i].empty()){
                if(stripSum[i] + boxWidths[boxDecrease[j]][mates[boxDecrease[j]]] <= maxStripWidth){
                    if(adjMatrix[strip[i].back()][boxDecrease[j]] == 1){
                        strip[i].push_back(boxDecrease[j]);
                        strip[i].push_back(mates[boxDecrease[j]]);
                        stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                        stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                        break;
                    }
                    else if (adjMatrix[strip[i].back()][mates[boxDecrease[j]]] == 1){
                        strip[i].push_back(mates[boxDecrease[j]]);
                        strip[i].push_back(boxDecrease[j]);
                        stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                        stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                        break;
                    }
                    else{
                        continue;
                    }
                }
                else{
                    continue;
                }
            }
            else if (strip[i].empty()){
                strip[i].push_back(boxDecrease[j]);
                strip[i].push_back(mates[boxDecrease[j]]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                break;
            }
        }
    }
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            stripNumBoxes[i] = strip[i].size() / 2;
            ++numStrips;
        }
    }

    cout << "FFI: " << numStrips << " strips\n-----------------------\n";

    cout << "Strips FFI (scores):\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strips FFI (boxWidths):\n";
    for(i = 0; i < stripWidth.size(); ++i){
        if(!stripWidth[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < stripWidth[i].size(); ++j){
                cout << stripWidth[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strip Widths FFI:\n";
    cout << "Strip\t#Boxes\tWidth\tResidual\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] !=0) {
            cout << i << "\t" << stripNumBoxes[i] << "\t" << stripSum[i] << "\t" << maxStripWidth - stripSum[i] << endl;
        }
    }
    cout << endl << endl;



}

void packStripsNFI(int numBox, int maxBoxWidth, int maxStripWidth, vector<vector<int> > &adjMatrix, vector<int> &mates, vector<vector<int> > &boxWidths){

    int i, j, mini;
    int min = 0;
    int max = maxBoxWidth;
    int numStrips = 0;
    vector<int> stripSum(numBox, 0);
    vector<vector<int> > strip(numBox);
    vector<int> boxDecrease;
    vector<vector<int> > stripWidth(numBox);
    vector<int> stripNumBoxes(numBox, 0);

    while(boxDecrease.size() < numBox -1) { //numBox -1, doesn't include dominating vertices
        for (i = 0; i < mates.size(); ++i) {
            if (boxWidths[i][mates[i]] > min && boxWidths[i][mates[i]] < max) { //what happens if two boxes have the same width?
                max = boxWidths[i][mates[i]];
                mini = i;
            }
        }
        boxDecrease.push_back(mini);
        min = max;
        max = maxBoxWidth;
    }

    strip[0].push_back(boxDecrease[0]);
    strip[0].push_back(mates[boxDecrease[0]]);
    stripSum[0] += boxWidths[boxDecrease[0]][mates[boxDecrease[0]]];
    stripWidth[0].push_back(boxWidths[boxDecrease[0]][mates[boxDecrease[0]]]);

    i = 0;
    for(j = 1; j < boxDecrease.size(); ++j){
        if(stripSum[i] + boxWidths[boxDecrease[j]][mates[boxDecrease[j]]] <= maxStripWidth){
            if(adjMatrix[strip[i].back()][boxDecrease[j]] == 1){
                strip[i].push_back(boxDecrease[j]);
                strip[i].push_back(mates[boxDecrease[j]]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                continue;
            }
            else if (adjMatrix[strip[i].back()][mates[boxDecrease[j]]] == 1){
                strip[i].push_back(mates[boxDecrease[j]]);
                strip[i].push_back(boxDecrease[j]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                continue;
            }
            else{
                ++i;
                strip[i].push_back(boxDecrease[j]);
                strip[i].push_back(mates[boxDecrease[j]]);
                stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
                stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
                continue;

            }
        }
        else{
            ++i;
            strip[i].push_back(boxDecrease[j]);
            strip[i].push_back(mates[boxDecrease[j]]);
            stripSum[i] += boxWidths[boxDecrease[j]][mates[boxDecrease[j]]];
            stripWidth[i].push_back(boxWidths[boxDecrease[j]][mates[boxDecrease[j]]]);
            continue;
        }
    }

    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            stripNumBoxes[i] = strip[i].size() / 2;
            ++numStrips;
        }
    }

    cout << "NFI: " << numStrips << " strips\n-----------------------\n";

    cout << "Strips NFI (scores):\n";
    for(i = 0; i < strip.size(); ++i){
        if(!strip[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < strip[i].size(); ++j){
                cout << strip[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strips NFI (boxWidths):\n";
    for(i = 0; i < stripWidth.size(); ++i){
        if(!stripWidth[i].empty()){
            cout << "Strip " << i << ": ";
            for(j = 0; j < stripWidth[i].size(); ++j){
                cout << stripWidth[i][j] << " ";
            }
            cout << endl;
        }
    }
    cout << endl;

    cout << "Strip Widths NFI:\n";
    cout << "Strip\t#Boxes\tWidth\tResidual\n";
    for(i = 0; i < stripSum.size(); ++i){
        if(stripSum[i] !=0) {
            cout << i << "\t" << stripNumBoxes[i] << "\t" << stripSum[i] << "\t" << maxStripWidth - stripSum[i] << endl;
        }
    }
    cout << endl << endl;





}



























