#include "headers/mochila.hpp"

typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void mochilaSolver() {
    IloEnv env;
    try {
        int weightMax = 12;
        int numItems = 8;
        int items[8][2] = { {10, 2},
                            {3, 1},
                            {6, 2},
                            {8, 3},
                            {15, 7},
                            {20, 8},
                            {9, 5},
                            {10, 6}
                                };

        IloModel mochila(env, "Problema da Mochila");

        IloCplex cplex(mochila);

		IloIntVarArray x(env, numItems, 0, 1);
		IloExpr profit(env);
		IloExpr weight(env);

        for (int i = 0; i < numItems; ++i) {
            profit += x[i]*items[i][0];
            weight += x[i]*items[i][1];
        }

        mochila.add(IloMaximize(env, profit));
        mochila.add(weight <= weightMax);

        if (cplex.solve())
            cout << "Lucro máximo" << cplex.getObjValue() << endl;

		IloNumArray sol(env, numItems);
        cplex.getValues(sol, x);

		for (int i = 0; i < numItems; i++) {
            cout << "Item preço:" << items[i][0] << " peso: "  << items[i][1] << " id: "<< i+1 << " sel: " << sol[i] << endl;

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




