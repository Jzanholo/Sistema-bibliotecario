#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 25
///Struct dos Clientes
typedef struct clientes{
    int codigo,emprestado;
    char nome[MAX];
    struct clientes *prox;
}Clientes;
///Struct de Livros
typedef struct livros{
    Clientes li_em;
    char titulo[MAX];
    char assunto[MAX];
    char autor[MAX];
    int registro;
    int alugado;
    struct livros *prox;
}Livros;
/// Funcao para criar uma lista
Livros* CriaLista (void)
{
    return NULL;
}
/// Funcao para inserir um novo livro
Livros* inserir_livros(Livros* recebida, Livros L, Livros *emprestados)
{
    Livros *aux;
    int R;
    fflush(stdin);
    printf("Digite o nome do livro: ");
    gets(L.titulo);
    strupr(L.titulo);
    printf("\nDigite o autor do livro: ");
    gets(L.autor);
    strupr(L.autor);
    printf("\nDigite o assunto do livro: ");
    gets(L.assunto);
    strupr(L.assunto);
    do{
        printf("\nDigite o n\243mero de registro: ");
        fflush(stdin);
        scanf("%d", &L.registro);
    }while(L.registro<1 || L.registro>50);


    for(aux=recebida;aux!=NULL;aux=aux->prox)
        if(aux->registro==L.registro)
            R=1;


    for(aux=emprestados;aux!=NULL;aux=aux->prox)
        if(aux->registro==L.registro)
            R=1;

    if(R==1)
    {
        printf("Este n\243mero de registro j\240 est\240 em uso!");
        return recebida;
    }

    if(R!=1)
    {
        Livros  *novo ;
        novo= (Livros*) malloc(sizeof(Livros));
        strcpy(novo->titulo,L.titulo);
        strcpy(novo->assunto,L.assunto);
        strcpy(novo->autor,L.autor);
        novo->registro=L.registro;
        novo->prox = recebida;
        novo->alugado=0;
        printf("\nLivro cadastrado com sucesso");
        return novo;
    }
    return recebida;
}
///Funcao imprime os livros
void imprime_livros(Livros* recebida)
{
    Livros *aux;
    aux=CriaLista();
    if(recebida==NULL)
    {
        printf("Nenhum livro cadastrado");
    }
    for(aux=recebida;aux!=NULL;aux=aux->prox)
    {
        printf("\n-----------------------------");
        printf("\nT\241tulo:   %s", aux->titulo);
        printf("\nAssunto:  %s", aux->assunto);
        printf("\nAutor:    %s", aux->autor);
        printf("\nRegistro: %d", aux->registro);
        printf("\n-----------------------------");
    }
}
///Funcao para imprimir todos os livros que estao alugados para os clientes
void imprime_livros_clientes(Livros* recebida, Clientes * clientes)
{
    Livros *aux;
    Clientes *aux2=NULL;
    aux=CriaLista();
    if(recebida==NULL)
    {
        printf("Nenhum livro cadastrado");
    }

    for(aux2=clientes;aux2!=NULL;aux2=aux2->prox)
    {
        if (aux2->emprestado==1)
        {
            printf("\nLivros de %s\n",aux2->nome);
            for(aux=recebida;aux!=NULL;aux=aux->prox)
            {
                if(aux->alugado==aux2->codigo)
                {
                    printf("\n-----------------------------");
                    printf("\nT\241tulo:   %s", aux->titulo);
                    printf("\nAssunto:  %s", aux->assunto);
                    printf("\nAutor:    %s", aux->autor);
                    printf("\nRegistro: %d", aux->registro);
                    printf("\nCodigo do Cliente: %d", aux2->codigo);
                    printf("\n-----------------------------");
                }
            }
        }
    }
}
///Funcao para registrar um novo cliente
Clientes* inserir_cliente(Clientes* recebida, Clientes C)
{
    Clientes *aux;
    int R;
    fflush(stdin);
    printf("\nDigite seu nome: ");
    gets(C.nome);
    strupr(C.nome);
    do {
        printf("\nDigite seu c\242digo de identifica\207\306o: ");
    fflush(stdin);
    scanf("%d", &C.codigo);
    }while(C.codigo<1 || C.codigo>50);

    for(aux=recebida;aux!=NULL;aux=aux->prox)
    {
        if(aux->codigo==C.codigo)
        {
            printf("C\242digo de identificac\207\306o j\240 est\240 em uso!");
            R=1;
            break;
        }
    }
    if(R!=1)
    {
        Clientes  *novo;
        novo= (Clientes*) malloc(sizeof(Clientes));
        strcpy(novo->nome,C.nome);
        novo->codigo=C.codigo;
        novo->emprestado=0;
        novo->prox = recebida;
        printf("\nCliente cadastrado com sucesso");
        return novo;
    }
    return recebida;
}
/// Funcao para tirar o livro da lista de disponiveis e colocar na lista de livros emprestados
Livros* EmprestaLivro(Livros ***recebida, char titulo[],Livros *emprestados)
{
    Livros *aux, *aux2, *aux3;
    int cont=0;
    aux=CriaLista();
    aux2=CriaLista();
    aux3=CriaLista();

    aux=**recebida;
    aux2=**recebida;
    Livros  *novo ;
    novo= (Livros*) malloc(sizeof(Livros));

    while(aux!=NULL)
    {
        if (cont>1)
            aux2=aux2->prox;
        Livros *t=aux->prox;

        if(strcmp(aux->titulo,titulo)==0)
        {
            strcpy(novo->titulo,aux->titulo);
            strcpy(novo->assunto,aux->assunto);
            strcpy(novo->autor,aux->autor);
            novo->registro=aux->registro;
            novo->alugado=aux->alugado;
            novo->prox=emprestados;

            free(aux);

            if(cont==0)
                **recebida=t;

            else
                aux2->prox=t;

            return novo;
        }
        aux=t;
        cont++;
    }
}
///Funcao para alugar um livro da biblioteca
Livros* aluguel(Livros** recebida, Livros L, Clientes* clientes,Livros *emprestado)
{
    int opcao, opcao1, codigo, existe=0;
    char autor[MAX], assunto[MAX], titulo[MAX];
    Livros *aux;
    Clientes *aux1;
    do{
        printf("Digite seu c\242digo de identificac\207\306o: ");
        fflush(stdin);
        scanf("%d", &codigo);
    }while(codigo<1 || codigo>50);

    for(aux1=clientes;aux1!=NULL;aux1=aux1->prox)
    {
        if(codigo==aux1->codigo)
        {
            existe=1;
            if(recebida==NULL)
            {
                printf("\nNenhum livro cadastrado");
                printf("\n");
                system("pause");
                break;
            }

            do{
                printf("Caso voc\210 n\306o lembre o nome do livro, digite  '1'. Se n\306o digte '0': ");
                fflush(stdin);
                scanf("%d", &opcao);
            }while(opcao<0 || opcao>1);

            if(opcao==1)
            {
                do{
                    printf("\nVoce deseja pesquisar por autor ou assunto? 1<autor> 2<assunto>: ");
                    fflush(stdin);
                    scanf("%d", &opcao1);
                }while(opcao1<1 || opcao1>2);

                if(opcao1==1)
                {
                    printf("\nDigite o nome do autor: ");
                    fflush(stdin);
                    gets(autor);
                    strupr(autor);
                    for(aux=*recebida;aux!=NULL;aux=aux->prox)
                    {
                        if(strcmp(autor,aux->autor)==0)
                        {
                            printf("\n----------------------------");
                            printf("\nTitulo:   %s", aux->titulo);
                            printf("\nAssunto:   %s", aux->assunto);
                            printf("\n----------------------------\n");
                        }
                    }
                    system("pause");

                }
                if(opcao1==2)
                {
                    printf("\nDigite o nome do assunto: ");
                    fflush(stdin);
                    gets(assunto);
                    strupr(assunto);
                    for(aux=*recebida;aux!=NULL;aux=aux->prox)
                    {
                        if(strcmp(assunto,aux->assunto)==0)
                        {
                            printf("\n----------------------------");
                            printf("\nTitulo:   %s", aux->titulo);
                            printf("\nAutor:   %s", aux->autor);
                            printf("\n----------------------------");
                        }
                    }
                    system("pause");
                }
            }

            printf("\nDigite o nome do livro que voce deseja alugar: ");
            fflush(stdin);
            gets(titulo);
            strupr(titulo);
            for(aux=*recebida;aux!=NULL;aux=aux->prox)
            {
                if(strcmp(titulo,aux->titulo)==0)
                {
                    printf("\nLivro disponivel");
                    printf("\n----------------------------");
                    printf("\nTitulo:   %s", aux->titulo);
                    printf("\nAssunto:  %s", aux->assunto);
                    printf("\nAutor:    %s", aux->autor);
                    printf("\n----------------------------");
                    printf("\nAluguel do livro %s realizado com sucesso\n", aux->titulo);
                    aux->alugado=codigo;

                    emprestado=EmprestaLivro(&recebida,titulo,emprestado);
                    aux1->emprestado=1;

                    system("pause");
                    return emprestado;
                }
            }
            printf("\nLivro indispon\241vel\n");
            system("pause");

        }
        else if(aux1==NULL)
        {
            printf("Cliente inexistente\n");
            system("pause");
            break;
        }
    }
}
///Funcao para fazer as impressoes do programa;
void impressoes(Livros* recebida, Livros L, Clientes* clientes, Livros *emprestados)
{
    int opcao, opcao1, codigo;
    Livros *aux;
    Clientes *aux1;
    int escolha2;

    printf("IMPRESS\345ES:");
    printf("\n___________\n");
    printf("\n1-Imprimir os livros que est\306o emprestados por um dado cliente");
    printf("\n2-Imprimir a lista de todos os clientes com os respectivos livros emprestados");
    printf("\n3-Imprimir a lista de livros dispon\241veis da Biblioteca");
    printf("\n4-Voltar");
    do{
        printf("\n\nDigite a op\207\306o que voc\210 deseja: ");
        fflush(stdin);
        scanf("%d", &escolha2);
    }while(escolha2<1 || escolha2>4);

    if(escolha2==1)
    {
        printf("Digite o c\242digo de identifica\207\306o do cliente: ");
        scanf("%d",&codigo);
        if(clientes==NULL)
        {
            printf("\nNenhum cliente foi registrado\n");
            system("pause");
            return;
        }
        for(aux1=clientes;aux1!=NULL;aux1=aux1->prox)
        {
            if(codigo==aux1->codigo)
            {
                for(aux=emprestados;aux!=NULL;aux=aux->prox)
                {
                    if(codigo==aux->alugado)
                    {
                        printf("\n----------------------------");
                        printf("\nT\241tulo:   %s", aux->titulo);
                        printf("\nAssunto:  %s", aux->assunto);
                        printf("\nAutor:    %s", aux->autor);
                        printf("\n----------------------------\n\n\n");
                    }
                }
           }
            else if(aux1->prox==NULL)
            {
                printf("Cliente n\306o registrado no sistema\n");
                system("pause");
                return;
            }
        }
        system("pause");}
        if(escolha2==2)
        {
            imprime_livros_clientes(emprestados,clientes);
            printf("\n");
            system("pause");
        }
        if(escolha2==3)
        {
           imprime_livros(recebida);
           printf("\n");
           system("pause");
        }
}

