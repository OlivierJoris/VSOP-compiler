CC=g++
FLAGS=-g -std=c++17 -Wall -Wextra
PROGRAM=vsopc

DIR=vsopcompiler/
SOURCES=$(DIR)/vsopc.cpp
OBJECTS=$(SOURCES:.cpp=.o)

all: $(PROGRAM)

$(PROGRAM): %c: $(DIR)%.yy.c $(OBJECTS)
	$(CC) -o $@ $(OBJECTS)

$(DIR)%.yy.c: $(DIR)%.lex
	flex -o $@ $^

%.o : %.cpp
	$(CC) $(FLAGS) -c $< -o $@

install-tools:
	sudo apt-get install flex	