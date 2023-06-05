# Variables
CXX = g++
CXXFLAGS = -std=c++11 -Wall
SRCDIR = src
OBJDIR = obj
BINDIR = bin
EXECUTABLE = $(BINDIR)/app
CASOSDEUSODIR = $(SRCDIR)/system/useCases

# Archivos fuente
MAIN = main.cpp

CPP_DATATYPES_FILES := $(SRCDIR)/datatypes/DTUsuario.cpp \
	$(SRCDIR)/datatypes/DTEstudiante.cpp \
	$(SRCDIR)/datatypes/DTProfesor.cpp \
	$(SRCDIR)/datatypes/DTNotificacion.cpp \
	$(SRCDIR)/datatypes/DTDate.cpp \




CPP_CASOSDEUSO_FILES := $(CASOSDEUSODIR)/AltaDeUsuario.cpp \
	$(CASOSDEUSODIR)/AgregarEjercicio.cpp \
	$(CASOSDEUSODIR)/AgregarLeccion.cpp \
	$(CASOSDEUSODIR)/AltaDeCurso.cpp \
	$(CASOSDEUSODIR)/AltaDeIdioma.cpp \
	$(CASOSDEUSODIR)/ConsultaDeNotificaciones.cpp \
	$(CASOSDEUSODIR)/ConsultaDeUsuario.cpp \
	$(CASOSDEUSODIR)/ConsultarCurso.cpp \
	$(CASOSDEUSODIR)/ConsultarEstadisticas.cpp \
	$(CASOSDEUSODIR)/ConsultarIdiomas.cpp \
	$(CASOSDEUSODIR)/EliminarCurso.cpp \
	$(CASOSDEUSODIR)/EliminarSuscripciones.cpp \
	$(CASOSDEUSODIR)/HabilitarCurso.cpp \
	$(CASOSDEUSODIR)/InscribirseACurso.cpp \
	$(CASOSDEUSODIR)/RealizarEjercicio.cpp \
	$(CASOSDEUSODIR)/SuscribirseANotificaciones.cpp \


CPP_CLASSES_FILES := $(SRCDIR)/classes/Usuario/Usuario.cpp \
	$(SRCDIR)/classes/Usuario/Estudiante.cpp \
	$(SRCDIR)/classes/Usuario/Profesor.cpp \
	$(SRCDIR)/classes/Idioma.cpp \

CPP_CONTROLLERS_FILES := $(SRCDIR)/controllers/ControladorUsuario.cpp 

CPP_FACTORY_FILES := $(SRCDIR)/factory/fabrica.cpp \

CPP_COLLECTIONS_FILES := $(SRCDIR)/handlers/HandlerIdioma.cpp \
	$(SRCDIR)/handlers/HandlerUsuario.cpp \

CPP_FILES := $(MAIN) \
	$(SRCDIR)/system/operaciones.cpp \
	$(SRCDIR)/system/Sistema.cpp \
	$(CPP_DATATYPES_FILES) \
	$(CPP_CASOSDEUSO_FILES) \
	$(CPP_CLASSES_FILES) \
	$(CPP_CONTROLLERS_FILES) \
	$(CPP_FACTORY_FILES) \
	$(CPP_COLLECTIONS_FILES) \
	$(CASOSDEUSODIR)/CargarDatosDePrueba.cpp \



# Objetos
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(CPP_FILES))

# Regla principal
rerun: clean build run

build: $(EXECUTABLE)

# Regla para el ejecutable
$(EXECUTABLE): $(OBJECTS)
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(EXECUTABLE)

# Regla para los objetos
$(OBJDIR)/%.o: $(SRCDIR)/%.cpp
	@mkdir -p $(@D)
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regla para limpiar los archivos generados
clean:
	rm -rf $(OBJDIR) $(EXECUTABLE) $(BINDIR)

run:
	@clear
	@./$(EXECUTABLE)

valgrind:
	@clear
	@valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes ./$(EXECUTABLE)

