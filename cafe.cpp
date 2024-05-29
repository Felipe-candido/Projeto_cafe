#include <iostream>
#include <limits>
using namespace std;

// ESTRUTURAS DO SISTEMA
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

// PROTÓTIPO DAS FUNÇOES   
int menu();
CADASTRO cadastrar_membro();
REGISTRO* registrar(LISTA *lista, CADASTRO* membro);
void exibir_membros(LISTA* lista);
    
int main(){
    
    // INICIA A LISTA
    LISTA lista_registros = { nullptr, nullptr };
    
    // ESTRUTURA PARA CHAMAR O MENU DURANTE O FUNCIONAMENTO DO PROGRAMA
    int opcao = 0;
    do{
        opcao = menu();
        
        switch (opcao)
        {
        case 1:{
            // CRIANDO NOVO CADASTRO
            CADASTRO novo_cadastro = cadastrar_membro();
            registrar(&lista_registros, &novo_cadastro);
            cout << "Cadastro realizado com sucesso!" << endl;
            break;
        }

       case 2:
           // EXIBINDO MEMBROS CADASTRADOS
           exibir_membros(&lista_registros);
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

// FUNÇÃO PARA CRIA UM CADASTRO DE MEMBROS
CADASTRO cadastrar_membro()
{
    // CRIA UM NOVO CADASTRO;
    CADASTRO novo_membro;
    cout << endl;
    cout << "CADASTRO DE MEMBROS\n";
    cout << "================================\n";
    cout << "Primeiro nome: ";
    cin >> novo_membro.nome;
    
    
    cout << "Semestre: ";
    cin >> novo_membro.semestre;
    

    cout << "Ano de ingresso: ";
    cin >> novo_membro.ano_ingresso;
    

    cout << "Curso(SI, DSM ou GE): ";
    cin >> novo_membro.curso;
    cout << endl;

    return novo_membro;
}


// REGISTRA UM MEMBRO NA LISTA DO SISTEMA
REGISTRO* registrar(LISTA* lista, CADASTRO* membro)
{
    if (lista == nullptr) {
        cerr << "Erro: A lista não foi inicializada corretamente." << endl;
        return nullptr;
    }

    REGISTRO *novo_registro = new REGISTRO;
    // VALIDAÇÃO PARA VERIFICAR CRIAÇÃO DO NOVO REGISTRO NO SISTEMA
    if (novo_registro == NULL){
        cerr << "Acabou a memória." << endl;
        exit(1);
    }

    // CRIAÇÃO DO REGISTRO
    novo_registro->membro = *membro;
    novo_registro->next = NULL;
    novo_registro->prev = lista->final;
     

    // VERIFICA SE A LISTA ESTÁ VAZIA OU NÃO
    if (lista->final != NULL){
        novo_registro->membro.id = lista->final->membro.id + 1;
        lista->final->next = novo_registro;

    }
    else{
        lista->inicio = novo_registro;
        novo_registro->membro.id = 1;
    }
    lista->final = novo_registro;


    return novo_registro;
}


// FUNÇÃO PARA EXIBIR OS MEMBROS
void exibir_membros(LISTA* lista)
{
    if (lista == nullptr) {
        cout << "Erro: A lista não foi inicializada corretamente." << endl;
        return;
    }

    REGISTRO* aux;
    aux = lista->inicio;
    if(lista->inicio != NULL){
        cout << "============================\n";
        cout << "Lista de membros\n";
        cout << "============================\n";
       
        // EXIBE OS MEMBROS ATÉ CHEGAR NO ULTIMO REGISTRO
        while(aux != NULL)
        {
            cout << "-----------------------\n";
            cout << "ID: " << aux->membro.id << endl;
            cout << "NOME: " << aux->membro.nome << endl; 
            cout << "SEMESTRE: " << aux->membro.semestre << endl;
            cout << "ANO DE INGRESSO: " << aux->membro.ano_ingresso << endl;
            cout << "curso: " << aux->membro.curso << endl;
            cout << "-----------------------\n" << endl;
            cout << endl;
            aux = aux->next;
            
        }
    }
    else{
        cout << "Lista de membros vazia..." << endl;
    }
    return;
}

