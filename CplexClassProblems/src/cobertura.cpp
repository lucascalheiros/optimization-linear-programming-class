#include "../headers/cobertura.hpp"

typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;

using namespace std;

void coberturaSolver() {
    IloEnv env;
    try {
        int cityNum = 8;

        //cidades adjacentes
        int cityAdj[8][8] = {{1, 1, 1, 0, 0, 0, 0, 0},
                                         {1, 1, 1, 1, 0, 0, 0, 0},
                                         {1, 1, 1, 0, 1, 1, 0, 0},
                                         {0, 1, 0, 1, 1, 0, 1, 0},
                                         {0, 0, 1, 1, 1, 0, 1, 0},
                                         {0, 0, 1, 0, 0, 1, 0, 1},
                                         {0, 0, 0, 1, 1, 0, 1, 1},
                                         {0, 0, 0, 0, 0, 1, 1, 1}};

        IloModel cobertura(env, "Problema da Cobertura");

        IloCplex cplex(cobertura);

		IloIntVarArray x(env, cityNum, 0, 1);
		IloExprArray schoolExpr(env, cityNum);
		IloExpr totalSchool(env);

        for (int i = 0; i < cityNum; ++i) {
            schoolExpr[i] = IloExpr(env);
        }

        for (int i = 0; i < cityNum; i++) {
            for (int j = 0; j < cityNum; j++) {
                if (cityAdj[i][j] == 1) {
                    schoolExpr[i] += x[j];
                }
            }
        }

        for (int i = 0; i < cityNum; i++) {
           totalSchool += x[i];
        }

        for (int i = 0; i < cityNum; i++) {
            cobertura.add(schoolExpr[i] >= 1); //pelo menos uma escola deve ser construída na vizinhança de uma cidade
        }

        cobertura.add(IloMinimize(env, totalSchool)); //minimizando número de escolas construídas


        if (cplex.solve())
            cout << "Cobertura " << cplex.getObjValue() << endl;

		IloNumArray sol(env, cityNum);
        cplex.getValues(sol, x);

		for (int i = 0; i < cityNum; i++) {
            cout << "Cidade " << i+1 << ": " << sol[i] << endl;

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



