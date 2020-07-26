#include "../headers/frequencia.hpp"

typedef IloArray<IloIntVarArray> IntVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void frequenciaSolver() {
    IloEnv env;
    try {
        int numAntennas = 8;
        int radius[8] = {1, 1, 1, 4, 2, 1, 3, 4};
        int antennas[8][8] = {  {0, 1, 1, 2, 2, 2, 2, 3},
                                {1, 0, 1, 1, 4, 3, 4, 5},
                                {1, 1, 0, 3, 1, 1, 3, 2},
                                {2, 1, 3, 0, 1, 3, 1, 4},
                                {2, 4, 1, 1, 0, 3, 1, 8},
                                {2, 3, 1, 3, 3, 0, 7, 1},
                                {2, 4, 3, 1, 1, 7, 0, 1},
                                {3, 5, 2, 4, 8, 1, 1, 0}
                                };

        IloModel frequencia(env, "Problema de Frequencia");

        IloCplex cplex(frequencia);

        // O número máximo de frenquencias diferentes é o total de antenas
		IloIntVarArray x(env, numAntennas, 1, numAntennas);

		// A tarefa de encontrar um número mínimo de frequências é análoga a encontrar um somatorio mínimo de uma lista de frequências ordenadas
        IloIntExpr freqSum(env);

        for (int i = 0; i < numAntennas; ++i) {
            freqSum += x[i];
        }

        // Restrição de mesma frequência, se os raios se interceptam
        for (int i = 0; i < numAntennas; ++i) {
            for (int j = 0; j < numAntennas; ++j) {
                if (i != j && radius[i] >= antennas[i][j]) {
                    frequencia.add(x[i] != x[j]);
                }
            }
        }

        // Minimiza a soma das frequências
        frequencia.add(IloMinimize(env, freqSum));

        if (cplex.solve())
            cout << "Soma de frequencias " << cplex.getObjValue() << endl;

        IloNumArray sol(env, numAntennas);
        cplex.getValues(sol, x);

        int max = 0;
        // Verifica a frequência ordenada máxima
        for (int i = 0; i < numAntennas; ++i) {
            if (sol[i] > max) {
                max = sol[i];
            }
            cout << "Antena: "<< i + 1 << " frequencia: " << sol[i] << endl;
		}
		cout << "Num de frequencias = " << max << endl;
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







