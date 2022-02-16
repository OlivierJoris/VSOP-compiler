CC=g++
FLAGS=-std=c++17 -Wall -Wextra -O3
PROGRAM=vsopc
DIR=vsopcompiler/

all: $(PROGRAM)

$(PROGRAM): $(DIR)vsopc.o 
	$(CC) $(FLAGS) -o $@ $^

$(DIR)vsopc.o: $(DIR)vsopc.yy.c 
	$(CC) $(FLAGS) -c $< -o $@

$(DIR)vsopc.yy.c: $(DIR)vsopc.lex
	flex -o $@ $^

install-tools:
	sudo apt-get install flex	

clean:
	rm -f $(DIR)*.yy.c
	rm -f $(DIR)*.o
	rm $(PROGRAM)
	clear