#include "../headers/topKclique.hpp"

typedef IloArray<IloIntVarArray> IntVarMatrix;
typedef IloArray<IloIntExprArray> IntExprMatrix;


using namespace std;


void topKcliqueSolver() {
    IloEnv env;
    try {
        int numEdges = 13; // Quantidade de vértices
        int numNodes = 10; // Quantidade de arestas
        int k        = 3;  // Quantidade de cliques

        // Arestas ij
        int edges[13][2] = {{1, 2},
                            {1, 3},
                            {1, 4},
                            {2, 3},
                            {3, 5},
                            {3, 6},
                            {4, 5},
                            {5, 6},
                            {5, 10},
                            {6, 7},
                            {6, 8},
                            {8, 9},
                            {9, 10}};

        IloModel clique(env, "Problem Top K Clique");

        IloCplex cplex(clique);

        // Array de vertices em cada clique
		IntVarMatrix x(env, k);

		// Vizinhos para cada vertice em cada clique
		IntExprMatrix nodeCliqueNeighbor(env, k);

		// Contador de vertices em cada clique
		IloIntExprArray totalKClique(env, k);

		// Contabiliza o numero de vertices na cobertura
		IloExprArray coverageNodes(env, numNodes);

		// Inicialização
        for (int i = 0; i < k; ++i) {
            x[i]                      = IloIntVarArray(env, numNodes, 0, 1);
            totalKClique[i]       = IloIntExpr(env);
            nodeCliqueNeighbor[i] = IloIntExprArray(env, numNodes);

            for (int j = 0; j < numNodes; ++j) {
                nodeCliqueNeighbor[i][j] = IloIntExpr(env);
            }
        }

		// Inicialização
        for (int i = 0; i < numNodes; ++i) {
            coverageNodes[i] = IloExpr(env);
        }

        // Contador de vertices vizinhos dentro de cada clique
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < numEdges; j++) {
                int node0 = edges[j][0] - 1;
                int node1 = edges[j][1] - 1;
                nodeCliqueNeighbor[i][node0] += x[i][node0] * x[i][node1];
                nodeCliqueNeighbor[i][node1] += x[i][node0] * x[i][node1];
            }
        }

        // Total de vertices em cada clique
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                totalKClique[i] += x[i][j];
            }
        }

        // Se o vertice pertence a clique então seu numero de vizinhos da clique deve ser o total da clique -1,
        // se nao o numero de vizinhos dentro da clique deve ser igual a 0
        for (int i = 0; i < k; ++i) {
            for (int j = 0; j < numNodes; ++j) {
                clique.add(nodeCliqueNeighbor[i][j] >= x[i][j] * (totalKClique[i] - 1));
            }
        }

        // Restrição de igualdade entre duas cliques
        for (int i = 0; i < k; ++i) {
            for (int j = i+1; j < k; ++j) {
                IloIntExpr cliqueEquality(env);
                for (int h = 0; h < numNodes; ++h) {
                    cliqueEquality += IloAbs(x[i][h] - x[j][h]);
                }
                clique.add(cliqueEquality != 0);
            }
        }

        // Intersecção entre cada clique
        for (int i = 0; i < k; ++i) {
            for (int h = 0; h < numNodes; ++h) {
                coverageNodes[h] = (x[i][h] + coverageNodes[h] + IloAbs(x[i][h] - coverageNodes[h]))/2;
            }
        }

        // Maximiza a quantidade de vertices na cobertura
        clique.add(IloMaximize(env, IloSum(coverageNodes)));

        if (cplex.solve())
            cout << "Tam cobertura maxima " << cplex.getObjValue() << endl;

		IloArray<IloNumArray> sol(env, k);
        for (int i = 0; i < k; ++i) {
            sol[i] = IloNumArray(env, numNodes);
            cplex.getValues(sol[i], x[i]);
            
            cout << "Clique " << i + 1 << ": {";
            for (int j = 0; j < numNodes; j++) {
                if (sol[i][j] == 1)
                    cout << " "  << j + 1;
            }
              cout  << " } " << endl;
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







