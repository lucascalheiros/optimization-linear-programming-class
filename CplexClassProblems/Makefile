CPLEXFLAGS=-O3 -m64 -O -fPIC -fexceptions -DNDEBUG -DIL_STD -I/Users/macministant/Documents/dev/CPLEX_Studio129/cplex/include -I/Users/macministant/Documents/dev/CPLEX_Studio129/concert/include  -L/Users/macministant/Documents/dev/CPLEX_Studio129/cplex/lib/x86-64_osx/static_pic -lilocplex -lcplex -L/Users/macministant/Documents/dev/CPLEX_Studio129/concert/lib/x86-64_osx/static_pic -lconcert -lm -pthread -std=c++0x -ldl

CFLAGS=-std=c++11 -static-libstdc++ -Wall

all:main.o dieta.o racao.o
	g++ -o ./release/main.run ./compiled/main.o ./compiled/dieta.o ./compiled/racao.o $(CPLEXFLAGS) $(CFLAGS)

%.o: %.cpp %.hpp
	g++ -c $< -o $@ $(CFLAGS)

main.o: main.cpp
	g++ -c -o ./compiled/main.o main.cpp $(CPLEXFLAGS) $(CFLAGS)

dieta.o: dieta.cpp
	g++ -c -o ./compiled/dieta.o dieta.cpp $(CPLEXFLAGS) $(CFLAGS)

racao.o: dieta.cpp
	g++ -c -o ./compiled/racao.o racao.cpp $(CPLEXFLAGS) $(CFLAGS)

clean:
	rm -f ./compiled/*.o ./release/*.run
