#ifndef OPERACIONES
#define OPERACIONES

#include <iostream>

#include "../enums/NIVEL.h"

#include <set>
#include <string>
#include <vector>

using namespace std;

typedef unsigned long int nat;

/* Limpia la consola en Linux */
void limpiarConsola();

/* Imprime un espacio */
void espacioSimple();

/* Pide que se seleccione un elemento de una lista de elementos. Devuelve el
 * elemento seleccionado. Si se ingresa 0, devuelve un string vacio */
string seleccionarElemento(set<string> elementos, string nombreElemento);
int seleccionarElemento(vector<string> elementos, string nombreElemento);

/*Imprime una linea de - */
void imprimirLinea();

/* Imprime un mensaje de error */
void imprimirMensajeDeError(string mensaje);

/* Imprime un espacio, una linea de - y espacio */
void imprimirLineaDeSeparacion();

/* Imprime un mensaje de despedida */
void imprimirMensajeDespedida();

/* Imprime un conjunto de strings, con indice . Si el conjunto esta vacio,
 * imprime un mensaje indicando que no hay elementos disponibles */
void imprimirSet(const set<string>& conjunto, string nombreDelConjunto);

/* Imprime un vector de strings, con indice . Si el conjunto esta vacio,
 * imprime un mensaje indicando que no hay elementos disponibles */
void imprimirVector(const vector<string>& conjunto, string nombreDelConjunto);

/* Imprime una linea de guiones, un string, otra linea de guiones y un salto de
 * linea */
void imprimirMensaje(string mensaje);

/* Imprime un mensaje de bienvenida */
void imprimirMensajeBienvenida();

/* Imprime una lista de todos los casos de uso disponibles */
void imprimirMenu();

/* Imprime un conjunto de strings, con indice . Si el conjunto esta vacio,
 * imprime un mensaje indicando que no hay elementos disponibles. Ademas, agrega
 * una opcion 0 para cancelar */
void imprimirOpcionesSet(const set<string>& conjunto, string nombreDelConjunto);

string obtenerOpcion(const set<string>& conjunto, int opcion);
string obtenerOpcion(const vector<string>& conjunto, int opcion);

/* Lee un numero por consola.Si es un numero, verifica que sea una opcion valida
 * (entre 0 y cantOpciones). Si no es un numero, pide que se ingrese un numero.
 * Si es un numero pero no es una opcion valida, pide que se ingrese una opcion
 * valida. Devuelve la opcion elegida. */
int ingresarOpcion(int cantOpciones);

/* Pregunta por consola si se desea realizar otra operacion. Devuelve true si se desea
 * realizar otra operacion, false en caso contrario */
bool deseaRealizarOtraOperacion();

/* Pide un parametro por consola. Devuelve el parametro ingresado */
string ingresarParametro(string parametro);

string ingresarPalabra(string parametro);


/* Pregunta por consola si se desea continuar. Devuelve true si se desea
 * continuar, false en caso contrario */
bool deseaContinuar(string mensaje);


/* Imprime un mensaje de error y cancela la operacion */
void cancelarOperacion(string error, string operacion);

nat contarEspaciosACompletar(string frase);

string ingresarFraseACompletar();

vector<string> ingresarConjuntoDePalabras(int cantEspacios);

// Ingresa un nivel por consola
Nivel ingresarNivel();

// Ingresa un booleano por consola
bool ingresarBooleano(string pregunta);

// Ingresar Tipo de Ejercicio
int ingresarTipoEjercicio();

#endif
