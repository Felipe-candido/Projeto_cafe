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
    string nome;
    string curso;
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
void limpar_lista1(LISTA* lista1);
void limpar_lista2(LISTA2* lista2);
void salvar_contribuintes(LISTA2* lista2, LISTA* lista1);
void ler_contribuintes(const string& nome_arquivo, LISTA2* lista2);
void exibir_contribuintes(LISTA2* lista2);
void salvar_contribuintes_por_curso(LISTA2* lista2);
bool id_existe(LISTA2* lista, int id);

int main(){
    SetConsoleOutputCP(CP_UTF8);
    
    // INICIA A LISTA
    LISTA lista_registros = {NULL, NULL};
    LISTA2 lista_contribuintes = {NULL, NULL};

    // AO INICIAR O PROGRAMA, ELE AUTOMATICAMENTE PUXA OS DADOS DO ARQUIVO TXT E ALIMENTA A LISTA DO SISTEMA
    string nome_arquivo = "participantes.txt";
    ler_txt(nome_arquivo, &lista_registros);

    // AO INICIAR O PROGRAMA, ELE AUTOMATICAMENTE PUXA OS DADOS DO ARQUIVO TXT E ALIMENTA A LISTA DO SISTEMA
    string nome_arquivo2 = "contribuintes.txt";
    ler_contribuintes(nome_arquivo2, &lista_contribuintes);
    
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
            registrar_pagamento(&lista_contribuintes, &novo_cadastro);
            break;
        }
        
        case 5:
            // EXIBINDO CONTRIBUINTES
            exibir_contribuintes(&lista_contribuintes);
            break;


        // case 5:{
        //     // LÊ ARQUIVO EXTERNO E ALIMENTA EXTRUTURA DO SISTEMA
        //     string nome_arquivo = "participantes.txt";
        //     ler_txt(nome_arquivo, &lista_registros);
        //     break;
        // }
        

        // case 6:
        //     // GRAVA TODOS 0S REGISTROS PRESENTES NA ESTRUTURA DE LISTA EM UM ARQUIVO TXT
        //     salvar_cadastros(&lista_registros);
        //     cout << "Cadastros salvos com sucesso no documento participantes.txt" << endl;
        //     break;

        case 6:
            // AO FECHAR O SISTEMA, ELE AUTOMATICAMENTE SALVA TODOS OS DADOS EM UM ARQUIVO TXT
            salvar_cadastros(&lista_registros);
            salvar_contribuintes(&lista_contribuintes, &lista_registros);
            salvar_contribuintes_por_curso(&lista_contribuintes);
            // AO FECHAR O PROGRAMA, A LISTA É APAGADA PARA EVITAR VAZAMENTOS DE MEMÓRIA
            limpar_lista1(&lista_registros);
            limpar_lista2(&lista_contribuintes);
            cout << "Fechando...";
            break;
        
        default:
        cout << "Por favor insira um numero válido" << endl;
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
    cout << "4 - Registrar pagamento\n";
    cout << "5 - Exibir contribuintes\n";
    // cout << "5 - Ler arquivo externo\n";
    // cout << "6 - Gravar em arquivo externo\n";
    cout << "6 - Sair\n";
    
    // (cin >> opção) TENTA LER A ENTRADA E ARMAZENA NA VARIÁVEL OPCAO
    while(!(cin >> opcao) ) // VERIFICA ESTADO DE FALHA DO CIN
    {
        // SE A ENTRADA FALHAR, O PROGRAMA LIMPA O CIN E CONTINUA VERIFICANDO OUTRAS ENTRADAS DO USUÁRIO
        cout << "Entrada inválida, por favor insira um número" << endl;
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
    // while(!(cin >> novo_membro.semestre) ) // VERIFICA ESTADO DE FALHA DO CIN
    // {
    //     // SE A ENTRADA FALHAR, O PROGRAMA LIMPA O CIN E CONTINUA VERIFICANDO OUTRAS ENTRADAS DO USUÁRIO
    //     cout << "Entrada inválida, por favor insira um número" << endl;
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // }
    

    cout << "Ano de ingresso: ";
    cin >> novo_membro.ano_ingresso;
    // while(!(cin >> novo_membro.ano_ingresso) ) // VERIFICA ESTADO DE FALHA DO CIN
    // {
    //     // SE A ENTRADA FALHAR, O PROGRAMA LIMPA O CIN E CONTINUA VERIFICANDO OUTRAS ENTRADAS DO USUÁRIO
    //     cout << "Entrada inválida, por favor insira um número" << endl;
    //     cin.clear();
    //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
    // }
    
    

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


// FUNÇÃO PARA EXIBIR CONTRIBUINTES
void exibir_contribuintes(LISTA2* lista2)
{
    if (lista2 == NULL) {
        cout << "Erro: A lista de contribuintes está vazia, ou não foi inicializada corretamente." << endl;
        return;
    }

    NODE* aux;
    aux = lista2->inicio;
    if(lista2->inicio != NULL){
        cout << "============================\n";
        cout << "Lista de contribuintes\n";
        cout << "============================\n";
       
        // EXIBE OS MEMBROS ATÉ CHEGAR NO ULTIMO REGISTRO
        while(aux != NULL)
        {
            cout << "-----------------------\n";
            cout << "ID: " << aux->pagamento.id_membro << endl;
            cout << "MES: " << aux->pagamento.mes << endl;
            cout << "ANO: " << aux->pagamento.ano << endl;
            cout << "VALOR: " << aux->pagamento.valor << endl;
            cout << "CURSO: " << aux->pagamento.curso << endl;
            cout << "-----------------------\n";
            aux = aux->next;
            
        }
    }
    else{
        cout << "Lista de contribuintes vazia..." << endl;
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


// FUNÇÃO PARA LER E ALIMENTAR A ESTRUTURA COM UM ARQUIVO DE CONTRIBUINTES EXTERNO
void ler_contribuintes(const string& nome_arquivo, LISTA2* lista2)
{
    ifstream arquivo(nome_arquivo);
    if(!arquivo){
        cerr << "Erro ao abrir arquivo externo. Nenhum registro inserido." << endl;
        return;
    }

    string line;
    cout << endl;
    cout << "_________________________________________________________________________\n";
    cout << "Conteúdo do arquivo de contribuintes que será iserido na lista." << endl;
    cout << "==================================================\n";
    cout << "ID || NOME || CURSO || MES || ANO || VALOR || CURSO\n";
    cout << "==================================================\n";
    while(getline(arquivo, line)){
        cout << line << endl;

        PAGAMENTO novo_cadastro;
        // CRIA UM OBJETO QUE VAI RECEBER UMA LINHA DO ARQUIVO TXT PARA MANIPULAR
        istringstream linha(line);

        // CONVERTE CADA PARTE DA LINHA DENTRO DA ESTRUTURA DE CADASTRO
        linha >> novo_cadastro.id_membro;
        linha >> novo_cadastro.mes;
        linha >> novo_cadastro.ano;
        linha >> novo_cadastro.valor;
        linha >> novo_cadastro.curso;

        // Verifica se o ID já existe na lista antes de inserir
        if (!id_existe(lista2, novo_cadastro.id_membro)) {
            registrar_pagamento(lista2, &novo_cadastro);
        } else {
            // cout << "ID duplicado encontrado: " << novo_cadastro.id_membro << ". Ignorando o registro." << endl;
        }

        
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
        // while(!(cin >> novo_pagamento.mes) ) // VERIFICA ESTADO DE FALHA DO CIN
        // {
        //     // SE A ENTRADA FALHAR, O PROGRAMA LIMPA O CIN E CONTINUA VERIFICANDO OUTRAS ENTRADAS DO USUÁRIO
        //     cout << "Entrada inválida, por favor insira um número" << endl;
        //     cin.clear();
        //     cin.ignore(numeric_limits<streamsize>::max(), '\n');
        // }
    
        
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
       
        REGISTRO* aux = lista1->inicio;
        while (aux != NULL){
            if(aux->membro.id == novo_pagamento.id_membro){
                novo_pagamento.nome = aux->membro.nome;
                novo_pagamento.curso = aux->membro.curso;
            }
            aux = aux->next;
        }
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
    if(novo_registro == NULL){
        cerr << "Erro ao alocar memória para novo registro de pagamento.\n";
    return;
    }

    if(pagamento->id_membro == -1){
        return;
    }

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


// FUNÇÃO PARA DESALOCAR AS MEMÓRIAS ANTES DE FECHAR O PROGRAMA
void limpar_lista1(LISTA* lista1)
{
    if(lista1->inicio == NULL){
        cout << "A comunidade de membros do café está vazia.\n";
        return;
    }

    REGISTRO* aux;
    aux = lista1->inicio;
    
    while(aux != NULL){
        REGISTRO* apagar = aux;
        aux = aux->next;
        delete apagar;
    }
    lista1->inicio = NULL;
    lista1->final = NULL;
}


void limpar_lista2(LISTA2* lista2)
{
    if(lista2->inicio == NULL){
        cout << "A comunidade de membros do café está vazia.\n";
        return;
    }

    NODE* aux;
    aux = lista2->inicio;
    
    while(aux != NULL){
        NODE* apagar = aux;
        aux = aux->next;
        delete apagar;
    }
    lista2->inicio = NULL;
    lista2->final = NULL;
}


// FUNÇÃO PARA SALVAR OS PAGAMENTOS EM ARQUIVO TXT
void salvar_contribuintes(LISTA2* lista2, LISTA* lista1)
{
    // CRIA E ABRE ARQUIVO PARA LEITURA
    ofstream arquivo("contribuintes.txt", ios::out | ios::trunc);
    if(!arquivo){
        cerr << "Erro ao abrir o arquivo de contribuintes.";
        return;
    }

    // VERIFICA SE A LISTA DO SISTEMA ESTÁ VAZIA
    if (lista2 == NULL) {
        cout << "Erro: A lista está vazia, ou não foi inicializada corretamente." << endl;
        return;
    }
    
    // VERIFICA SE O ARQUIVO ABRIU CORRETAMENTE
    if(arquivo.is_open()){
        NODE* aux = lista2->inicio;

        // PERCORRE A LISTA SALVANDO OS REGISTROS
        while (aux != NULL)
        {
            arquivo << aux->pagamento.id_membro; arquivo << " ";
            arquivo << aux->pagamento.mes; arquivo << " ";
            arquivo << aux->pagamento.ano; arquivo << " ";
            arquivo << aux->pagamento.valor; arquivo << " ";
            // PROCURA O CURSO CORRESPONDENTE NA LISTA1
            REGISTRO* membro_aux = lista1->inicio;
            while (membro_aux != NULL) {
                if (membro_aux->membro.id == aux->pagamento.id_membro) {
                    arquivo << membro_aux->membro.curso << endl;
                    break;
                }
                membro_aux = membro_aux->next;
            }
            arquivo << endl;
            aux = aux->next;  
        }
        return;
    }
}


// FUNÇÃO PARA SEPARAR OS CONTRIBUINTES POR CURSO E SALVAR EM TXT
void salvar_contribuintes_por_curso(LISTA2* lista2) {
    if (lista2 == NULL) {
        cout << "Erro: A lista está vazia, ou não foi inicializada corretamente." << endl;
        return;
    }
    
    ofstream arquivo_DSM("contribuintes_DSM.txt", ios::out | ios::trunc);
    ofstream arquivo_SI("contribuintes_SI.txt", ios::out | ios::trunc);
    ofstream arquivo_GE("contribuintes_GE.txt", ios::out | ios::trunc);
    
    if (!arquivo_DSM || !arquivo_SI || !arquivo_GE) {
        cerr << "Erro ao abrir algum dos arquivos de contribuintes." << endl;
        return;
    }
    
    NODE* aux = lista2->inicio;
    while (aux != NULL) {
        ofstream* arquivo;
        if (aux->pagamento.curso == "DSM" || aux->pagamento.curso == "dsm") {
            arquivo = &arquivo_DSM;
        } else if (aux->pagamento.curso == "SI" || aux->pagamento.curso == "si") {
            arquivo = &arquivo_SI;
        } else if (aux->pagamento.curso == "GE" || aux->pagamento.curso == "ge") {
            arquivo = &arquivo_GE;
        } else {
            // cerr << "Curso desconhecido para o contribuinte com ID " << aux->pagamento.id_membro << endl;
            aux = aux->next;
            continue;
        }
        
        *arquivo << aux->pagamento.id_membro << " "
                 << aux->pagamento.curso << " "
                 << aux->pagamento.mes << " "
                 << aux->pagamento.ano << " "
                 << aux->pagamento.valor << endl;
        
        aux = aux->next;
    }
    
    arquivo_DSM.close();
    arquivo_SI.close();
    arquivo_GE.close();
}


// FUNÇÃO PARA VERIFICAR SE JA EXISTE O MEMBRO NO TXT
bool id_existe(LISTA2* lista, int id) {
    NODE* aux = lista->inicio;
    while (aux != NULL) {
        if (aux->pagamento.id_membro == id) {
            return true; // ID encontrado na lista
        }
        aux = aux->next;
    }
    return false; // ID não encontrado na lista
}