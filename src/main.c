/*
  Arquivo: MAIN.C
  Autor: Roberto Bauer
  Observacoes: 
            Arquivo central do programa, funcaoh main()
*/

#define __MAIN_C__

#include "main.h"



int main(int argc, char *argv[])
{
    SBINTREE *BT;

    // configura a estrutura de dados da arvore binaria
    BT = CreateBinTree( CreateData,
                        DeleteData,
                        DuplicatedNode,
                        NodeDataCmp, 
                        PrintData);

    if (BT == NULL)
    {
        fprintf(stderr, "Erro criando arvore binaria\n");
        exit(EXIT_FAILURE);
    }

    // controla as opcoes para teste
    // na arvore criada
    // possui um loop interno que serah finalizado 
    // quando o usuario escolher a opcaoh
    Menu(BT);

    // libera toda a memoria utilizada pela arvore binaria
    DestroyBinTree(BT);

    return (EXIT_SUCCESS);
}


