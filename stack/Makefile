
# Automatically generated Makefile
# Makefile-generator programmed by Hans de Nivelle, 2002


Flags = -Wpedantic -pedantic-errors -std=c++17
CPP = g++


main : Makefile   tokenizer.o stack.o main.o 
	$(CPP) $(Flags) -o main   tokenizer.o stack.o main.o 

tokenizer.o : Makefile   tokenizer.cpp   tokenizer.h 
	$(CPP) -c $(Flags) tokenizer.cpp -o  tokenizer.o


stack.o : Makefile   stack.cpp   stack.h 
	$(CPP) -c $(Flags) stack.cpp -o  stack.o


main.o : Makefile   main.cpp   tokenizer.h stack.h 
	$(CPP) -c $(Flags) main.cpp -o  main.o


