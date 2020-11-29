#include <bits/stdc++.h>

using namespace std;

bool balance_problem( int suppliers,  int destinations,  int &total_supply,  int &total_demand, bool &extra_supply, bool &extra_demand, vector<int>& Demand_unb, vector<int>& Supply_unb, vector<vector<int>>& Cost_unb, vector<int>& Supply, vector<int>& Demand, vector<vector<int>>& Cost) {

    if(total_supply > total_demand)
    {
        extra_supply = true;

        int residual = total_supply - total_demand;
        for(int i = 0; i < destinations; i++)
        {
            Demand_unb[i] = Demand[i];
        }
        Demand_unb[destinations] = residual;

        for (int i = 0; i < suppliers; i++)
        {
            Cost_unb[i][destinations] = 0;
            for (int j = 0; j < destinations; j++)
            {
                Cost_unb[i][j] = Cost[i][j];
            }
        }

        total_supply = 0, total_demand = 0;
        for (int i = 0; i < suppliers; i++) {
            total_supply += Supply[i];
        }
        for (int i = 0; i < destinations+1; i++) {
            total_demand += Demand_unb[i];
        }

    }

    else if(total_supply < total_demand)
    {
        extra_demand = true;

        int residual = total_demand - total_supply;
        for(int i = 0; i < suppliers; i++)
        {
            Supply_unb[i] = Supply[i];
        }
        Supply_unb[suppliers] = residual;

        for (int i = 0; i < destinations; i++)
        {
            Cost_unb[suppliers][i] = 0;
            for (int j = 0; j < suppliers; j++)
            {
                Cost_unb[j][i] = Cost[j][i];
            }
        }

        total_supply = 0, total_demand = 0;
        for (int i = 0; i < suppliers; i++) {
            total_supply += Supply[i];
        }
        for (int i = 0; i < destinations+1; i++) {
            total_demand += Demand_unb[i];
        }

    }

    return total_supply == total_demand;
        
}