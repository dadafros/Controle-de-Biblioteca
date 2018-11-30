#include "biblioteca.h"

int main() {
	Usuario davi("Davi", "0945133113", "UFMG street, 21", "(31)2535-9052");
	Livro biblia(777, "holy bible", "Editora Moishe", "131", "Jesus de Nazaré", 100);
	Livro kalman(3, "Filtro de Kalman para cura do câncer", "Editora Dada", "2018", "Davi Frossard", 5);
	Livro quebra(8, "Pau quebra", "IEEE", "2017", "Carla Perez", 1);

	time_t t = time(NULL); 
	tm dataDev = *localtime(&t);
	dataDev.tm_mday += 4;
	mktime(&dataDev);
	Emprestimo proDavi(dataDev, davi);
	proDavi.addItem(biblia);
	proDavi.addItem(kalman);
	proDavi.addItem(quebra);
	proDavi.devolver(biblia);
	proDavi.remvItem(kalman);
	

	system("pause");
}