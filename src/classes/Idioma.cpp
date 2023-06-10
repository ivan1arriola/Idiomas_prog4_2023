#include "../../include/classes/Idioma.h"

#include <string>

#include "../../include/interfaces/ISuscriptor.h"

using namespace std;

// Constructor

Idioma::Idioma() {}

Idioma::Idioma(string nombre) {
  this->nombre = nombre;
  this->suscriptores = map<string, ISuscriptor*>();
}

// Getters

string Idioma::getNombre() {
  return this->nombre;
}

// Operaciones

void Idioma::agregarSuscriptor(ISuscriptor* suscriptor) {
  this->suscriptores.insert(pair<string, ISuscriptor*>(suscriptor->getNickname(), suscriptor));
}

//void Idioma::eliminarSuscriptor(string nickname);



void Idioma::notificarSuscriptores(string nombreCurso) {
  for (map<string, ISuscriptor*>::iterator it = this->suscriptores.begin(); it != this->suscriptores.end(); it++) {
    it->second->enviarNotificacion(nombreCurso, this->nombre);
  }
}

bool Idioma::contieneSuscriptor(string nickname) {
  return this->suscriptores.count(nickname) > 0;
}

set<string> Idioma::getIdiomasProfesor() {
  set<string> idiomasProfesor;
  
  return idiomasProfesor;
}

// Destructor

Idioma::~Idioma() {}

bool Idioma::operator==(const Idioma& otro) {
  const Idioma& otroIdioma = dynamic_cast<const Idioma&>(otro);
  return this->nombre == otroIdioma.nombre;
}