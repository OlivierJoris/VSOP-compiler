CC=clang
CXX=clang++
LLVM_CONFIG=llvm-config
CXXFLAGS=-Wall $(shell ${LLVM_CONFIG} --cxxflags)
LDFLAGS=$(shell ${LLVM_CONFIG} --ldflags --system-libs --libs all)
PROGRAM=vsopc
DIR=./

all: $(PROGRAM)

$(PROGRAM): $(DIR)Class.o $(DIR)Args.o $(DIR)Block.o $(DIR)Field.o $(DIR)If.o $(DIR)Let.o $(DIR)Literals.o $(DIR)Method.o $(DIR)Operators.o $(DIR)While.o $(DIR)Formal.o $(DIR)AbstractSyntaxTree.o $(DIR)TypeChecking.o $(DIR)$(PROGRAM).yy.c $(DIR)$(PROGRAM).tab.c
	$(CXX) -Wno-deprecated $(LDFLAGS) -o $@ $^

$(DIR)$(PROGRAM).tab.c: $(DIR)$(PROGRAM).y
	bison -v -o $@ -d $^ -Wcounterexample

$(DIR)$(PROGRAM).yy.c: $(DIR)$(PROGRAM).l
	flex --nounput -o $@ $^

install-tools:
	sudo apt-get install flex
	sudo apt-get install bison	
	sudo apt-get install clang
	sudo apt-get install llvm-config

clean:
	rm -f $(DIR)*.yy.c
	rm -f $(DIR)*.o
	rm -f $(DIR)*.tab.h
	rm -f $(DIR)*.tab.c
	rm -f $(PROGRAM)
	clear