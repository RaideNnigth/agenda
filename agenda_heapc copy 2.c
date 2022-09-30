/*
    Faça uma agenda capaz de incluir, apagar, buscar e listar quantas pessoas o usuário desejar, porém toda a informação
    incluída na agenda deve ficar num único lugar chamado: “void *pBuffer”. [OK] (revisar parte de listar)
        1 - Não pergunte para o usuário quantas pessoas ele vai incluir. [OK]
        2 - Não pode alocar espaço para mais pessoas do que o necessário. [OK]
        3 - Cada pessoa tem nome[10], idade e telefone. [OK]
        4 - Nenhuma variável pode ser declarada em todo o programa, somente ponteiros. [OK]
        5 - Todos os dados do programa devem ser guardados dentro do pBuffer. [OK]
        6 - Nem mesmo como parâmetro de função. Só ponteiros que apontam para dentro do pBuffer. 
            Exemplo do que não pode: int c; char a; int v[10];  void Funcao(int parametro) [OK]
        7 - Não pode usar struct em todo o programa. [OK]
        8 - Usar fila ordenada (heap) para armazenar as pessoas em ordem alfabética sempre que o usuário incluir uma nova pessoa.
        9 - Implementar a base de dados da agenda usando lista duplamente ligada
       10 - Somente essa base de dados pode ficar fora do buffer principal, ou seja, pode usar um malloc para cada nodo.
*/
/*
    Autor: Gustavo Pereira - GPP
    Data de criação: 02/09/2022
    Última atualização: 02/09/2022
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void *pBuffer;

int *estaRodando;

void * insert(char* name, int* age, long* number, void * stackHead, int*stackSize);
void * newNode(char* name, int* age, long* number);
void * reset(void* head);
void   list(void* stackHead);
int*   getLexographicallyOrder(char* str1, char* str2);
void* getNext(void* element);
void* getPrev(void* element);
long*  getNumber(void* element);
int*   getAge(void* element);
char*  getName(void* element);
int* size;

void menu();

int main(int argc, char *argv[])
{
    estaRodando = (int *)malloc(sizeof(int));
    *estaRodando = 0;
    pBuffer = NULL;
    
    while (*estaRodando == 0)
        menu();
    
    free(size);
    free(estaRodando);
    return 0;
}

void * newNode(char* name, int* age, long* number){
    void * node = (void *)malloc(sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**) * 2);

    char * pName = (char *)node;
    int * pAge = (int *)(node + sizeof(char) * 11);
    long * pNumber =  (long *)(node + sizeof(char) * 11 + sizeof(int));
    void ** pPrev = (void *)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    void ** pNext = (void *)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    
    memcpy(pName, name, strlen(name));
    *pAge = *age;
    *pNumber = *number;
    *pPrev = NULL;
    *pNext = NULL;

	return node;
}

int* getLexographicallyOrder(char* str1, char* str2){
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    int *res = malloc(sizeof(int));
    *res = (*str1 - *str2);

    if (*res < 0)
        *res = -1;
    else if (*res > 0)
        *res = 1;

    return res;
}
void * insert(char* name, int* age, long* number, void * stackHead, int* stackSize)
{
    void *nodo = newNode(name, age, number);

    if (nodo == NULL) {
        abort();
    }
    if(stackHead == NULL){
        return nodo;
    }

    void ** new = &stackHead;
     while (*new != NULL) {
        if(*getLexographicallyOrder(name, (char*)*new) == -1)
            break;
        new = (void **)(*new + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        new = new;
    }
    void **nodoNext = (void *)(nodo + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    *nodoNext = *new;
    void **nodoPrev = (void *)(nodo + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    void **personPrev = (void *)(new + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    *nodoPrev = *(void**)personPrev;
    *personPrev = nodo;
    if(*new == stackHead)
        *new = nodo;
    return stackHead;
}
void list(void* stackHead){
    void * current  = stackHead;
    while (current != NULL) {
        printf("The person's name is %s\n", (char*)current);
        current += sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**);
        current = *(void**)current;
    }
}
void menu()
{
    printf("-------------------------------\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("1) Adicionar contato:  \n");
    printf("2) Remover contato: \n");
    printf("3) Listar contatos: \n");
    printf("4) Procurar por nome: \n");
    printf("5) Procurar por idade: \n");
    printf("6) Procurar por telefone: \n");
    printf("7) Sair: \n");

    int opcao = 0;
    scanf("%d", &opcao);
    switch (opcao)
    {
    case 1:
        int *age = malloc(sizeof(int));
        long *number = malloc(sizeof(long));
        char *name = malloc(sizeof(char) * 11);
        
        printf("Digite o nome: ");
        scanf("%10s", name);
        printf("Digite a idade: ");
        scanf("%d", age);
        printf("Digite o telefone: ");
        scanf("%ld", number);
        pBuffer = insert(name, age, number, pBuffer, size);
        break;
    case 2:

        break;
    case 3:
        list(pBuffer);
        break;
    case 4:

        break;
    case 5:

        break;
    case 6:

        break;
    case 7:
        *estaRodando = 1;
        break;
    default:
        printf("-------------------------------\n");
        printf("Opcao invalidas\n");
        break;
    }
}