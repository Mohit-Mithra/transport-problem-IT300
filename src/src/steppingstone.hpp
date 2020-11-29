#include <bits/stdc++.h>

using namespace std;

#define EPSILON -1

void SteppingStoneOptimize(int row, int col, vector< int>& Supply, vector< int> Demand, vector<vector<int>>& Cost, vector<vector<int>>& Allocate, int ctr) 
{
	double maxReduction = 0;
    int move[1000][2],leaving[2] = {-1,-1},movelen = 0;
    int count=0;
    for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) 
    {
        if (Allocate[i][j]) 
        {
            count++;
        }
    }
    
    if (count != row + col - 1) {

        if (ctr == 0) {
            cout << "\nDegenerate basic feasible encountered\n";
            ctr++;
        }
        int i, j;
        for(i=0;i<row;i++)
        {
            for(j=0;j<col;j++)
            {
                if (!Allocate[i][j]) {
                    Allocate[i][j] = EPSILON;
                    if (findloop(row,col,Allocate,i,j) == -1) {
                        goto out_of_loop;
                    }
                    
                    else {

                        Allocate[i][j] = 0;
                        continue;

                    }
                        
                }
            }
        }

        out_of_loop:

        if (i == row && j == col) {
            return;  // cannot remove degeneracy
        }

        
        // fprintf(stderr, "Error: Invalid Problem for Optimal Solution\n\
        // Number of Allocated Cell: %d\n", count);
        // exit(EXIT_FAILURE);
    }

    printf("\n\n");
    //printf("Reduction calculated for each unallocated (i,j):\n");
    int chosen_x, chosen_y;

    for(int r=0;r<row;r++)
    {
        for(int c=0;c<col;c++)
        {
            if(Allocate[r][c]){
                continue;
            }
            findloop(row,col,Allocate,r,c);

            double reduction = 0;
            double lowestQuantity = 2147483647;
            int leavingCandidate[2];
            int plus = 1;

            for(int i = 0;i<loopy;i++)
            {
                if(plus){
                    reduction += Cost[looppathx[i]][looppathy[i]];
                }
                else{
                    reduction -= Cost[looppathx[i]][looppathy[i]];
                    if(Allocate[looppathx[i]][looppathy[i]] < lowestQuantity){
                        leavingCandidate[0] = looppathx[i];
                        leavingCandidate[1] = looppathy[i];
                        lowestQuantity = Allocate[looppathx[i]][looppathy[i]];
                    }
                }
                plus = 1 - plus;
            }
            //printf("Reduction for %d,%d = %f\n",r,c,reduction);
            if (reduction < maxReduction){
                for(int i = 0;i<loopy;i++){
                    move[i][0] = looppathx[i];
                    move[i][1] = looppathy[i];
                }
                movelen = loopy;
                leaving[0] = leavingCandidate[0];
                leaving[1] = leavingCandidate[1];
                maxReduction = reduction;
                chosen_x = r;
                chosen_y = c;
            }

        }
    }

    if (!Allocate[chosen_x][chosen_y])
        cout << "\nChoose x: " << chosen_x << ", and y: " << chosen_y << "\n";
    else
        cout << "\nOptimal Solution Reached\n";

    if(movelen != 0 && leaving[0] != -1)
    {
        int q = Allocate[leaving[0]][leaving[1]];
        int plus = 1;

        if (q == EPSILON) {  // epsilon is changing position

            Allocate[leaving[0]][leaving[1]] = 0;
            Allocate[chosen_x][chosen_y] = EPSILON;
            
        }

        else {

            for(int i=0;i<movelen;i++){

                if (Allocate[move[i][0]][move[i][1]] == EPSILON)  // degeneracy being removed
                    Allocate[move[i][0]][move[i][1]] = q;
                else
                    Allocate[move[i][0]][move[i][1]] += plus ? q : -q;
                plus = 1 - plus;
            }

        }

        
        SteppingStoneOptimize(row,col,Supply,Demand,Cost,Allocate, ctr);
    }
}