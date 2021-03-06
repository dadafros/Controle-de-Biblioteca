#include <vector>
#include <ctime>
#include <string>
#include <functional>

#define SECONDS_TO_DAYS 86400

#ifndef Erro_H
#define Erro_H
class Erro {
private:
	std::string tipo_erro;
public:
	Erro(const std::string &tp) : tipo_erro(tp) {};
	inline std::string what() { return tipo_erro; };
};
#endif

#ifndef Usuario_H
#define Usuario_H
class Usuario {
private:
	std::string nome;
	std::string cpf;
	std::string endereco;
	std::string fone;
	tm dataPenalizacao;
public:
	Usuario(std::string n, std::string doc, std::string addr, std::string phone) : nome(n), cpf(doc), endereco(addr), fone(phone) { time_t t = time(NULL); dataPenalizacao = *localtime(&t); };
	inline void setdataPen(const tm &data) { dataPenalizacao = data; };
	inline tm getdataPen() const { return dataPenalizacao; };
	inline std::string getCPF() const { return cpf; };
};
#endif

#ifndef Publicacao_H
#define Publicacao_H
class Publicacao {
private:
	int codPublicacao;
	std::string titulo;
	std::string editora;
	std::string ano;
public:
	Publicacao(int cod, std::string tit, std::string ed, std::string year) : codPublicacao(cod), titulo(tit), editora(ed), ano(year) {};
	inline int getCodPub() const { return codPublicacao; };
	inline std::string getTitulo() const { return titulo; };
	virtual void dummy() {};
};
#endif

#ifndef Livro_H
#define Livro_H
class Livro : public Publicacao {
private:
	std::string autores;
	int qtdeExemplares;
public:
	Livro(int cod, std::string tit, std::string ed, std::string year, std::string aut, int qtde = 0) : Publicacao(cod, tit, ed, year), autores(aut), qtdeExemplares(qtde) {};
	inline void incQtdeExemplares() { qtdeExemplares++; };
	inline void decQtdeExemplares() { if (qtdeExemplares > 0) qtdeExemplares--; else throw Erro("Quantidade de Exemplares Insuficiente"); };
	inline int getQtdeExemplares() const { return qtdeExemplares; };
	inline std::string getAutores() const { return autores; };
};
#endif

#ifndef Periodico_H
#define Periodico_H
class Periodico : public Publicacao {
private:
	int numEdicao;
	std::string mes;
public:
	Periodico(int cod, std::string tit, std::string ed, std::string year, int numed, std::string month) : Publicacao(cod, tit, ed, year), numEdicao(numed), mes(month) {};
};
#endif

#ifndef ItemEmprestimo_H
#define ItemEmprestimo_H
class ItemEmprestimo {
private:
	tm dataDevolucao;
	Livro livro;
public:
	ItemEmprestimo(Livro &book) : livro(book) { init_tm_null(dataDevolucao); };
	inline Livro getLivro() const { return livro; };
	inline void setdataDev(const tm &data) { dataDevolucao = data; };
	friend void init_tm_null(tm &tms);
};
#endif

#ifndef Emprestimo_H
#define Emprestimo_H
class Emprestimo {
private:
	int numero;
	tm dataEmprestimo;
	tm dataPrevDevolucao;
	Usuario usuario;
	std::vector <ItemEmprestimo> itens;
	static int proximoNumero;
public:
	Emprestimo(tm &dataPDev, Usuario &user) : dataPrevDevolucao(dataPDev), usuario(user) { numero = proximoNumero++; time_t t = time(NULL); dataEmprestimo = *localtime(&t); };
	void addItem(Livro &book);
	void remvItem(Livro &book);
	void devolver(Livro &book);
	void devolvertodos();
	inline Usuario getUser() const { return usuario; };
	inline std::vector <ItemEmprestimo> getItens() const { return itens; };
	inline int getNumero() const { return numero; } ;
};
#endif

#ifndef Biblioteca_H
#define Biblioteca_H
class Biblioteca {
private:
	std::vector<std::reference_wrapper<Usuario>> usuarios;
	std::vector<std::reference_wrapper<Publicacao>> publicacoes;
	std::vector<std::reference_wrapper<Emprestimo>> emprestimos;
public:
	Biblioteca() {};
	inline void inserirUser(Usuario &user) { usuarios.push_back(user); };
	void excluirUser(const Usuario &user);
	inline void inserirPub(Publicacao &pub) { publicacoes.push_back(pub); };
	void excluirPub(const Publicacao &pub);
	inline void inserirEmp(Emprestimo &emp) { emprestimos.push_back(emp); };
	void excluirEmp(const Emprestimo &emp);
	void inserirItemEmp(Emprestimo &emp, Livro &book); 
	void excluirItemEmp(Emprestimo &emp, Livro &book); 
	void devolverItem(Emprestimo &emp, Livro &book); 
	void devolvertodosItens(Emprestimo &emp); 
	inline std::vector<std::reference_wrapper<Usuario>> getUser() const { return usuarios; };
	inline std::vector<std::reference_wrapper<Publicacao>> getPub() const { return publicacoes; };
	inline std::vector<std::reference_wrapper<Emprestimo>> getEmp() const { return emprestimos; };
	std::vector<Publicacao> pesqPub(const std::string &pesquisa) const;
	std::vector<std::reference_wrapper<Publicacao>> pesqLivro(const std::string &pesquisa);
};
#endif


