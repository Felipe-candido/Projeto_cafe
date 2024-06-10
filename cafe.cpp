#include <iostream>
// BIBLIOTECA 
#include <limits>
// BIBLIOTECA PARA MANIPULAÇÃO DE STRINGS
#include <cstring>
// BIBLIOTECA PARA MANUPULAÇÃO DE ARQUIVOS EXTERNOS
#include <fstream>

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
void editar_membros(LISTA *lista, int id);
void ler_txt(const string& nome_arquivo);
    
int main(){
    
    // INICIA A LISTA
    LISTA lista_registros = { NULL, NULL };
    
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

        case 3:
            // EDITA AS INFORMAÇÕES DO MEMBRO DESEJADO
            int id;
            cout << "Insira o ID do membro que deseja fazer alterações: ";
            cin >> id;
            editar_membros(&lista_registros, id);
            break;

        case 4:{
            // LÊ ARQUIVO EXTERNO E ALIMENTA EXTRUTURA DO SISTEMA
            string nome_arquivo = "projeto_cafe/participantes.txt";
            ler_txt(nome_arquivo);
            break;
        }

        case 6:
            cout << "Fechando...";
            break;
        
        default:
        cout << "Por favor insira um numero valido" << endl;
            break;
        }
    }while(opcao != 6);
    
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
    cout << "3 - Editar membros\n";
    cout << "4 - Ler arquivo externo\n";
    cout << "5 - Gravar em arquivo externo\n";
    cout << "6 - Sair\n";
    
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
    cin.ignore();
    getline(cin, novo_membro.nome);
    
    
    cout << "Semestre: ";
    cin >> novo_membro.semestre;
    

    cout << "Ano de ingresso: ";
    cin >> novo_membro.ano_ingresso;
    

    cout << "Curso(SI, DSM ou GE): ";
    cin.ignore();
    getline(cin, novo_membro.curso);
    cout << endl;

    return novo_membro;
}


// REGISTRA UM MEMBRO NA LISTA DO SISTEMA
REGISTRO* registrar(LISTA* lista, CADASTRO* membro)
{
    if (lista == NULL) {
        cerr << "Erro: A lista não foi inicializada corretamente." << endl;
        return NULL;
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
    if (lista == NULL) {
        cout << "Erro: A lista está vazia, ou não foi inicializada corretamente." << endl;
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
            cout << "CURSO: " << aux->membro.curso << endl;
            cout << "-----------------------\n" << endl;
            aux = aux->next;
            
        }
    }
    else{
        cout << "Lista de membros vazia..." << endl;
    }
    return;
}


// FUNÇÃO PARA EDITAR AS INFORMAÇÕES DO MEMBRO
void editar_membros(LISTA *lista, int id)
{
    if (lista == NULL) {
        cout << "Erro: A lista está vazia, ou não foi inicializada corretamente." << endl;
        return;
    }

    REGISTRO* aux;
    aux = lista->inicio;
    
    while(aux != NULL)
    {
        if(aux->membro.id == id){
            // MOSTRA O MEMBRO QUE SERÁ EDITADO
            cout << "EDITAR MEMBRO:\n";
            cout << "-----------------------\n";
            cout << "ID: " << aux->membro.id << endl;
            cout << "NOME: " << aux->membro.nome << endl; 
            cout << "SEMESTRE: " << aux->membro.semestre << endl;
            cout << "ANO DE INGRESSO: " << aux->membro.ano_ingresso << endl;
            cout << "CURSO: " << aux->membro.curso << endl;
            cout << "-----------------------\n" << endl;
            cout << endl;
            
            // ABRE A EDIÇÃO DO MEMBRO
            cout << "-----------------------\n";
            cout << "Editar nome: ";
            cin.ignore();
            getline(cin, aux->membro.nome); 
            cout << "Editar semestre: ";
            cin >> aux->membro.semestre;
            cout << "Editar ano de ingresso: ";
            cin >> aux->membro.ano_ingresso;
            cout << "Editar curso: ";
            cin.ignore();
            getline(cin, aux->membro.curso);
            cout << "-----------------------\n" << endl;
            return;
        }
        aux = aux->next;
    }
    cout << "Não foi encontrado um membro com esse id." << endl;
}


// FUNÇÃO PARA LER ARQUIVO DE TEXTO E ALIMENTAR A ESTRUTURA DO SISTEMA
void ler_txt(const string& nome_arquivo)
{
    ifstream arquivo(nome_arquivo);
    if(!arquivo){
        cerr << "Erro ao abrir arquivo externo." << endl;
        return;
    }

    string line;
    cout << "Conteúdo do arquivo (participantes.txt)." << endl;
    cout << "=================================\n";
    while(getline(arquivo, line)){
        cout << line << endl;
    }
    arquivo.close();
}

