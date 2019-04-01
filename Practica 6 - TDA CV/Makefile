# GRADO EN INGENIERIA INFORMATICA
#
# (C) IGNACIO PINEDA MOCHON
#
# Makefile practica ClinVar
#

bin/principal: obj/enfermedad.o obj/mutacion.o obj/ClinVar.o obj/principal.o
	g++ -o bin/principal obj/enfermedad.o obj/mutacion.o obj/ClinVar.o obj/principal.o -std=c++11

obj/enfermedad.o: src/enfermedad.cpp include/enfermedad.h
	g++ -c -o obj/enfermedad.o src/enfermedad.cpp -I./include -std=c++11

obj/mutacion.o: src/mutacion.cpp include/enfermedad.h include/mutacion.h
	g++ -c -o obj/mutacion.o src/mutacion.cpp -I./include -std=c++11

obj/ClinVar.o: src/ClinVar.cpp include/enfermedad.h include/mutacion.h include/ClinVar.h
	g++ -c -o obj/ClinVar.o src/ClinVar.cpp -I./include -std=c++11

obj/principal.o: src/principal.cpp include/enfermedad.h include/mutacion.h include/ClinVar.h
	g++ -c -o obj/principal.o src/principal.cpp -I./include -std=c++11
