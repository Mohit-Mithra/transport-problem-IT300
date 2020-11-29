#include <bits/stdc++.h>

using namespace std;

int VogelApprox(int row, int col, vector< int>& Supply, vector< int>& Demand, vector<vector<int>>& Cost, vector<vector<int>>& Allocate)
{

    int sum = 0, tsup = 0, tdem = 0, RowDiff[row], ColDiff[col];
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++)
    {
        Allocate[i][j] = 0;
    }

    for (int k = 0, n = row + col; k < n; k++)
    {
        // cout << "k: " << k << " n: " << n << "\n";
        fflush(stdout);
        int min1, min2, maxx = -1, maxy = -1;
        for (int i = 0; i < row; i++)
        {
            RowDiff[i] = -1;
            min1 = min2 = -1;
            for (int j = 0; Supply[i] && j < col; j++)
            {
                if (Demand[j])
                {
                    if (min1 == -1 || Cost[i][j] < min1)
                    {
                        min2 = min1;
                        min1 = Cost[i][j];
                    }
                    else if (min2 == -1 || Cost[i][j] < min2)
                    {
                        min2 = Cost[i][j];
                    }
                }
            }
            if (Supply[i] && min1 >= 0)
            {
                RowDiff[i] = min2 > 0 ? min2 - min1 : min1;
                if (maxx == -1 || RowDiff[i] > RowDiff[maxx])
                {
                    maxx = i;
                }
            }
        }
        
        for (int i = 0; i < col; i++)
        {
            ColDiff[i] = -1;
            min1 = min2 = -1;
            for (int j = 0; Demand[i] && j < row; j++)
            {
                if (Supply[j])
                {
                    if (min1 == -1 || Cost[j][i] < min1)
                    {
                        min2 = min1;
                        min1 = Cost[j][i];
                    }
                    else if (min2 == -1 || Cost[j][i] < min2)
                    {
                        min2 = Cost[j][i];
                    }
                }
            }
            if (Demand[i] && min1 >= 0)
            {
                ColDiff[i] = min2 > 0 ? min2 - min1 : min1;
                if (maxy == -1 || ColDiff[i] > ColDiff[maxy])
                {
                    maxy = i;
                }
            }
        }

        if (maxx < 0 || maxy < 0)
            break;
        
        if (RowDiff[maxx] > ColDiff[maxy])
        {
            maxy = -1;
            for (int i = 0; i < col; i++)
            {
                if (Demand[i] && (maxy == -1 || Cost[maxx][i] < Cost[maxx][maxy]))
                {
                    maxy = i;
                }
            }
        }
        else
        {
            maxx = -1;
            for (int i = 0; i < row; i++)
            {
                if (Supply[i] && (maxx == -1 || Cost[i][maxy] < Cost[maxx][maxy]))
                {
                    maxx = i;
                }
            }
        }
        
        if (maxx < 0 || maxy < 0)
            break;
        
        if (Supply[maxx] > Demand[maxy])
        {
            Allocate[maxx][maxy] = Demand[maxy];
            Supply[maxx] -= Demand[maxy];
            Demand[maxy] = 0;
        }
        else
        {
            Allocate[maxx][maxy] = Supply[maxx];
            Demand[maxy] -= Supply[maxx];
            Supply[maxx] = 0;
        }

    }

    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++)
    {
        sum += Allocate[i][j] * Cost[i][j];
    }
    return sum;
}
