#MAKEFILE PABLO HUERTAS ARROYO
###############################################################################
HOME = .

SRC = $(HOME)/src
OBJ = $(HOME)/obj
INCLUDE = $(HOME)/include
BIN = $(HOME)/bin
LIB = $(HOME)/lib

CXX = g++ -O3
CXXFLAGS = -std=c++14 -I./include -L./lib -fopenmp


.PHONY : clean
.PHONY : mr.proper

OBJETOS= $(BIN)/mainBBO

all : preambulo $(OBJETOS) arbol final


###############################################################################
# P4
###############################################################################
$(BIN)/mainBBO : $(OBJ)/mainBBO.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Generacional.o $(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o \
$(OBJ)/BBO.o $(OBJ)/ES.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o $(OBJ)/BBO.o $(OBJ)/ES.o

###############################################################################

#EJECUTABLES
###############################################################################

$(BIN)/% : $(OBJ)/%.o
	@echo Creando $@a
	$(CXX) -o $@ $< $(CXXFLAGS) 
	@echo

$(BIN)/main : $(OBJ)/main.o $(OBJ)/funciones.o $(OBJ)/random.o \
$(OBJ)/Generacional.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o \
$(OBJ)/BL.o 
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o $(OBJ)/BL.o

$(BIN)/mainILS : $(OBJ)/mainILS.o $(OBJ)/funciones.o $(OBJ)/random.o \
$(OBJ)/Generacional.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o \
$(OBJ)/BL.o $(OBJ)/ILS.o $(OBJ)/ES.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o $(OBJ)/BL.o \
	$(OBJ)/ILS.o $(OBJ)/ES.o

$(BIN)/mainILS_ES : $(OBJ)/mainILS_ES.o $(OBJ)/funciones.o $(OBJ)/random.o \
$(OBJ)/Generacional.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o \
$(OBJ)/BL.o $(OBJ)/ILS.o $(OBJ)/ES.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o $(OBJ)/BL.o \
	$(OBJ)/ILS.o $(OBJ)/ES.o

$(BIN)/mainBMB : $(OBJ)/mainBMB.o $(OBJ)/funciones.o $(OBJ)/random.o \
$(OBJ)/Generacional.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o \
$(OBJ)/BL.o $(OBJ)/BMB.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o $(OBJ)/BL.o \
	$(OBJ)/BMB.o

$(BIN)/mainES : $(OBJ)/mainES.o $(OBJ)/funciones.o $(OBJ)/random.o \
$(OBJ)/Generacional.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o \
$(OBJ)/BL.o $(OBJ)/ES.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o $(OBJ)/BL.o \
	$(OBJ)/ES.o

$(BIN)/mainP2 : $(OBJ)/mainP2.o $(OBJ)/funciones.o $(OBJ)/random.o \
$(OBJ)/Generacional.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o \
$(OBJ)/BL.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Estacionario.o $(OBJ)/Cruces.o $(OBJ)/Memetico.o $(OBJ)/BL.o



##############################################################################################
# ALGORITMOS PRACTICA 2
##############################################################################################

$(BIN)/mainGeneracionalPosicion : $(OBJ)/mainGeneracionalPosicion.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Generacional.o $(OBJ)/Cruces.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Cruces.o

$(BIN)/mainGeneracionalUniforme : $(OBJ)/mainGeneracionalUniforme.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Generacional.o $(OBJ)/Cruces.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Cruces.o


$(BIN)/mainEstacionarioPosicion : $(OBJ)/mainEstacionarioPosicion.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Estacionario.o \
	$(OBJ)/Cruces.o


$(BIN)/mainEstacionarioUniforme : $(OBJ)/mainEstacionarioUniforme.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Estacionario.o $(OBJ)/Cruces.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Estacionario.o \
	$(OBJ)/Cruces.o

$(BIN)/mainMemetico1 : $(OBJ)/mainMemetico1.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Generacional.o $(OBJ)/Cruces.o $(OBJ)/BL.o \
$(OBJ)/Memetico.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o

$(BIN)/mainMemetico2 : $(OBJ)/mainMemetico2.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Generacional.o $(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o

$(BIN)/mainMemetico3 : $(OBJ)/mainMemetico3.o $(OBJ)/funciones.o \
$(OBJ)/random.o $(OBJ)/Generacional.o $(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o $(OBJ)/Generacional.o \
	$(OBJ)/Cruces.o $(OBJ)/BL.o $(OBJ)/Memetico.o

###############################################################################
#OBJETOS
###############################################################################


$(OBJ)/%.o : $(SRC)/%.cpp
	@echo Creando $@
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@echo

$(OBJ)/main.o : $(SRC)/main.cpp
	@echo Creando $@
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@echo

$(OBJ)/random.o : $(INCLUDE)/random.h
	@echo Creando $@
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@echo

$(OBJ)/Memetico.o : $(SRC)/Memetico.cpp $(INCLUDE)/funciones.h \
$(INCLUDE)/Generacional.h $(INCLUDE)/BL.h  
	@echo Creando $@
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@echo

$(OBJ)/ILS.o : $(SRC)/ILS.cpp $(INCLUDE)/funciones.h \
$(INCLUDE)/BL.h  $(INCLUDE)/ES.h
	@echo Creando $@
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@echo

$(OBJ)/BBO.o : $(SRC)/BBO.cpp $(INCLUDE)/funciones.h \
$(INCLUDE)/Generacional.h $(INCLUDE)/BL.h $(INCLUDE)/ES.h
	@echo Creando $@
	$(CXX) -c -o $@ $(CXXFLAGS) $<
	@echo

###############################################################################
arbol :
	-@tree $(OBJ) $(BIN)

###############################################################################
#LIMPIEZA
###############################################################################
clean :
	@echo  Borrando objetos...
	-rm -r $(OBJ)/*
	@echo

clean-objs :
	@echo  Borrando objetos...
	-rm -r $(OBJ)/*
	@echo

clean-bin :
	@echo Borrando ejecutables...
	-rm -r $(BIN)/*
	@echo

clean-lib :
	@echo Borrando bibliotecas...
	-rm -r $(LIB)/*
	@echo

mr.proper : clean-objs clean-bin clean-lib

###############################################################################
#PREAMBULO
###############################################################################

preambulo:
	@echo
	@echo ------------------------------------------------------------
	@echo
	@echo Fichero makefile
	@echo
	@echo METODOLOGÍA DE LA PROGRAMACIÓN
	@echo
	@echo Pablo Huertas Arroyo
	@echo
	@echo ------------------------------------------------------------
	@echo

###############################################################################
#FINAL
###############################################################################

final :
	@echo ------------------------------------------------------------
	@echo

###############################################################################
#TEST
###############################################################################
