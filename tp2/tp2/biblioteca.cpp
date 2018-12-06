#include "biblioteca.h"

int Emprestimo::proximoNumero = 1;

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

void Biblioteca::excluirUser(const Usuario &user) {
	for (int i = 0; i < emprestimos.size(); i++)
		if (emprestimos[i].get().getUser().getCPF() == user.getCPF())
			throw Erro("Usuario possui emprestimos e nao pode ser excluido");
	for (int i = 0; i < usuarios.size(); i++)
		if (usuarios[i].get().getCPF() == user.getCPF()) {
			usuarios.erase(usuarios.begin() + i);
			break;
		}
}

void Biblioteca::excluirPub(const Publicacao &pub) {
	for (int i = 0; i < emprestimos.size(); i++)
		for (int j = 0; j < emprestimos[i].get().getItens().size(); j++)
			if (emprestimos[i].get().getItens()[j].getLivro().getCodPub() == pub.getCodPub())
				throw Erro("Publicacao possui emprestimos e nao pode ser excluida");
	for (int i = 0; i < publicacoes.size(); i++)
		if (publicacoes[i].get().getCodPub() == pub.getCodPub()) {
			publicacoes.erase(publicacoes.begin() + i);
			break;
		}
}

void Biblioteca::excluirEmp(const Emprestimo &emp) {
	for (int i = 0; i < emprestimos.size(); i++)
		if (emprestimos[i].get().getNumero() == emp.getNumero()) {
			emprestimos.erase(emprestimos.begin() + i);
			break;
		}
}

void Biblioteca::inserirItemEmp(Emprestimo &emp, Livro &book) { 
	for (int i = 0; i < emprestimos.size(); i++)
		if (emprestimos[i].get().getNumero() == emp.getNumero()) {
			emprestimos[i].get().addItem(book);
			break;
		}
};

void Biblioteca::excluirItemEmp(Emprestimo &emp, Livro &book) {
	for (int i = 0; i < emprestimos.size(); i++)
		if (emprestimos[i].get().getNumero() == emp.getNumero()) {
			emprestimos[i].get().remvItem(book);
			break;
		}
};

void Biblioteca::devolverItem(Emprestimo &emp, Livro &book) {
	for (int i = 0; i < emprestimos.size(); i++)
		if (emprestimos[i].get().getNumero() == emp.getNumero()) {
			emprestimos[i].get().devolver(book);
			break;
		}
};

void Biblioteca::devolvertodosItens(Emprestimo &emp) {
	for (int i = 0; i < emprestimos.size(); i++)
		if (emprestimos[i].get().getNumero() == emp.getNumero()) {
			emprestimos[i].get().devolvertodos();
			break;
		}
};

std::vector<Publicacao> Biblioteca::pesqPub(const std::string &pesquisa) const {
	std::vector<Publicacao> resultado;
	for (int i = 0; i < publicacoes.size(); i++) {
		size_t found = publicacoes[i].get().getTitulo().find(pesquisa);
		if (found != std::string::npos)
			resultado.push_back(publicacoes[i]);
	}
	return resultado;
}

std::vector<std::reference_wrapper<Publicacao>> Biblioteca::pesqLivro(const std::string &pesquisa) {
	std::vector<std::reference_wrapper<Publicacao>> resultado;
	for (int i = 0; i < publicacoes.size(); i++) {
		Publicacao *pub = &publicacoes[i].get();
		Livro *book = dynamic_cast<Livro*>(pub); // downcasting 
		if (book != 0) {
			size_t found = book[0].getAutores().find(pesquisa);
			if (found != std::string::npos)
				resultado.push_back(publicacoes[i]);
		}
	}
	return resultado;
}

void Emprestimo::addItem(Livro &book) {
	if (difftime(mktime(&usuario.getdataPen()), time(NULL)) <= 0) {
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
	if (penalizacao <= 0) {
		int dias = abs(penalizacao / SECONDS_TO_DAYS);
		data.tm_mday += 3*dias;
		if (difftime(mktime(&usuario.getdataPen()), mktime(&data)) <= 0) // usuário já tem penalização maior?
			usuario.setdataPen(data);
	}
}

void Emprestimo::devolvertodos() {
	time_t t = time(NULL);
	tm data = *localtime(&t);
	for (int i = 0; i < itens.size(); i++) {
			itens[i].setdataDev(data);
			itens[i].getLivro().incQtdeExemplares();
		}
	double penalizacao = difftime(mktime(&dataPrevDevolucao), t);
	if (penalizacao <= 0) {
		int dias = abs(penalizacao / SECONDS_TO_DAYS);
		data.tm_mday += 3*dias;
		if (difftime(mktime(&usuario.getdataPen()), mktime(&data)) <= 0) // usuário já tem penalização maior?
			usuario.setdataPen(data);
	}
}
