#include <iostream>
#include "../headers/dieta.hpp"
#include "../headers/racao.hpp"
#include "../headers/plantio.hpp"
#include "../headers/tintas.hpp"
#include "../headers/transporte.hpp"
#include "../headers/clique_maxima.hpp"
#include "../headers/cobertura.hpp"
#include "../headers/escalonamento.hpp"
#include "../headers/facilidades.hpp"

using namespace std;

int main()
{
    cout << "DIETA PROBLEM ------\n\n";
    dietaSolver();
    
    cout << "\nRAÇÃO PROBLEM ------\n\n";
    racaoSolver();

    cout << "\nPLANTIO PROBLEM ------\n\n";
    plantioSolver();
    
    cout << "\nTINTAS PROBLEM ------\n\n";
	tintasSolver();

    cout << "\nTRANSPORTE PROBLEM ------\n\n";
	transporteSolver();

    cout << "\nCLIQUE MAXIMA PROBLEM ------\n\n";
    cliqueSolver();

    cout << "\nCOBERTURA PROBLEM ------\n\n";
    coberturaSolver();

    cout << "\nESCALONAMENTO PROBLEM ------\n\n";
    escalonamentoSolver();

    cout << "\nFACILIDADES PROBLEM ------\n\n";
    facilidadesSolver();
	return 0;
}
