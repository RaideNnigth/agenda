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

void **pBuffer;

int *estaRodando;

void insert(char* name, int* age, long* number, void ** stackHead);
void * newNode(char* name, int* age, long* number);
void * reset(void* head);
void   list(void** stackHead);
int*   getLexographicallyOrder(char* str1, char* str2);
void*  getNext(void* element);
void*  getPrev(void* element);
long*  getNumber(void* element);
int*   getAge(void* element);
char*  getName(void* element);
int* size;

void menu();

int main(int argc, char *argv[])
{
    estaRodando = (int *)malloc(sizeof(int));
    *estaRodando = 0;
    pBuffer = malloc(sizeof(void**));
    *pBuffer = NULL;
    
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
void insert(char* name, int* age, long* number, void ** stackHead)
{
    void *node = newNode(name, age, number);

 /* Maintain two pointers to the previous and current nodes: */
    void *prev, *curr;
    prev = NULL;
    curr = (void*)*stackHead;

    void ** pPrev = (void *)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    void ** pNext = (void *)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    
    /* Case 1: consider if the list is empty: */
    if (*stackHead == NULL) {
        *stackHead = node;
        return;
    }
    
    /* Now iterate until we find the correct position in the list: */
    while (curr != NULL && *getLexographicallyOrder(name, (char*)curr) >= 0) {
        prev = curr;
        curr = *(void**)(curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    }

    /* 
     * Case 2: now consider if we are at the beginning of the list. We know we haven't entered the loop if 
     * prev never got reassigned:
     */
    if (prev == NULL) {
        *pNext = curr;
        /* Next line not needed if it's a singly linked list */
        curr = *(void**)(curr + sizeof(char) * 11 + sizeof(int) + sizeof(long));
        curr = node; 
        *stackHead = node;
    }

    /* Case 3: now consider if we are in between nodes in the list: */
    else if (curr != NULL) {
        prev = *(void**)(curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**)); 
        prev = node;
        *pNext = curr;
        /* Next two lines not needed if it's a singly linked list */
        curr = *(void**)(curr + sizeof(char) * 11 + sizeof(int) + sizeof(long));
        curr = node;
        *pPrev = prev;
    }

    /*
     * Case 4: now consider if we are inserting at the end of the list. We know we are at the end if curr is 
     * NULL, but we know at this point that we must be at the end, since the list is not empty, we aren't inserting 
     * at the front, and we aren't inserting in the middle:
     */
    else {
        *pPrev = prev;
        prev = *(void**)(prev + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**)); 
        prev = node;
        /* Next line not needed if singly linked list */
    }

    /* Now we are done! */
    return;
}
void list(void** stackHead){
    void *curr, *prev;
    curr = (void*)*stackHead;
    prev = NULL;
    while (curr != NULL) {
        printf("Nome: %s\n", (char*)curr);
        prev = curr;
        curr = *(void**)(curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
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
    printf("5) Sair: \n");

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
        insert(name, age, number, pBuffer);
        break;
    case 2:

        break;
    case 3:
        list(pBuffer);
        break;
    case 4:

        break;
    case 5:
        *estaRodando = 1;
        break;
    default:
        printf("-------------------------------\n");
        printf("Opcao invalidas\n");
        break;
    }
}