int Menu()
{
    int escolha;
    printf("BEM-VINDO AO SISTEMA BIBLIOTECARIO: ");
    printf("\n____________________________________\n");
    printf("\n1-Cadastrar um livro");
    printf("\n2-Cadastrar um cliente");
    printf("\n3-Alugar um livro (o cliente deve estar cadastrado)");
    printf("\n4-Impress\344es");
    printf("\n5-Sair");
    do{
        printf("\n\nDigite a op\207\306o que voc\210 deseja: ");
        fflush(stdin);
        scanf("%d", &escolha);
    }while(escolha< 1 || escolha>5);

    system("cls");
    return escolha;
}

int main()
{

    int escolha3, codigo;
    Livros *LD, *LE;
    Livros LI;
    Clientes *C = NULL;
    Clientes cliente;
    LD=CriaLista();
    LE=NULL;
    int escolha1, escolha2;

    while(escolha1!=5)
    {
        escolha1=0;
        escolha2=1;
        system("cls");
        escolha1 = Menu();
        if(escolha1==1)
        {
            printf("CADASTRO DE LIVROS:");
            printf("\n______________________\n");
            while(escolha2==1)
            {
                LD=inserir_livros(LD, LI,LE);
                do{
                    printf("\nDeseja cadastrar mais algum livro? 1<SIM> 2<N\307O>");
                    fflush(stdin);
                    scanf("%d", &escolha2);
                }while(escolha2<1 || escolha2>2);
            }
        }
        else if(escolha1==2)
        {
            escolha2==1;
            printf("CADASTRO DE CLIENTES:");
            printf("\n______________________\n");
            while(escolha2==1)
            {
                C=inserir_cliente(C, cliente);
                do{
                    printf("\nDeseja cadastrar mais algum cliente? 1<SIM> 2<N\307O>");
                    fflush(stdin);
                    scanf("%d", &escolha2);
                }while(escolha2<1 || escolha2>2);
            }
        }
        else if(escolha1==3)
        {
            LE=aluguel(&LD,LI,C,LE);
        }
        else if(escolha1==4)
        {
            impressoes(LD,LI,C,LE);
        }
    }
    printf("\n\n");
    return 0;
}
