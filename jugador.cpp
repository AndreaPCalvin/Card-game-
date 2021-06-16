//Andrea Peña Calvin

#include "jugador.h"

tTecla leerTecla() {
	tTecla sol = TERROR;

	int dir;
	std::cin.sync();
	dir = _getch();	//	dir:	tipo	int	

	if (dir == 13) sol = TSALIR;

	else if (dir == 32)  sol = TLASER;

	else if (dir == 0xe0) {
		dir = _getch();

		switch (dir) {

		case 72: sol = TAVANZA; break;

		case 75: sol = TIZQUIERDA; break;

		case 77: sol = TDERECHA; break;

		default: sol = TERROR;
		}
	}
	return sol;
}

void mostrarJuego(const tJuego & mijuego) {
	//tablero
	mostrarTablero(mijuego.tablero);
	std::cout << '\n';
	//jugadores
	for (int i = 0; i < mijuego.numjugadores; i++) {
		colorFondo(PALETA[i + 5]);
		if (mijuego.turno == i) std::cout << "> ";
		std::cout << i + 1 << " " << mijuego.arrayjug[i].nombre << ":";
		colorFondo(0);
		std::cout << " " << mijuego.arrayjug[i].manojug[0];
		colorFondo(PALETA[9]);
		std::cout << "^";
		colorFondo(0);
		std::cout << " " << mijuego.arrayjug[i].manojug[1];
		colorFondo(PALETA[9]);
		std::cout << "<";
		colorFondo(0);
		std::cout << " " << mijuego.arrayjug[i].manojug[2];
		colorFondo(PALETA[9]);
		std::cout << ">";
		colorFondo(0);
		std::cout << " " << mijuego.arrayjug[i].manojug[3];
		colorFondo(PALETA[9]);
		std::cout << "-" << '\n';
		colorFondo(0);
	}
}

bool realizarMovimiento(tTablero & tablero, tCoordenada & coor, const tArrayCartas & vCartas, const int & tamano) {
	
	bool encontrarjoya = false;
	tDir direccion = tablero[coor.x][coor.y].tort.dir;

	for (int k = 0; k < tamano && !encontrarjoya; k++) {
		if (*(vCartas[k]) == AVANZAR) {
			if (movPosible(tablero, coor, direccion)) {
				if (tablero[coor.x + incF[direccion]][coor.y + incC[direccion]].estado == JOYA)	encontrarjoya = true;
				avanzar(tablero, direccion, coor);
			}
		}
		else if (*(vCartas[k]) == GIRODERECHA) {
			++direccion;
		}
		else if (*(vCartas[k]) == GIROIZQUIERDA) {
			--direccion;
		}
		else if (*(vCartas[k]) == LASER) {
			laser(tablero, coor, direccion);
		}

	}
	tablero[coor.x][coor.y].tort.dir = direccion;
	return encontrarjoya;
}

bool ejecutarturnos(tJuego & mijuego) {
	bool ok = false;//verdadero si encuentra la joya
	char op;
	std::cout << "Elija una opcion: robar (R) o crear una secuencia (E)." << '\n';
	std::cin >> op;

	while (op != 'R' && op != 'E') {
		std::cout << "Opcion no valida, introduzca una correcta: " << '\n';
		std::cin >> op;
	}

	if (op == 'R') {
		bool a; tCarta carta;

		a = cogerCarta(mijuego.arrayjug[mijuego.turno].mazojug, carta);

		if (a) {

			++mijuego.arrayjug[mijuego.turno].manojug[carta];

		}
	}

	else if (op == 'E') {
		std::cout << "Introduce la secuencia: ";

		tArrayCartas vectorcartas, cartasadevolver;
		for (int i = 0; i < NUMEROCARTAS; i++) {
			vectorcartas[i] = new tCarta;
			cartasadevolver[i] = new tCarta;
		}

		tTecla key = leerTecla();
		
		int x = 0;
		while (key != TSALIR) {

			if (key != TERROR) {
				if (mijuego.arrayjug[mijuego.turno].manojug[key] > 0) {
				
					
					*(vectorcartas[x])=tCarta(key);
					*(cartasadevolver[x]) = tCarta(key);
					x++;
					
					mijuego.arrayjug[mijuego.turno].manojug[key]--;
					
					if (key == TAVANZA)std::cout << "A ";
					else if (key == TLASER)std::cout << "LA ";
					else if (key == TIZQUIERDA)std::cout << "GI ";
					else if (key == TDERECHA)std::cout << "GD ";
				}
				else std::cout << "No tienes esa carta, introduce otra: ";
			}

			else std::cout << "Introduzca una tecla valida: ";

			key = leerTecla();
		}
		
		std::cout << '\n';


		ok = realizarMovimiento(mijuego.tablero, mijuego.arrayjug[mijuego.turno].coorjug, vectorcartas, x);
		devolverCarta(mijuego.arrayjug[mijuego.turno].mazojug, cartasadevolver, x);

		for (int j = 0; j < NUMEROCARTAS; ++j) {
			delete vectorcartas[j];
			delete cartasadevolver[j];
		}

	}
	return ok;
}

void mazosmanos(tJuego & mijuego) {//crea el mazo y la mano de cada jugador
	tCarta carta;
	bool a;
	
	for (int i = 0; i < mijuego.numjugadores; i++) {
		crearMazoAleatorio(mijuego.arrayjug[i].mazojug);   //mazo

		
		mijuego.arrayjug[i].manojug.resize(NUM_DIRECCIONES, 0);

		//mano=03 cartas de la parte superior
		for (int k = 0; k < NUM_DIRECCIONES-1; k++) {
			a = cogerCarta(mijuego.arrayjug[i].mazojug, carta);
			if (a) 
				++mijuego.arrayjug[i].manojug[carta];
		}
	}
}
