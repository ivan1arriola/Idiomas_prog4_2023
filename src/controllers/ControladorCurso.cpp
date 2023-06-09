#include "../../include/controllers/ControladorCurso.h"
#include "../../include/interfaces/IControladorCurso.h"
#include "../../include/datatypes/DTDataCurso.h"

#include "../../include/classes/Curso/Curso.h"
#include "../../include/classes/Usuario/Profesor.h"

#include "../../include/handlers/HandlerCurso.h"
#include "../../include/handlers/HandlerUsuario.h"
#include "../../include/handlers/HandlerIdioma.h"
#include "../../include/system/operaciones.h"

#include "../../include/classes/Curso/Completar.h"
#include "../../include/classes/Curso/Curso.h"
#include "../../include/classes/Curso/Ejercicio.h"
#include "../../include/classes/Curso/Leccion.h"
#include "../../include/classes/Curso/Traducir.h"

#include <string>
#include <algorithm>
#include <vector>
#include <map>

using namespace std;

ControladorCurso *ControladorCurso::instancia = NULL;

HandlerCurso *ControladorCurso::coleccionCursos = NULL;
HandlerUsuario *ControladorCurso::coleccionUsuarios = NULL;
HandlerIdioma *ControladorCurso::coleccionIdiomas = NULL;

ControladorCurso::ControladorCurso()
{
    ControladorCurso::coleccionCursos = HandlerCurso::getInstancia();
    ControladorCurso::coleccionUsuarios = HandlerUsuario::getInstancia();
    ControladorCurso::coleccionIdiomas = HandlerIdioma::getInstancia();

    ControladorCurso::usuarioActual = NULL;
    ControladorCurso::nombreCursoActual = "";
    ControladorCurso::nicknameProfesorActual = "";
    ControladorCurso::descripcionCursoActual = "";
    ControladorCurso::dificultadlCursoActual = Nivel::PRICIPIANTE;
    ControladorCurso::idiomaCursoActual = NULL;
    ControladorCurso::leccionesCursoActual = vector<Leccion *>();
    ControladorCurso::cursosPreviosCursoActual = set<Curso *>();
    ControladorCurso::leccionActual = NULL;
    ControladorCurso::ejercicioActual = NULL;
    ControladorCurso::ejerciciosLeccionActual = set<Ejercicio *>();
}

ControladorCurso::~ControladorCurso()
{

    if (ControladorCurso::coleccionCursos != NULL)
    {
        ControladorCurso::coleccionCursos->deleteInstancia();
        ControladorCurso::coleccionCursos = NULL;
    }

    if (ControladorCurso::coleccionUsuarios != NULL)
    {
        ControladorCurso::coleccionUsuarios->deleteInstancia();
        ControladorCurso::coleccionUsuarios = NULL;
    }

    if (ControladorCurso::coleccionIdiomas != NULL)
    {
        ControladorCurso::coleccionIdiomas->deleteInstancia();
        ControladorCurso::coleccionIdiomas = NULL;
    }

    ControladorCurso::instancia = NULL;
}

IControladorCurso *ControladorCurso::getInstancia()
{
    if (instancia == NULL)
    {
        instancia = new ControladorCurso();
    }
    return instancia;
}

set<string> ControladorCurso::listarCursosHabilitados()
{

    HandlerCurso *h = HandlerCurso::getInstancia();
    map<string, Curso *> mapCursos = h->obtenerCursos();
    set<string> cursosDisponibles;
    string insertar;

    for (auto it = mapCursos.begin(); it != mapCursos.end(); ++it)
    {
        // Si el curso se encuentra disponible (habilitado) lo agregamos a la lista de cursos
        if (it->second->getDisponible())
        {
            insertar = it->second->getNombre();
            cursosDisponibles.insert(insertar);
        }
    }

    return cursosDisponibles;
}

void ControladorCurso::seleccionarIdioma(string nombreIdioma)
{
    if (coleccionIdiomas->existeIdioma(nombreIdioma)){
        this->idiomaCursoActual = coleccionIdiomas->obtenerIdioma(nombreIdioma);
        this->cursoActual ->setIdioma(this->idiomaCursoActual);}
    else
        throw invalid_argument("No existe el idioma");
}

