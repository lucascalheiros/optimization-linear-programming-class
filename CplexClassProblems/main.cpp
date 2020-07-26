#include <iostream>
#include "headers/dieta.hpp"
#include "headers/racao.hpp"
#include "headers/plantio.hpp"
#include "headers/tintas.hpp"
#include "headers/transporte.hpp"

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
	return 0;
}
