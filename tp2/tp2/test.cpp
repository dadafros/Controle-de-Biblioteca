#include "biblioteca.h"

int main() {
	Usuario davi("Davi", "0945133113", "UFMG street, 21", "(31)2535-9052");
	Livro biblia(777, "holy bible", "Editora Moishe", "131", "Jesus de Nazaré", 100);
	Periodico journal(777, "filtro de Kalman", "IEEE", "2017", 3, "fevereiro");

	time_t t = time(NULL); 
	tm *dataDev = localtime(&t);
	dataDev->tm_mday += 4;
	mktime(dataDev);
	Emprestimo proDavi(dataDev, davi);
	proDavi.addItem(biblia);

	system("pause");
}