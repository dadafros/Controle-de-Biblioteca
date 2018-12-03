#include "biblioteca.h"

using namespace std;

int main() {
	//construção de usuários, livros e periodicos
	Usuario davi("Davi", "0945133113", "UFMG street, 21", "(31)2535-9052");
	Usuario carla("Carla", "12345678", "UFMG street2, 01", "(31)3464-9052");
	Livro biblia(777, "holy bible", "Editora Moishe", "131", "Jesus de Nazaré", 100);
	Livro kalman(3, "Filtro de Kalman para cura do câncer", "Editora Dada", "2018", "Davi Frossard de Jesus", 5);
	Livro quebra(8, "Pau quebra no Kalman", "IEEE", "2017", "Carla Perez", 2);
	Periodico artigo(8, "Robo móvel", "IEEE", "2017", 1, "fevereiro");

	time_t t = time(NULL); // declaração de um empréstimo com data de devolução para daqui 4 dias
	tm dataDev = *localtime(&t);
	dataDev.tm_mday += 4;
	mktime(&dataDev);
	Emprestimo proDavi(dataDev, davi);
	Emprestimo praCarla(dataDev, carla);

	Biblioteca bib; // declaração de uma biblioteca
	bib.inserirUser(davi); // inserção de usuários na biblioteca
	bib.inserirUser(carla);
	bib.inserirPub(biblia); // inserção de publicações na biblioteca
	bib.inserirPub(kalman);
	bib.inserirPub(quebra);
	bib.inserirPub(artigo);
	bib.inserirEmp(proDavi); // inserção de empréstimos na biblioteca
	bib.inserirEmp(praCarla);
	bib.inserirItemEmp(proDavi, biblia); // inserção de itens aos empréstimos da biblioteca
	bib.inserirItemEmp(proDavi, kalman);
	bib.inserirItemEmp(proDavi, quebra);
	bib.inserirItemEmp(praCarla, kalman);
	bib.inserirItemEmp(praCarla, quebra);

	vector<Emprestimo> resultado1 = bib.getEmp(); // obtém os registros da biblioteca (emprestimos, publicações e usuários)
	vector<std::reference_wrapper<Publicacao>> resultado2 = bib.getPub();
	vector<Usuario> resultado3 = bib.getUser();
	
	vector<Publicacao> resultado4 = bib.pesqPub("Kalman"); // pesquisas nas publicações da biblioteca
	vector<Publicacao> resultado5 = bib.pesqLivro("Jesus");

	system("pause");
}