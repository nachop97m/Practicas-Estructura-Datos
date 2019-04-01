SRC = src
INC = include
OBJ = obj
LIB = lib
BIN = bin
CXX = g++ -std=c++11
AR = ar rvs		
AR_MACOSX = libtool -static -o  # Para MACs
CPPFLAGS = -Wall -g  -I$(INC) -c



all: $(BIN)/ejemploKtree $(BIN)/pruebanmer

# ************ Generación de documentación ******************
documentacion:
	doxygen doc/doxys/doxPractica.txt

	
# ************ Compilación de módulos ************
$(BIN)/ejemploKtree: $(OBJ)/ejemploKtree.o $(LIB)/libNmer.a $(INC)/ktree.h
	$(CXX) -o $(BIN)/ejemploKtree $(OBJ)/ejemploKtree.o -I$(INC) -L$(LIB) -lNmer

$(OBJ)/ejemploKtree.o: $(SRC)/ejemploKtree.cpp
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/ejemploKtree.o $(SRC)/ejemploKtree.cpp 

$(LIB)/libNmer.a: $(OBJ)/Nmer.o
	$(AR) $(LIB)/libNmer.a $(OBJ)/Nmer.o

$(OBJ)/Nmer.o: $(SRC)/Nmer.cpp $(INC)/Nmer.h
	$(CXX) $(CPPFLAGS)  -o $(OBJ)/Nmer.o $(SRC)/Nmer.cpp 

# ************ Compilación de módulos ************
$(BIN)/pruebanmer: $(OBJ)/pruebanmer.o $(LIB)/libNmer.a $(INC)/Nmer.h 
	$(CXX) -o $(BIN)/pruebanmer $(OBJ)/pruebanmer.o -I$(INC) -L$(LIB) -lNmer

$(OBJ)/pruebanmer.o: $(SRC)/pruebanmer.cpp
	g++ $(CPPFLAGS)  -o $(OBJ)/pruebanmer.o $(SRC)/pruebanmer.cpp -std=c++11 

$(LIB)/libNmer.a: $(OBJ)/Nmer.o
	$(AR) $(LIB)/libNmer.a $(OBJ)/Nmer.o

$(OBJ)/Nmer.o: $(SRC)/Nmer.cpp $(INC)/Nmer.h
	g++ $(CPPFLAGS)  -o $(OBJ)/Nmer.o $(SRC)/Nmer.cpp -std=c++11

# ************ Limpieza ************
clean :
	-rm $(OBJ)/* $(SRC)/*~ $(INC)/*~ ./*~

clean_bin : clean
	-rm $(BIN)/*

clean_doc : clean
	-rm doc/html/* doc/latex/*
