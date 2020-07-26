#include "../headers/coloracao.hpp"

typedef IloArray<IloIntVarArray> IntVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void coloracaoSolver() {
    IloEnv env;
    try {
        int numNodes = 6;
        int numEdges = 8;
        int edges[8][2] = { {1, 2},
                            {1, 3},
                            {2, 3},
                            {2, 4},
                            {2, 6},
                            {3, 5},
                            {3, 6},
                            {4, 5}
                            };

        IloModel coloracao(env, "Problema de Coloração de arestas");

        IloCplex cplex(coloracao);

        // O número máximo de cores diferentes é o total de vertices
		IloIntVarArray x(env, numEdges, 1, numNodes);

        IloIntExpr colorSum(env);

        for (int i = 0; i < numEdges; ++i) {
            colorSum += x[i];
        }

        // Restrição de mesma cor, se as arestas forem vizinhas
        for (int i = 0; i < numEdges; ++i) {
            for (int j = 0; j < numEdges; ++j) {
                if (i != j) {
                    int y0 = edges[i][0];
                    int y1 = edges[i][1];
                    int x0 = edges[j][0];
                    int x1 = edges[j][1];
                    if (y0 == x0 || y0 == x1 || y1 == x0 || y1 == x1) {
                        coloracao.add(x[i] != x[j]);
                    }
                }
            }
        }

        // Minimiza a soma das cores
        coloracao.add(IloMinimize(env, colorSum));

        if (cplex.solve())
            cout << "Soma de cores " << cplex.getObjValue() << endl;

        IloNumArray sol(env, numEdges);
        cplex.getValues(sol, x);

        for (int i = 0; i < numEdges; ++i) {
            cout << "Aresta: "<< i + 1 << " Cor: " << sol[i] << endl;
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







