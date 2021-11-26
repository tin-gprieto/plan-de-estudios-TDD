#ifndef __MATERIAS_H__
#define __MATERIAS_H__

#include "../../toolbox/code/interfaz/interfaz.h"
#include "../../toolbox/code/tools/tools.h"
#include "../../toolbox/code/TDAs/lista/lista.h"
#include "../../toolbox/code/TDAs/hash/hash.h"

#define MAX_NOMBRE_MATERIA 30

#define MATERIA_SIN_CORRELATIVAS NULL
#define MATERIA_SIN_NOTA -1

#define MATERIA_APROBADA 'A'
#define MATERIA_CURSADA 'C'
#define MATERIA_HABILITADA 'H'
#define MATERIA_PENDIENTE 'P'

typedef struct materia materia_t;

typedef struct carrera carrera_t;

#endif /* __MATERIAS_H__ */