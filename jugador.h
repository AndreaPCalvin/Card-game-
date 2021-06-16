//Andrea Peña Calvin

//#pragma once
#ifndef JUGADOR_H
#define JUGADOR_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include<vector>
#include<string>
#include<conio.h>
#include<Windows.h>

#include "tablero.h"
#include "cartas.h"

struct tJugador {
	std::string nombre;
	tMazo mazojug;
	tMano manojug;
	tCoordenada coorjug;
};

struct tJuego {
	tTablero tablero;
	int numjugadores;
	int turno;
	std::vector<tJugador> arrayjug;
};

enum tTecla { TAVANZA, TIZQUIERDA, TDERECHA, TLASER, TSALIR, TERROR };

tTecla leerTecla();//LEE LA TECLA INTRODUCIDA POR EL JUGADOR

void mostrarJuego(const tJuego & mijuego);//VISUALIZA EL ESTADO ACTUAL DEL JUEGO

bool realizarMovimiento(tTablero & tablero, tCoordenada & coor, const tArrayCartas & vCartas, const int & tamano);//REALIZA EL MOV DE LA TORTUGA

bool ejecutarturnos(tJuego & mijuego);//LEE LA OPCION DEL JUGADOR ACTUAL Y LA EJECUTA

void mazosmanos(tJuego & mijuego); //INICIA LAS MANOS Y MANOS DE LOS JUGADORES

#endif // !JUGADOR_H

