#include "../headers/plantio.hpp"

using namespace std;

void plantioSolver() {

    int numFarms       = 3;
    int numPlantations = 3;

    int farmAreaMaxLimit[3]  = {400, 650, 350};   //área disponíevel para plantio em cada fazenda
    int farmWaterMaxLimit[3] = {1800, 2200, 950}; //água disponíevel em cada fazenda

    int plantationMaxLimit[3]    = {660, 880, 400};    //área máxima para plantio de milho, arroz e feijao
    float plantationWaterCost[3] = {5.5, 4, 3.5};      //água utilziada nas plantações de milho, arroz e feijao
    int plantationProfit[3]      = {5000, 4000, 1800}; //lucro por área de milho, arroz e feijao

    IloEnv env;
    try {
        IloModel plantio(env, "Problema do Plantio");

        IloCplex cplex(plantio);

        IloNumVarArray x(env, numFarms*numPlantations, 0, IloInfinity);

        IloExpr profit(env);

        for (int i = 0; i < numFarms*numPlantations; i++) {
			profit += plantationProfit[i%numPlantations] * x[i];
        }

		plantio.add(IloMaximize(env, profit)); //maximizando lucro

        IloExprArray farmWater(env, numFarms);
        IloExprArray farmArea(env, numFarms);
        IloExprArray plantationArea(env, numPlantations);

		for (int i = 0; i < numFarms; i++) {
			farmWater[i] = IloExpr(env);
			farmArea[i]  = IloExpr(env);
        }

		for (int i = 0; i < numPlantations; i++) {
			plantationArea[i] = IloExpr(env);
        }

		for (int i = 0; i < numFarms*numPlantations; i++) {
			farmWater[i/numFarms]            += plantationWaterCost[i%numPlantations] * x[i];
			farmArea[i/numFarms]             += x[i];
			plantationArea[i%numPlantations] += x[i];
        }


		for (int i = 0; i < numFarms; i++) {
			plantio.add(farmWater[i] <= farmWaterMaxLimit[i]); //água utilizada não pode exceder a quantidade disponívvel
			plantio.add(farmArea[i] <= farmAreaMaxLimit[i]);   //área de plantio não pode exceder a área máxima da fazenda
        }


		for (int i = 0; i < numPlantations; i++) {
			plantio.add(plantationArea[i] <= plantationMaxLimit[i]); //área de plantio não pode exceder a área máxima da cultura
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

        //proporção do plantio de milho nas 3 fazendas deve ser a mesma
        plantio.add(propCorn0 == propCorn1);
        plantio.add(propCorn1 == propCorn2);

        //proporção do plantio de arroz nas 3 fazendas deve ser a mesma
        plantio.add(propRice0 == propRice1);
        plantio.add(propRice1 == propRice2);

        //proporção do plantio de feijão nas 3 fazendas deve ser a mesma
        plantio.add(propBean0 == propBean1);
        plantio.add(propBean1 == propBean2);

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
