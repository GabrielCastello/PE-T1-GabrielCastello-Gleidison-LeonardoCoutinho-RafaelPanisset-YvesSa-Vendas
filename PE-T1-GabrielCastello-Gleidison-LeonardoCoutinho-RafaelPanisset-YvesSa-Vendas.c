#include <stdio.h>

int getSellsQty(int *file)
{
  int counter = 0;
  while (!feof(file))
  {
    int sellID;
    fscanf(file, "%i %*s %*f %*i %*i", &sellID);
    printf("\nSellID: %i", sellID);
    counter++;
  }
  fclose(file);
  return counter;
}

// void getSellIDs(int *file)
// {
//   while (!feof(file))
//   {
//     int number;
//     for (int i = 0; i < rows; i++)
//     {
//       for (int j = 0; j < columns; j++)
//         fscanf(file, "%i", &srcMatrix[i][j]);
//       printf("\n");
//     }
//   }
//   fclose(file);
// }
int genSellCode()
{
  int startNumber = 1, endNumber = 1000;
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

int insertSellToFile(int *file, char *name[100], float sellValue, int day, int month)
{
  fprintf(file, "%i %s %f %i %i\n", genSellCode(), name, sellValue, day, month);
}

int main()
{
  srand(time(NULL));

  /* Abre o arquivo Vendas.txt no modo leitura "r" */
  // FILE *sellsFile = fopen("Vendas.txt", "r");
  FILE *sellsFile = fopen("VendasBackup.txt", "r");
  if (!verifyFile(sellsFile))
  {
    /* Cria o arquivo Vendas.txt no modo de escrita */
    printf("\nCriando arquivo Vendas.txt...");
    sellsFile = fopen("Vendas.txt", "w");
    if (verifyFile(sellsFile))
    {
      printf("\nArquivo Vendas.txt criado com sucesso.");
      char name[100];
      float value = 0;
      int month, day;
      printf("\nInforme o nome do vendedor: ");
      scanf(" %s", name);
      printf("\nInforme o valor da venda: ");
      scanf("%f", &value);
      printf("\nInforme o dia da venda: ");
      scanf("%i", &day);
      printf /* code */ ("\nInforme o mês da venda: ");
      scanf("%i", &month);
      insertSellToFile(sellsFile, name, value, day, month);
    }
  }
  else
  {
    printf("\nTotal de vendas: %i", getSellsQty(sellsFile));
  }

  printf("\n\n");
  return 0;
}