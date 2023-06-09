#include <iostream>
#include <string>
#include <set>
#include <vector>

#include "../../../include/system/Sistema.h"

#include "../../../include/system/operaciones.h"

using namespace std;

/*
Nombre: Consultar curso
Actores: Usuario
Sinopsis: El caso de uso comienza cuando se desea obtener la información de un curso. Para ello,
el Sistema lista todos los nombres de los cursos y el Usuario selecciona uno. Luego, el
Sistema muestra el nombre del curso, la descripción, la dificultad (Principiante, Medio,
Avanzado), el nombre del idioma, el nombre del profesor y si se encuentra habilitado o
no. Si posee lecciones, se mostrarán en orden, con el tema y objetivo y, si la lección
posee ejercicios, se mostrará la descripción y la información particular para cada
ejercicio. Si el curso posee inscripciones, se listará el nombre de los estudiantes y la
fecha en la que se realizó la inscripción correspondiente.
*/

void Sistema::consultarCurso() {
    try
    {
            imprimirMensaje("Consultar curso");

        // Obtener colección de cursos
        set<string> nombresCursos = controladorCurso->listarNombreCursos();

        // Imprimir cursos disponibles
        if (nombresCursos.empty()) throw invalid_argument("No hay cursos disponibles");

        // Seleccionar curso
        string nombreCurso = seleccionarElemento(nombresCursos, "curso");
        if (nombreCurso.empty()) throw invalid_argument("No se ha seleccionado un curso");
        imprimirMensaje("Ha seleccionado el curso: " + nombreCurso);

        controladorCurso->seleccionarCurso(nombreCurso);

        cout << endl;

        // Obtener información del curso
        DTDataCurso* dtCurso = controladorCurso->mostrarDatosCurso();

        cout << *dtCurso << endl;
        cout << endl; 


        // Obtener inscripciones del curso
        set<DTInscripcion*> inscripciones = controladorCurso->mostrarInscripciones();
        
        if(!inscripciones.empty()){
            int i = 1;
            imprimirMensaje("Inscripciones del curso:");
            for(const DTInscripcion *inscripcion : inscripciones){
                cout << "-----Inscripción " << i << "-----" << endl;
                cout << *inscripcion << endl;
                delete inscripcion;
            }
        }else{
            imprimirMensaje("El curso no cuenta con inscripciones aún");
        }

        delete dtCurso;
        inscripciones.clear();
    }
    catch(const std::exception& e)
    {
        cancelarOperacion(e.what(), "consultar curso");
    }
    
}
