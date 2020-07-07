#include "tintas.hpp"

#define SEC 0
#define COR 1
#define SR 0
#define SN 1

using namespace std;

void tintasSolver() {
    IloEnv env;
    try {
        string varName[8] = {"SRsolA", "SRsolB", "SRcompSec", "SRcompCor", "SNsolA", "SNsolB", "SNcompSec", "SNcompCor"};
        int numVar = 8;
        int secCorSRMinLimit[2] = {250, 500};
        int secCorSNMinLimit[2] = {50, 125};
        int qtSR = 1000;
        int qtSN = 250;
        float secCorProp[4][2] = {  {0.3, 0.7}, // solA composition
                                    {0.6, 0.4}, // solB composition
                                    {1, 0},     // SEC
                                    {0, 1}};    // COR
        float cost[4] = {1.5, 1, 4, 6};

        IloModel tintas(env, "Problema das Tintas");

        IloCplex cplex(tintas);

		IloNumVarArray x(env, numVar, 0, IloInfinity);

        IloExpr costSum(env);

		for (int i = 0; i < numVar; i++)
			costSum += cost[i % 4] * x[i];

		tintas.add(IloMinimize(env, costSum));

        IloExprArray qtdSecCorSR(env, 2);
        IloExprArray qtdSecCorSN(env, 2);

		for (int i = 0; i < 2; i++) {
			qtdSecCorSR[i] = IloExpr(env);
			qtdSecCorSN[i] = IloExpr(env);
        }

        IloExpr qtdSN(env);
        IloExpr qtdSR(env);

		for (int i = 0; i < 4; i++) {
			qtdSR += x[i];
            qtdSN += x[i+4];
            qtdSecCorSR[SEC] += secCorProp[i][SEC] * x[i];
            qtdSecCorSR[COR] += secCorProp[i][COR] * x[i];
            qtdSecCorSN[SEC] += secCorProp[i][SEC] * x[i+4];
            qtdSecCorSN[COR] += secCorProp[i][COR] * x[i+4];
         }

		tintas.add(qtdSecCorSR[SEC] >= secCorSRMinLimit[SEC]);
		tintas.add(qtdSecCorSN[SEC] >= secCorSNMinLimit[SEC]);
		tintas.add(qtdSecCorSR[COR] >= secCorSRMinLimit[COR]);
		tintas.add(qtdSecCorSN[COR] >= secCorSNMinLimit[COR]);
		tintas.add(qtdSR == qtSR);
		tintas.add(qtdSN == qtSN);

        if (cplex.solve())
            cout << "Custo ótimo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numVar);
		cplex.getValues(sol, x);

		for (int i = 0; i < numVar; i++)
			cout << varName[i] << ": " << sol[i] << endl;


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
