#ifndef DTDATACURSOESTUDIANTE
#define DTDATACURSOESTUDIANTE

#include <string>

using namespace std;

class DTDataCursoEstudiante {
    private:
        string nombreCurso;
        float porcentajeAvanceEstudiante;
    public:
        DTDataCursoEstudiante(string nombreCurso, float porcentajeAvanceEstudiante);
        string getNombreCurso();
        float getPorcentajeAvanceEstudiante();
        ~DTDataCursoEstudiante();

        friend ostream& operator<<(ostream& os, const DTDataCursoEstudiante& dtCursoEstudiante);
};

#endif