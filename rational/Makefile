
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wall -pedantic -pedantic-errors -std=c++17
CPP = g++


main : Makefile   main.o bigint.o rational.o 
	$(CPP) $(Flags) -o main   main.o bigint.o rational.o 

main.o : Makefile   main.cpp   rational.h bigint.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


bigint.o : Makefile   bigint.cpp   bigint.h 
	$(CPP) -c $(Flags) bigint.cpp -o  bigint.o


rational.o : Makefile   rational.cpp   rational.h bigint.h 
	$(CPP) -c $(Flags) rational.cpp -o  rational.o


