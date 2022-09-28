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

void * insert(char* name, int* age, long* number, int* size, void * stackHead);
void * newNode(char* name, int* age, long* number, int* size);
int* getLexographicallyOrder(char* str1, char* str2);
int* size;
void menu();

int main(int argc, char *argv[])
{
    estaRodando = (int *)malloc(sizeof(int));
    pBuffer = (void *)calloc(1, (sizeof(char) * 11) + sizeof(long) + (sizeof(int) * 2) + (sizeof(void**) * 2));
    size = pBuffer;
    *size = *(int*)pBuffer;
    *estaRodando = 0;
    
    while (*estaRodando == 0)
        menu();
    
    free(pBuffer);
    free(estaRodando);
    return 0;
}
void * newNode(char* name, int* age, long* number, int* size){
    void * node = (void *)malloc((sizeof(int)) + (sizeof(char) * 11) + (sizeof(int)) + (sizeof(long)) + (sizeof(void**) * 2));
    int * pAge = (int *)(node + (sizeof(int)) + (sizeof(char) * 11));
    long * pNumber =  (long *)(node + (sizeof(int)) + (sizeof(char) * 11) + (sizeof(int)));
    char * pName = (char *)(node + (sizeof(int)));
    int * pSize= (int *)node;
    int * pCurrentSize = (int*)node;
    void ** pPrev = (void **)(node + ((sizeof(int)) + (sizeof(char) * 11) + (sizeof(int)) + (sizeof(long))));
    void ** pNext = (void **)(node + ((sizeof(int)) + (sizeof(char) * 11) + (sizeof(int)) + (sizeof(long)) + (sizeof(void*))));
    memcpy(pName, name, strlen(name));
    
    *pAge = *age;
    *pNumber = *number;
    *pSize = *size;
    *pPrev = NULL;
    *pNext = NULL;

	return node;
}
void * insert(char* name, int* age, long* number, int* size, void * stackHead)
{
    void* head = stackHead + sizeof(int);
    if(*size == 0){       
        stackHead += sizeof(int);
        memcpy((char*)stackHead, name, strlen(name));
        stackHead += sizeof(char) * 11;
        *(int*)stackHead = *age;
        stackHead += sizeof(int);
        *(int*)stackHead = *number;
        stackHead += sizeof(int);
        *(void**)stackHead = NULL;
        stackHead += sizeof(void**);
        *(void**)stackHead = NULL;
        stackHead = head - sizeof(int);
        (*size)++;
        return stackHead;
    }
    void *node = newNode(name, age, number, size);
    void **pPrev = node + sizeof(char) * 11 + sizeof(int) + sizeof(long);
    void **pNext = node + sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void **);

    void * prev = NULL;
    void * current = NULL;
    void * next = NULL;
    int * checkValue = NULL;
    
    for (int i = 0; i < *size; i++)
    {
        checkValue = getLexographicallyOrder(name, (char*)head);
        if( *checkValue < 0 ){
            
            if(i != 0){
                prev = head;
                prev -= sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**) * 2;
            }
            else{
                head = stackHead;
                prev = head;
            }
            current = head;
            next = head;
            if(*size != 1 && i+1 < *size)
                next += sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**) * 2;
            if(i != 0){
                *(void**)pPrev = (void*)prev;
                prev += sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**);
            }
            current += sizeof(char) * 11 + sizeof(int) + sizeof(long);
            *(void**)current = (void*)node;
            current += sizeof(void**);
            if(*size != 1 && i+1 < *size){
                *(void**)pNext = (void*)current;
                *(void**)prev = (void*)node;
                *(void**)current = (void*)next;
            }
            next += sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**);
            *(void**)next = (void*)head;
            if(i == 0){
                stackHead = node;
            }
            break;
        }
        head += sizeof(char) * 11 + sizeof(int) + sizeof(long) + sizeof(void**);
        head = *(void**)head;
    }

    (*size)++;
    free(checkValue);
    return stackHead;
}
int* getLexographicallyOrder(char* str1, char* str2){
    while (*str1 && *str2 && *str1 == *str2) {
        str1++;
        str2++;
    }
    int *result = malloc(sizeof(int));
    *result = (*str1 - *str2);

    if (*result < 0)
        *result = -1;
    else if (*result > 0)
        *result = 1;

    return result;
}
void menu()
{
    printf("-------------------------------\n");
    printf("Escolha uma das opcoes abaixo: \n");
    printf("1) Adicionar contato:  \n");
    printf("2) Remover contato: \n");
    printf("3) Listar contato: \n");
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
        pBuffer = insert(name, age, number, size, pBuffer);
        break;
    case 2:

        break;
    case 3:

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