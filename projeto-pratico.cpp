#include <iostream>
#include <fstream>
using namespace std;

struct cadastro{
	char nome[50];
	long long int cpf;
	long int matricula;
	char endereco[50];
	char telefone[20];
	char email[30];
	char situacao[7];
};

string cadastrar(){
	cadastro user, busca;
	fstream ler("usuarios.dat", ios::in|ios::ate);
	ofstream gravar("usuarios.dat", ios::app);
	string nome, end;
	cout << "Nome do usuario:\n";
	cin.ignore();
	getline(cin, nome);
	for(int i = 0; i < nome.size(); i++)
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
	for(int i = 0; i < end.size(); i++)
		user.endereco[i] = end[i];
	cout << "Telefone:\n";
	cin.ignore();
	cin >> user.telefone;
	cout << "Email:\n";
	cin.ignore();
	cin >> user.email;
	string sit = "ativo**";
	for(int i = 0; i < 7; i++)
		user.situacao[i] = sit[i];
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
	if(erro == true)
		return "\nERRO! ESSE CPF JA POSSUI USUARIO CADASTRADO!\n\n";
	else {
		gravar.write((const char*)(&user), sizeof(cadastro));
		gravar.close();
		return "\nCADASTRO EFETUADO COM SUCESSO!\n\n";
	}
}

void listar_ativos(){
	fstream ler("usuarios.dat", ios::in|ios::ate);
	ofstream gravar("usuarios.dat", ios::app);
	long long int bytes = ler.tellg();
	int num_users = int(bytes/sizeof(cadastro));
	int cont = 0;
	cadastro busca;
	string ativo = "ativo**";
	char vet[7] = {'*','*','*','*','*','*','*'};
	for(int i = 0; i < 5; i++)
		vet[i] = ativo[i];
	if(ler){
		while (cont < num_users){
			ler.seekg(cont*sizeof(cadastro));
			ler.read((char*)&busca, sizeof(cadastro));
			bool ok = true;
			for(int i = 0; i < 7; i++){
				if(busca.situacao[i] != ativo[i])
					ok = false;
			}
			if(ok){
				string nome, email;
				for(int i = 0; i < 50; i++)
					cout << busca.nome[i];
				for(int i = 0; i < 30; i++)
					email[i] = busca.email[i];
				cout << nome << " " << busca.matricula << " " << email << endl;
			}
			cont++;
		}
	}
}

string excluir_dados(){
	cadastro *usuario, *copia;
	long long int matricula;
	int cap = 3, qtd = 0, confirmar = 0;
	cout << "Numero de matricula:\n";
	cin >> matricula;
	
	if(confirmar == 1)
		return "situaçao: inativo";
	else
		return "Exclusao cancelada";
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
			cout << excluir_dados();
		
		/*else if(opcao == 5)
			cout << efetuar_emprestimo();*/
		else if(opcao != 8)
			cout << "Digite uma opcao valida";
	}
	cout << "\nEncerrando o sistema...\n\n";

	return 0;
}
