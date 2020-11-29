#include <bits/stdc++.h>

using namespace std;

int loopx,loopy;
vector<int> looppathx(1000);
vector<int> looppathy(1000);
vector<vector<int>> haspath_vertical(1000, vector<int>(1000));
vector<vector<int>> haspath_horizontal(1000, vector<int>(1000));

vector<vector<pair<int, int>>> next_vertical(1000, vector<pair<int, int>>(1000));
vector<vector<pair<int, int>>> next_horizontal(1000, vector<pair<int, int>>(1000));

int lookv(int row, int col,vector<vector<int>>& Allocate,int x,int y,int x2,int y2);

int lookh(int row, int col, vector<vector<int>>& Allocate,int x,int y,int x2,int y2);

//vertical travelling for loop finding
int lookv(int row, int col,vector<vector<int>>& Allocate,int x,int y,int x2,int y2)
{
    if (haspath_vertical[x][y] != -1)
        return haspath_vertical[x][y];
    
    for(int i=0;i<row;i++)
    {
        if(i!=x && Allocate[i][y]!=0)
        {
            if (haspath_horizontal[i][y] == 0)
                continue;

            if((haspath_horizontal[i][y] == 1) || lookh(row,col,Allocate,i,y,x2,y2)==1)
            {
                haspath_vertical[x][y] = 1;
                next_vertical[x][y] = {i, y};
                return 1;
            }
        }
    }

    haspath_vertical[x][y] = 0;
    return 0;
}

//horizontal travelling for loop finding
int lookh(int row, int col, vector<vector<int>>& Allocate,int x,int y,int x2,int y2)
{
    if (haspath_horizontal[x][y] != -1)
        return haspath_horizontal[x][y];
    
    for(int i=0;i<col;i++)
    {
        if(i!=y && Allocate[x][i]!=0)
        {
            if(i==y2)
            {
                haspath_horizontal[x][y] = 1;
                next_horizontal[x][y] = {x, y2};
                next_vertical[x][y2] = {x2, y2};
                return 1;
            }
            else if (haspath_vertical[x][i] == 0)
                continue;
            else if((haspath_vertical[x][i] == 1) || lookv(row,col,Allocate,x,i,x2,y2)==1)
            {
                haspath_horizontal[x][y] = 1;
                next_horizontal[x][y] = {x, i};
                return 1;
            }
        }
    }
    
    haspath_horizontal[x][y] = 0;
    return 0;
}

//to find the loop of x,y
int findloop(int row, int col, vector<vector<int>>& Allocate,int x,int y)
{

    loopx = 1;
    loopy = 1;

    fill(haspath_horizontal.begin(), haspath_horizontal.end(), vector<int>(1000, -1));
    fill(haspath_vertical.begin(), haspath_vertical.end(), vector<int>(1000, -1));
    
    fill(next_vertical.begin(), next_vertical.end(), vector<pair<int, int>>(1000));
    fill(next_horizontal.begin(), next_horizontal.end(), vector<pair<int, int>>(1000));

    looppathx[0] = x;
    looppathy[0] = y;

    if (lookh(row,col,Allocate,x,y,x,y) == 0)
    {
        // printf("No path exists\n");
        return -1;
    }
    else
    {
        //printf("path found\n");

        int i = 1, curr_x = x, curr_y = y;
        do {
            
            if (i % 2 == 1) {
                looppathx[i] = next_horizontal[curr_x][curr_y].first;
                looppathy[i] = next_horizontal[curr_x][curr_y].second;
            }

            else {
                looppathx[i] = next_vertical[curr_x][curr_y].first;
                looppathy[i] = next_vertical[curr_x][curr_y].second;
            }

            curr_x = looppathx[i];
            curr_y = looppathy[i];
            // cout << "\nnext_x: " << looppathx[i] << " next_y: " << looppathy[i] << "\n";
            i++;
            loopx++;
            loopy++;

        } while (curr_x != x || curr_y != y);

        loopx--;
        loopy--;

        return 1;
    }
}