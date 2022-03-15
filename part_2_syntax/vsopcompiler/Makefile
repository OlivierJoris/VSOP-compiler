CC=g++
FLAGS=-std=c++17 -g -Wall -Wextra -pedantic -O3
PROGRAM=vsopc
DIR=./

all: $(PROGRAM)

$(PROGRAM): $(DIR)AbstractSyntaxTree.o $(DIR)$(PROGRAM).yy.c $(DIR)$(PROGRAM).tab.c
	$(CC) $(FLAGS) -o $@ $^

$(DIR)AbstractSyntaxTree.o: $(DIR)AbstractSyntaxTree.cpp
	$(CC) $(FLAGS) -c $^ -o $@

$(DIR)$(PROGRAM).tab.c: $(DIR)$(PROGRAM).y
	bison -o $@ -d $^

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