#include "../headers/padroes.hpp"

typedef IloArray<IloNumVarArray> NumVarMatrix;
typedef IloArray<IloExprArray> ExprMatrix;


using namespace std;


void padroesSolver() {
    IloEnv env;
    try {
        int numPatterns = 4;
        int canProfit = 50;
        int costBody = 50;
        int costHead = 3;
        int plate1Qtd = 200;
        int plate2Qtd = 90;
        int timeLimit = 400;
        int plates[4][3] = {{1, 7, 2}, // Corpo|Tampa|Tempo
                            {0, 9, 2},
                            {4, 4, 1},
                            {2, 3, 3} // Faz parte da placa de tipo 2
                            };

        IloModel padroes(env, "Problema dos Padroes");

        IloCplex cplex(padroes);

		IloIntVarArray x(env, numPatterns, 0, IloInfinity);
		IloIntVar y(env, 0, IloInfinity);
		IloIntExpr profit(env);
		IloIntExpr body(env);
		IloIntExpr head(env);
		IloIntExpr time(env);
        IloIntExpr cans(env);
        IloIntExpr plate1(env);
        IloIntExpr plate2(env);

        // Separa os tipos de placas do array
        for (int i = 0; i < 3; ++i) {
            plate1 += x[i];
        }
        plate2 += x[3];

        for (int i = 0; i < numPatterns; ++i) {
            body += x[i]*plates[i][0];
            head += x[i]*plates[i][1];
            time += x[i]*plates[i][2];
        }

        // Restringe a variavel das latas ao limite, ou do numero de corpos, ou do numero de tampas
        padroes.add(y <= body);
        padroes.add(y <= head/2);

        // Restrição de tempo
        padroes.add(time <= timeLimit);

        // Restrição de placas
        padroes.add(plate1 <= plate1Qtd);
        padroes.add(plate2 <= plate2Qtd);

        profit += y * canProfit - (body - y) * costBody - (head - y * 2) * costHead;

        padroes.add(IloMaximize(env, profit));

        if (cplex.solve())
            cout << "Lucro máximo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numPatterns);
        cplex.getValues(sol, x);

		for (int i = 0; i < numPatterns; i++) {
            cout << "Item id: "<< i+1 << " sel: " << sol[i] << endl;

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





