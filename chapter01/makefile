chapter01 : A.o B.o Bind.o
	g++ -o chapter01 A.o B.o Bind.o main.cc

A.o 	: include/A.h src/A.cc
	g++ -c include/A.h src/A.cc

B.o 	: include/B.h src/B.cc
	g++ -c include/B.h src/B.cc

Bind.o 	: A.o B.o include/Bind.h src/Bind.cc
	g++ -c include/Bind.h src/Bind.cc