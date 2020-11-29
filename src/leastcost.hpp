#include <bits/stdc++.h>

using namespace std;

int LeastCost(int row, int col, vector< int>& Supply, vector< int>& Demand, vector<vector<int>>& Cost, vector<vector<int>>& Allocate) 
{
    int sum = 0, minx, miny;
    
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        Allocate[i][j] = 0;
    }
    while (1) {
        minx = miny = -1;
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
            if (Supply[i] && Demand[j] && (minx < 0 || Cost[i][j] < Cost[minx][miny])) {
                minx = i, miny = j;
            }
        }
        if (minx < 0) {
            break;
        }
        if (Supply[minx] > Demand[miny]) {
            Allocate[minx][miny] = Demand[miny];
            Supply[minx] -= Demand[miny];
            Demand[miny] = 0;
        } else {
            Allocate[minx][miny] = Supply[minx];
            Demand[miny] -= Supply[minx];
            Supply[minx] = 0;
        }
    }
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        sum += Allocate[i][j] * Cost[i][j];
    }
    return sum;
}