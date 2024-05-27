#include <iostream>
#include <limits>
using namespace std;

typedef struct MEMBRO{
    int id;
    string nome;
    int semestre;
    int ano_ingresso;
    string curso;
}CADASTRO;

struct REGISTRO{
    MEMBRO membro;
    REGISTRO* next;
    REGISTRO* prev;
};

typedef struct lista{
    REGISTRO *inicio;
    REGISTRO *final;
}LISTA;

    
    int menu();
    CADASTRO cadastrar_membro();
    REGISTRO registrar(CADASTRO *membro);
    
    int main(){
    
    // INICIA A LISTA
    //LISTA *lista_registros;
    
    // ESTRUTURA PARA CHAMAR O MENU DURANTE O FUNCIONAMENTO DO PROGRAMA
    int opcao;
    do{
        opcao = 0;
        int menu();
        opcao = menu();
        switch (opcao)
        {
        case 1:
            // CRIANDO NOVO CADASTRO
            cadastrar_membro();
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
    cout << "1 - Cadastrar Membro\n";
    cout << "2 - Exibir membros\n";
    cout << "3 - Registrar pagamentos\n";
    cout << "4 - Cadastro de membros\n";
    cout << "5 - Sair\n";
    
    // (cin >> opção) TENTA LER A ENTRADA E ARMAZENA NA VARIÁVEL OPCAO
    while(!(cin >> opcao) ) // VERIFICA ESTADO DE FALHA DO CIN
    {
        // SE A ENTRADA FALHAR, O PROGRAMA LIMPA O CIN E CONTINUA VERIFICANDO OUTRAS ENTRADAS DO USUÁRIO
        cout << "Entrada invalida, por favor insira um numero" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return opcao;
}

// FUNÇÃO PARA REGISTRO DE MEMBROS
CADASTRO cadastrar_membro()
{
    // CRIA UM NOVO CADASTRO;
    CADASTRO *novo_membro = new CADASTRO;
    cout << endl;
    cout << "CADASTRO DE MEMBROS\n";
    cout << "================================\n";
    cout << "Primeiro nome: ";
    cin >> novo_membro->nome;
    
    
    cout << "Semestre: ";
    cin >> novo_membro->semestre;
    

    cout << "Ano de ingresso: ";
    cin >> novo_membro->ano_ingresso;
    

    cout << "Curso(SI, DSM ou GE): ";
    cin >> novo_membro->curso;
    cout << endl;

    return *novo_membro;
}

// REGISTRO registrar(LISTA *lista_registros, CADASTRO *membro)
// {
//     REGISTRO *novo_registro = new REGISTRO;
//     // VALIDAÇÃO PARA VERIFICAR CRIAÇÃO DO NOVO REGISTRO NO SISTEMA
//     if (novo_registro == NULL){
//         cerr << "Acabou a memória." << endl;
//         exit(1);
//     }

//     // CRIAÇÃO DO REGISTRO
//     novo_registro->membro = *membro;
//     novo_registro->next = NULL;
//     novo_registro->prev = NULL;

//     if (lista_registros->inicio == NULL){
//         lista_registros->inicio = novo_registro;
//         lista_registros->final = novo_registro;
//         return *novo_registro;
//     }
//     if (lista_registros->final->membro.id == 1){

//     }
// }
