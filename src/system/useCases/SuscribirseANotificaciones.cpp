#include <iostream>
#include <string>

#include "../../../include/system/Sistema.h"

#include "../../../include/system/operaciones.h"

using namespace std;

static bool ingresarOpcionSiONo(string mensaje) {
    imprimirMensaje(mensaje) ;
    imprimirMensaje("1. Sí") ;
    imprimirMensaje("2. No") ;

    int opcion = ingresarOpcion(2) ;

    return opcion == 1 ;
}

static string seleccionarElemento(set<string> elementos, string nombreElemento) {
    int opcion = -1;

    imprimirMensaje("Seleccione un " + nombreElemento + " de la lista:") ;
    imprimirSet(elementos, nombreElemento + "s") ;

    opcion = ingresarOpcion(elementos.size()) ;

    if (opcion == 0) {
        return string();
    }

    return obtenerOpcion(elementos, opcion) ;
}



/**
 * Nombre Suscribirse a notificaciones
Actores Usuario
Sinopsis: El caso de uso comienza cuando un usuario desea suscribirse para recibir notificaciones
relativas a la creación de cursos de uno o más idiomas. Para ello, el Usuario indica un
nickname (de estudiante o profesor) y el Sistema devuelve la lista de todos los idiomas
a los que no está suscrito dicho usuario. Posteriormente, el Usuario indica los idiomas
a los que desea suscribirse y el Sistema lo agrega a la lista de suscriptores.
 * **/

void Sistema::suscribirseANotificaciones() {
    imprimirMensaje("Suscribirse A Notificaciones");

    set<string> nicknames = controladorUsuario->listarNicknameUsuarios();
    // Selecciona un nickname de los usuarios existentes
    string nickname = seleccionarElemento(nicknames, "Nickname");

    if (nickname.empty()) {
        imprimirMensaje("No se seleccionó un nickname");
        imprimirMensaje("Cancelando suscripción a notificaciones");
        return;
    }

    set<string> idiomas = controladorUsuario->listarIdiomasNoSuscriptos(nickname);

    bool deseaSuscribirse = true;

    imprimirMensaje("Idiomas a los que no está suscripto:");
    do {
        // Selecciona un idioma de los idiomas disponibles
        string idioma = seleccionarElemento(idiomas, "Idioma");

        controladorUsuario->suscribirse(idioma);
        idiomas.erase(idioma);
        
    

        if(!idiomas.empty()) {
            deseaSuscribirse = ingresarOpcionSiONo("¿Desea suscribirse a otro idioma? (S/N)");
        } else {
            deseaSuscribirse = false;
        }
    } while (deseaSuscribirse && !idiomas.empty());







}
