#ifndef CONTROLADORCURSO_H
#define CONTROLADORCURSO_H

#include "../interfaces/IControladorCurso.h"
#include "../classes/Idioma.h"

#include "../handlers/HandlerCurso.h"
#include "../handlers/HandlerUsuario.h"
#include "../handlers/HandlerIdioma.h"

#include "../enums/NIVEL.h"

using namespace std;

class ControladorCurso : public IControladorCurso
{
private:
    string nombreIdioma;
    string nombreCurso;

    // Datos del usuario actual
    Usuario *usuarioActual;
    string nicknameActual;
    string nicknameUsuarioActual;

    // Datos del curso actual
    Curso *cursoActual;
    string nombreCursoActual;
    string nicknameProfesorActual;
    string descripcionCursoActual;
    Nivel dificultadlCursoActual;
    Idioma *idiomaCursoActual;
    vector<Leccion *> leccionesCursoActual;
    set<Curso *> cursosPreviosCursoActual;

    // Datos de la leccion actual
    Leccion *leccionActual;

    // Datos del ejercicio actual
    Ejercicio *ejercicioActual;
    set<string> solC_actual;
    string solT_actual;
    set<Ejercicio *> ejerciciosLeccionActual;

    static ControladorCurso *instancia;

    // Colecion de cursos
    static HandlerCurso *coleccionCursos;

    // Coleccion de Usuarios
    static HandlerUsuario *coleccionUsuarios;

    // Coleccion de Idiomas
    static HandlerIdioma *coleccionIdiomas;

    ControladorCurso();

public:
    static IControladorCurso *getInstancia();

    set<string> obtenerCursos();
    string getNombreCurso();
    set<string> getDataCurso();
    string getNickProfesor();
    set<string> getNombresCursosPrevios();
    set<DTDataLeccion> getLecciones();
    void eliminarCurso(string nombre);
    void ingresarNicknameEstudiante(string nomEstudiante);
    set<string> listarCursosInscrip();
    set<string> mostrarCursosNoAprobados();
    set<string> mostrarEjerciciosNoAprobados();
    void seleccionarEjercicio(string nombreEjercicio);
    void ingresarSolucionCompletar(set<string> solC);
    void ingresarSolucionTraducir(string solT);
    void marcarEjercicioAprobado();
    void marcarEjercicioNoAprobado();
    void setLeccionActual(Leccion *leccion);
    vector<DTDataCursoAInscribir*> obtenerCursosDisponibles(set<string> cursosHabilitados);
    void realizarInscripcion(DTDate* fechaInscripcion);

    ~ControladorCurso(); // Destructor

    // Operaciones para Consulta Curso
    set<string> listarNombreCursos();
    DTDataCurso *mostrarDatosCurso();
    int cantidadDeLecciones();
    DTDataLeccion *mostrarDatosLeccion(int posicion);
    int cantidadDeEjerciciosLeccion(int posicion);
    set<DTEjercicio*> mostrarEjercicios(int posLeccion);
    set<DTInscripcion*> mostrarInscripciones();

    // Operaciones para Alta Curso
    void seleccionarProfesor(string nickname);
    void ingresarDatosCurso(string nombre, string descripcion, Nivel dificultad, string nickname);
    void seleccionarIdioma(string nombreIdioma);
    set<string> listarCursosHabilitados();
    void seleccionarCurso(string nombreCurso);
    void agregarLeccion(string tema, string objetivo);
    void agregarEjercicio(string nombre, string tipoEjercicio, string descEjercicio);
    void altaCurso(bool disponible);
    void agregarFraseTraducir(string fraseATraducir, string fraseTraducida);
    void agregarFraseCompletar(string fraseACompletar, vector<string> palabras);
    void agregarCursoPrevio(string nombreCurso);

    //Operacion agregarLeccion
    void agregarLeccionACurso(Leccion *leccion);

    //Operaciones para agregarEjercicio
    //Lista los temas de cada leccion en orden
    vector<string> listarLecciones(Curso *curso);
    void darDeAltaCompletar(string descripcion, string fraseACompletar, vector<string> palabrasFaltantes);
    void darDeAltaTraducir(string descripcion, string fraseATraducir, string fraseTraducida);

    // operaciones para habilitar curso
    set<string> listarCursosNoHabilitados();

    Ejercicio* getejActual();
    string getSolT_actual();
    set<string> getSolC_actual();
    void corregirEj();
};

#endif
