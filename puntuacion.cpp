//Andrea Peña Calvin

#include "puntuacion.h"

void iniciar(tPuntuaciones & punt) {
	punt.capacidad = TAM_INI_ARRAY;
	punt.num_jugadores = 0;
	punt.array_clasificacion = new tPunt_nom*[TAM_INI_ARRAY];
}

void redimensionar(tPuntuaciones & clasificacion) {

	tPunt_nom ** aux = clasificacion.array_clasificacion;
	clasificacion.array_clasificacion = new tPunt_nom*[clasificacion.capacidad + 4];
	for (int i = 0; i < clasificacion.num_jugadores; i++) 
		clasificacion.array_clasificacion[i] = aux[i];
	delete[] aux;
	clasificacion.capacidad += 4;
	
}

void escribirFichero(const tPuntuaciones & punt) { //escribe en el fichero los resultados
	std::string jug;
	bool igual = false;
	std::ofstream fichero;

	fichero.open(FICH_PUNT);

	if (fichero.is_open()) {

		for (int i = 0; i < punt.num_jugadores; i++) {
			fichero << punt.array_clasificacion[i]->jugador << " " << punt.array_clasificacion[i]->puntos << '\n';
		}
	}

	fichero.close();
}

void leerFichero(tPuntuaciones & punt) { //carga las puntuaciones desde el fichero
	std::string a;
	int c;
	
	std::ifstream ficheroI;
	ficheroI.open(FICH_PUNT);

	if (ficheroI.is_open()) {

		ficheroI >> a >> c;
		
		while (!ficheroI.fail()) {
			
			if (punt.capacidad == punt.num_jugadores) redimensionar(punt);
			    
			punt.array_clasificacion[punt.num_jugadores] = new tPunt_nom;
				punt.array_clasificacion[punt.num_jugadores]->jugador=a;
				punt.array_clasificacion[punt.num_jugadores]->puntos = c;
				ficheroI >> a >> c;
				punt.num_jugadores++;			
		}
	}

	else std::cout << "NO se ha podido abrir el fichero que carga las puntuaciones" << '\n';
	ficheroI.close();
}

void mostrarpuntuaciones(const tPuntuaciones & punt) {
	for (int i = 0; i < punt.num_jugadores; i++) 
		std::cout << punt.array_clasificacion[i]->jugador << ": " << punt.array_clasificacion[i]->puntos << '\n';
	
	std::cout << '\n';
}

std::string minus(std::string const & pal) {
	std::string palabra = pal;
	for (int i = 0; i < palabra.size(); i++)
		if ('A' <= palabra[i] && palabra[i] <= 'Z')
			palabra[i] = 'a' + (palabra[i] - 'A');
	return palabra;
}

void ordenar_alf(tPuntuaciones & puntu) {
	size_t N = puntu.num_jugadores;

	for (size_t i = 1; i < N; ++i) {
		std::string elemento = puntu.array_clasificacion[i]->jugador;
		int element2 = puntu.array_clasificacion[i]->puntos;
		size_t j = i;

		while (j > 0 && minus(elemento) < minus(puntu.array_clasificacion[j - 1]->jugador)) {
			puntu.array_clasificacion[j]->puntos = puntu.array_clasificacion[j - 1]->puntos;
			puntu.array_clasificacion[j]->jugador = puntu.array_clasificacion[j - 1]->jugador;
			--j;
		}
		if (j != i) {
			puntu.array_clasificacion[j]->puntos = element2;
			puntu.array_clasificacion[j]->jugador = elemento;
		}
	}

}

bool ord(tPunt_nom * p1, tPunt_nom * p2) {

	if (p1->puntos > p2->puntos) return true;
	else if (p1->puntos < p2->puntos) return false;
	else return minus(p1->jugador) < minus(p2->jugador);
}

bool buscarbin(tPuntuaciones const & punt, tPunt_nom* jug, int & pos) {
	int ini = 0, fin = punt.num_jugadores, mitad;
	bool encontrado = false;

	//ver si esta el jugador
	int i = 0;
	while (i < punt.num_jugadores && !encontrado) {
		if (jug->jugador == punt.array_clasificacion[i]->jugador)
			encontrado = true;
		else ++i;
	}
	//posicion en la que debe estar el nuevo jugador
	while (ini < fin && !encontrado) {
		mitad = (ini + fin - 1) / 2;
		if (ord(jug, punt.array_clasificacion[mitad])) fin = mitad;
		else if (ord(punt.array_clasificacion[mitad], jug)) ini = mitad + 1;
		//else encontrado = true; No deberia pasar

	}
	if (encontrado)pos = i;
	else pos = ini;


	return encontrado;
}

void existente(tPuntuaciones & puntu, const int & pos, const int & numjugadores) {
	int i = pos;//en la que esta
	bool colocado = false;

	puntu.array_clasificacion[pos]->puntos += numjugadores; //ACTUALIZAS SU PUNTUACION


	while (i > 0 && !colocado) {
		if (ord(puntu.array_clasificacion[i], puntu.array_clasificacion[i - 1]))
			std::swap(puntu.array_clasificacion[i], puntu.array_clasificacion[i - 1]);
		else colocado = true;
		--i;
	}
}

void actualizarPunt(tPuntuaciones & puntu, const tJugador & jug, const int & numjugadores) {
	//puntuacion del jugador==numjugadores
	bool encontrado;
	int pos;//posicion de la busq bin

	tPunt_nom* nuevo = new tPunt_nom;

	nuevo->jugador = jug.nombre;
	nuevo->puntos = numjugadores;

	//BUSQUEDA BINARIA
	encontrado = buscarbin(puntu, nuevo, pos);// , ord());//jugnombre vs tPunt_nom

	if (encontrado) {
		existente(puntu, pos, numjugadores);
		delete nuevo;
	}


	else {//nuevo jug
		  //ya se ha hecho la busqueda bin y sabes en que pos debe ir
		if (puntu.num_jugadores == puntu.capacidad) redimensionar(puntu);

		for (int i = puntu.num_jugadores; i > pos; --i) {
			puntu.array_clasificacion[i] = puntu.array_clasificacion[i - 1];
		}
		puntu.array_clasificacion[pos] = nuevo;

		puntu.num_jugadores++;

	}
	
}

void liberar(tPuntuaciones & clasificacion) {

	for (int i = 0; i < clasificacion.num_jugadores; i++) 
		delete clasificacion.array_clasificacion[i];


	delete[] clasificacion.array_clasificacion;
	clasificacion.array_clasificacion = nullptr;
	
	clasificacion.capacidad = 0;
	clasificacion.num_jugadores = 0;

}