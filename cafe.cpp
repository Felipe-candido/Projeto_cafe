#include <iostream>
#include <limits>
using namespace std;

int menu();

struct MEMBRO{
    int id;
    string nome;
    int semestre;
    int ano_ingresso;
    string curso;
    int contador;
};

    int main(){
    
    int opcao;
    do{
        opcao = 0;
        int menu();
        opcao = menu();
        switch (opcao)
        {
        case 1:
            cout << "TESTE";
            break;
        
        case 5:
            cout << "Fechando...";
            break;
        
        default:
        cout << "Por favor insira um numero valido" << endl;
            break;
        }
    }while(opcao != 5);
    
    return 0;
}

// FUNÇÃO QUE CRIA UM MENU INICIAL E RETORNA UMA DAS OPÇÕES DO PROGRAMA
int menu()
{
    int opcao;
    cout << "======================================\n";
    cout << "            Menu inicial              \n";
    cout << "======================================\n";
    cout << "1 - Cadastro de membros\n";
    cout << "2 - Exibir membros\n";
    cout << "3 - Registrar pagamentos\n";
    cout << "4 - Cadastro de membros\n";
    
    // (cin >> opção) TENTA LER A ENTRADA E ARMAZENA NA VARIÁVEL OPCAO
    while(!(cin >> opcao) ) // VERIFICA ESTADO DE FALHA DO CIN
    {
        cout << "Entrada invalida, por favor insira um numero" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return opcao;
}

// FUNÇÃO PARA REGISTRO DE MEMBROS
void cadastro_membro()
{
    //
    MEMBRO *new_member = new MEMBRO;
    cout << "================================\n";
    cout << "Nome: ";
    cin >> new_member->nome;
    cout << endl;
    cout << "Nome: ";
    cin >> new_member->nome;
    cout << endl;
}
