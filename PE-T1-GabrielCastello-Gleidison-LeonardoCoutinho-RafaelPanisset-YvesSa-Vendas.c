#include <stdio.h>

int genSellCode(int startNumber, int endNumber)
{
  return rand() % endNumber + startNumber;
}

int verifyFile(int *file)
{
  if (file == NULL)
  {
    printf("\nFalha na abertura do arquivo\n\n");
    return 0;
  }
  return 1;
};

int main()
{
  srand(time(NULL));

  /* Abre o arquivo Vendas.txt no modo leitura "r" */
  FILE *vendasFile = fopen("Vendas.txt", "r");
  if (!verifyFile(vendasFile))
  {
    /* Cria o arquivo Vendas.txt no modo de escrita */
    printf("\nCriando arquivo Vendas.txt...");
    vendasFile = fopen("Vendas.txt", "w");
    if (verifyFile(vendasFile))
      printf("\nArquivo Vendas.txt criado com sucesso.");
  }

  printf("\n\n");
  return 0;
}