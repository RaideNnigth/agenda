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
void *pPositionBuffer;

int *nPeople;
int *estaRodando;

void addPerson();
void removePersonByTelefone();
void listPeople();
void searchPersonByName();
void searchPersonByAge();
void searchPersonByTelefone();
void sort();
void menu();

int main(int argc, char *argv[])
{
    nPeople = (int *)malloc(sizeof(int));
    estaRodando = (int *)malloc(sizeof(int));
    pBuffer = (void *)malloc((sizeof(char) * 10) + (sizeof(int) * 2));
    *nPeople = 0;
    *estaRodando = 0;
    
    
    while (*estaRodando == 0)
        menu();
    
    free(nPeople);
    free(pBuffer);
    return 0;
}
void addPerson()
{
    (*nPeople)++;
    pBuffer = (void *)realloc(pBuffer, *nPeople * ((sizeof(char) * 10) + (sizeof(int) * 2)));
    pPositionBuffer = pBuffer;
    pPositionBuffer += (*nPeople - 1) * ((sizeof(char) * 10) + (sizeof(int) * 2));
    printf("--------------------------------------------------------\n");
    printf("Adicionando novo contato!\n");
    printf("Digite um nome para adicionar (ate 10 caracteres): \n");
    scanf("%s", (char *)pPositionBuffer);
    pPositionBuffer += sizeof(char) * 10;
    printf("--------------------------------------------------------\n");
    printf("Digite a idade da pessoa: \n");
    scanf("%d", (int *)pPositionBuffer);
    pPositionBuffer += sizeof(int);
    printf("--------------------------------------------------------\n");
    printf("Digite o numero de telefone a adicionar: \n");
    scanf("%d", (int *)pPositionBuffer);
    sort();
}
void removePersonByTelefone()
{
    if (*nPeople != 0)
    {
        int *pTelefoneBuffer;
        pTelefoneBuffer = malloc(sizeof(int));
        pPositionBuffer = pBuffer;
        *pTelefoneBuffer = 0;
        printf("--------------------------------------------------------\n");
        printf("Telefone para excluir: \n");
        scanf("%d", pTelefoneBuffer);
        for (int i = 0; i < *nPeople; i++)
        {
            if (*pTelefoneBuffer == *(int *)(pPositionBuffer + (sizeof(char) * 10 + sizeof(int))))
            {
                memmove(pPositionBuffer, pPositionBuffer, (*nPeople - i) * 
                                                                        (sizeof(char) * 10) + (sizeof(int) * 2));
                (*nPeople)--;
                break;
            }else
                pPositionBuffer += (sizeof(int)) * 2 + (sizeof(char) * 10);
        }
        free(pTelefoneBuffer);
    }else{
        printf("--------------------------------------------------------\n");
        printf("Primeiro adicione alguem a lista: \n");
    }
}
void listPeople()
{
    if (*nPeople != 0)
    {
        pPositionBuffer = pBuffer;
        for (int i = 0; i < *nPeople; i++)
        {
            printf("--------------------------------------------------------\n");
            printf("Nome: %s \n", (char *)pPositionBuffer);
            pPositionBuffer += (sizeof(char) * 10);
            printf("Idade: %d \n", *(int *)pPositionBuffer);
            pPositionBuffer += sizeof(int);
            printf("Telefone: %d \n", *(int *)pPositionBuffer);
            pPositionBuffer += sizeof(int);
        }
    }else{
        printf("--------------------------------------------------------\n");
        printf("Primeiro adicione alguem a lista: \n");
    }
}
void searchPersonByName()
{
    if (*nPeople != 0)
    {
        char *pNameBuffer;
        int *pBool;
        pNameBuffer = malloc(sizeof(char) * 10);
        pBool = malloc(sizeof(int));
        pPositionBuffer = pBuffer;
        *pBool = 0;
        printf("--------------------------------------------------------\n");
        printf("Nome para procurar: \n");
        scanf("%s", pNameBuffer);
        for (int i = 0; i < *nPeople; i++)
        {
            for (int j = 0; j < strlen(pNameBuffer); j++)
                if (((char *)pPositionBuffer)[j] != pNameBuffer[j])
                {
                    *pBool = 1;
                    break;
                }
            if (*pBool == 0)
            {
                printf("--------------------------------------------------------\n");
                printf("Nome: %s \n", (char *)pPositionBuffer);
                pPositionBuffer += (sizeof(char) * 10);
                printf("Idade: %d \n", *(int *)pPositionBuffer);
                pPositionBuffer += sizeof(int);
                printf("Telefone: %d \n", *(int *)pPositionBuffer);
                pPositionBuffer += sizeof(int);
            }
            else
                pPositionBuffer += (sizeof(char) * 10) + (sizeof(int) * 2);
            *pBool = 0;
        }
        free(pNameBuffer);
        free(pBool);
    }else{
        printf("--------------------------------------------------------\n");
        printf("Primeiro adicione alguem a lista: \n");
    }
}
void searchPersonByAge()
{
    if (*nPeople != 0)
    {
        int *pAgeBuffer;
        pAgeBuffer = malloc(sizeof(int));
        pPositionBuffer = pBuffer;
        *pAgeBuffer = 0;
        printf("--------------------------------------------------------\n");
        printf("idade para procurar: \n");
        scanf("%d", pAgeBuffer);
        for (int i = 0; i < *nPeople; i++)
        {
            if (*pAgeBuffer == *(int *)(pPositionBuffer + (sizeof(char) * 10)))
            {
                printf("--------------------------------------------------------\n");
                printf("Nome: %s \n", (char *)pPositionBuffer);
                pPositionBuffer += (sizeof(char) * 10);
                printf("Idade: %d \n", *(int *)pPositionBuffer);
                pPositionBuffer += sizeof(int);
                printf("Telefone: %d \n", *(int *)pPositionBuffer);
                pPositionBuffer += sizeof(int);
            }else
                pPositionBuffer += (sizeof(int)) * 2 + (sizeof(char) * 10);
        }
        free(pAgeBuffer);
    }else{
        printf("--------------------------------------------------------\n");
        printf("Primeiro adicione alguem a lista: \n");
    }
}
void searchPersonByTelefone()
{
    if (*nPeople != 0)
    {
        int *pTelefoneBuffer;
        pTelefoneBuffer = malloc(sizeof(int));
        pPositionBuffer = pBuffer;
        *pTelefoneBuffer = 0;
        printf("--------------------------------------------------------\n");
        printf("Telefone para procurar: \n");
        scanf("%d", pTelefoneBuffer);
        for (int i = 0; i < *nPeople; i++)
        {
            if (*pTelefoneBuffer == *(int *)(pPositionBuffer + (sizeof(char) * 10 + sizeof(int))))
            {
                printf("--------------------------------------------------------\n");
                printf("Nome: %s \n", (char *)pPositionBuffer);
                pPositionBuffer += (sizeof(char) * 10);
                printf("Idade: %d \n", *(int *)pPositionBuffer);
                pPositionBuffer += sizeof(int);
                printf("Telefone: %d \n", *(int *)pPositionBuffer);
                pPositionBuffer += sizeof(int);
                break;
            }else
                pPositionBuffer += (sizeof(int)) * 2 + (sizeof(char) * 10);
        }
        free(pTelefoneBuffer);
    }else{
        printf("--------------------------------------------------------\n");
        printf("Primeiro adicione alguem a lista: \n");
    }
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
        addPerson();
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