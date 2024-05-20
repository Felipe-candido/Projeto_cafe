#include <iostream>
using namespace std;

struct MEMBRO{
    int id;
    string nome;
    int semestre;
    int ano_ingresso;
    string curso;
    int contadorgerhrhnrnrnfhfndgbgbed
};

    int main(){
    
    do{
        int menu();
        int opcao = menu();
        switch (opcao)
        {
        case 1:
            
            break;
        
        default:
            break;
        }
    }while(menu() != 5);
    return 0;
}

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
    cin >> opcao;
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
