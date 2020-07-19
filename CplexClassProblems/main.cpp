#include "racao.hpp"
#include "dieta.hpp"
#include "plantio.hpp"
#include "tintas.hpp"
#include "transporte.hpp"
#include "escalonamento.hpp"
#include "fluxo_maximo.hpp"
#include "cobertura.hpp"
#include "mochila.hpp"

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
	coberturaSolver();
	mochilaSolver();
	return 0;
}
