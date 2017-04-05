
/*
  Arquivo: BTDRIVER.C
  Autor: Roberto Bauer
  Observacoes:

*/

#define __BTDRIVER_C__

#include "main.h"

#define STR_SIZE        80


PRIVATE void Insert( SBINTREE * );
PRIVATE void Delete( SBINTREE * );
PRIVATE void Search( SBINTREE * );
PRIVATE void Display( SBINTREE * );
PRIVATE char *StrUpr (char *);
PRIVATE void LoadFile( SBINTREE * );
PRIVATE void SaveLog( SBINTREE * );

PRIVATE void Input( char *, char *, int );


void Menu( SBINTREE *BT )
    {
    char cTmp[10];
    int iChoice;
    BOOL bLoop = TRUE;

    while (bLoop) 
    {
        printf("\n\n( 1 ) Inserir\n");
        printf(    "( 2 ) Apagar\n");
        printf(    "( 3 ) Busca\n");
        printf(    "( 4 ) Imprime\n");
        printf(    "( 5 ) Carrega arquivo\n");
        printf(    "( 6 ) Salva\n");
        printf(    "( 0 ) Sair\n\n");


        Input("Escolha umas das alternativas anteriores : " , cTmp, 10 );
        if ( cTmp[0] != '\0' && (isdigit(*cTmp)) ) 
        {
            iChoice = atoi(cTmp) ;
            switch ( iChoice ) {
                case 1: Insert(BT);     break;
                case 2: Delete(BT);     break;
                case 3: Search(BT);     break;
                case 4: Display(BT);    break;
                case 5: LoadFile(BT);   break;
                case 6: SaveLog(BT);    break;
                case 0: bLoop = FALSE;  break;
            }
        }
    }
}

PRIVATE void Insert( SBINTREE *BT )
{
    char strWord[STR_SIZE];

    for ( ; ; ) {
        Input("Incluir palavra : " , strWord, STR_SIZE );
        if ( strWord[0] == '\0' ) break;

        // insere na arvore
        if (AddNode( BT, strWord ) == FALSE)
            fprintf(stderr, "ERRO! naoh adicionou noh.\n");
    }
}

PRIVATE void Delete( SBINTREE *BT )
{
    char strWord[STR_SIZE] ;

    Input("Excluir palavra : " , strWord, STR_SIZE );

    // apaga 
    if (DeleteNode( BT, strWord ))
        printf("\nNoh removido.");
    else
        printf("\nNaoh encontrou noh para remover.");
}

PRIVATE void Search( SBINTREE *BT )
{
    char strWord[STR_SIZE] ;

    Input("Procurar palavra : " , strWord, STR_SIZE );

    // procura
    if (FindNode( BT, strWord ))
        printf("\nEncontrou noh.");
    else
        printf("\nNaoh encontrou noh.");
}

PRIVATE void Display( SBINTREE *BT )
{
    PrintForest(stdout, BT) ;
}

PRIVATE char *StrUpr (char *str)
{
  char *ptr = str;

  while (*ptr) {
      *ptr = toupper (*ptr);
      ptr++;
  }

  return (str);
}

PRIVATE void LoadFile( SBINTREE *BT )
{
    FILE *fin;                 // arquivo de entrada
    char strWord[STR_SIZE] ;
    char *ptrStr;
    int iChar;
    int i = 0;

    Input("Nome do arquivo : " , strWord, STR_SIZE );


    fin = fopen(strWord, "rt");
    if (fin) 
    {
        // comecah a processar o arquivo
        while (!feof(fin)) 
        {
            // percorre o texto pulando os espacosh e pontuncaoesh
            do {
                iChar = getc(fin);
            } while ( iChar != EOF && (isspace(iChar) || ispunct(iChar)));

            // tendo um caracter valido
            // comecah a montar a palavra
            ptrStr = strWord;
            do {
                *ptrStr++ = iChar;
                iChar = getc(fin);
            } while ( iChar != EOF && !isspace(iChar) && !ispunct(iChar) );

            // fim do arquivo, sai do loop
            if (iChar == EOF)
                break;

            // fecha a palavra com o terminador nulo
            *ptrStr = '\0';

            // todos os caracteres em maiuscula
            ptrStr = StrUpr(strWord);

            // insere na tabela
            AddNode( BT, ptrStr);
            i++;

            if ((i %1000) == 0)
                fprintf(stdout, "Tratou palavras %u\n", i);

        }   // while (!feof(fin)) 

        fclose(fin);

        fprintf(stdout, "Carregou arquivo\n");

    }
    else 
    {
        fprintf(stderr, "Naoh conseguiu encontrar/abrir o arquivo %s\n", strWord);
    }

}

PRIVATE void SaveLog( SBINTREE *BT )
{
    FILE *fLog;

    fLog = fopen("log.txt", "at");
    if (fLog)
    {
        PrintForest(fLog, BT);

        fclose(fLog);
    }
    else
        fprintf(stderr, "ERRO AO CRIAR LOG\n");
}

PRIVATE void Input( char *pText , char *pContent , int size )
{
    printf( pText ) ;
    fgets( pContent , size-1 , stdin ) ;
    pContent[strlen(pContent)-1] = '\0' ;   
}

