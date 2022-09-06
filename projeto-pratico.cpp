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

cadastro *cadastrar(int &n,cadastro user[]){         // CADASTRO DE USUARIOS EM ARQUIVO BINARIO
    cadastro *copia = new cadastro [3];
	int qtd=1;
	for(int i=0;i<n;i++){
		if(i==0)
			cadastro *copia = new cadastro [3];
		cout << "Nome do usuario:\n";

		cin.getline(user[i].nome,50);
		cin.ignore();
		cout << "CPF:\n";
		cin >> user[i].cpf;
		cout << "Numero de matricula:\n";
		cin >> user[i].matricula;
		cout << "Endereco:\n";
		cin.ignore();
		cin.getline(user[i].endereco,50);
		cout << "Telefone:\n";
		cin.ignore();
		cin.getline(user[i].telefone,20);
		cout << "Email:\n";
		cin.ignore();
		cin.getline(user[i].email,150);
		qtd++;
		copia[i] = user[i];
		if(qtd == 3){
			n += 3;
			delete[] user;
			user = new cadastro[n];
			for(int x=0;x<3;x++){
				user[i] = copia[i];
			}
			delete[] copia;
		}
		else
			i = n;

	}
	return user;
}

int main(){
	int opcao = 0,t=3,cont=0;
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
			pont = cadastrar(t,cad);
			for(int i=0;i<t;i++){
				for(int j=0;j<t;j++){
					if(pont[i].matricula = pont[j].matricula and j != i){
						cout << "\nCPF ja cadastrado\n";
						pont[i].situacao = 0;
					}
					else{
						pont[i].situacao = 1;
						cont++;
					}
				}
			}
			if(cont == t)
				cout << "\nCadastro efetuado com sucesso\n";
		}
		else if(opcao == 3)
			listar_ativos();
		else if(opcao == 4)
			excluir_dados();
		
		else if(opcao == 5)
			cout << efetuar_emprestimo(n,cad);
		else if(opcao != 8)
			cout << "Digite uma opcao valida";
	}
	cout << "\nEncerrando o sistema...\n\n";
	return 0;
}
