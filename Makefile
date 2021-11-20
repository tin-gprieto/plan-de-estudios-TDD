CC=gcc
V= valgreen
GDB= gdb
CFLAGS= -std=c99 -g -O0
GFLAGS= -tui
WFLAGS= -Wall -Wconversion -Werror
VFLAGS= --leak-check=full --track-origins=yes --show-reachable=yes

LIB=toolbox/lib/*.o

EXE= carrera.exe
TEST_EXE= testing.exe

$(EXE): code/main.c code/materias.c $(LIB) 
	clear
	$(CC) code/main.c code/materias.c $(LIB) $(CFLAGS) $(WFLAGS) -o $(EXE)

exe: $(EXE)
	./$(EXE)

$(TEST_EXE): test/pruebas.c $(LIB) $(TDA)
	clear
	$(CC) test/pruebas.c $(LIB) $(TDA) $(CFLAGS) $(WFLAGS) -o $(TEST_EXE)

test: $(TEST_EXE)
	$(V) $(VFLAGS) ./$(TEST_EXE)

gdb: $(TEST_EXE)
	$(GDB) $(TEST_EXE) $(GFLAGS)