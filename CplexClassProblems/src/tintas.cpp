#include "../headers/tintas.hpp"

#define SEC 0
#define COR 1
#define SR 0
#define SN 1

using namespace std;

void tintasSolver() {
    IloEnv env;
    try {
        int numVar              = 8;
        int secCorSRMinLimit[2] = {250, 500}; //quantidade de SEC e COR em 1000 litros de SR
        int secCorSNMinLimit[2] = {50, 125};  //quantidade de SEC e COR em 250 litros de SN
        int qtSR                = 1000;       //quantidade mínima a ser produzida da tinta SR
        int qtSN                = 250;        //quantidade mínima a ser produzida da tinta SN

        float secCorProp[4][2] = {{0.3, 0.7}, // proporção de SEC e COR na SolA
                                  {0.6, 0.4}, // proporção de SEC e COR na SolB
                                  {1, 0},     // SEC
                                  {0, 1}};    // COR

        float cost[4] = {1.5, 1, 4, 6}; //custo por litro de SolA, solB, SEC e COR

        string varName[8] = {"SRsolA", "SRsolB", "SRcompSec", "SRcompCor", "SNsolA", "SNsolB", "SNcompSec", "SNcompCor"};


        IloModel tintas(env, "Problema das Tintas");

        IloCplex cplex(tintas);

		IloNumVarArray x(env, numVar, 0, IloInfinity);

        IloExpr costSum(env);

		for (int i = 0; i < numVar; i++)
			costSum += cost[i % 4] * x[i];

		tintas.add(IloMinimize(env, costSum)); //minimizando custo

        IloExprArray qtdSecCorSR(env, 2);
        IloExprArray qtdSecCorSN(env, 2);

		for (int i = 0; i < 2; i++) {
			qtdSecCorSR[i] = IloExpr(env);
			qtdSecCorSN[i] = IloExpr(env);
        }

        IloExpr qtdSN(env);
        IloExpr qtdSR(env);

		for (int i = 0; i < 4; i++) {
			qtdSR            += x[i];
            qtdSN            += x[i+4];
            qtdSecCorSR[SEC] += secCorProp[i][SEC] * x[i];
            qtdSecCorSR[COR] += secCorProp[i][COR] * x[i];
            qtdSecCorSN[SEC] += secCorProp[i][SEC] * x[i+4];
            qtdSecCorSN[COR] += secCorProp[i][COR] * x[i+4];
         }

		tintas.add(qtdSecCorSR[SEC] >= secCorSRMinLimit[SEC]); //quantidade de  SEC usada em SR deve ser maior ou igual à mínima
		tintas.add(qtdSecCorSN[SEC] >= secCorSNMinLimit[SEC]); //quantidade de  SEC usada em SN deve ser maior ou igual à mínima
		tintas.add(qtdSecCorSR[COR] >= secCorSRMinLimit[COR]); //quantidade de  COR usada em SR deve ser maior ou igual à mínima
		tintas.add(qtdSecCorSN[COR] >= secCorSNMinLimit[COR]); //quantidade de  COR usada em SN deve ser maior ou igual à mínima

		tintas.add(qtdSR == qtSR); //quantidade de SR deve ser exatamnete igual à definida
		tintas.add(qtdSN == qtSN); //quantidade de SN deve ser exatamnete igual à definida

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
