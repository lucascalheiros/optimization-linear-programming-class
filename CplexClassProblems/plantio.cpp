#include "plantio.hpp"

using namespace std;

void plantioSolver() {

    int numFarms = 3;
    int numPlantations = 3;

    int farmAreaMaxLimit[3] = {400, 650, 350};
    int farmWaterMaxLimit[3] = {1800, 2200, 950};

    int plantationMaxLimit[3] = {660, 880, 400};
    float plantationWaterCost[3] = {5.5, 4, 3.5};
    int plantationProfit[3] = {5000, 4000, 1800};

    IloEnv env;
    try {
        IloModel plantio(env, "Problema do Plantio");

        IloCplex cplex(plantio);

        IloNumVarArray x(env, numFarms*numPlantations, 0, IloInfinity);

        IloExpr profit(env);

        for (int i = 0; i < numFarms*numPlantations; i++) {
			profit += plantationProfit[i%numPlantations] * x[i];
        }

		plantio.add(IloMaximize(env, profit));

        IloExprArray farmWater(env, numFarms);
        IloExprArray farmArea(env, numFarms);
        IloExprArray plantationArea(env, numPlantations);

		for (int i = 0; i < numFarms; i++) {
			farmWater[i] = IloExpr(env);
			farmArea[i] = IloExpr(env);
        }

		for (int i = 0; i < numPlantations; i++) {
			plantationArea[i] = IloExpr(env);
        }

		for (int i = 0; i < numFarms*numPlantations; i++) {
			farmWater[i/numFarms] += plantationWaterCost[i%numPlantations] * x[i];
			farmArea[i/numFarms] += x[i];
			plantationArea[i%numPlantations] += x[i];
        }


		for (int i = 0; i < numFarms; i++) {
			plantio.add(farmWater[i] <= farmWaterMaxLimit[i]);
			plantio.add(farmArea[i] <= farmAreaMaxLimit[i]);
        }


		for (int i = 0; i < numPlantations; i++) {
			plantio.add(plantationArea[i] <= plantationMaxLimit[i]);
        }


        for (int i = 0; i < numFarms*numPlantations; i++) {

        }

        IloExpr propCorn0 = x[0]/farmAreaMaxLimit[0];
        IloExpr propCorn1 = x[3]/farmAreaMaxLimit[1];
        IloExpr propCorn2 = x[6]/farmAreaMaxLimit[2];

        IloExpr propRice0 = x[1]/farmAreaMaxLimit[0];
        IloExpr propRice1 = x[4]/farmAreaMaxLimit[1];
        IloExpr propRice2 = x[7]/farmAreaMaxLimit[2];

        IloExpr propBean0 = x[2]/farmAreaMaxLimit[0];
        IloExpr propBean1 = x[5]/farmAreaMaxLimit[1];
        IloExpr propBean2 = x[8]/farmAreaMaxLimit[2];

        plantio.add(propCorn0 == propCorn1);
        plantio.add(propCorn2 == propCorn1);

        plantio.add(propRice0 == propRice1);
        plantio.add(propRice2 == propRice1);

        plantio.add(propBean0 == propBean1);
        plantio.add(propBean2 == propBean1);

        if (cplex.solve())
            cout << "Lucro ótimo " << cplex.getObjValue() << endl;

		IloNumArray sol(env, numFarms*numPlantations);
		cplex.getValues(sol, x);

		for (int i = 0; i < numFarms*numPlantations; i++)
			cout << "Fazenda " << i/numFarms + 1 <<" Plantio " << i%numPlantations + 1 << ": " << sol[i] << endl;


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
