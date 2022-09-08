#include <fstream>
#include <iostream>
#include <cstring>
using namespace std;

struct cadastro{
char nome[50];
long long int cpf;
long int matricula;
char endereco[50];
char telefone[20];
char email[150];
int situacao;
};
struct emprestimo{
    long int matricula;
    char livro[50];
    char data[10];

};

cadastro *cadastrar(int n,cadastro user[],int &qtd){      // CADASTRO DE USUARIOS EM ARQUIVO BINARIO
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

void consultar_emprestimo(emprestimo usuario[], int n){
     emprestimo dados;
     cout << "Numero de matricula:\n";
     cin >> dados.matricula;
     for(int i=0; i<n; i++){
       if(dados.matricula==usuario[i].matricula)
       cout << char(34) << usuario[i].livro << " - " << "Devolução prevista:" << usuario[i].data<<endl;
     }
}

void listar_ativos(int q,cadastro c[]){
	for(int i=0;i<q;i++){
		if(c[i].situacao == 1 or c[i].situacao == 0){
			for(int j = 0; j < strlen(c[i].nome); j++)
				cout << c[i].nome[j];
			cout << " " << c[i].matricula << " ";
			for(int j = 0; j < strlen(c[j].email); j++)
				cout << c[i].email[j];
			cout << endl;
		}
	}
}

void excluir_dados(int tamanho,cadastro v[]){
	bool ok=false;
	long int matricula;
	int confirmar,novasit=1;
	string nome;
	cout << "Numero de matricula:\n";
	cin >> matricula;
	cout << "\nNome do usuario: ";
	cin.ignore();
	getline(cin,nome);
	cout << "Comfirma exclusao? 1-sim 2-nao \n";
	cin >> confirmar;
	if(confirmar == 1)
		novasit = 0;
	for(int i=0;i<tamanho;i++){
		if(v[i].matricula == matricula and v[i].situacao == 1){
			v[i].situacao = novasit;
			ok = true;
			i = tamanho;
		}
		else
			ok = false;
	}
	if(ok){
		cout << "\nNome do usuario: " << nome << endl;
		if(novasit == 0)
			cout << "situacao: inativo" << endl;
		else
			cout << "situacao: ativo" << endl;
	}
	else
		cout << "Matricula nao encontrada\n";
}

emprestimo *efetuar_emprestimo(int p, cadastro busca[], emprestimo usuario[], int q, int &n){
    emprestimo *copia;
cout << "Numero de matricula:\n";
cin >> usuario[n].matricula;
cin.ignore();
for(int j=0; j<q; j++){
      if(usuario[n].matricula==busca[j].matricula){
      cout << "Nome do livro a ser emprestado:\n";
      cin.getline(usuario[n].livro, 50);
      cout << "Data de devolucao:\n";
      cin >> usuario[n].data;
      }
    }
    copia=usuario;
    if(n==3){
      p+=3;
      delete[] usuario;
      usuario=new emprestimo[p];
      for(int x=0; x<n; x++){
         usuario[x]=copia[x];
      }
      delete[] copia;
    }
    n++;
    return usuario;
}

void exportar_binario(cadastro pont, cadastro pont2, int q, int n){
	ofstream grava("binario.dat");
	fstream ler("binario.dat", ios::in);
}

int main(){
int opcao = 0,t=3,cont=0,q=0, n=0, p=3;
    cadastro *cad = new cadastro[q];
    emprestimo *emp = new emprestimo[n];
    cadastro *pont;
    emprestimo *pont2;

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
        else if(opcao == 5){
            bool teste=false;
            pont2 = efetuar_emprestimo(p, cad, emp, q, n);
                for(int j=0;j<q;j++){
                    if(pont2[n-1].matricula == pont[j].matricula){
                        cout << "\nEmprestimo realizado com sucesso\n";
                        j=q;
                        teste = true;
                    }
                }
            if(teste == false)
                cout << "\nMatricula nao cadastrada\n";
        }
    /*else if(opcao == 4)
        cout << excluir_dados();
    else if(opcao == 5)
        cout<<efetuar_emprestimo();
    /*else if(opcao == 5)
        cout << efetuar_emprestimo();
    else if(opcao!=8)
        cout << "Digite uma opcao valida\n";
    }
    cout << "Encerrando sistema..."<<endl;*/
    return 0;
    }
}
