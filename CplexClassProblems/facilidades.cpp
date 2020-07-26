#include "headers/facilidades.hpp"

typedef IloArray<IloIntVarArray> IntVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void facilidadesSolver() {
    IloEnv env;
    try {
        int numClients = 5;
        int numWarehouse = 5;
        int costInstall[5] =    {5, 7, 5, 8, 3};
        int costClient[5][5] = {{1, 7, 2, 5, 3},
                                {4, 9, 2, 4, 2},
                                {4, 4, 7, 1, 4},
                                {2, 3, 3, 2, 4},
                                {4, 2, 5, 4, 7}};

        IloModel facilidades(env, "Problema das Facilidades");

        IloCplex cplex(facilidades);

        IntVarMatrix x(env, numWarehouse);
        IloIntVarArray y(env, numWarehouse, 0, 1);
        IloIntExpr cost(env);
        IloIntExprArray clientCheck(env, numClients);

        for (int i = 0; i < numWarehouse; ++i) {
            x[i] = IloIntVarArray(env, numClients, 0, 1);
        }

        for (int j = 0; j < numClients; ++j) {
            clientCheck[j] = IloIntExpr(env);
        }

        // Expressão para função de custo
        for (int i = 0; i < numWarehouse; ++i) {
            cost += costInstall[i] * y[i];
            for (int j = 0; j < numClients; ++j) {
                cost += costClient[i][j] * x[i][j];
            }
        }

        // Cria a expressão para verificar o atendimento dos clientes
        for (int i = 0; i < numWarehouse; ++i) {
            for (int j = 0; j < numClients; ++j) {
                clientCheck[j] += x[i][j];
            }
        }

        // Restrição: se ao menos um cliente é atendido em um deposito então e necessário que o deposito seja instalado
        for (int i = 0; i < numWarehouse; ++i) {
            for (int j = 0; j < numClients; ++j) {
                facilidades.add(y[i] >= x[i][j]);
            }
        }

        // Restrição de atendimento dos clientes
        for (int j = 0; j < numClients; ++j) {
            facilidades.add(clientCheck[j] == 1);
        }

       facilidades.add(IloMinimize(env, cost));


        if (cplex.solve())
            cout << "Custo minimo " << cplex.getObjValue() << endl;


        IloArray<IloNumArray> sol(env, numWarehouse);
		for (int i = 0; i < numWarehouse; ++i) {
            sol[i] = IloNumArray(env, numClients);
            cplex.getValues(sol[i], x[i]);
        }

        for (int i = 0; i < numWarehouse; ++i) {
            for (int j = 0; j < numClients; ++j) {
                cout << "Deposito: "<< i+1 << " Cliente: "<< j+1 << "  " << sol[i][j] << endl;
            }
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






