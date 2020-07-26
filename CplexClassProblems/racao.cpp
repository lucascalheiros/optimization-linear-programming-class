#include "racao.hpp"

using namespace std;


void racaoSolver() {
    IloEnv env;
    try {
        int numVar     = 2;
        int meatLimit  = 10000; //carne disponível em quilos
        int grainLimit = 30000; //cereal disponível em quilos

        int meat[2]   = {1, 4};   //carne necessária para fabricação de "Ração AMGS" e "Ração RE"
        int grain[2]  = {5, 2};   //cereal necessário para fabricação de "Ração AMGS" e "Ração RE"
        int profit[2] = {11, 12}; //lucro de unidade de "Ração AMGS" e "Ração RE"

        string typeName[2] = {"Ração AMGS", "Ração RE"};

        IloModel racao(env, "Problema da Ração");

        IloCplex cplex(racao);

	IloNumVarArray x(env, numVar, 0, IloInfinity);

        IloExpr profitSum(env); //função objetivo

		for (int i = 0; i < numVar; i++)
			profitSum += profit[i] * x[i];

		racao.add(IloMaximize(env, profitSum)); //maximizando lucro
        IloExpr qtdMeat(env);
        IloExpr qtdGrain(env);

		for (int i = 0; i < numVar; i++) {
			qtdMeat  += meat[i] * x[i];
			qtdGrain += grain[i] * x[i];
        }

		racao.add(qtdGrain <= grainLimit); //quantidade de cereal utilziada no deve exceder a disponível
		racao.add(qtdMeat <= meatLimit);   //quantidade de carne utilziada no deve exceder a disponível

        if (cplex.solve())
            cout << "Lucro ótimo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numVar);
		cplex.getValues(sol, x);

		for (int i = 0; i < numVar; i++)
			cout << typeName[i] << ": " << sol[i] << endl;
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
