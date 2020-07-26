CPLEXFLAGS=-O3 -m64 -O -fPIC -fexceptions -DNDEBUG -DIL_STD -I/Users/macministant/Documents/dev/CPLEX_Studio129/cplex/include -I/Users/macministant/Documents/dev/CPLEX_Studio129/concert/include  -L/Users/macministant/Documents/dev/CPLEX_Studio129/cplex/lib/x86-64_osx/static_pic -lilocplex -lcplex -L/Users/macministant/Documents/dev/CPLEX_Studio129/concert/lib/x86-64_osx/static_pic -lconcert -lm -pthread -std=c++0x -ldl

CFLAGS=-std=c++11 -static-libstdc++ -Wall

all:main.o dieta.o racao.o plantio.o tintas.o transporte.o clique_maxima.o cobertura.o escalonamento.o facilidades.o fluxo_maximo.o frequencia.o mochila.o padroes.o
	g++ -o ./release/main.run ./compiled/main.o ./compiled/dieta.o ./compiled/racao.o ./compiled/plantio.o ./compiled/tintas.o ./compiled/transporte.o ./compiled/clique_maxima.o ./compiled/cobertura.o ./compiled/escalonamento.o ./compiled/facilidades.o ./compiled/fluxo_maximo.o ./compiled/frequencia.o ./compiled/mochila.o ./compiled/padroes.o $(CPLEXFLAGS) $(CFLAGS)

%.o: %.cpp %.hpp
	g++ -c $< -o $@ $(CFLAGS)

main.o: ./src/main.cpp
	g++ -c -o ./compiled/main.o ./src/main.cpp $(CPLEXFLAGS) $(CFLAGS)

dieta.o: ./src/dieta.cpp
	g++ -c -o ./compiled/dieta.o ./src/dieta.cpp $(CPLEXFLAGS) $(CFLAGS)

racao.o: ./src/racao.cpp
	g++ -c -o ./compiled/racao.o ./src/racao.cpp $(CPLEXFLAGS) $(CFLAGS)

plantio.o: ./src/plantio.cpp
	g++ -c -o ./compiled/plantio.o ./src/plantio.cpp $(CPLEXFLAGS) $(CFLAGS)

tintas.o: ./src/tintas.cpp
	g++ -c -o ./compiled/tintas.o ./src/tintas.cpp $(CPLEXFLAGS) $(CFLAGS)

transporte.o: ./src/transporte.cpp
	g++ -c -o ./compiled/transporte.o ./src/transporte.cpp $(CPLEXFLAGS) $(CFLAGS)

clique_maxima.o: ./src/clique_maxima.cpp
	g++ -c -o ./compiled/clique_maxima.o ./src/clique_maxima.cpp $(CPLEXFLAGS) $(CFLAGS)

cobertura.o: ./src/cobertura.cpp
	g++ -c -o ./compiled/cobertura.o ./src/cobertura.cpp $(CPLEXFLAGS) $(CFLAGS)

escalonamento.o: ./src/escalonamento.cpp
	g++ -c -o ./compiled/escalonamento.o ./src/escalonamento.cpp $(CPLEXFLAGS) $(CFLAGS)

facilidades.o: ./src/facilidades.cpp
	g++ -c -o ./compiled/facilidades.o ./src/facilidades.cpp $(CPLEXFLAGS) $(CFLAGS)

fluxo_maximo.o: ./src/fluxo_maximo.cpp
	g++ -c -o ./compiled/fluxo_maximo.o ./src/fluxo_maximo.cpp $(CPLEXFLAGS) $(CFLAGS)

frequencia.o: ./src/frequencia.cpp
	g++ -c -o ./compiled/frequencia.o ./src/frequencia.cpp $(CPLEXFLAGS) $(CFLAGS)

mochila.o: ./src/mochila.cpp
	g++ -c -o ./compiled/mochila.o ./src/mochila.cpp $(CPLEXFLAGS) $(CFLAGS)

padroes.o: ./src/padroes.cpp
	g++ -c -o ./compiled/padroes.o ./src/padroes.cpp $(CPLEXFLAGS) $(CFLAGS)

clean:
	rm -f ./compiled/*.o ./release/*.run