void ControladorCurso::altaCurso(bool disponible)
{
    bool existeCurso = coleccionCursos->existeCurso(this->cursoActual->getNombre());
    if (!existeCurso)
    {
        Profesor* profesor = this->cursoActual->getProfesor();
        coleccionCursos->agregarCurso(this->cursoActual);
        profesor->agregarACursosDeProfesor(this->cursoActual);
        this->idiomaCursoActual->notificarSuscriptores(this->cursoActual->getNombre());
        this->cursoActual = NULL;


    } else {
        delete this->cursoActual;
        this->cursoActual = NULL;
        throw invalid_argument("Ya existe un curso con ese nombre");

    }   
}

set<string> ControladorCurso::obtenerCursos()
{
    HandlerCurso *h = HandlerCurso::getInstancia();
    map<string, Curso *> mapCursos = h->obtenerCursos();
    set<string> cursos;
    for (auto it = mapCursos.begin(); it != mapCursos.end(); ++it)
    {
        cursos.insert(it->second->getNombre());
    }
    // Implementación de la función obtenerCursos
    // Código para obtener la lista de cursos disponibles
    return cursos;
}

void ControladorCurso::setLeccionActual(Leccion *leccion)
{
    this->leccionActual = leccion;
}

string ControladorCurso::getNombreCurso()
{
    return nombreCurso;
}

set<string> ControladorCurso::getDataCurso()
{
    set<string> dataCurso;
    // Implementación de la función getDataCurso
    // Código para obtener los datos del curso seleccionado
    return dataCurso;
}

string ControladorCurso::getNickProfesor()
{
    // Implementación de la función getNickProfesor
    string nickProfesor;
    // Código para obtener el nick del profesor del curso seleccionado
    return nickProfesor;
}

set<string> ControladorCurso::getNombresCursosPrevios()
{
    set<string> cursosPrevios;
    // Implementación de la función getNombresCursosPrevios
    // Código para obtener los nombres de los cursos previos del curso seleccionado
    return cursosPrevios;
}

set<DTDataLeccion> ControladorCurso::getLecciones()
{
    set<DTDataLeccion> lecciones;
    // Implementación de la función getLecciones
    // Código para obtener las lecciones del curso seleccionado
    return lecciones;
}

void ControladorCurso::eliminarCurso(string nombre)
{
    HandlerCurso *h = HandlerCurso::getInstancia();

    h->eliminarCurso(nombre);

    // Implementación de la función eliminarCurso
    // Código para eliminar el curso con el nombre proporcionado
}

void ControladorCurso::agregarLeccion(string tema, string objetivo)
{
    if (this->leccionActual == NULL)
    {
        this->leccionActual = new Leccion();
    }
    this->leccionActual->setTema(tema);
    this->leccionActual->setObjetivo(objetivo);
    this->cursoActual->agregarLeccion(this->leccionActual);
    this->leccionActual = NULL;
}

void ControladorCurso::agregarEjercicio(string nombre, string tipoEjercicio, string descEjercicio)
{
    if (this->leccionActual == NULL)
    {
        this->leccionActual = new Leccion();
    }

    if (tipoEjercicio == "Traducir")
    {
        this->ejercicioActual = new Traducir(descEjercicio);
        this->leccionActual->agregarEjercicio(this->ejercicioActual);
        return;
    }
    if (tipoEjercicio == "Completar")
    {
        this->ejercicioActual = new Completar(descEjercicio);
        this->leccionActual->agregarEjercicio(this->ejercicioActual);
        return;
    }

    throw invalid_argument("Tipo de ejercicio no válido");
}

void ControladorCurso::agregarLeccionACurso(Leccion *leccion)
{
    // curso al que queremos agregar leccion
    Curso *curso = coleccionCursos->obtenerCurso(this->nombreCurso);
    curso->agregarLeccion(leccion);
}

