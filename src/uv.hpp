#include <bits/stdc++.h>

using namespace std;

#define EPSILON -1

void UVOptimize(int row, int col, vector<vector<int>>& Cost, vector<vector<int>>& Allocate) 
{
    int count = 0, U[row], V[col], Penalty[row][col], maxx = -1, maxy = -1;

    
    while(1) 
    {   
        count=0;
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) 
        {
            if (Allocate[i][j]) 
            {
                count++;
            }
        }
        if (count != row + col - 1) {

            cout << "\nDegenerate Basic Feasible Solution Encountered.\n\n";
            int i, j,minCost=INT_MAX,minpos[2] = {-1,-1};
            for(i=0;i<row;i++)
            {
                for(j=0;j<col;j++)
                {
                    if (!Allocate[i][j]) {
                        Allocate[i][j] = EPSILON;
                        if (findloop(row,col,Allocate,i,j) == -1) {
                            //goto out_of_loop;
                            if(Cost[i][j] <= minCost){
                                minpos[0]=i;
                                minpos[1]=j;
                                minCost = Cost[i][j];
                            }
                            Allocate[i][j] = 0;
                        }
                    
                        else {

                            Allocate[i][j] = 0;
                            continue;
                        }    
                    }   
                }
            }

            //out_of_loop:

            if (minpos[0]==-1) {
                return;  // cannot remove degeneracy
            }
            else{
                Allocate[minpos[0]][minpos[1]] = EPSILON;
            }
        }
    
        printf("Allocation Matrix\n\n");
        for(int i=0;i<row;i++)
        {
            for(int j=0;j<col;j++)
            {
                if (Allocate[i][j] != -1)
                    printf("%d\t",Allocate[i][j]);
                else
                    printf("eps\t");
            }
            printf("\n");
        }
        printf("\n\n");

        maxx=-1;
        maxy=-1;
        U[0] = 0;
        for (int i = 1; i < row; i++) 
        {
            U[i] = -1;
        }
        for (int i = 0; i < col; i++) 
        {
            V[i] = -1;
        }
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) 
        {
            Penalty[i][j] = 0;
        }
        int k=0;

        while(1)
        {
            for(int i=0;i<row;i++)
            {
                for(int j=0;j<col;j++)
                {
                    if(Allocate[i][j]!=0)
                    {
                        if(U[i]!=-1 && V[j]==-1)
                        {
                            V[j]=Cost[i][j]-U[i];
                            k++;
                        }
                        else if(U[i]==-1 && V[j]!=-1)
                        {
                            U[i]=Cost[i][j]-V[j];
                            k++;
                        }
                    }
                }
            }
            if(k==row+col-1)
            {
                break;
            }
        }
        for (int i = 0, j = 0; j < col || (j = 0, ++i) < row; j++) 
        {
            if (! Allocate[i][j]) 
            {
                Penalty[i][j] = U[i] + V[j] - Cost[i][j];
            }
            if (maxx == -1 || Penalty[i][j] > Penalty[maxx][maxy]) 
            {
                maxx = i, maxy = j;
            }
        }

         

        if (maxx == -1 || Penalty[maxx][maxy] <= 0) 
        {
            printf("Optimal Solution has been reached.\n");
            return;
        }
        else
        {
            /*
             for (int i = 0; i < row; i++) {
                 printf("U[%d]=%d ", i + 1, U[i]);
             }
             for (int i = 0; i < col; i++) {
                 printf("V[%d]=%d ", i + 1, V[i]);
             }
             puts("");
            
             for(int i=0;i<row;i++)
             {
                for(int j=0;j<col;j++)
                {
                    if (! Allocate[i][j]) 
                    {
                        printf("penalty %d %d %d\n",i,j,Penalty[i][j]);
                    }
                }
             }
             */

             findloop(row,col,Allocate,maxx,maxy);
             cout << "Chosen x: " << maxx << ", Chosen y: " << maxy << "\n\n";

             //printf("LOOP PATH OF %d , %d\n",maxx,maxy);
             int min=INT_MAX;
             for(int i=1;i<loopy;i=i+2)
             {
                if(min>Allocate[looppathx[i]][looppathy[i]])
                {
                    if(Allocate[looppathx[i]][looppathy[i]] == EPSILON)
                    {
                        Allocate[looppathx[i]][looppathy[i]] = 0;
                        min = 0;
                    }
                    else
                        min=Allocate[looppathx[i]][looppathy[i]];
                }
             }

             for(int i=0;i<loopy;i++)
             {
                if(i%2==0)
                {
                    if(Allocate[looppathx[i]][looppathy[i]] == EPSILON)
                        Allocate[looppathx[i]][looppathy[i]] = min;
                    else
                        Allocate[looppathx[i]][looppathy[i]] += min;
                    if(Allocate[looppathx[i]][looppathy[i]] == 0){
                        Allocate[looppathx[i]][looppathy[i]] = EPSILON;
                    }
                }
                else
                {
                    if(Allocate[looppathx[i]][looppathy[i]] == EPSILON)
                        Allocate[looppathx[i]][looppathy[i]] = 0;
                    else
                        Allocate[looppathx[i]][looppathy[i]] -= min;
                }
                //printf("%d %d \n",looppathx[i], looppathy[i]);
             }
        }
    }
}