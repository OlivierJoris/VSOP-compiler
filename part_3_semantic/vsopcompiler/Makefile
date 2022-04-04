CC=g++
FLAGS=-std=c++17 -g -Wall -Wextra -pedantic -O3
PROGRAM=vsopc
DIR=./

SOURCES=$(wildcard *.cpp)
OBJECTS=$(SOURCES:.cpp=.o)

all: $(PROGRAM)

$(PROGRAM): $(DIR)Class.o $(DIR)Args.o $(DIR)Block.o $(DIR)Field.o $(DIR)If.o $(DIR)Let.o $(DIR)Literals.o $(DIR)Method.o $(DIR)Operators.o $(DIR)While.o $(DIR)Formal.o $(DIR)AbstractSyntaxTree.o $(DIR)TypeChecking.o $(DIR)$(PROGRAM).yy.c $(DIR)$(PROGRAM).tab.c
	$(CC) $(FLAGS) -o $@ $^

$(DIR)Class.o: $(DIR)Class.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Args.o: $(DIR)Args.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Block.o: $(DIR)Block.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Field.o: $(DIR)Field.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)If.o: $(DIR)If.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Let.o: $(DIR)Let.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Literals.o: $(DIR)Literals.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Method.o: $(DIR)Method.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Operators.o: $(DIR)Operators.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)While.o: $(DIR)While.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)Formal.o: $(DIR)Formal.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)AbstractSyntaxTree.o: $(DIR)AbstractSyntaxTree.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)TypeChecking.o: $(DIR)TypeChecking.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)$(PROGRAM).tab.c: $(DIR)$(PROGRAM).y
	bison -v -o $@ -d $^ -Wcounterexample

$(DIR)$(PROGRAM).yy.c: $(DIR)$(PROGRAM).l
	flex --nounput -o $@ $^

install-tools:
	sudo apt-get install flex
	sudo apt-get install bison	

clean:
	rm -f $(DIR)*.yy.c
	rm -f $(DIR)*.o
	rm -f $(DIR)*.tab.h
	rm -f $(DIR)*.tab.c
	rm -f $(PROGRAM)
	clear