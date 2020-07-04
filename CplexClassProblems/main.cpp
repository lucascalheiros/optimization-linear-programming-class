#include "racao.hpp"
#include "dieta.hpp"

using namespace std;

int main()
{
racaoSolver();
dietaSolver();
//	// Criando o ambiente
//	IloEnv env;
//	try
//	{
//
//		// Entrada
//		int n_ing = 6;
//		int qnt_min_A = 9;
//		int qnt_min_C = 19;
//		int vit_A[6] = {1,0,2,2,1,2};
//		int vit_C[6] = {0,1,3,1,3,2};
//		int custo[6] = {35,30,60,50,27,22};
//
//		// Modelo
//		IloModel dieta(env, "Problema da Dieta");
//
//		// Inicializando o objeto cplex
//		IloCplex cplex(dieta);
//
//
//		// Variável de decisão
//		IloNumVarArray x(env, n_ing, 0, IloInfinity);
//
//		// Função Objetivo
//		IloExpr somatorio(env);
//		for(int i = 0; i < n_ing; i++)
//			somatorio += custo[i] * x[i];
//
//		dieta.add(IloMinimize(env, somatorio)); // min somatorio
//
//		// Restrição Vitamina A
//		IloExpr qnt_A(env);
//		for(int i = 0; i < n_ing; i++)
//			qnt_A += vit_A[i] * x[i];
//		dieta.add(qnt_A >= qnt_min_A);
//
//		// Restrição Vitamina C
//		IloExpr qnt_C(env);
//		for(int i = 0; i < n_ing; i++)
//			qnt_C += vit_C[i] * x[i];
//		dieta.add(qnt_C >= qnt_min_C);
//
//		// Rodando o algoritmo
//		if ( cplex.solve() )
//			cout << "Custo ótimo " << cplex.getObjValue() << endl;
//
//		// Obtendo a solução
//		IloNumArray sol(env,  n_ing);
//		cplex.getValues(sol, x);
//
//		// Imprimindo a solução
//		for(int i = 0; i < n_ing; i++)
//			cout << "Quantidade do ingrediente " << i+1 << ": " << sol[i] << endl;
//
//}
//	catch (const IloException& e)
//	{
//		cerr << "Exception caught: " << e << endl;
//	}
//	catch (...)
//	{
//		cerr << "Unknown exception caught!" << endl;
//	}
//
//	env.end();
	return 0;
}
