#include <iostream>
// BIBLIOTECA PARA LIMITAR CARACTERES
#include <limits>
// BIBLIOTECA PARA MANIPULAÇÃO DE STRINGS
#include <cstring>
// BIBLIOTECA PARA MANUPULAÇÃO DE ARQUIVOS EXTERNOS
#include <fstream>
// BIBLIOTECA PARA MANIPULAR FLUXOS DE ENTRADA E SAÍDA DE STRINGS
#include <sstream>

#include <windows.h>

using namespace std;

// ESTRUTURAS DO SISTEMA
typedef struct CADASTRO{
    int id;
    string nome;
    int semestre;
    int ano_ingresso;
    string curso;
}MEMBRO;

struct REGISTRO{
    MEMBRO membro;
    REGISTRO* next;
    REGISTRO* prev;
};

typedef struct pagamento{
    int id_membro;
    int mes;
    int ano;
    float valor;
}PAGAMENTO;

struct NODE{
    PAGAMENTO pagamento;
    NODE* next;
    NODE* prev;
};

typedef struct lista{
    REGISTRO *inicio;
    REGISTRO *final;
}LISTA;

typedef struct lista2{
    NODE *inicio;
    NODE *final;
}LISTA2;



// PROTÓTIPO DAS FUNÇOES   
int menu();
MEMBRO cadastrar_membro();
PAGAMENTO cadastrar_pagamento(LISTA* lista1);
void registrar_membro(LISTA* lista, CADASTRO* membro);
void registrar_pagamento(LISTA2* lista, PAGAMENTO* pagamento);
void exibir_membros(LISTA* lista);
void editar_membros(LISTA* lista, int id);
void ler_txt(const string& nome_arquivo, LISTA* lista);
void salvar_cadastros(LISTA* lista);
bool validar_id(LISTA* lista1, int id_pagamento);
    
