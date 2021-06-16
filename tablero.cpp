//Andrea Peña Calvin

#include "tablero.h"



std::string casilla2char(const tCasilla & casilla) { //transformar un casilla a una cadena de caracteres
	std::string a = "";
	switch (casilla.estado) {
	case MURO: a = "||"; break;
	case HIELO: a = "**"; break;
	case JOYA: a = "00"; break;
	case CAJA: a = "[]"; break;
	case VACIA: a = "  "; break;
	case TORTUGA: switch (casilla.tort.dir) {
	case UP: a = "^^";  break;
	case DOWN:  a = "vv"; break;
	case RIGHT: a = ">>"; break;
	case LEFT: a = "<<"; break;
	} break;
	}
	return a;
}


tCasilla char2casilla(const char & caracter, const int & idtortu) { //transformar un caracter en una casilla 
	tCasilla a;

	switch (caracter) {
	case ' ': a.estado = VACIA; break;
	case '#': a.estado = MURO; break;
	case '@': a.estado = HIELO; break;
	case 'C': a.estado = CAJA; break;
	case '$': a.estado = JOYA; break;

	case 'U': { a.tort.dir = UP; a.estado = TORTUGA; a.tort.ident = idtortu;  break; }
	case 'D': {a.tort.dir = DOWN; a.estado = TORTUGA; a.tort.ident = idtortu; break; }
	case 'R': {a.tort.dir = RIGHT; a.estado = TORTUGA; a.tort.ident = idtortu; break; }
	case 'L': {a.tort.dir = LEFT; a.estado = TORTUGA; a.tort.ident = idtortu; break; }
	}
	return a;
}

std::ostream & operator << (std::ostream & arch, const tCasilla & casilla) {
	std::string cas = casilla2char(casilla);

	if (casilla.estado == HIELO) colorFondo(PALETA[1]);
	else if (casilla.estado == MURO) colorFondo(PALETA[2]);
	else if (casilla.estado == CAJA) colorFondo(PALETA[3]);
	else if (casilla.estado == JOYA) colorFondo(PALETA[4]);
	else if (casilla.estado == VACIA) colorFondo(PALETA[0]);
	else {//tortuga
		if (casilla.tort.ident == 1) colorFondo(PALETA[5]);
		else if (casilla.tort.ident == 2) colorFondo(PALETA[6]);
		else if (casilla.tort.ident == 3) colorFondo(PALETA[7]);
		else if (casilla.tort.ident == 4) colorFondo(PALETA[8]);
	}

	arch << cas;
	colorFondo(0);
	return arch;
}

std::ostream & operator << (std::ostream & arch, const tTablero & tablero) {
	for (int f = 0; f < tablero.size(); ++f) {
		for (int c = 0; c < tablero[0].size(); ++c) {
			arch << tablero[f][c];
		}
		std::cout << '\n';
	}
	return arch;
}

void colorFondo(int color) {
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(handle, 15 | (color << 4));
}

void mostrarTablero(const tTablero & tablero) {
	std::cout << tablero;
}

bool cargar(const std::string & nomfich, tTablero & tablero, int njugadores, std::vector<tCoordenada>& Vcoord) {
	bool b=true;
	std::string linea;
	std::ifstream fich;

	//fich.open("nomfich"); COMENTADO PARA EVITAR ERRORES AL INTRODUCIR EL NOMBRE AL DEPURAR
	fich.open("tableros.txt");
	
	if(fich.is_open()){

	getline(fich, linea);
	std::stringstream ss; ss << linea;
	int ntortugas;
	ss >> ntortugas;
	ss.clear();

	while (ntortugas != njugadores) {

		for (int i = 0; i<DIMENSION; i++) getline(fich, linea);

		getline(fich, linea);
		ss << linea;
		ss >> ntortugas;
		ss.clear();
	}
	int numtort = 1;
	
	tCoordenada asdf;
	for (int f = 0; f < DIMENSION; ++f) {
		getline(fich, linea);
		for (int j = 0; j < DIMENSION; j++) {
			tablero[f][j] = char2casilla(linea[j], numtort);
			if (tablero[f][j].estado == TORTUGA) {
				numtort++;
				
				asdf.x = f; asdf.y = j;
				Vcoord.push_back(asdf);
								
			}
		}
	}
	}
	else b=false;
	fich.close();
	return b;
}

bool compcoord(const tTablero & tablero, const tCoordenada & coord) {//comprueba si una casilla esta en el tablero

	return (coord.x < tablero.size() && coord.y < tablero.size() && coord.x >= 0 && coord.y >= 0);
}

void laser(tTablero & tablero, const tCoordenada & coord, const tDir & dirtort) {
	int i = coord.x + incF[dirtort];
	int j = coord.y + incC[dirtort];
	bool noparar = true;
	while (i>=0 && j>=0 && i<DIMENSION && j<DIMENSION && noparar) {

		if (tablero[i][j].estado == HIELO) {
			tablero[i][j].estado = VACIA;
			noparar = false;
		}
		else if (tablero[i][j].estado != VACIA) {
			noparar = false;
		}

		i = i + incF[int(dirtort)];
		j = j + incC[int(dirtort)];
	}

}


bool caja(const tTablero & tablero, tCoordenada  coordenada, const tDir & direccion) {
	bool b = false;

	coordenada.x += incF[direccion];
	coordenada.y += incC[direccion];
	bool x = compcoord(tablero, coordenada);
	if (x && tablero[coordenada.x][coordenada.y].estado == VACIA) b = true;
	return b;
}

bool movPosible(const tTablero & tablero, tCoordenada coord, const tDir & direccion) {
	bool mover = false;

	coord.x += incF[direccion];
	coord.y += incC[direccion];

	bool pcaja = caja(tablero, coord, direccion);

	if (compcoord(tablero, coord) && (tablero[coord.x][coord.y].estado == VACIA || tablero[coord.x][coord.y].estado == JOYA
		|| (tablero[coord.x][coord.y].estado == CAJA && pcaja))) mover = true;

	return mover;
}

void avanzar(tTablero & tablero, const tDir & direccion, tCoordenada & coordenada) {

	if (tablero[coordenada.x + incF[direccion]][coordenada.y + incC[direccion]].estado == CAJA) {//si hay una caja en la posicion a la que vas
																								 
		//mover caja
		tablero[coordenada.x + 2*incF[direccion]][coordenada.y + 2*incC[direccion]].estado = CAJA;
	}

	//mover totuga
	tablero[coordenada.x + incF[direccion]][coordenada.y + incC[direccion]] = tablero[coordenada.x][coordenada.y];
	
	//casilla vacia en la que estaba la tortuga	
	tablero[coordenada.x][coordenada.y].estado = VACIA;

	coordenada.x += incF[direccion];
	coordenada.y += incC[direccion];
}

// incremento prefijo
tDir operator++(tDir & dir) {
	dir = tDir((int(dir) + 1) % NUM_DIRECCIONES);
	return dir;
}
// decremento prefijo
tDir operator--(tDir & dir) {
	if (int(dir) == 0) dir = tDir(NUM_DIRECCIONES-1);
	else dir = tDir((int(dir) - 1));
	return dir;
}

