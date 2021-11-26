#include "materias.h"

typedef struct materia{
  char nombre[MAX_NOMBRE_MATERIA];
  char estado;
  int nota;
  lista_t* codigos_correlativas;
} materia_t;

typedef struct carrera{
  hash_t* materias;
} carrera_t;

//Formato de lectura
#define FORMATO_R "%[^;];%[^;];%c;%i;%[^\n]\n"
//                codigo;nombre;estado;nota;correlativas

//Formato de escritura
#define FORMATO_W "%s;%s;%c;%i;%s\n"

#define NOTA_MINIMA 4
const char* EXTENSION = "csv";

/*
Se crea en el heap la estructura completa de una materia.
Pre : -
Post: Puntero a la carrera o NULL en caso de error
*/
carrera_t* carrera_estructura_crear(){
  carrera_t* aux = malloc(sizeof(carrera_t));
  if(!aux)
    return NULL;
  return aux;
}

/*
Crea un archivo vacío dada una ruta de archivo
Pre : La ruta debe tener una extensión .csv y no ser vacía
Post: Se crea un archivo con la ruta pasada por parámetro si corresponde
*/
int archivo_crear(const char *ruta_archivo){
  if(ruta_cumple_extension(ruta_archivo, EXTENSION)){
    FILE* archivo = fopen(ruta_archivo, ESCRITURA);
    fclose(archivo);
    return EXITO;
  }
  return ERROR;
}

/*
Se crea una materia completa (con archivo y estructura)
Pre : La ruta debe tener una extensión .csv y no ser vacía
Post: Devuelve el puntero a la materia (o NULL en caso de error) 
      y se crea el archivo vacío
*/
carrera_t* carrera_crear(const char *ruta_archivo){
  int creacion_archivo = archivo_crear(ruta_archivo);
  if(creacion_archivo == ERROR) return NULL;
  return carrera_estructura_crear();
}

/*
Devuelve la cantidad de materias que tiene la carrera
Pre : -
Post: -
*/
int carrera_cantidad_materias(carrera_t* carrera){
  return 0;
}

/*
Se libera todo el espacio ocupado de la carrera en el heap
Pre : Carrera existente (puntero válido)
Post: Carrera destruida
*/
void carrera_destruir(carrera_t* carrera){
  if(carrera) free(carrera);
}

/*
Devuelve la lista de correlativas que corresponde en la inicialización
Pre : -
Post: Devuelve una lista de correlativas (vacía si no se recibió nada por parámetro)
*/
lista_t* materia_inicializar_correlativas(lista_t* correlativas){
  return correlativas ? correlativas : lista_crear();
}

/*
Evalua si las correlativas están todas aprobadas
Pre : Lista de correlativas no nula
Post: Verdadero si están todas aprobadas
*/
bool correlativas_estan_aprobadas(lista_t* correlativas){
  return lista_vacia(correlativas) ? true : false;
}

/*
Inicializa el estado de la materia según sus características
Pre : Nota válida y lista no nula
Post: Materia aprobada con nota > 4, 
      Materia habilitada si tiene sus correlativas aprobadas,
      Materia pendiente en caso de no tener nota o de tener correlativas desaprobadas.
*/
char materia_inicializar_estado(int nota, lista_t* correlativas){
  if(nota >= NOTA_MINIMA)
    return MATERIA_APROBADA;
  if(correlativas_estan_aprobadas(correlativas))
    return MATERIA_HABILITADA;
  return MATERIA_PENDIENTE;
}

/*
Evalua si los parámetros son válidos para crear una materia
Pre : - 
Verdadero si: nombre no vacío, 
              nota entre -1(MATERIA_SIN_NOTA) y 10, 
              lista de correlativas o NULL(en caso de no tenerlas)
*/
bool materia_cumple_condiciones (char nombre[MAX_NOMBRE_MATERIA], int nota){
  return strlen(nombre) > 0 && (MATERIA_SIN_NOTA <= nota && nota <= 10);
}

/*
Inicializa los valores de una carrera
Pre : Parámetros válidos según los criterios de materia_crear
Post: Materia inicializada con valores válidos
*/
void inicializar_materia(materia_t* materia, char nombre[MAX_NOMBRE_MATERIA], int nota, lista_t* correlativas){
  strcpy(materia->nombre, nombre);
  materia->nota = nota;
  materia->codigos_correlativas = materia_inicializar_correlativas(correlativas);
  materia->estado = materia_inicializar_estado(nota, correlativas);
}

/*
Crea una materia dadas sus características impresindibles 
Pre : nombre no vacío, 
      nota entre -1(MATERIA_SIN_NOTA) y 10, 
      lista de correlativas o NULL(en caso de no tenerlas)
Post: materia creada en el heap y completa
*/
materia_t* materia_crear(char nombre[MAX_NOMBRE_MATERIA], int nota, lista_t* correlativas){
  if(!materia_cumple_condiciones(nombre, nota)) return NULL;
  materia_t* materia_aux = malloc(sizeof(materia_t));
  if(!materia_aux) return NULL;
  inicializar_materia(materia_aux, nombre, nota, correlativas);
  return materia_aux;
}

/*
Libera el espacio ocupado por una materia
Pre : materia pasada por parámetro
Post: materia destruida sin ocupar espacio en el heap
*/
void materia_destruir(void* materia){
  materia_t* materia_aux = (materia_t*) materia;
  if(!materia_aux) return;
  lista_destruir(materia_aux->codigos_correlativas);
  free(materia_aux);
}