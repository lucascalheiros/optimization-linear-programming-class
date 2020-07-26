#include <iostream>
#include "dieta.hpp"
#include "racao.hpp"
#include "plantio.hpp"
#include "tintas.hpp"

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
	return 0;
}