void ControladorCurso::ingresarNicknameEstudiante(string nomEstudiante)
{
    // Código para ingresar el nickname del estudiante para realizar ejercicios o inscribirse a un curso
    if (coleccionUsuarios->existeUsuario(nomEstudiante))
    {
        this->nicknameUsuarioActual = nomEstudiante;
        return;
    }

    throw invalid_argument("Nickname no registrado");
}

void ControladorCurso::ingresarDatosCurso(string nombre, string desc, Nivel dificultad, string nickname)
{
    

    if (!coleccionUsuarios->existeUsuario(nickname))
        throw invalid_argument("No hay un usuario con el nickname " + nickname);
    this->nombreCursoActual = nombre;
    this->descripcionCursoActual = desc;
    this->dificultadlCursoActual = dificultad;

    this->nicknameProfesorActual = nickname;

    Profesor *profesor = dynamic_cast<Profesor *>(coleccionUsuarios->obtenerUsuario(nickname));

    this->cursoActual = new Curso();

    this->cursoActual->setNombre(nombre);
    this->cursoActual->setDescripcion(desc);
    this->cursoActual->setNivel(dificultad);
    this->cursoActual->setProfesor(profesor);
    this->cursoActual->setDisponible(false);

    
}

set<string> ControladorCurso::listarCursosInscrip()
{
    Estudiante *estudiante = dynamic_cast<Estudiante *>(coleccionUsuarios->obtenerUsuario(this->nicknameUsuarioActual));
    map<string, Inscripcion *> cursosInscriptos = estudiante->getInscripciones();
    set<string> result = set<string>();
    string ncurso;

    for (map<string, Inscripcion *>::iterator it = cursosInscriptos.begin(); it != cursosInscriptos.end(); ++it)
    {
        bool aprobado = it->second->getAprobado();
        if (!aprobado)
        {
            ncurso = it->first;
            result.insert(ncurso);
        }
    }

    return result;
}

set<string> ControladorCurso::mostrarCursosNoAprobados()
{
    set<string> cursosNoAprobados;
    // Implementación de la función mostrarCursosNoAprobados
    // Código para obtener la lista de cursos no aprobados del estudiante
    return cursosNoAprobados;
}

set<string> ControladorCurso::mostrarEjerciciosNoAprobados()
{
    HandlerUsuario *h = HandlerUsuario::getInstancia();
    Estudiante *e = dynamic_cast<Estudiante *>(h->obtenerUsuario(this->nicknameUsuarioActual));
    map<string, Inscripcion *> map = e->getInscripciones();
    Inscripcion *i = map.find(this->nombreCurso)->second;
    set<Ejercicio *> ej = i->getejNoAprobados();
    set<string> ejerciciosNoAprobados;

    for (set<Ejercicio *>::iterator it = ej.begin(); it != ej.end(); ++it)
    {
        Ejercicio *ptr = *it;
        ejerciciosNoAprobados.insert(ptr->getDescripcion());
    }
    // Implementación de la función mostrarEjerciciosNoAprobados
    // Código para obtener la lista de ejercicios no aprobados del estudiante
    return ejerciciosNoAprobados;
}

void ControladorCurso::seleccionarEjercicio(string descEjercicio)
{
    HandlerUsuario *h = HandlerUsuario::getInstancia();
    Estudiante *e = dynamic_cast<Estudiante *>(h->obtenerUsuario(this->nicknameUsuarioActual));
    map<string, Inscripcion *> map = e->getInscripciones();
    Inscripcion *i = map.find(this->nombreCurso)->second;
    set<Ejercicio *> ej = i->getejNoAprobados();

    auto it = ej.begin();
    while (it != ej.end() && (*it)->getDescripcion() != descEjercicio)
    {
        ++it;
    }

    this->ejercicioActual = *it;

    // Implementación de la función seleccionarEjercicio
    // Código para obtener los datos del ejercicio seleccionado por su nombre
}

