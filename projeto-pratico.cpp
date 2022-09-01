#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct cadastro{      // CRIANDO REGISTRO DE CADASTRO
	char nome[50];
	long long int cpf;
	long int matricula;
	char endereco[50];
	char telefone[20];
	char email[150];
	int situacao;
};

string cadastrar(){         // CADASTRO DE USUARIOS EM ARQUIVO BINARIO
	cadastro user, busca;
	fstream ler("usuarios.dat", ios::in|ios::ate);
	ofstream gravar("usuarios.dat", ios::app);
	string nome, end, email;
	int sit;
	cout << "Nome do usuario:\n";
	cin.ignore();
	getline(cin, nome);
	int x=nome.size();
	for(int i = 0; i < x; i++)
		user.nome[i] = nome[i];
	cout << "CPF:\n";
	cin.ignore();
	cin >> user.cpf;
	cout << "Numero de matricula:\n";
	cin >> user.matricula;
	cin.ignore();
	cout << "Endereco:\n";
	cin.ignore();
	getline(cin, end);
	int n=end.size();
	for(int i = 0; i < n; i++)
		user.endereco[i] = end[i];
	cout << "Telefone:\n";
	cin.ignore();
	cin >> user.telefone;
	cout << "Email:\n";
	cin.ignore();
	getline(cin,email);
	int t=email.size();
	for(int i=0;i<t;i++){
		user.email[i] = email[i]; 
	}
	user.situacao = 1;
	sit = user.situacao;
	long long int bytes = ler.tellg();
	int num_users = int(bytes/sizeof(cadastro));
	int cont = 0;
	bool erro = false;
	if(ler){
		while (cont < num_users){
			ler.seekg(cont*sizeof(cadastro));
			ler.read((char*)&busca, sizeof(cadastro));
			if(user.cpf == busca.cpf)
				erro = true;
			cont++;
		}
	}
	if(erro == true and user.situacao == 1)
		return "\nERRO! ESSE CPF JA POSSUI USUARIO CADASTRADO!\n\n";
	else {
		gravar.write((const char*)(&user), sizeof(cadastro));
		gravar.close();
		return "\nCADASTRO EFETUADO COM SUCESSO!\n\n";
	}
}
/*string consultar_livros(){
	fstream ler("emprestimos.dat");

}*/

void listar_ativos(){       //LISTAGEM DE USUARIOS ATIVOS
	fstream ler("usuarios.dat", ios::in|ios::ate);
	ofstream gravar("usuarios.dat", ios::app);
	long long int bytes = ler.tellg();
	int num_users = int(bytes/sizeof(cadastro));
	int cont = 0;
	cadastro busca;
	int ativo = 1;
	if(ler){
		while (cont < num_users){
			ler.seekg(cont*sizeof(cadastro));
			ler.read((char*)&busca, sizeof(cadastro));
			bool ok = true;
			if(busca.situacao != 1)
				ok = false;
			if(ok){
				for(int i = 0; i < strlen(busca.nome); i++)
					cout << busca.nome[i];
				cout << " " << busca.matricula << " ";
				for(int i = 0; i < strlen(busca.email); i++)
					cout << busca.email[i];
				cout << endl;
			}
			cont++;
		}
	}
}

void excluir_dados(){      //EXCLUSAO DE DADOS
	cadastro usuario;
	string nome;
	long int matricula;
	int cont = 0, confirmar,novasit;
	fstream ler("usuarios.dat", ios::in);
	ofstream grava("usuarios.dat");
	cout << "Numero de matricula:\n";
	cin >> matricula;
	cout << "\nNome do usuario: ";
	cin.ignore();
	getline(cin,nome);
	cout << "Comfirma exclusao? 1-sim 2-nao \n";
	cin >> confirmar;
	if(confirmar == 1)
		novasit = 0;
	else
		novasit = 1;
	if(ler){
		bool ok=false;
		long int tamanhob=ler.tellg();
		long long int num_regs=int(tamanhob/sizeof(cadastro));
		while ((cont < num_regs)  and (ok)){
      		ler.seekp(cont*sizeof(cadastro));
      		ler.read((char*) &usuario, sizeof(cadastro));
      		if (usuario.matricula == matricula){
          		ler.seekp((cont)*sizeof(cadastro));
				usuario.situacao = novasit;
          		grava.write((char*)(&usuario), sizeof(cadastro));
          		ok=0;
      		}
      		cont++;
  		}
	}
	ler.close();
	if(usuario.matricula == matricula){
		cout << "\nNome do usuario: " << nome << endl;
		if(usuario.situacao == 1)
			cout << "situacao: ativo" << endl;
		else
			cout << "situacao: inativo" << endl;
	}
	else{
		usuario.situacao = 1;
		cout << "Matricula nao encontrada\n";
	}
	grava.write((char*)(&usuario), sizeof(cadastro));
	grava.close();
}

/*string efetuar_emprestimo(){
	long long int matricula, numero;
	string livro, data;
	cout << "Numero de matricula:\n";
	cin >> matricula;
	cout << "Nome do livro a ser emprestado:\n";
	cin.ignore();
	getline(cin, livro);
	cout << "Data de devolucao:\n";
	cin >> data;
	return "\nEmprestimo realizado com sucesso!";
	ifstream ler("emprestimos");
	ofstream gravar("emprestimos");
	while(ler){
	}
}*/


int main(){
	int opcao = 0;
	while (opcao != 8){
		cout << "----- MENU PRINCIPAL -----\n\n";
		cout << "[1] - Cadastrar novo usuario" << endl
			<< "[2] - Consultar emprestimos" << endl
			<< "[3] - Ver usuarios ativos" << endl
			<< "[4] - Excluir usuario" << endl
			<< "[5] - Efetuar emprestimo" << endl
			<< "[6] - Efetuar devolucao" << endl
			<< "[7] - Exportar contas" << endl
			<< "[8] - Sair" << endl
			<< "Escolha uma opcao: "; //impressão do menu
		cin >> opcao; //escolha da ação pelo usuário
		if(opcao == 1)
			cout << cadastrar();
		else if(opcao == 3)
			listar_ativos();
		else if(opcao == 4)
			excluir_dados();
		
		/*else if(opcao == 5)
			cout << efetuar_emprestimo();*/
		else if(opcao != 8)
			cout << "Digite uma opcao valida";
	}
	cout << "\nEncerrando o sistema...\n\n";

	return 0;
}
