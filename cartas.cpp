//Andrea Peña Calvin

#include "cartas.h"

std::ostream & operator << (std::ostream & arch, const tMazo & mazo) {
	std::string a;
	for (int i = 0; i < NUMEROCARTAS; i++) {
		arch << mazo.lista[(i + mazo.inicio) % NUMEROCARTAS] << ' ';
	}
	std::cout << '\n';
	return arch;
}

std::ostream & operator << (std::ostream & arch, const tCarta & carta) {
	std::string a;
	switch (carta) {
	case AVANZAR: a = "A"; break;
	case GIRODERECHA: a = "GD"; break;
	case GIROIZQUIERDA: a = "GI"; break;
	case LASER: a = "L"; break;

	}
	arch << a;
	return arch;
}

tCarta string2carta(std::string const& s) {
	tCarta c;
	if (s == "AVANZAR") c = AVANZAR;
	else if (s == "GIRODERECHA")  c = GIRODERECHA;
	else if (s == "GIROIZQUIERDA") c = GIROIZQUIERDA;
	else c = LASER;
	return c;
}

void crearMazoAleatorio(tMazo & mimazo) {
	
	mimazo.numelem = NUMEROCARTAS;
	
	for (int i = 0; i < NUMEROCARTAS; i++) mimazo.lista[i] = new tCarta;

	for (int i = 0; i < CARTASAVANZA; i++) *(mimazo.lista[i])=AVANZAR;
	for (int i = CARTASAVANZA; i < CARTASAVANZA+CARTASGI; i++)  *(mimazo.lista[i])=GIROIZQUIERDA;
	for (int i = CARTASAVANZA+CARTASGI; i < CARTASAVANZA + CARTASGI+CARTASGD; i++)  *(mimazo.lista[i])=GIRODERECHA;
	for (int i = CARTASAVANZA + CARTASGI + CARTASGD; i < NUMEROCARTAS; i++)  *(mimazo.lista[i])=LASER;

	std::random_shuffle(mimazo.lista, mimazo.lista+NUMEROCARTAS);

	mimazo.final = 0;
	mimazo.inicio = 0;

}

bool cogerCarta(tMazo & mazo, tCarta & carta) {
	bool existecarta;
	if (mazo.numelem == 0) existecarta = false;
	else {
		existecarta = true;
		carta = *(mazo.lista[mazo.inicio]);
		mazo.inicio = (mazo.inicio + 1) % NUMEROCARTAS;
		mazo.numelem--;
	}
	return existecarta;
}

void devolverCarta(tMazo & mazo, tArrayCartas & vec, const int & tamaarray) {

	std::random_shuffle(vec, vec+tamaarray);

	for (int i = 0; i < tamaarray; i++) {
	
		*mazo.lista[mazo.final] = *vec[i];
		mazo.final = (mazo.final + 1) % NUMEROCARTAS;
	}

	mazo.numelem = mazo.numelem + tamaarray;
	
}

void liberar(tMazo & mazo) {
	
	for (int i = 0; i < mazo.numelem; i++) {
		delete mazo.lista[i];
	}
	mazo.numelem = 0;
	mazo.final = 0;
	mazo.inicio = 0;
}