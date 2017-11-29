# Makefile

# the C++ compiler
CXX     = g++
CXXVERSION = $(shell g++ --version | grep ^g++ | sed 's/^.* //g')

# options to pass to the compiler
CXXFLAGS = -O0 -g3

ifeq "$(CXXVERSION)" "4.6.3"
	CXXFLAGS += -std=c++0x
else
	CXXFLAGS += -std=c++11
endif

All: all
all: main

main:	main.cpp Formula.o BoolFormula.o Assignment.o BankAccount.o
	$(CXX) $(CXXFLAGS) main.cpp BoolFormula.o Formula.o Assignment.o BankAccount.o -o main

modelmain:	main.cpp ModelFormula.o BoolFormula.o Assignment.o ModelBankAccount.o
	$(CXX) $(CXXFLAGS) main.cpp BoolFormula.o ModelFormula.o Assignment.o ModelBankAccount.o -o modelmain

BoolFormula.o: BoolFormula.cpp BoolFormula.h Formula.h
	$(CXX) $(CXXFLAGS) -c BoolFormula.cpp

Formula.o: Formula.cpp Formula.h Assignment.h
	$(CXX) $(CXXFLAGS) -c Formula.cpp 

#ModelFormula.o: ModelFormula.cpp ModelFormula.h Assignment.h
#	$(CXX) $(CXXFLAGS) -c ModelFormula.cpp 

Assignment.o: Assignment.cpp Assignment.h
	$(CXX) $(CXXFLAGS) -c Assignment.cpp 

BankAccount.o: BankAccount.cpp BankAccount.h
	$(CXX) $(CXXFLAGS) -c BankAccount.cpp

#ModelBankAccount.o: ModelBankAccount.cpp ModelBankAccount.h
#	$(CXX) $(CXXFLAGS) -c ModelBankAccount.cpp

deepclean: 
	rm -f *~ *.o Main

clean:
	-rm -f *~ *.o 
	-rm -Rf Main.dSYM/*
	-rmdir Main.dSYM