void ControladorCurso::corregirEj()
{
    Ejercicio *e = this->getejActual();

    if (Traducir *tr = dynamic_cast<Traducir *>(e))
    {
        string sol;
        cout << "Ejercicio de traduccion " << endl
             << "frase a traducrir: " << tr->getFraseATraducir() << endl;
        cout << "Ingrese la solucion:" << endl;
        sol = ingresarParametro("la solucion");
        this->ingresarSolucionTraducir(sol);
        if (this->getSolT_actual() == tr->getFraseCorrecta())
        {
            this->marcarEjercicioAprobado();
            cout << "Respuesta correcta" << endl;
        }
        else
        {
            cout << "Respuesta incorrecta" << endl;
            this->marcarEjercicioNoAprobado();
        }
    }

    else if (Completar *c = dynamic_cast<Completar *>(e))
    {
        set<string> solucion;
        cout << "Ejercicio de completar " << endl
             << "frase a completar: " << c->getFraseACompletar() << endl;
        cout << "Ingrese las palabras faltantes:" << endl;
        for (long unsigned int i = 0; i < c->getPalabrasFaltantes().size(); i++)
        {
            string palabra;
            cin >> palabra;
            solucion.insert(palabra);
        }
        this->ingresarSolucionCompletar(solucion);
        bool soniguales = true;
        vector<string> v = c->getPalabrasFaltantes();
        set<string> s = this->getSolC_actual();

        if (v.size() == s.size())
        {

            vector<string> sortedVector = v;
            sort(sortedVector.begin(), sortedVector.end());
            set<string> sortedSet = s;
            vector<string> sortedSetVector(sortedSet.begin(), sortedSet.end());
            soniguales = (sortedVector == sortedSetVector);

            if (soniguales)
            {
                this->marcarEjercicioAprobado();
                cout << "Respuesta correcta" << endl;
            }
            else
            {
                cout << "Respuesta incorrecta" << endl;
                this->marcarEjercicioNoAprobado();
            }
        }

        else
        {
            this->marcarEjercicioNoAprobado();
        }
    }
}

void ControladorCurso::ingresarSolucionCompletar(set<string> solC)
{
    this->solC_actual = solC;
    // Implementación de la función ingresarSolucionCompletar
    // Código para ingresar la solución del ejercicio de completar en el Controlador de Ejercicio
}

void ControladorCurso::ingresarSolucionTraducir(string solT)
{
    this->solT_actual = solT;
    // Implementación de la función ingresarSolucionTraducir
    // Código para ingresar la solución del ejercicio de traducción en el Controlador de Ejercicio
}

void ControladorCurso::marcarEjercicioAprobado()
{
    HandlerUsuario *h = HandlerUsuario::getInstancia();
    Estudiante *e = dynamic_cast<Estudiante *>(h->obtenerUsuario(this->nicknameUsuarioActual));
    map<string, Inscripcion *> map = e->getInscripciones();
    Inscripcion *i = map.find(this->nombreCurso)->second;
    i->setejAprobado(this->ejercicioActual);
    i->setcantEjAprobados();

    this->nicknameUsuarioActual = "";
    this->nombreCurso = "";
    this->solT_actual = "";
    this->solC_actual.clear();
    this->ejercicioActual = NULL;
    // Implementación de la función marcarEjercicioAprobado
    // Código para marcar el ejercicio actual como aprobado en el Controlador de Ejercicio
}

void ControladorCurso::marcarEjercicioNoAprobado()
{
    this->nicknameUsuarioActual = "";
    this->nombreCurso = "";
    this->solT_actual = "";
    this->solC_actual.clear();
    this->ejercicioActual = NULL;

    // Implementación de la función marcarEjercicioNoAprobado
    // Código para marcar el ejercicio actual como no aprobado en el Controlador de Ejercicio
}

// Operaciones para Consulta Curso

set<string> ControladorCurso::listarNombreCursos()
{
    map<string, Curso *> cursos = ControladorCurso::coleccionCursos->obtenerCursos();
    set<string> nombresCursos;
    for (map<string, Curso *>::iterator it = cursos.begin(); it != cursos.end(); ++it)
    {
        nombresCursos.insert(it->first);
    }
    return nombresCursos;
}

void ControladorCurso::seleccionarCurso(string nombreCurso)
{
    this->nombreCurso = nombreCurso;
    this->leccionesCursoActual = coleccionCursos->obtenerCurso(nombreCurso)->getLecciones();
}

