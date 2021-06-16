//Andrea Peña Calvin

#ifndef TABLERO_H
#define TABLERO_H

//#pragma once
#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <string>
#include <Windows.h>

const int DIMENSION = 8, TIPOS = 6, NUM_DIRECCIONES = 4;

enum tDir { UP, RIGHT, DOWN, LEFT };

struct tTortuga {
	int ident;
	tDir dir;
};

enum tEstadoCasilla { VACIA, HIELO, MURO, CAJA, JOYA, TORTUGA };

struct tCasilla {
	tEstadoCasilla estado;
	tTortuga tort;
};

using tTablero = std::vector<std::vector<tCasilla> >;

struct tCoordenada {
	int x;
	int y;
};

const std::vector<int>PALETA{ 1,11,7,4,12,14,13,9,10,3 };

const std::vector<int> incF{ -1, 0, 1, 0 };
const std::vector<int> incC{ 0, 1, 0, -1 };

//funciones 

std::string casilla2char(const tCasilla & casilla);

tCasilla char2casilla(const char & caracter, const int & idtortu);

std::ostream & operator << (std::ostream & arch, const tCasilla & casilla);

std::ostream & operator << (std::ostream & arch, const tTablero & tablero);

void colorFondo(int color);//CAMBIA EL COLOR DEL TABLERO

void mostrarTablero(const tTablero & tablero);//MUESTRA EL TABLERO

bool cargar(const std::string & nf,tTablero & tablero, int njugadores, std::vector<tCoordenada> &Vcoord);//CARGA EL TALERO

bool compcoord(const tTablero & tablero, const tCoordenada & coord);//COMPRUEBA SI UNA COORDENADA SE ENCUENTRA EN EL TABLERO

void laser(tTablero & tablero, const tCoordenada & coord, const tDir & dirtort);//DISPARA LASER

bool caja(const tTablero & tablero, tCoordenada  coordenada, const tDir & direccion);//COMPRUEBA SI SE PUEDE MOVER LA CAJA

bool movPosible(const tTablero & tablero, tCoordenada coord, const tDir & direccion);//COMPRUEBA SI SE PUEDE REALIZAR UN MOVIMIENTO

void avanzar(tTablero & tablero, const tDir & direccion, tCoordenada & coordenada);//AVANZA LA TORTUGA

tDir operator++(tDir & dir);

tDir operator--(tDir & dir);

#endif // !TABLERO_H
