#include "clique_maxima.hpp"

typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void cliqueSolver() {
    IloEnv env;
    try {
        int graphDim = 8;
        int graphAdj[8][8] = {   {0, 1, 1, 1, 0, 0, 0, 0},
                                {1, 0, 1, 1, 0, 0, 0, 0},
                                {1, 1, 0, 1, 1, 1, 0, 0},
                                {1, 1, 1, 0, 1, 0, 1, 0},
                                {0, 0, 1, 1, 0, 0, 1, 0},
                                {0, 0, 1, 0, 0, 0, 0, 1},
                                {0, 0, 0, 1, 1, 0, 0, 1},
                                {0, 0, 0, 0, 0, 1, 1, 0}
                                };

        IloModel clique(env, "Problema da Clique maxima");

        IloCplex cplex(clique);

		IloIntVarArray x(env, graphDim, 0, 1);
		IloIntExprArray edgeNode(env, graphDim);
		IloIntExpr totalClique(env);

        for (int i = 0; i < graphDim; ++i) {
            edgeNode[i] = IloIntExpr(env);
        }

        // Contador de arrestas para cada no dentro da clique
        for (int i = 0; i < graphDim; i++) {
            for (int j = i; j < graphDim; j++) {
                if (graphAdj[i][j] == 1) {
                    edgeNode[i] += x[j]*x[i]*graphAdj[i][j];
                    edgeNode[j] += x[j]*x[i]*graphAdj[i][j];
                }
            }
        }

        // Total de vertices na clique
        for (int i = 0; i < graphDim; i++) {
           totalClique += x[i];
        }

        // Se o nó pertence a clique então seu numero de arrestas deve ser o total da clique -1
        for (int i = 0; i < graphDim; i++) {
            clique.add(edgeNode[i] >= x[i]*(totalClique-1));
        }
        clique.add(IloMaximize(env, totalClique));


        if (cplex.solve())
            cout << "Tam clique maxima " << cplex.getObjValue() << endl;

		IloNumArray sol(env, graphDim);
        cplex.getValues(sol, x);

		for (int i = 0; i < graphDim; i++) {
            cout << "Vertice " << i+1 << ": " << sol[i] << endl;

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




