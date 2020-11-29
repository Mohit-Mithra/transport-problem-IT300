#include <bits/stdc++.h>
#include "src/balance.hpp"
#include "src/vogel.hpp"
#include "src/leastcost.hpp"
#include "src/northwest.hpp"
#include "src/findloops.hpp"
#include "src/uv.hpp"
#include "src/steppingstone.hpp"

using namespace std;

int get_final_cost(int row, int col, vector<vector<int>>& Cost, vector<vector<int>>& Allocate);

int main() {

    int suppliers, destinations;
    string filename;

    cout << "-------------------------------------------------------\n\n";
    cout << "              Transportation Optimization            \n\n";
    cout << "-------------------------------------------------------\n\n";

    cout << "\nThis is a system to minimise Transportation Cost."<<endl;
    cout << "This can be modeled into a vaccine supply scenario as such:"<<endl<<endl;
    cout << "There will be a few vaccine suppliers who supply the vaccine and"<<endl;
    cout << "a few vaccine purchasers who purchase them and stores them."<<endl<<endl;
    cout << "Since there are many potential supplier and buyer locations,"<<endl;
    cout << "we have different costs for each pair of (supplier, purchaser)."<<endl<<endl;
    cout << "So, the objective is to try and meet the supplies with the demands "<<endl;
    cout << "with the least overall cost, so that it can be possible to effectively"<<endl;
    cout << "manage the COVID-19 Pandemic."<<endl<<endl;

    cout << "Enter the input filename: ";
    if (!(cin >> filename)) {  // read failed
        cout << "Invalid input, exiting\n";
        exit(EXIT_FAILURE);
    }

    ifstream file(filename);
    if (file.fail()) {
        cout << "Couldn't open file " << filename << "\n";
        exit(EXIT_FAILURE);
    }

    file >> suppliers >> destinations;
    if (file.fail()) {
        cout << "Please follow the correct input format in " << filename << "\n";
        exit(EXIT_FAILURE);
    }
    else if (suppliers <= 0 || destinations <= 0) {
        cout << "Please enter a positive number of suppliers and destinations in " << filename << "\n";
        exit(EXIT_FAILURE);
    }

    bool extra_supply = false, extra_demand = false;

    vector< int> Supply(suppliers);
    vector< int> Demand(destinations);
    vector<vector<int>> Cost(suppliers, vector<int>(destinations));
    vector<vector<int>> Allocate(suppliers + 1, vector<int>(destinations + 1));

    vector<int> Supply_unb(suppliers+1);
    vector<int> Demand_unb(destinations+1);
    vector<vector<int>> Cost_unb(suppliers+1, vector<int>(destinations+1));

    int total_supply = 0, total_demand = 0;

    for (int i = 0; i < suppliers; i++) {

        file >> Supply[i];
        if (file.fail()) {
            cout << "Please follow the correct input format in " << filename << "\n";
            exit(EXIT_FAILURE);
        }
        else if (Supply[i] < 0) {
            cout << "Please enter non negative supplies in " << filename << "\n";
            exit(EXIT_FAILURE);
        }
        total_supply += Supply[i];

    }

    for (int i = 0; i < destinations; i++) {

        file >> Demand[i];
        if (file.fail()) {
            cout << "Please follow the correct input format in " << filename << "\n";
            exit(EXIT_FAILURE);
        }
        else if (Demand[i] < 0) {
            cout << "Please enter non negative demands in " << filename << "\n";
            exit(EXIT_FAILURE);
        }
        total_demand += Demand[i];

    }


    for (int i = 0, j = 0; j < destinations || (j = 0, ++i) < suppliers; j++) {

        file >> Cost[i][j];
        if (file.fail()) {
            cout << "Please follow the correct input format in " << filename << "\n";
            exit(EXIT_FAILURE);
        }
        else if (Cost[i][j] < 0) {
            cout << "Please enter non negative costs in " << filename << "\n";
            exit(EXIT_FAILURE);
        }

    }

    if (total_supply != total_demand) 
    {
        cout << "\nUnbalanced Transportation Problem Found.\nTotal Supply: " << total_supply <<",  Total Demand: " << total_demand << "\n";
        cout << "Balancing it now...\n";

        if (balance_problem (suppliers, destinations, total_supply, total_demand, extra_supply, extra_demand, Demand_unb, Supply_unb, Cost_unb, Supply, Demand, Cost)) 
            cout << "\nBalancing performed successfully, Moving on\n";
        else {
            cout << "\nOops: Unbalanced transportation problem could not be balanced.\nTotal Supply: " << total_supply <<",  Total Demand: " << total_demand << "\n";
            exit(EXIT_FAILURE);
        }
            
    }

    int mincost, final_cost;

    if (extra_supply) {
           
        destinations++;

        // cout << "\ndestinations\n";
        Demand.assign(Demand_unb.begin(), Demand_unb.end());

        // for (int i = 0; i < destinations + 1; i++) 
        //     cout << Demand[i];
        // cout << "\nCosts\n";

        Cost.assign(Cost_unb.begin(), Cost_unb.end());
        // for (int i = 0; i < suppliers; i++) {
        //     for (int j = 0; j < destinations + 1; j++) {
        //         cout << Cost[i][j] << " ";
        //     }
        //     cout << "\n";
        // }
    }
    else if (extra_demand) {
        suppliers++;
        Supply.assign(Supply_unb.begin(), Supply_unb.end());
        Cost.assign(Cost_unb.begin(), Cost_unb.end());
    }
    
    cout << "\nChoose the desired method for finding initial feasible solution: \n";
    cout << "1. North West Corner Method\n2. Least Cost Method\n3. Vogel's Approximation Method\n";
    cout << "\nEnter your choice: ";

    int basic_ch;
    if (!(cin >> basic_ch) || (basic_ch < 1 || basic_ch > 3)) {

        cout << "\nInvalid option entered, exiting\n";
        exit(EXIT_FAILURE);

    }

    switch(basic_ch) {

        case 1:
            
            mincost = NorthWest(suppliers, destinations, Supply, Demand, Cost, Allocate);
            cout << "\nCost of transportation after North West Corner Method: " << mincost << "\n";

            break;

        case 2:

            mincost = LeastCost(suppliers, destinations, Supply, Demand, Cost, Allocate);
            cout << "\nCost of transportation after Least Cost Method: " << mincost << "\n";

            break;
            
        case 3:

            mincost = VogelApprox(suppliers, destinations, Supply, Demand, Cost, Allocate);
            cout << "\nCost of transportation after Vogel Approximation Method: " << mincost << "\n";

            break;

    }

    cout << "\nCurrent State of Allocation Matrix\n\n";

    for(int i=0;i<suppliers;i++)
    {
        for(int j=0;j<destinations;j++)
        {
            if (Allocate[i][j] == EPSILON)
                Allocate[i][j] = 0;
            
            printf("%d\t",Allocate[i][j]);
            
        }
        printf("\n");
    }


    cout << "\nChoose the desired method for finding optimized solution: \n";
    cout << "1. UV Optimization (MODI method)\n2. Stepping Stone Method\n";
    cout << "\nEnter your choice: ";

    int opt_ch;
    if (!(cin >> opt_ch) || (opt_ch < 1 || opt_ch > 2)) {

        cout << "\nInvalid option entered, exiting\n";
        exit(EXIT_FAILURE);

    }

    switch(opt_ch) {

        case 1:
            
            UVOptimize(suppliers,destinations,Cost,Allocate);
            cout << "\nResults of UV Optimization: \n\n";
            break;

        case 2:

            SteppingStoneOptimize(suppliers, destinations, Supply, Demand, Cost, Allocate, 0);
            cout << "\nResults of Stepping Stone Optimization: \n\n";
            break;

    }

    cout << "Final Allocation Matrix\n\n";

    for(int i=0;i<suppliers;i++)
    {
        for(int j=0;j<destinations;j++)
        {
            if (Allocate[i][j] == EPSILON)
                Allocate[i][j] = 0;
            
            cout << Allocate[i][j] << "\t";
            
        }
        cout << "\n";
    }

    final_cost = get_final_cost(suppliers, destinations, Cost, Allocate); 
    cout << "\nFinal Cost after Optimization " << final_cost << "\n";

    return 0;
}

int get_final_cost(int row, int col, vector<vector<int>>& Cost, vector<vector<int>>& Allocate)
{
	int final_cost=0;
	for(int i=0;i<row;i++)
	{
	    for(int j=0;j<col;j++)
	    {
	        final_cost+=Allocate[i][j]*Cost[i][j];
	    }
	}

	return final_cost;
}