int main(){
    SetConsoleOutputCP(CP_UTF8);
    
    // INICIA A LISTA
    LISTA lista_registros = {NULL, NULL};
    LISTA2 lista_pagantes = {NULL, NULL};

    // AO INICIAR O PROGRAMA, ELE AUTOMATICAMENTE PUXA OS DADOS DO ARQUIVO TXT E ALIMENTA A LISTA DO SISTEMA
    string nome_arquivo = "participantes.txt";
    ler_txt(nome_arquivo, &lista_registros);
    
    // ESTRUTURA PARA CHAMAR O MENU DURANTE O FUNCIONAMENTO DO PROGRAMA
    int opcao = 0;
    do{
        opcao = menu();
        
        switch (opcao)
        {
        case 1:{
            // CRIANDO NOVO CADASTRO
            MEMBRO novo_cadastro = cadastrar_membro();
            registrar_membro(&lista_registros, &novo_cadastro);
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
            // REGISTRANDO NOVO PAGAMENTO
            PAGAMENTO novo_cadastro = cadastrar_pagamento(&lista_registros);
            registrar_pagamento(&lista_pagantes, &novo_cadastro);
            break;
        }

        case 5:{
            // LÊ ARQUIVO EXTERNO E ALIMENTA EXTRUTURA DO SISTEMA
            string nome_arquivo = "participantes.txt";
            ler_txt(nome_arquivo, &lista_registros);
            break;
        }
        

        case 6:
            // GRAVA TODOS 0S REGISTROS PRESENTES NA ESTRUTURA DE LISTA EM UM ARQUIVO TXT
            salvar_cadastros(&lista_registros);
            cout << "Cadastros salvos com sucesso no documento participantes.txt" << endl;
            break;

        case 7:
            // AO FECHAR O SISTEMA, ELE AUTOMATICAMENTE SALVA TODOS OS DADOS EM UM ARQUIVO TXT
            salvar_cadastros(&lista_registros);
            cout << "Fechando...";
            break;
        
        default:
        cout << "Por favor insira um numero válido" << endl;
            break;
        }
    }while(opcao != 7);
    
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
    cout << "4 - Registrar pagamento\n";
    cout << "5 - Ler arquivo externo\n";
    cout << "6 - Gravar em arquivo externo\n";
    cout << "7 - Sair\n";
    
    // (cin >> opção) TENTA LER A ENTRADA E ARMAZENA NA VARIÁVEL OPCAO
    while(!(cin >> opcao) ) // VERIFICA ESTADO DE FALHA DO CIN
    {
        // SE A ENTRADA FALHAR, O PROGRAMA LIMPA O CIN E CONTINUA VERIFICANDO OUTRAS ENTRADAS DO USUÁRIO
        cout << "Entrada inválida, por favor insira um nú6mero" << endl;
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    return opcao;
}

// FUNÇÃO PARA CRIA UM CADASTRO DE MEMBROS
MEMBRO cadastrar_membro()
{
    // CRIA UM NOVO CADASTRO;
    MEMBRO novo_membro;
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
void registrar_membro(LISTA* lista, MEMBRO* membro)
{
    if (lista == NULL) {
        cerr << "Erro: A lista não foi inicializada corretamente." << endl;
        return;
    }

    REGISTRO *novo_registro = new REGISTRO;
    // VALIDAÇÃO PARA VERIFICAR CRIAÇÃO DO NOVO REGISTRO NO SISTEMA
    if (novo_registro == NULL){
        cerr << "Acabou a memória." << endl;
        return;
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
    return;
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
            cout << "-----------------------\n";
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

// FUNÇÃO PARA SALVAR OS REGISTROS EM UM ARQUIVO TXT
void salvar_cadastros(LISTA* lista)
{
    // CRIA E ABRE ARQUIVO PARA LEITURA
    ofstream arquivo("participantes.txt");
    if(!arquivo){
        cerr << "Erro ao abrir o arquivo de participantes.";
        return;
    }

    // VERIFICA SE A LISTA DO SISTEMA ESTÁ VAZIA
    if (lista == NULL) {
        cout << "Erro: A lista está vazia, ou não foi inicializada corretamente." << endl;
        return;
    }
    
    // VERIFICA SE O ARQUIVO ABRIU CORRETAMENTE
    if(arquivo.is_open()){
        REGISTRO *aux = lista->inicio;

        // PERCORRE A LISTA SALVANDO OS REGISTROS
        while (aux != NULL)
        {
            arquivo << aux->membro.id; arquivo << " ";
            arquivo << aux->membro.nome; arquivo << " ";
            arquivo << aux->membro.curso; arquivo << " ";
            arquivo << aux->membro.semestre; arquivo << " ";
            arquivo << aux->membro.ano_ingresso; arquivo << " ";
            arquivo << endl;
            aux = aux->next;  
        }
        return;
    }
}


// FUNÇÃO PARA LER ARQUIVO DE TEXTO E ALIMENTAR A ESTRUTURA DO SISTEMA
void ler_txt(const string& nome_arquivo, LISTA* lista)
{
    ifstream arquivo(nome_arquivo);
    if(!arquivo){
        cerr << "Erro ao abrir arquivo externo. Nenhum registro inserido." << endl;
        return;
    }

    
    string line;
    cout << "_________________________________________________________________________\n";
    cout << "Conteúdo do arquivo de participantes que será iserido na lista." << endl;
    cout << "==================================================\n";
    cout << "ID || NOME || CURSO || SEMESTRE || ANO DE INGRESSO\n";
    cout << "==================================================\n";
    while(getline(arquivo, line)){
        cout << line << endl;

        MEMBRO novo_cadastro;
        // CRIA UM OBJETO QUE VAI RECEBER UMA LINHA DO ARQUIVO TXT PARA MANIPULAR
        istringstream linha(line);

        // CONVERTE CADA PARTE DA LINHA DENTRO DA ESTRUTURA DE CADASTRO
        linha >> novo_cadastro.id;
        linha >> novo_cadastro.nome;
        linha >> novo_cadastro.curso;
        linha >> novo_cadastro.semestre;
        linha >> novo_cadastro.ano_ingresso;

        // INSERE O CADASTRO CRIADO DENTRO DA LISTA
        registrar_membro(lista, &novo_cadastro);
    }
    arquivo.close();
    return;
}


// FUNÇÃO PARA CADASTRO DE PAGANTES
PAGAMENTO cadastrar_pagamento(LISTA* lista1)
{
    // CRIA UM NOVO CADASTRO;j
    PAGAMENTO novo_pagamento;
    cout << endl;
    cout << "CADASTRAR PAGAMENTO\n";
    cout << "================================\n";
    
    cout << "ID do membro: ";
    cin >> novo_pagamento.id_membro;
    
    if(validar_id(lista1, novo_pagamento.id_membro) == true){
    cout << "Mes do pagamento: ";
    cin >> novo_pagamento.mes;
    

    cout << "Ano do pagamento: ";
    cin >> novo_pagamento.ano;
    while(novo_pagamento.ano < 2024){
        cout << "por favor digite um ano válido.\n";
        cout << "Ano do pagamento: ";
        cin >> novo_pagamento.ano;
    }
    

    cout << "Valor: ";
    cin >> novo_pagamento.valor;
    cout << endl;
    cout << "Pagamento realizado com sucesso!" << endl;
    }

    else{
        cout << "Esse id não corresponde a nenhum membro cadastrado.\n";
        cout << "Por favor cadastre esse membro antes de realizar o pagamento.\n";
        novo_pagamento.id_membro = -1;
    }  
    return novo_pagamento;
}


 // FUNÇÃO PARA REGISTRAR PAGAMENTOS NA LISTA DO SISTEMA
 void registrar_pagamento(LISTA2* lista, PAGAMENTO* pagamento)
 {
    if (lista == NULL)
    {
        cerr << "Erro ao iniciar a lista.\n";
        return;
    }
    
    NODE* novo_registro = new NODE;

    novo_registro->pagamento = *pagamento;
    novo_registro->next = NULL;
    novo_registro->prev = lista->final;

    if(lista->final != NULL){
    lista->final->next = novo_registro;
    }

    else{
    lista->inicio = novo_registro;
    }
    
    lista->final = novo_registro;
    return;
 }



// FUNÇÃO PARA VALIDAR ID DO PAGAMENTO
bool validar_id(LISTA* lista1, int id_pagamento)
{
    if(lista1 == NULL){
        cerr << "A lista de membros stá vazia.\n";
        return false;
    }

    REGISTRO* aux = lista1->inicio;
   
    while(aux != NULL){
        if(aux->membro.id == id_pagamento){
            return true;
        }
        
        else{
            aux = aux->next;
        }
    }
    return false;
}