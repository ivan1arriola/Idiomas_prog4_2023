#include "../../../include/classes/Curso/Completar.h"

#include <iostream>

Completar::Completar() {
    // Implementación del constructor por defecto
}


Completar::Completar(string descripcion) : Ejercicio(descripcion) {
    // Implementación del constructor con parámetros
    this->fraseACompletar = "";
    this->palabrasFaltantes = vector<string>();
}

Completar::Completar(string descripcion, string fraseACompletar, vector<string> palabrasFaltantes) : Ejercicio(descripcion) {
    this->fraseACompletar = fraseACompletar;
    this->palabrasFaltantes = palabrasFaltantes;
}

string Completar::getFraseACompletar() {
    return fraseACompletar;
}

vector<string> Completar::getPalabrasFaltantes() {
    return palabrasFaltantes;
}

void Completar::setFraseACompletar(string fraseACompletar) {
    this->fraseACompletar = fraseACompletar;
}

void Completar::setPalabrasFaltantes(vector<string> palabrasFaltantes) {
    this->palabrasFaltantes = palabrasFaltantes;
}

Completar::~Completar() {
    // Implementación del destructor
}

ostream& operator<<(ostream& os, const Completar& completar) {
    // Implementación del operador de salida
    os << "Tipo de ejercicio: Completar" << endl;
    os << "Frase a completar: " << completar.fraseACompletar << endl;
    return os;
}
