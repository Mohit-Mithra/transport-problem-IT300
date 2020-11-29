#include <bits/stdc++.h>

using namespace std;

int NorthWest(int row, int col, vector< int>& Supply, vector< int>& Demand, vector<vector<int>>& Cost, vector<vector<int>>& Allocate) 
{
    int sum = 0;
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        Allocate[i][j] = 0;
    }

    for (int i = 0, j = 0; i < row && j < col;) {
        if (Supply[i] > Demand[j]) {
            Allocate[i][j] = Demand[j];
            Supply[i] -= Demand[j];
            Demand[j] = 0;
            j++;
        } else {
            Allocate[i][j] = Supply[i];
            Demand[j] -= Supply[i];
            Supply[i] = 0;
            i++;
        }
    }
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) {
        sum += Allocate[i][j] * Cost[i][j];
    }
    return sum;
}