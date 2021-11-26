#include "../code/lib/materias.c" /*Procedimientos internos de la librería*/
#include "../toolbox/code/tools/testing.h"

#define MAX_RUTA 50

void test_01_seCreaUnPlanDeEstudios(){
    const char ruta [MAX_RUTA] = "test/txt/vacio.csv";
    remove(ruta);
    carrera_t* carrera = carrera_crear(ruta);
    FILE* archivo = fopen(ruta, LECTURA);
    test_afirmar(carrera != NULL, "Se crea una carrera correctamente");
    test_afirmar(carrera_cantidad_materias(carrera) == 0, "La carrare creada no tiene materias");
    test_afirmar(archivo != NULL, "La carrera creada se guarda en un archivo");
    carrera_destruir(carrera);
    if(archivo) fclose(archivo);

}
void test_02_noSePuedeCrearUnPlanDeEstudiosSinRutaValida(){
    const char ruta_vacia [MAX_RUTA] = "";
    carrera_t* carrera = carrera_crear(ruta_vacia);
    test_afirmar(carrera == NULL, "La carrera no se puede crear sin una ruta");
    carrera_destruir(carrera);
}

void test_03_noSePuedeCrearUnPlanDeEstudiosConUnaRutaNoCsv(){
    const char ruta_incorrecta [MAX_RUTA] = "hola.txt";
    carrera_t* carrera = carrera_crear(ruta_incorrecta);
    test_afirmar(carrera == NULL, "La carrera no se puede crear sin una ruta");
    carrera_destruir(carrera);
}

void test_04_seCreaUnaMateriaSinNotaYSinCorrelativas(){
    char materia_nombre [MAX_NOMBRE_MATERIA] = "Materia";
    materia_t* materia = materia_crear(materia_nombre, MATERIA_SIN_NOTA, MATERIA_SIN_CORRELATIVAS);
    test_afirmar(materia != NULL, "Se crea una materia sin nota ni correlativas correctamente");
    test_afirmar(strcmp(materia->nombre, materia_nombre) == 0, "La materia contiene el nombre esperado");
    test_afirmar(materia->nota == MATERIA_SIN_NOTA, "La materia no tiene nota");
    test_afirmar(lista_vacia(materia->codigos_correlativas), "La materia no tiene correlativas");
    test_afirmar(materia->estado == MATERIA_HABILITADA, "La materia está habilitada (sin correlativas pendientes)");
    materia_destruir(materia);
}

void test_05_seCreaUnaMateriaConUnaNotaValida(){
    char materia_nombre [MAX_NOMBRE_MATERIA] = "Materia";
    int nota_valida = 8;
    materia_t* materia = materia_crear(materia_nombre, nota_valida, MATERIA_SIN_CORRELATIVAS);
    test_afirmar(materia->estado == MATERIA_APROBADA, "Se crea una materia que está aprobada (con nota válida)");
    test_afirmar(materia->nota == nota_valida, "La materia tiene la nota correspondiente");
    materia_destruir(materia);
}

void test_06_seCreaUnaMateriaConCorrelativas(){
    char materia_nombre [MAX_NOMBRE_MATERIA] = "Materia";
    lista_t* correlativas = lista_crear();
    const char* codigo = "123";
    lista_insertar(correlativas, (void*)codigo);
    materia_t* materia = materia_crear(materia_nombre, MATERIA_SIN_NOTA, correlativas);
    bool afirmacion = !lista_vacia(materia->codigos_correlativas) && strcmp((const char*)lista_elemento_en_posicion(materia->codigos_correlativas, 0), codigo) == 0;
    test_afirmar(afirmacion, "Se crea una materia con correlativas y contiene los códigos que corresponden");
    test_afirmar(materia->estado == MATERIA_PENDIENTE, "La materia está pendiente (con correlativas sin aprobar)");
    materia_destruir(materia);
}

void test_07_noSePuedeCrearUnaMateriaSinNombre(){
    char materia_nombre [MAX_NOMBRE_MATERIA] = "";
    materia_t* materia = materia_crear(materia_nombre, MATERIA_SIN_NOTA, MATERIA_SIN_CORRELATIVAS);
    test_afirmar(materia == NULL, "No se crea una materia sin nombre");
    materia_destruir(materia);
}

void test_08_noSePuedeCrearUnaMateriaConNotaNegativa(){
    char materia_nombre [MAX_NOMBRE_MATERIA] = "Materia";
    int nota_negativa=-4;
    materia_t* materia = materia_crear(materia_nombre, nota_negativa, MATERIA_SIN_CORRELATIVAS);
    test_afirmar(materia == NULL, "No se crea una materia con nota negativa");
    materia_destruir(materia);
}

void test_09_noSePuedeCrearUnaMateriaConNotaSuperiorA10(){
    char materia_nombre [MAX_NOMBRE_MATERIA] = "Materia";
    int nota_negativa=11;
    materia_t* materia = materia_crear(materia_nombre, nota_negativa, MATERIA_SIN_CORRELATIVAS);
    test_afirmar(materia == NULL, "No se crea una materia con nota superior a 10");
    materia_destruir(materia);
}

int main (){
    test_nuevo_grupo("TEST PLAN DE ESTUDIOS");
    test_nuevo_sub_grupo("Creación de una carrera");
    test_01_seCreaUnPlanDeEstudios();
    test_nuevo_sub_grupo("Creación inválida de una carrera");
    test_02_noSePuedeCrearUnPlanDeEstudiosSinRutaValida();
    test_03_noSePuedeCrearUnPlanDeEstudiosConUnaRutaNoCsv();
    test_nuevo_sub_grupo("Creación de una materia");
    test_04_seCreaUnaMateriaSinNotaYSinCorrelativas();
    test_05_seCreaUnaMateriaConUnaNotaValida();
    test_06_seCreaUnaMateriaConCorrelativas();
    test_nuevo_sub_grupo("Creación inválida de una materia");
    test_07_noSePuedeCrearUnaMateriaSinNombre();
    test_08_noSePuedeCrearUnaMateriaConNotaNegativa();
    test_09_noSePuedeCrearUnaMateriaConNotaSuperiorA10();
    test_mostrar_reporte();
}