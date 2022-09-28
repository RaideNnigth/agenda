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

void addPerson(void * stackHead);
void removePersonByTelefone();
void listPeople();
void searchPersonByName();
void searchPersonByAge();
void searchPersonByTelefone();

void menu();

int main(int argc, char *argv[])
{
    estaRodando = (int *)malloc(sizeof(int));
    pBuffer = (void *)calloc(1, (sizeof(char) * 10) + (sizeof(int) * 3) + sizeof(void**) * 2);

    *estaRodando = 0;
    
    while (*estaRodando == 0)
        menu();
    
    free(pBuffer);
    free(estaRodando);
    return 0;
}
void addPerson(void * stackHead)
{
    void *pPosition = NULL;
    void *pElement = NULL;
    int *size = NULL;
    size = stackHead;
    pPosition = stackHead;

    pElement = malloc((sizeof(char) * 10) + (sizeof(int) * 2) + sizeof(void**));
    void *pElementStart = pElement;
    printf("--------------------------------------------------------\n");
    printf("Adicionando novo contato!\n");
    printf("Digite um nome para adicionar (ate 10 caracteres): \n");
    scanf("%s", (char *)pElement);
    pElement += sizeof(char) * 10;
    printf("--------------------------------------------------------\n");
    printf("Digite a idade da pessoa: \n");
    scanf("%d", (int *)pElement);
    pElement += sizeof(int);
    printf("--------------------------------------------------------\n");
    printf("Digite o numero de telefone a adicionar: \n");
    scanf("%d", (int *)pElement);
    pElement = pElementStart;
    (*(int*)pPosition)++;
    if(*(int*)pPosition == 1){
        pPosition += sizeof(int);
        memcpy((char *)pPosition, (char *)pElement, strlen((char *)pElement));
        pPosition += sizeof(char) * 10;
        pElement += sizeof(char) * 10;
        *(int *)pPosition = *(int *)pElement;
        pElement += sizeof(int);
        pPosition += sizeof(int);
        *(int *)pPosition = *(int *)pElement;
        pPosition += sizeof(int);
        *(void **)pPosition = NULL;
        pPosition += sizeof(void **);
        *(void **)pPosition = NULL;
        pPosition = stackHead;
 
    }
    pPosition += sizeof(int);
    pElement = pElementStart;
    int *checkValue = malloc(sizeof(int));
    *checkValue = 0;
    for(int i = 1; i < *size; i++){
        for (int j = 0; j < strlen((char *)pElement); j++)
        {
            if(strncmp((char *)(pElement + j), (char *)pPosition + j, 1) < 0){
                *checkValue = 1;
                break;
            }
        }
        if(*checkValue == 1){
            void *currentPosition = pPosition;
            //pPosition += (sizeof(char) * 10) + (sizeof(int) * 2);
            void * prevPosition = NULL;
            prevPosition = pPosition;
            prevPosition -= (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void**) * 2);
            void *nextPosition = pPosition;
            nextPosition += (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void**) * 2);
            
            for (int i = 0; i < *size; i++)
            {    
                if(pPosition == currentPosition){
                    //pElement PREV and NEXT
                    pElement += (sizeof(char) * 10) + (sizeof(int) * 2);
                    *(void**)pElement = (void*)prevPosition;
                    pElement += sizeof(void**);
                    *(void**)pElement = (void*)currentPosition;
                    //RESET pElement POS
                    pElement = pElementStart;
                    //prevPosition NEXT
                    prevPosition += (sizeof(char) * 10) + (sizeof(int) * 2) + sizeof(void**);
                    *(void**)prevPosition = (void*)pElement;
                    //current BEFORE
                    currentPosition += (sizeof(char) * 10) + (sizeof(int) * 2);
                    *(void**)currentPosition = (void*)pElement;
                    //current NEXT
                    currentPosition += sizeof(void**);
                    *(void**)currentPosition = (void*)nextPosition;
                    //current RESET
                    currentPosition -= (sizeof(char) * 10) + (sizeof(int) * 2) + sizeof(void**);
                    //next BEFORE
                    nextPosition += (sizeof(char) * 10) + (sizeof(int) * 2);
                    *(void**)nextPosition = (void*)currentPosition;
                    //RESET pElement POS
                    pElement = pElementStart;
                    break;
                }   
                pPosition += (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void**) * 2); 
            }
            break;
        }
        pPosition += (sizeof(char) * 10) + (sizeof(int) * 2) + (sizeof(void**) * 2);
    }
    free(checkValue);
}
void removePersonByTelefone()
{}
void listPeople()
{}
void searchPersonByName()
{}
void searchPersonByAge()
{}
void searchPersonByTelefone()
{}
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
        addPerson(pBuffer);
        break;
    case 2:
        removePersonByTelefone();
        break;
    case 3:
        listPeople();
        break;
    case 4:
        searchPersonByName();
        break;
    case 5:
        searchPersonByAge();
        break;
    case 6:
        searchPersonByTelefone();
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