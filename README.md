Programa Plan de Estudios
--------------------------

El programa de Plan estudios consiste en un gestor para un plan de estudios universitario. En él se pueden asignar las calificaciones de las materias, teniendo así un registro de las materias aprobadas, aquellas habilitadas para poder cursar según las correlatividades, y tambien el porcentaje realizado de la carrera junto con el promedio de la misma.

------------------------------------------------

## Funcionalidades

Para la utilización del programa se cuenta con un menú con opciones que determinará que tipo de función se le dará al mismo. Entre estas funciones se encuentran:

- Buscar una materia según su código (mostrando estado y calificación si correspondiera)

- Listar materias según estados

- Modificar la calificación de una materia (asignar calificación y optar entre estado aprobada o cursada)

## Estados

Para categorizar las materias y poder tener una disposición útil para aquel usuario que utilice el programa, se optó por la asignación de estados, aquellos son:

- **Aprobada**: Materia promocionada, sea de manera directa o con final. *1

- **Cursada**: Materia con cursada aprobada pero con la falta del final aprobado. *1

- **Habilitada**: Materia aún no cursada, pero que cuenta con todas sus correlativas aprobadas.

- **Pendiente**: Materia aún no cursada y tampoco habilitada.

*1 - Estas materias debe contar sí o sí con una calificación

## Formato de archivo

Tanto para buscar como para modificar materias, se deberá hacerlo a partir del código de la misma. Para ello hace falta hablar del formato en el que se debe disponer el archivo .txt que contenga el listado de todas las materias. Para ello, se debe utilizar un archivo de texto que contenga a todas las materias distanciadas por un "enter" y con el siguente formato: 


    [código];[nombre];[estado];[nota];[correlativas]


Las materias se contarán como válidas en el caso de que se cumplan los siguentes requisitos: 

    [estado] -> - A (Aprobada)
                - C (Cursada)
                - H (Habilitada)
                - P (Pendiente)
    
    [nota] -> (4 a 10) 
              o        
              -1 (en caso de no contar con calificación)
    
    [correlativas] ->   ;[código de correlativa 1]-[código de correlativa 2]-[...]-[código de correlativa n] 
                        o 
                        ;-1 (en caso de no contar con correlativas)

----------------------------------------------------------------

### Ideas a implementar

- Agregar/crear el archivo desde el mismo programa
- Gestión de materias optativas
- Simultaneidades con otra carrera (plan de estudios) 