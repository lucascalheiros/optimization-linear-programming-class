#include "escalonamento.hpp"

using namespace std;

void escalonamentoSolver() {
    int numVar              = 7;
    int nurseDemandByDay[7] = {8, 9, 5, 8, 10, 7, 6};

    IloEnv env;
    try {
        IloModel escalonamento(env, "Problema do Escalonamento de Horários");

        IloCplex cplex(escalonamento);

        IloNumVarArray x(env, numVar, 0, IloInfinity);

        IloExpr hired(env);

        for (int i = 0; i < numVar; i++)
			hired += nurseDemandByDay[i] * x[i];

		escalonamento.add(IloMinimize(env, hired));

        IloExprArray nursesBeginToWork(env, numVar);

		for (int i = 0; i < numVar; i++) {
			nursesBeginToWork[i] = IloExpr(env);
        }

		for (int i = 0; i < numVar; i++) {
            nursesBeginToWork[i] += x[i % numVar]
                                  + x[(i + 1) % numVar]
                                  + x[(i + 2) % numVar]
                                  + x[(i + 3) % numVar]
                                  + x[(i + 4) % numVar];
        }


		for (int i = 0; i < numVar; i++) {
			escalonamento.add(nursesBeginToWork[i] >= nurseDemandByDay[i]);
        }

        if (cplex.solve())
            cout << "Escalonamento ótimo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numVar);
		cplex.getValues(sol, x);

		for (int i = 0; i < numVar; i++)
			cout << "Dia " << i + 1 << ":" << sol[i] << endl;

    } catch (const IloException& e) {
		cerr << "Exception caught: " << e << endl;
	} catch (...) {
		cerr << "Unknown exception caught!" << endl;
	}

	env.end();
	return;
}

