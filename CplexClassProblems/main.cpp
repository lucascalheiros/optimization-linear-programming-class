#include <iostream>
#include "dieta.hpp"
#include "racao.hpp"
#include "plantio.hpp"
#include "tintas.hpp"
#include "transporte.hpp"

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