DTDataCurso *ControladorCurso::mostrarDatosCurso()
{
    string nombreCurso = this->nombreCurso;
    Curso *curso = coleccionCursos->obtenerCurso(nombreCurso);
    return curso->getDT();
}

int ControladorCurso::cantidadDeLecciones()
{
    Curso *curso = coleccionCursos->obtenerCurso(this->nombreCurso);
    int cantLecciones = curso->getCantLecciones();

    return cantLecciones;
}

DTDataLeccion *ControladorCurso::mostrarDatosLeccion(int posicion)
{
    Leccion *leccion = this->leccionesCursoActual[posicion];
    DTDataLeccion *dtLeccion = leccion->getDTLeccion();

    return dtLeccion;
}

int ControladorCurso::cantidadDeEjerciciosLeccion(int posicion)
{
    Leccion *leccion = this->leccionesCursoActual[posicion];
    int cant = leccion->getCantEj();

    return cant;
}

set<DTEjercicio *> ControladorCurso::mostrarEjercicios(int posLeccion)
{
    set<Ejercicio *> ejercicios = this->leccionesCursoActual[posLeccion]->getEjercicios();
    set<DTEjercicio *> dtEjercicios;
    for (Ejercicio *ej : ejercicios)
    {
        dtEjercicios.insert(ej->getDTEjercicio());
    }
    return dtEjercicios;
}

set<DTInscripcion *> ControladorCurso::mostrarInscripciones()
{
    Curso *curso = coleccionCursos->obtenerCurso(this->nombreCurso);
    set<DTInscripcion *> dtInscripciones;
    DTInscripcion *dtInscripcion;
    Inscripcion *i;

    map<string, Inscripcion *> inscripciones = curso->getInscripciones();
    for (auto it = inscripciones.begin(); it != inscripciones.end(); ++it)
    {
        i = it->second;
        dtInscripcion = i->getDTInscripcion();
        dtInscripciones.insert(dtInscripcion);
    }

    return dtInscripciones;
}

void ControladorCurso::seleccionarProfesor(string nickname)
{
    // Averigua si existe el profesor, lo busca en la coleccion de usuarios y lo asigna a usuarioActual
    if (coleccionUsuarios->existeUsuario(nickname))
    {
        this->usuarioActual = coleccionUsuarios->obtenerUsuario(nickname);
    }
    else
    {
        throw invalid_argument("No existe el profesor");
    }
}

set<string> ControladorCurso::listarCursosNoHabilitados()
{
    HandlerCurso *h = HandlerCurso::getInstancia();
    map<string, Curso *> o = h->obtenerCursos();
    set<string> resultado;

    for (map<string, Curso *>::iterator it = o.begin(); it != o.end(); ++it)
    {
        if (it->second->getDisponible() == false)
        {
            resultado.insert(it->second->getNombre());
        }
    }
    return resultado;
}

vector<string> ControladorCurso::listarLecciones(Curso *curso)
{
    vector<string> lecciones;

    vector<Leccion *> l = curso->getLecciones();
    string tema;

    for (auto it = l.begin(); it != l.end(); ++it)
    {
        tema = (*it)->getTema();
        lecciones.push_back(tema);
    }

    return lecciones;
}

void ControladorCurso::darDeAltaCompletar(string descripcion, string fraseACompletar, vector<string> palabrasFaltantes)
{
    Leccion *leccion = this->leccionActual;
    leccion->crearEjercicioCompletarYAgregarlo("", descripcion, fraseACompletar, palabrasFaltantes);
}

void ControladorCurso::darDeAltaTraducir(string descripcion, string fraseATraducir, string fraseTraducida)
{
    Leccion *leccion = this->leccionActual;
    leccion->crearEjercicioTraducirYAgregarlo("", descripcion, fraseATraducir, fraseTraducida);
}

