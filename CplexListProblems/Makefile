CPLEXFLAGS=-O3 -m64 -O -fPIC -fexceptions -DNDEBUG -DIL_STD -I/Users/macministant/Documents/dev/CPLEX_Studio129/cplex/include -I/Users/macministant/Documents/dev/CPLEX_Studio129/concert/include  -L/Users/macministant/Documents/dev/CPLEX_Studio129/cplex/lib/x86-64_osx/static_pic -lilocplex -lcplex -L/Users/macministant/Documents/dev/CPLEX_Studio129/concert/lib/x86-64_osx/static_pic -lconcert -lm -pthread -std=c++0x -ldl

CFLAGS=-std=c++11 -static-libstdc++ -Wall

all:main.o coloracao.o steiner.o topKclique.o
	g++ -o ./release/main.run ./compiled/main.o ./compiled/coloracao.o ./compiled/steiner.o ./compiled/topKclique.o $(CPLEXFLAGS) $(CFLAGS)

%.o: %.cpp %.hpp
	g++ -c $< -o $@ $(CFLAGS)

main.o: ./src/main.cpp
	g++ -c -o ./compiled/main.o ./src/main.cpp $(CPLEXFLAGS) $(CFLAGS)

coloracao.o: ./src/coloracao.cpp
	g++ -c -o ./compiled/coloracao.o ./src/coloracao.cpp $(CPLEXFLAGS) $(CFLAGS)

steiner.o: ./src/steiner.cpp
	g++ -c -o ./compiled/steiner.o ./src/steiner.cpp $(CPLEXFLAGS) $(CFLAGS)

topKclique.o: ./src/topKclique.cpp
	g++ -c -o ./compiled/topKclique.o ./src/topKclique.cpp $(CPLEXFLAGS) $(CFLAGS)

clean:
	rm -f ./compiled/*.o ./release/*.run
