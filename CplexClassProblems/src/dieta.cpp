#include "../headers/dieta.hpp"

using namespace std;

void dietaSolver() {
    IloEnv env;
    try {
        int numVar       = 6;
        int vitALimitMin = 9;  //quantidade mínima de vitamina A necessária no composto
        int vitCLimitMin = 19; //quantidade mínima de vitamina C necessária no composto

        int vitA[6] = {1, 0, 2, 2, 1, 2};       //quantidade de cada ingrediente na vitamina A
        int vitC[6] = {0, 1, 3, 1, 3, 2};       //quantidade de cada ingrediente na vitamina C
        int cost[6] = {35, 30, 60, 50, 27, 22}; //custo de cada ingrediente

        IloModel dieta(env, "Problema da Dieta");

        IloCplex cplex(dieta);

		IloNumVarArray x(env, numVar, 0, IloInfinity);

        IloExpr costSum(env);

		for (int i = 0; i < numVar; i++)
			costSum += cost[i] * x[i];

		dieta.add(IloMinimize(env, costSum)); //minimizando custo

        IloExpr qtdVitA(env);
        IloExpr qtsVitC(env);

		for (int i = 0; i < numVar; i++) {
			qtdVitA += vitA[i] * x[i];
			qtsVitC += vitC[i] * x[i];
        }

		dieta.add(qtdVitA >= vitALimitMin); //quantidade de vitamina A no composto deve ser maior ou igual à mínima
		dieta.add(qtsVitC >= vitCLimitMin); //quantidade de vitamina C no composto deve ser maior ou igual à mínima

        if (cplex.solve())
            cout << "Custo ótimo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numVar);
		cplex.getValues(sol, x);

		for (int i = 0; i < numVar; i++)
			cout << "Tipo " << i + 1 << ": " << sol[i] << endl;
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
