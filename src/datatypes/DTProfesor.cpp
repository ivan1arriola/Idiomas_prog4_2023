#include "../../include/datatypes/DTProfesor.h"

#include <string>
#include <iostream>

using namespace std;

DTProfesor::DTProfesor() {}

DTProfesor::DTProfesor(string nickname, string contrasenia, string nombre, string descripcion, string instituto) : DTUsuario(nickname, contrasenia, nombre, descripcion, 0) {
    this->instituto = instituto;
}

DTProfesor::DTProfesor(string nickname, string contrasenia, string nombre, string descripcion, string instituto, set<string> idiomas) : DTUsuario(nickname, contrasenia, nombre, descripcion, 0){
    this->instituto = instituto;
    this->idiomas = idiomas;
}

// Getters

string DTProfesor::getInstituto() const {
    return this->instituto;
}

set<string> DTProfesor::getIdiomas() const {
    return this->idiomas;
}

// Destructor

DTProfesor::~DTProfesor() {}


ostream& operator<<(ostream& os, const DTProfesor& dtProfesor) {
    os << "Tipo: Profesor" << endl;
    os << "Nickname: " << dtProfesor.getNickname() << endl;
    os << "Nombre: " << dtProfesor.getNombre() << endl;
    os << "Descripcion: " << dtProfesor.getDescripcion() << endl;
    os << "Instituto: " << dtProfesor.getInstituto() << endl;
    os << "Idiomas:" << endl;
    for(string i : dtProfesor.getIdiomas()){
        os << "- " << i << endl;
    }
    return os;
}
