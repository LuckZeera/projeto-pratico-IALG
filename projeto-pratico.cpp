#include <iostream>
#include <fstream>
#include <cstring>
using namespace std;

struct cadastro{      // CRIANDO REGISTRO DE CADASTRO
	char nome[50];
	long int cpf;
	long int matricula;
	char endereco[50];
	char telefone[20];
	char email[150];
	int situacao;
};

cadastro *cadastrar(int n,cadastro user[],int &qtd){         // CADASTRO DE USUARIOS EM ARQUIVO BINARIO
    cadastro *copia;
	cout << "Nome do usuario:\n";
	cin.ignore();
	cin.getline(user[qtd].nome,50);
	cout << "CPF:\n";
	cin >> user[qtd].cpf;
	cout << "Numero de matricula:\n";
	cin >> user[qtd].matricula;
	cout << "Endereco:\n";
	cin.ignore();
	cin.getline(user[qtd].endereco,50);
	cout << "Telefone:\n";
	cin.ignore();
	cin.getline(user[qtd].telefone,20);
	cout << "Email:\n";
	cin.ignore();
	cin.getline(user[qtd].email,150);
	copia = user;
	if(qtd == 3){
		n += 3;
		delete[] user;
		user = new cadastro[n];
		for(int x=0;x<qtd;x++){
			user[x] = copia[x];
		}
		delete[] copia;
	}
	qtd++;
	return user;
}

int main(){
	int opcao = 0,t=3,cont=0,q=0;
	cadastro *cad = new cadastro[t];
	cadastro *pont;
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
		if(opcao == 1){
			bool teste=true;
			pont = cadastrar(t,cad,q);
			for(int i=0;i<q;i++){
				for(int j=0;j<q;j++){
					if(pont[i].cpf == pont[j].cpf and j != i){
						cout << "\nCPF ja cadastrado\n";
						pont[i].situacao = 0;
						i=q;
						teste = true;
					}
					else{
						pont[i].situacao = 1;
						teste = false;
					}
				}
			}
			if(teste == false)
				cout << "\nCadastro efetuado com sucesso\n";
		}
		/*else if(opcao == 3)
			listar_ativos();
		else if(opcao == 4)
			excluir_dados();
		
		else if(opcao == 5)
			cout << efetuar_emprestimo(n,cad);
		else if(opcao != 8)
			cout << "Digite uma opcao valida";*/
	}
	cout << "\nEncerrando o sistema...\n\n";
	return 0;
}
