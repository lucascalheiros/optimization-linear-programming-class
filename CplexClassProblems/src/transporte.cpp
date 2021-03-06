#include "../headers/transporte.hpp"

using namespace std;

void transporteSolver() {
    IloEnv env;
    try {
        int numVar     = 9;
        int demand[3]  = {150, 70, 60}; //demanda dos depósitos 1, 2 e 3
        int offer[3]   = {120, 80, 80}; //oferta das fábricas 1, 2 e 3
        int cost[3][3] = {{8, 5, 6},    //custo de transporte da fábrica 1
                          {15, 10, 12}, //custo de transporte da fábrica 2
                          {3, 9, 10}};  //custo de transporte da fábrica 3

        IloModel transporte(env, "Problema do Transporte");

        IloCplex cplex(transporte);

		IloNumVarArray x(env, numVar, 0, IloInfinity);

        IloExpr costSum(env);

		for (int i = 0; i < numVar; i++) {
            int factory    = i/3;
		    int storehouse = i%3;
			costSum       += cost[factory][storehouse] * x[i];
        }

		transporte.add(IloMinimize(env, costSum)); //minimizando custo

        IloExprArray qtdDemands(env, 3);
        IloExprArray qtdOffers(env, 3);

        for (int i = 0; i < 3; i++) {
            qtdDemands[i] = IloExpr(env);
            qtdOffers[i]  = IloExpr(env);
        }

		for (int i = 0; i < numVar; i++) {
		    int factory             = i/3;
		    int storehouse          = i%3;
			qtdDemands[storehouse] += x[i];
			qtdOffers[factory]     += x[i];
        }

		for (int i = 0; i < 3; i++) {
            transporte.add(qtdDemands[i] == demand[i]); //demanda de cada depósito deve ser atendida
            transporte.add(qtdOffers[i] <= offer[i]);   //oferta de cada fábrica deve ser menor ou igual à demanda
        }

        if (cplex.solve())
            cout << "Custo ótimo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numVar);
		cplex.getValues(sol, x);

		for (int i = 0; i < numVar; i++) {
            int factory = i/3;
		    int storehouse = i%3;
            cout << "Fabrica " << factory+1 << " Deposito " << storehouse+1 << ": " << sol[i] << endl;

		}
    }
	catch (const IloException& e)
	{
		cerr << "Exception caught: " << e << endl;
	}
	catch (...)
	{
		cerr << "Unknown exception caught!" << endl;
	}

	env.end();
	return;
}