void ControladorCurso::agregarFraseTraducir(string fraseATraducir, string fraseTraducida)
{
    if (this->ejercicioActual == NULL)
        throw invalid_argument("No hay ejercicio seleccionado");

    Traducir *traducir = dynamic_cast<Traducir *>(this->ejercicioActual);
    if (traducir == NULL)
        throw invalid_argument("El ejercicio seleccionado no es de tipo Traducir");

    traducir->setFraseATraducir(fraseATraducir);
    traducir->setFraseCorrecta(fraseTraducida);
    this->ejercicioActual = NULL;
}

void ControladorCurso::agregarFraseCompletar(string fraseACompletar, vector<string> palabras)
{
    if (this->ejercicioActual == NULL)
        throw invalid_argument("No hay ejercicio seleccionado");

    Completar *completar = dynamic_cast<Completar *>(this->ejercicioActual);
    if (completar == NULL)
        throw invalid_argument("El ejercicio seleccionado no es de tipo Completar");
    completar->setFraseACompletar(fraseACompletar);
    completar->setPalabrasFaltantes(palabras);
    this->ejercicioActual = NULL;

}

Ejercicio *ControladorCurso::getejActual()
{
    return this->ejercicioActual;
}

string ControladorCurso::getSolT_actual()
{
    return this->solT_actual;
}

set<string> ControladorCurso::getSolC_actual()
{
    return this->solC_actual;
}

vector<DTDataCursoAInscribir *> ControladorCurso::obtenerCursosDisponibles(set<string> cursosHabilitados)
{
    Estudiante *e = dynamic_cast<Estudiante *>(coleccionUsuarios->obtenerUsuario(this->nicknameUsuarioActual));
    vector<DTDataCursoAInscribir *> cursosDisp;
    Curso *curs;
    set<Curso *> cursosPrevios;
    bool estaInscripto, cursoDisponible, tieneCursosPrevios, cursoPrevioAprobado;
    DTDataCursoAInscribir *dcai;
    for (const auto &nomCurs : cursosHabilitados)
    {
        cursoDisponible = true;
        // Verifica si el estudiante está inscripto a ese curso
        estaInscripto = e->estaInscripto(nomCurs);
        if (!estaInscripto)
        {
            // Verificar si tiene cursos previos
            curs = coleccionCursos->obtenerCurso(nomCurs);
            tieneCursosPrevios = ! curs->getCursosPrevios().empty();
            if (tieneCursosPrevios) {
                cursosPrevios = curs->getCursosPrevios();
                for (auto it = cursosPrevios.begin(); (it != cursosPrevios.end()) && cursoDisponible; ++it)
                {
                    if (!((*it)->getInscripciones().find(this->nicknameUsuarioActual)!= (*it)->getInscripciones().end()))
                    {
                        cursoPrevioAprobado = (*it)->getInscripciones().find(this->nicknameUsuarioActual)->second->getAprobado();
                        if (!cursoPrevioAprobado)
                        {
                            cursoDisponible = false;
                        }
                    }

                    else
                        cursoDisponible = false;
                }
            }
        } else
            cursoDisponible = false;
            
        if (cursoDisponible)
        {
            // Creamos el DTDataCurso con los datos de curs
            dcai = curs->getDTAInscribir();
            // Metemos en el set cursosDisp ese DTDataCurso creado
            cursosDisp.push_back(dcai);
        }
    }
    return cursosDisp;
}

void ControladorCurso::realizarInscripcion(DTDate *fechaInscripcion)
{
    Estudiante *e = dynamic_cast<Estudiante *>(coleccionUsuarios->obtenerUsuario(this->nicknameUsuarioActual));
    Curso *c = coleccionCursos->obtenerCurso(this->nombreCurso);
    Inscripcion *ins = new Inscripcion(fechaInscripcion, false, e, c);
    e->agregarInscripcion(this->nombreCurso, ins);
    c->agregarInscrip(this->nicknameUsuarioActual, ins);
}

void ControladorCurso::agregarCursoPrevio(string nombreCurso)
{
    Curso *curso = coleccionCursos->obtenerCurso(nombreCurso);
    if (curso == NULL)
        throw invalid_argument("No existe el curso");

    Curso *previo = coleccionCursos->obtenerCurso(nombreCurso);

    this->cursosPreviosCursoActual.insert(previo);
    this->cursoActual->agregarCursoPrevio(previo);
}