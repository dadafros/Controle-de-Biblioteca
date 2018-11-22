#include "biblioteca.h"


//void Biblioteca::excluirUser(Usuario user) {
//	for (int i = 0; i < emprestimos.size; i++)
//		if (emprestimos[i].getUser() == user)
//			throw Erro("Usuario possui emprestimos e nao pode ser excluido");
//	for (int i = 0; i < usuarios.size; i++)
//		if (usuarios[i] == user)
//			usuarios.erase(usuarios.begin() + i);
//}
//
//void Biblioteca::excluirPub(Publicacao pub) {
//	for (int i = 0; i < emprestimos.size; i++)
//		for (int j = 0; j < emprestimos[i].getItens().size; i++)
//			if (emprestimos[i].getItens()[j].getLivro() == pub)
//				throw Erro("Publicacao possui emprestimos e nao pode ser excluida");
//	for (int i = 0; i < publicacoes.size; i++)
//		if (publicacoes[i] == pub)
//			publicacoes.erase(publicacoes.begin() + i);
//}
//
//void Biblioteca::excluirEmp(Emprestimo emp) {
//	for (int i = 0; i < emprestimos.size; i++)
//		if (emprestimos[i] == emp)
//			emprestimos.erase(emprestimos.begin() + i);
//}
//
//vector<Publicacao> Biblioteca::pesqPub(string pesquisa) {
//
//}
//
//vector<Livro> Biblioteca::pesqAutor(string pesquisa) {
//
//}
//
//void Biblioteca::grava(ostream arquivo) const {
//	for(int i = 0; i < usuarios.size; i++)
//		arquivo.write((char *)&usuarios[i], sizeof(Usuario));
//	for (int i = 0; i < publicacoes.size; i++)
//		arquivo.write((char *)&publicacoes[i], sizeof(Publicacao));
//	for (int i = 0; i < emprestimos.size; i++)
//		arquivo.write((char *)&emprestimos[i], sizeof(Emprestimo));
//}
//
//void Biblioteca::le(istream arquivo) {
//	for (int i = 0; i < usuarios.size; i++)
//		arquivo.read((char *)&usuarios[i], sizeof(Usuario));
//	for (int i = 0; i < publicacoes.size; i++)
//		arquivo.read((char *)&publicacoes[i], sizeof(Publicacao));
//	for (int i = 0; i < emprestimos.size; i++)
//		arquivo.read((char *)&emprestimos[i], sizeof(Emprestimo));
//}

void Emprestimo::addItem(Livro book) {
	ItemEmprestimo item(book);
	if (item.getLivro().getQtdeExemplares > 0) {
		itens.push_back(item);
		item.getLivro().dec();
	}
	else
		throw Erro("Quantidade de Exemplares Insuficiente");
}

void Emprestimo::remvItem(Livro book) {
	for (int i = 0; i < itens.size; i++)
		if (itens[i].getLivro().getCodPub() == book.getCodPub()) {
			itens.erase(itens.begin() + i);
			itens[i].getLivro().inc();
		}
}

void Emprestimo::devolver(Livro book) {
	time_t t = time(NULL);
	for (int i = 0; i < itens.size; i++)
		if (itens[i].getLivro().getCodPub() == book.getCodPub()) {
			itens[i].setdataDev(localtime(&t));
			book.inc();
		}
}

void Emprestimo::devolvertodos() {
	time_t t = time(NULL);
	for (int i = 0; i < itens.size; i++) {
		itens[i].setdataDev(localtime(&t));
		itens[i].getLivro().inc();
	}
}
