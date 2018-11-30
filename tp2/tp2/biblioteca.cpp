#include "biblioteca.h"

int Emprestimo::proximoNumero = 0;

void init_tm_null(tm &tms) {
	tms.tm_hour = 0;
	tms.tm_sec = 0;   // seconds after the minute - [0, 60] including leap second
	tms.tm_min = 0;   // minutes after the hour - [0, 59]
	tms.tm_hour = 0;  // hours since midnight - [0, 23]
	tms.tm_mday = 0;  // day of the month - [1, 31]
	tms.tm_mon = 0;   // months since January - [0, 11]
	tms.tm_year = 0;  // years since 1900
	tms.tm_wday = 0;  // days since Sunday - [0, 6]
	tms.tm_yday = 0;  // days since January 1 - [0, 365]
	tms.tm_isdst = 0; // daylight savings time flag
}

void Biblioteca::excluirUser(Usuario &user) {
	for (int i = 0; i < emprestimos.size; i++)
		if (emprestimos[i].getUser() == user)
			throw Erro("Usuario possui emprestimos e nao pode ser excluido");
	for (int i = 0; i < usuarios.size; i++)
		if (usuarios[i] == user)
			usuarios.erase(usuarios.begin() + i);
}

void Biblioteca::excluirPub(Publicacao &pub) {
	for (int i = 0; i < emprestimos.size; i++)
		for (int j = 0; j < emprestimos[i].getItens().size; i++)
			if (emprestimos[i].getItens()[j].getLivro() == pub)
				throw Erro("Publicacao possui emprestimos e nao pode ser excluida");
	for (int i = 0; i < publicacoes.size; i++)
		if (publicacoes[i] == pub)
			publicacoes.erase(publicacoes.begin() + i);
}

void Biblioteca::excluirEmp(Emprestimo &emp) {
	for (int i = 0; i < emprestimos.size; i++)
		if (emprestimos[i] == emp)
			emprestimos.erase(emprestimos.begin() + i);
}

vector<Publicacao> Biblioteca::pesqPub(string &pesquisa) {

}

vector<Livro> Biblioteca::pesqAutor(string &pesquisa) {

}

void Biblioteca::grava(ostream arquivo) const {
	for(int i = 0; i < usuarios.size; i++)
		arquivo.write((char *)&usuarios[i], sizeof(Usuario));
	for (int i = 0; i < publicacoes.size; i++)
		arquivo.write((char *)&publicacoes[i], sizeof(Publicacao));
	for (int i = 0; i < emprestimos.size; i++)
		arquivo.write((char *)&emprestimos[i], sizeof(Emprestimo));
}

void Biblioteca::le(istream arquivo) {
	for (int i = 0; i < usuarios.size; i++)
		arquivo.read((char *)&usuarios[i], sizeof(Usuario));
	for (int i = 0; i < publicacoes.size; i++)
		arquivo.read((char *)&publicacoes[i], sizeof(Publicacao));
	for (int i = 0; i < emprestimos.size; i++)
		arquivo.read((char *)&emprestimos[i], sizeof(Emprestimo));
}

void Emprestimo::addItem(Livro &book) {
	if (difftime(time(NULL), mktime(&usuario.getdataPen())) < 0) {
		book.decQtdeExemplares();
		ItemEmprestimo item(book);
		itens.push_back(item);
	}
	else throw Erro("Usuario penalizado");
}

void Emprestimo::remvItem(Livro &book) {
	for (int i = 0; i < itens.size(); i++)
		if (itens[i].getLivro().getCodPub() == book.getCodPub()) {
			itens.erase(itens.begin() + i);
			book.incQtdeExemplares();
			break;
		}
}

void Emprestimo::devolver(Livro &book) {
	time_t t = time(NULL);
	tm data = *localtime(&t);
	for (int i = 0; i < itens.size(); i++)
		if (itens[i].getLivro().getCodPub() == book.getCodPub()) {
			itens[i].setdataDev(data);
			book.incQtdeExemplares();
			break;
		}
	double penalizacao = difftime(mktime(&dataPrevDevolucao), t);
	if (penalizacao < 0) {
		int dias = penalizacao / SECONDS_TO_DAYS;
		data.tm_mday += dias;
		if (difftime(mktime(&usuario.getdataPen()), mktime(&data)))
			usuario.setdataPen(data);
	}
}

void Emprestimo::devolvertodos() {
	time_t t = time(NULL);
	for (int i = 0; i < itens.size(); i++) {
		itens[i].setdataDev(*localtime(&t));
		itens[i].getLivro().incQtdeExemplares();
	}
}
