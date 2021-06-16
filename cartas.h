//Andrea Peña Calvin

#ifndef CARTAS_H
#define CARTAS_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include <algorithm>
#include <utility>
#include<string>
#include <ctime>        
#include <cstdlib>

const int DIM = 4;

const int CARTASAVANZA = 18;
const int CARTASGI = 8;
const int CARTASGD = 8;
const int CARTASL = 4;
const int NUMEROCARTAS = CARTASAVANZA + CARTASGI + CARTASGD + CARTASL;

enum tCarta { AVANZAR, GIROIZQUIERDA, GIRODERECHA, LASER };

//using tVCartas = std::vector<tCarta>;

/*struct tMazo {
	tVCartas baraja;
	int inicio;
	int final;
	int numcartas;
};*/
using tArrayCartas = tCarta *[NUMEROCARTAS];

struct tMazo {
	int inicio, final, numelem;
	tArrayCartas lista;
};

using tMano = std::vector<int>;


std::ostream & operator << (std::ostream & arch, const tCarta & carta);

std::ostream & operator << (std::ostream & arch, const tMazo & mazo);

tCarta string2carta(std::string const& s);

void crearMazoAleatorio(tMazo & mazo);//CREA UN MAZO

bool cogerCarta(tMazo & mazo, tCarta & carta);//SACA UNA CARTA

void devolverCarta(tMazo & mazo, tArrayCartas & vec, const int & tamano);//INSERTA CARTA

void liberar(tMazo & mazo);

#endif
