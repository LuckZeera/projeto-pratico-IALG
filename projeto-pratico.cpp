#include <iostream>
#include <fstream>
using namespace std;

struct cadastro{
	string nome;
	long long int cpf;
	long long int matricula;
	string endereco;
	string telefone;
	string email;
	string situacao;
};

string cadastrar(){
	cadastro *usuario, *copia;
	int cap = 3;
	bool erro = false;
	ifstream ler("usuarios");
	ofstream gravar("usuarios", ios::app);
	int qtd = 0;
	if(ler){
		while(ler){
			usuario = new cadastro[cap];
			for(int i = 0; i < qtd; i++){
				usuario[i] = copia[i];
			}
			getline(ler, usuario[qtd].nome);
			ler >> usuario[qtd].cpf >> usuario[qtd].matricula;
			getline(ler, usuario[qtd].endereco);
			ler >> usuario[qtd].telefone >> usuario[qtd].email >> usuario[qtd].situacao;
			qtd++;
			if(qtd == cap){
				cap += 3;
			}
			copia = usuario;
		}
		delete copia;
	}
	ler.close();
	if(gravar){
		cin.ignore();
		cout << "Nome do usuario:\n";
		getline(cin, usuario[qtd].nome);
		cout << "CPF:\n";
		cin >> usuario[qtd].cpf;
		cout << "Numero de matricula:\n";
		cin >> usuario[qtd].matricula;
		cout << "Endereco:\n";
		cin.ignore();
		getline(cin, usuario[qtd].endereco);
		cout << "Telefone:\n";
		cin >> usuario[qtd].telefone;
		cout << "Email:\n";
		cin >> usuario[qtd].email;
		usuario[qtd].situacao = "ativo";
		for(int i = 0; i < qtd; i++){
			if(usuario[i].cpf == usuario[qtd].cpf)
				erro = true;
		}
		if(erro == false){
			gravar << usuario[qtd].nome << endl << usuario[qtd].cpf << endl << usuario[qtd].matricula << endl << usuario[qtd].endereco << endl << usuario[qtd].telefone << endl << usuario[qtd].email << endl << usuario[qtd].situacao << endl;
		}
	}
	gravar.close();
	if(erro == true)
			return "\nERRO! ESSE CPF JA POSSUI USUARIO CADASTRADO!\n\n";
	else
		return "\nCADASTRO EFETUADO COM SUCESSO!\n\n";
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
		else if(opcao == 4)
			cout << excluir_dados();
		
		/*else if(opcao == 5)
			cout << efetuar_emprestimo();*/
		else
			cout << "Digite uma opcao valida";
	}
	cout << "Encerrando sistema...";

	return 0;
}
