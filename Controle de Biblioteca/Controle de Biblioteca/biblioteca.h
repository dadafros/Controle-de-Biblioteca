#include <iostream>
#include <vector>
#include <ctime>
#include <string>

using namespace std;
//carla passou aqui
#ifndef Biblioteca_H
#define Biblioteca_H
class Biblioteca {
private:
	vector<Usuario> usuarios;
	vector<Publicacao> publicacoes;
	vector<Emprestimo> emprestimos;
public:
	inline void inserirUser(const Usuario user) { usuarios.push_back(user); };
	void excluirUser(Usuario user);
	inline void inserirPub(const Publicacao pub) { publicacoes.push_back(pub); };
	void excluirPub(Publicacao pub);
	inline void inserirEmp(const Emprestimo emp) { emprestimos.push_back(emp); };
	void excluirEmp(Emprestimo emp);
	inline vector<Usuario> getUser() const { return usuarios; };
	inline vector<Publicacao> getPub() const { return publicacoes; };
	inline vector<Emprestimo> getEmp() const { return emprestimos; };
	vector<Publicacao> pesqPub(string pesquisa);
	vector<Livro> pesqAutor(string pesquisa);
	void grava(ostream arquivo) const;
	void le(istream arquivo);
};
#endif

#ifndef Usuario_H
#define Usuario_H
class Usuario {
private:
	string nome;
	string cpf;
	string endereco;
	string fone;
	tm *dataPenalizacao;
public:
	Usuario(string n, string doc, string addr, string phone) : nome(n), cpf(doc), endereco(addr), fone(phone) { time_t t = time(NULL); dataPenalizacao = localtime(&t); };
};
#endif

#ifndef Publicacao_H
#define Publicacao_H
class Publicacao {
private:
	int codPublicacao;
	string titulo;
	string editora;
	string ano;
public:
	Publicacao(int cod, string tit, string ed, string year) : codPublicacao(cod), titulo(tit), editora(ed), ano(year) {};
	inline int getCodPub() { return codPublicacao; };
};
#endif

#ifndef Livro_H
#define Livro_H
class Livro : public Publicacao {
private:
	string autores;
	int qtdeExemplares;
public:
	Livro(int cod, string tit, string ed, string year, string aut, int qtde = 0) : Publicacao(cod, tit, ed, year), autores(aut), qtdeExemplares(qtde) {};
	inline void inc() { qtdeExemplares++; };
	inline void dec() { if (qtdeExemplares > 0) qtdeExemplares--; else throw Erro("Quantidade de Exemplares Insuficiente"); };
	inline int getQtdeExemplares() { return qtdeExemplares; };
};
#endif

#ifndef Periodico_H
#define Periodico_H
class Periodico : public Publicacao {
private:
	int numEdicao;
	string mes;
public:
	Periodico(int cod, string tit, string ed, string year, int numed, string month) : Publicacao(cod, tit, ed, year), numEdicao(numed), mes(month) {};
};
#endif

#ifndef Emprestimo_H
#define Emprestimo_H
class Emprestimo {
private:
	int numero;
	tm *dataEmprestimo;
	tm *dataPrevDevolucao;
	Usuario usuario;
	vector <ItemEmprestimo> itens;
	static int proximoNumero;
public:
	Emprestimo(tm *dataPDev, Usuario user) : dataPrevDevolucao(dataPDev), usuario(user) { numero = proximoNumero++; time_t t = time(NULL); dataEmprestimo = localtime(&t); };
	void addItem(Livro book);
	void remvItem(Livro book);
	void devolver(Livro book);
	void devolvertodos();
	inline Usuario getUser() { return usuario; };
	inline vector <ItemEmprestimo> getItens() { return itens; };
};
#endif

#ifndef ItemEmprestimo_H
#define ItemEmprestimo_H
class ItemEmprestimo {
private:
	tm *dataDevolucao;
	Livro livro;
public:
	ItemEmprestimo(Livro book) : livro(book), dataDevolucao(NULL) {};
	Livro getLivro() { return livro; };
	void setdataDev(tm *data) { dataDevolucao = data; };
};
#endif

#ifndef Erro_H
#define Erro_H
class Erro {
private:
	string tipo_erro;
public:
	Erro(const string &tp) : tipo_erro(tp) {};
	void out() { cout << tipo_erro; };
};
#endif
