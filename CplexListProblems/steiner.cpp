#include "steiner.hpp"

typedef IloArray<IloIntVarArray> IntVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void steinerSolver() {
    IloEnv env;
    try {
        int numNodes = 7;
        int numEdges = 12;
        int l = 1;
        int r = 1;
        int numTerminal = 3;
        int terminalNodes[3] = {1, 4, 7};
        int edges[12][3] = { {1, 2, 10},
                            {1, 3, 1},
                            {2, 3, 1},
                            {2, 4, 10},
                            {3, 4, 12},
                            {4, 5, 1},
                            {2, 6, 1},
                            {3, 6, 1},
                            {5, 3, 1},
                            {7, 2, 3},
                            {5, 7, 1},
                            {5, 6, 1}

                            };

        IloModel steiner(env, "Problema de Steiner");

        IloCplex cplex(steiner);

        // Arestas de vertices de steiner no problema
		IloIntVarArray x(env, numEdges, 0, 1);

		IloExprArray nodeSteiner(env, numNodes);

		IloIntExprArray nodeSteinerNeighbor(env, numNodes);
        IloIntExpr nodeNeighbor2(env);
        IloIntExpr nodeNeighbor3p(env);

        IloIntExpr pathSum(env);


        for (int i = 0; i < numNodes; ++i) {
            nodeSteinerNeighbor[i] = IloIntExpr(env);
            nodeSteiner[i] = IloExpr(env);
        }

        // Contabiliza quais vertices fazem parte da arvore
        for (int i = 0; i < numEdges; ++i) {
            int node0 = edges[i][0] - 1;
            int node1 = edges[i][1] - 1;
            pathSum += x[i]*edges[i][2];
            nodeSteiner[node0] = (x[i] + nodeSteiner[node0] + IloAbs(x[i] - nodeSteiner[node0]))/2;
            nodeSteiner[node1] = (x[i] + nodeSteiner[node1] + IloAbs(x[i] - nodeSteiner[node1]))/2;
        }

        // Contabiliza o numero de vizinhos steiner
        for (int i = 0; i < numEdges; ++i) {
            int node0 = edges[i][0] - 1;
            int node1 = edges[i][1] - 1;
            nodeSteinerNeighbor[node0] += x[i];
            nodeSteinerNeighbor[node1] += x[i];
        }

        // Falta restrição para limitar o numero de vizinhos dos vertices steiner
        for (int i = 0; i < numNodes; ++i) {
            nodeNeighbor2 += nodeSteinerNeighbor[i] == 2;
            nodeNeighbor3p += nodeSteinerNeighbor[i] > 3;
        }
        steiner.add(nodeNeighbor2 <= l);
        steiner.add(nodeNeighbor3p <= r);

        // Restrição de 1 vizinho steiner por terminal
        for (int i = 0; i < numTerminal; ++i) {
            steiner.add(nodeSteinerNeighbor[terminalNodes[i]-1] == 1);
        }

        // Condição para arvore
        steiner.add(IloSum(x) + 1 == IloSum(nodeSteiner));

        steiner.add(IloMinimize(env, pathSum));

        if (cplex.solve())
            cout << "Soma do caminho " << cplex.getObjValue() << endl;

        IloNumArray sol(env, numEdges);
        cplex.getValues(sol, x);

        for (int i = 0; i < numEdges; ++i) {
            if ( sol[i] == 1)
                cout << "Aresta: "<< edges[i][0] <<", "<< edges[i][1] << endl;
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







