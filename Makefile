CC=gcc
V= valgrind
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

LIB=toolbox/code/interfaz/interfaz.c toolbox/code/tools/*.c
TDA=toolbox/TDAs/lista/lista.c toolbox/TDAs/hash/hash.c

EXE= carrera.exe
TEST_EXE= testing.exe

$(EXE): code/main.c code/materias.c $(LIB) $(TDA) 
	clear
	$(CC) code/main.c code/materias.c $(LIB) $(TDA) $(CFLAGS) $(WFLAGS) -o $(EXE)
exe: $(EXE)
	clear
	./$(EXE)

$(TEST_EXE): test/pruebas.c $(LIB) $(TDA)
	clear
	$(CC) test/pruebas.c $(LIB) $(TDA) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)
test: $(TEST_EXE)
	clear
	$(V) $(VFLAGS) ./$(TEST_EXE)

gdb: $(TEST_EXE)
	clear
	$(GDB) $(TEST_EXE) $(GFLAGS)