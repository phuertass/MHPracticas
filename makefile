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
$(OBJ)/random.o $(OBJ)/BL.o \
$(OBJ)/BBO.o $(OBJ)/ES.o
	$(CXX) -o $@ $< $(CXXFLAGS)  $(OBJ)/funciones.o \
	 $(OBJ)/BL.o  $(OBJ)/BBO.o $(OBJ)/ES.o

###############################################################################

#EJECUTABLES
###############################################################################

$(BIN)/% : $(OBJ)/%.o
	@echo Creando $@a
	$(CXX) -o $@ $< $(CXXFLAGS) 
	@echo


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




$(OBJ)/BBO.o : $(SRC)/BBO.cpp $(INCLUDE)/funciones.h \
 $(INCLUDE)/BL.h $(INCLUDE)/ES.h
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
