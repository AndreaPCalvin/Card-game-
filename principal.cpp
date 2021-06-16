//Andrea Peña Calvin

//#include "tablero.h"
//#include "cartas.h"
#include "puntuacion.h"
#include "jugador.h"
#include <conio.h>

const int VMIN = 0;//valor minimo aceptado en las opciones de juego
const int VMAX = 2;//valor maximo aceptado en las opciones de juego


/////////////////
int leeOpcion() {

	int opt; //opcion elegida 

	std::cout << "1- Jugar" << '\n';
	std::cout << "2- Mostrar puntuaciones" << '\n';
	std::cout << "0- Salir" << '\n';

	std::cout << "Ingrese una opcion: ";
	std::cin >> opt;

	while (!((VMIN <= opt) && (opt <= VMAX))) {//comprueba que el valor elegido sea un numero correcto
		std::cout << "Opcion incorrecta. Escoja una opcion valida: ";
		std::cin >> opt;
	}
	return opt;
}


void sesionDeJuego() {
	
	tPuntuaciones punt; //jugadores y su puntuacion
	iniciar(punt);
	leerFichero(punt); //carga la info de los jugadores

	int opcion = leeOpcion();//lee la opcion de juego elegida por el jugador

	while (opcion != 0) {
		
		if(opcion==1){
			std::string nomfich, nombrej;
			int njug;
			
			tJuego mijuego{tTablero(DIMENSION, std::vector<tCasilla>(DIMENSION))};//datos del juego actual

			std::cout << "Introduzca el nombre del fichero.txt y el numero de jugadores(maximo 4):\n";
			std::cin >> nomfich >> njug;
			
			while (njug < 1 || njug>NUM_DIRECCIONES) {
				std::cout << "Introduzca un numero correcto de jugadores:\n";
				std::cin >> njug;
			}

			mijuego.numjugadores = njug;
			
			std::vector<tCoordenada> Vcoord;
            
			//cargar tablero
			bool a=cargar(nomfich, mijuego.tablero, njug, Vcoord);
			if (a) {
				mijuego.arrayjug = std::vector<tJugador>(njug);

				std::cout << "Introduzca el nombre de los jugadores: ";

				for (int i = 0; i < njug; i++) {
					std::cin >> nombrej;       //ALAMACENAR LOS NOMBRES
					mijuego.arrayjug[i].nombre = nombrej;
					mijuego.arrayjug[i].coorjug = Vcoord[i];
				}

				//crear mazos y manos
				mazosmanos(mijuego);

				bool Ejoya = false;//si al ejecutar el turno el jugador llega a una joya, joya==true
				int turnos = -1;
				while (!Ejoya) {
					turnos = (turnos + 1) % njug;
					mijuego.turno = turnos;
					//limpiar pantalla y mostrar tablero
					system("cls");
					mostrarJuego(mijuego);
					//
					Ejoya = ejecutarturnos(mijuego);//ejecuta los turnos de los jugadores
					
				}

				//se encuentra la joya, actualizar la puntuacion d los jugadores
				system("cls");
				std::cout << "Has conseguido la joya! Enhorabuena "<< mijuego.arrayjug[turnos].nombre <<"!" << '\n';
				
				//ACTUALIZAR PUNT DE TODOS LOS JUGADORES
				int puntuacion;
				for (int x = 0; x < njug; ++x) {
					if (mijuego.arrayjug[x].nombre == mijuego.arrayjug[turnos].nombre) puntuacion = njug;
					else puntuacion = 0;
					actualizarPunt(punt, mijuego.arrayjug[x], puntuacion);
				}
				
				for (int i = 0; i < mijuego.numjugadores; i++)
					liberar(mijuego.arrayjug[i].mazojug);
			}
			else std::cout << "No se ha podido abrir el fichero que has introducido" << '\n';

			std::cout << '\n';
		}

		else{//opcion==2
			std::cout << " -Desea mostrar la lista con el orden por defecto (D) o por orden alfabetico (A)" << '\n';
			char letra;
			std::cin >> letra;

			while (letra != 'A' && letra != 'D') {
			std::cout << "Por favor, escoja una letra valida: A o D" << '\n';
			std::cin >> letra;
			}

			if(letra=='D')
			    mostrarpuntuaciones(punt);//por defecto

			else {//solo puede ser A
				
				tPuntuaciones aux;
				aux.num_jugadores = punt.num_jugadores;
				aux.capacidad = punt.num_jugadores;
				aux.array_clasificacion = new tPunt_nom*[punt.num_jugadores];
				
				for (int i = 0; i < punt.num_jugadores; ++i) {

				aux.array_clasificacion[i] = new tPunt_nom;
				aux.array_clasificacion[i]->jugador = punt.array_clasificacion[i]->jugador;
				aux.array_clasificacion[i]->puntos = punt.array_clasificacion[i]->puntos;
				
				}
				//ordenar aux
				ordenar_alf(aux);
				mostrarpuntuaciones(aux);
				liberar(aux);
			}
		}
		
		opcion = leeOpcion();//muestra al jugador las opciones
	}

	//Si opcion == 0: salir
	escribirFichero(punt);//escribe en el fichero las puntuaciones de las partidas jugadas
	liberar(punt);
	
}
// MAIN DE LA PRACTICA

int main() {
	srand(time(NULL));

	sesionDeJuego();
	
	
	system("PAUSE");

	return 0;
}