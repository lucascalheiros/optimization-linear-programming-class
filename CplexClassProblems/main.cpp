#include "racao.hpp"
#include "dieta.hpp"
#include "plantio.hpp"
#include "tintas.hpp"
#include "transporte.hpp"
#include "escalonamento.hpp"
#include "fluxo_maximo.hpp"

using namespace std;

int main()
{
    racaoSolver();
    dietaSolver();
	plantioSolver();
	tintasSolver();
	transporteSolver();
	escalonamentoSolver();
	fluxoSolver();
	return 0;
}
