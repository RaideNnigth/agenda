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

void   insert(char* name, int* age, long* number, void** stackHead);
void * newNode(char* name, int* age, long* number);
void   removePerName(char* name, void** stackHead);
void   searchName(void** stackHead,char* name); 
void   list(void** stackHead, int* howMany);
void   freeList(void** stackHead);
int    getLexographicallyOrder(char* str1, char* str2);

void menu();

int main(int argc, char *argv[])
{
    estaRodando = (int *)malloc(sizeof(int));
    *estaRodando = 0;
    pBuffer = malloc(sizeof(void**));
    *pBuffer = NULL;
    
    while (*estaRodando == 0)
        menu();
    
    free(estaRodando);
    free(pBuffer);
    return 0;
}

void * newNode(char* name, int* age, long* number){
    void * node = (void *)calloc(1, sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**) * 2);

    char * pName = (char *)node;
    int * pAge = (int *)(node + sizeof(char) * 11);
    long * pNumber =  (long *)(node + sizeof(char) * 11 + sizeof(int));
    void ** pPrev = (void **)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    void ** pNext = (void **)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    
    memcpy(pName, name, strlen(name));
    *pAge = *age;
    *pNumber = *number;
    *pPrev = NULL;
    *pNext = NULL;
	return node;
}

int getLexographicallyOrder(char* str1, char* str2){
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    int *res = malloc(sizeof(int));
    *res = (*str1 - *str2);

    if (*res < 0){
        free(res);
        return -1;
    }
    else if (*res > 0)
    {
        free(res);
        return 1;
    }

    free(res);
    return 0;
}
void insert(char* name, int* age, long* number, void ** stackHead)
{
    void *node = newNode(name, age, number);
    void **prev, **curr;
    prev = malloc(sizeof(void**));
    curr = malloc(sizeof(void**));
    *prev = NULL;
    *curr = (void*)*stackHead;

    void ** pPrev = (void **)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    void ** pNext = (void **)(node + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    
    if (*stackHead == NULL) {
        *stackHead = node;
        free(prev);
        free(curr);
        return;
    }
    while (*curr != NULL && getLexographicallyOrder(name, (char*)*curr) >= 0) {
        *prev = *curr;
        *curr = *(void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    }
    if (*prev == NULL) {
        *pNext = *curr;
        void** currPrev = (void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long));
        *currPrev = node;
        *stackHead = node;
    }
    else if (*curr != NULL) { 
        void** prevNext = (void**)(*prev + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        *prevNext = node;
        *pNext = *curr;
        void** currPrev = (void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long));
        *currPrev = node;
        *pPrev = prev;
    }
    else {
        void** prevNext = (void**)(*prev + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        *prevNext = node;
        *pPrev = *prev;
    }

    free(prev);
    free(curr);
    return;
}
void searchName(void** stackHead,char* name){
    if (*stackHead == NULL)
        return;
    
    void **prev, **curr;
    prev = malloc(sizeof(void**));
    curr = malloc(sizeof(void**));
    *prev = NULL;
    *curr = (void*)*stackHead;

    while (*curr != NULL && getLexographicallyOrder(name, (char*)*curr) != 0) {
        *prev = *curr;
        *curr = *(void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    }
    *prev = *curr;
    printf("-------------------------------\n");
    printf("Nome: %s\n", (char*)*prev);
    *prev += sizeof(char) * 11;
    printf("Idade: %d\n", *(int*)*prev);
    *prev += sizeof(int);
    printf("Number: %ld\n", *(long*)*prev);
    free(prev);
    free(curr);
    free(*curr);
}
void removePerName(char* name, void** stackHead){
    if (*stackHead == NULL)
        return;
    
    void **prev, **curr, **next;
    prev = malloc(sizeof(void**));
    curr = malloc(sizeof(void**));
    *prev = NULL;
    *curr = (void*)*stackHead;

    while (*curr != NULL && getLexographicallyOrder(name, (char*)*curr) != 0) {
        *prev = *curr;
        *curr = *(void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    }
    void ** pPrev = (void **)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    void ** pNext = (void **)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
    if (*prev == NULL) {
        void** currNext = (void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        *stackHead = *currNext;
    }
    else if (*curr != NULL) { 
        void** prevNext = (void**)(*prev + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        void** currNext = (void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        void** nextPrev = (void**)(*currNext + sizeof(char) * 11 + sizeof(int) + sizeof(long));
    }
    free(prev);
    free(curr);
}
void list(void** stackHead, int* howMany){
    void **prev, **curr;
    prev = malloc(sizeof(void**));
    curr = malloc(sizeof(void**));
    *prev = NULL;
    *curr = (void*)*stackHead;
    int *c = malloc(sizeof(int));
    *c = 0;
    while (*curr != NULL && *howMany > *c) {
        *prev = *curr;
        printf("-------------------------------\n");
        printf("Nome: %s\n", (char*)*(void**)prev);
        *prev += sizeof(char) * 11;
        printf("Idade: %d\n", *(int*)*prev);
        *prev += sizeof(int);
        printf("Number: %ld\n", *(long*)*prev);
        *curr = *(void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        (*c)++;
    }
    free(c);
    free(prev);
    free(curr);
}
void freeList(void** stackHead){
    void **prev, **curr;
    prev = malloc(sizeof(void**));
    curr = malloc(sizeof(void**));
    *prev = NULL;
    *curr = (void*)*stackHead;

    while (*curr != NULL) {
        *prev = *curr;
        *curr = *(void**)(*curr + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**));
        free(*prev);
    }
    free(prev);
    free(curr);
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
        free(age);
        free(name);
        free(number);
        break;
    case 2:
        char *nameToRemove = malloc(sizeof(char) * 11);
        printf("Digite o nome do contato a ser apagado: ");
        scanf(" %s", nameToRemove);
        removePerName(nameToRemove, pBuffer);
        free(nameToRemove);
        break;
    case 3:
        int *howMany = malloc(sizeof(int));
        printf("Quantos quer listar? ");
        scanf("%d", howMany);
        list(pBuffer, howMany);
        free(howMany);
        break;
    case 4:
        char *nameToSearch = malloc(sizeof(char) * 11);
        printf("Digite o nome do contato a ser exibido: ");
        scanf(" %s", nameToSearch);
        searchName(pBuffer, nameToSearch);
        free(nameToSearch);
        break;
    case 5:
        *estaRodando = 1;
        freeList(pBuffer);
        break;
    default:
        printf("-------------------------------\n");
        printf("Opcao invalidas\n");
        break;
    }
}