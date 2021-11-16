#include "materias.h"

typedef struct materia{
  char nombre[MAX_NOMBRE_MATERIA];
  char estado;
  int nota;
  lista_t* codigos_correlativas;
} materia_t;

//Formato de lectura
#define FORMATO_R "%[^;];%[^;];%c;%i;%[^\n]\n"
//                codigo;nombre;estado;nota;correlativas

//Formato de escritura
#define FORMATO_W "%s;%s;%c;%i;%s\n"