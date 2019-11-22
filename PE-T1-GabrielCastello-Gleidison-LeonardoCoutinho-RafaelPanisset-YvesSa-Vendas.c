#include <stdio.h>

void getSellsIDs(int *sellsIDs, int sellsQty)
{
  for (int i = 0; i < sellsQty; i++)
  {
    printf("\nID %i: %i;", i, sellsIDs[i]);
  }
}

void setSellsIDs(int *file, int *sellsIDs)
{
  int counter = 0, i = 0;
  while (!feof(file))
  {
    int sellID = NULL;
    fscanf(file, "%i %*s %*f %*f %*f", &sellID);
    if (sellID != NULL)
    {
      counter++;
      // printf("\nSellID: %i", sellID);
      sellsIDs[i] = sellID;
      i++;
    }
  }
}

int setSellsQty(int *file)
{
  int counter = 0;
  while (!feof(file))
  {
    int sellID = 0;
    fscanf(file, "%i %*s %*f %*f %*f", &sellID);
    // fscanf(file, "%i", &sellID);
    if (sellID != 0)
    {
      counter++;
      // printf("\nSellID: %i", sellID);
      // printf("\ncounter: %i", counter);
    }
  }
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

int genUniqSellCode(int sellsQty, int *sellsIDs)
{
  int randomSellCode, validator = 1;
  do
  {
    randomSellCode = genSellCode();
    printf("randomSellCode: %i", randomSellCode);
    for (int i = 0; i < sellsQty; i++)
    {
      if (randomSellCode == sellsIDs[i])
      {
        validator = 0;
      }
    }
  } while (validator == 0);
  return randomSellCode;
}

int insertSellToFile(int *file, int sellsQty, int *sellsIDs)
{
  char name[100];
  float value = 0;
  int month, day;
  printf("\nInforme o nome do vendedor: ");
  scanf(" %s", name);
  printf("\nInforme o valor da venda: ");
  scanf("%f", &value);
  printf("\nInforme o dia da venda: ");
  scanf("%i", &day);
  printf("\nInforme o mês da venda: ");
  scanf("%i", &month);
  fprintf(file, "\n%i %s %f %i %i", genUniqSellCode(sellsQty, sellsIDs), name, value, day, month);
  fclose(file);
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
      // insertSellToFile(sellsFile, name, value, day, month);
    }
  }
  else
  {
    int sellsQty = setSellsQty(sellsFile);
    int sellsIDs[sellsQty];

    // printf("\nTotal de vendas: %i", sellsQty);
    rewind(sellsFile);
    setSellsIDs(sellsFile, sellsIDs);
    fclose(sellsFile);
    // getSellsIDs(sellsIDs, sellsQty);

    int selectedOption;
    printf("\nBem-vindo ao software de vendas !");
    do
    {
      selectedOption = 0;

      printf("\nSelecione um dos items do menu: ");
      printf("\n######################################################################################################");
      printf("\n# - (1) Inserir uma venda (o código da venda não pode ser repetido)                                  #");
      printf("\n# - (2) Remover uma venda pelo código da venda                                                       #");
      printf("\n# - (3) Listar na tela todas as vendas de um vendedor pesquisando pelo nome do vendedor              #");
      printf("\n# - (4) Listar na tela todas as vendas de um vendedor em um determinado dia ou mês                   #");
      printf("\n# - (5) Imprimir na tela o valor total de vendas de um vendedor em um determinado dia ou mês         #");
      printf("\n# - (6) Sair da execução do algoritmo                                                                #");
      printf("\n######################################################################################################");
      printf("\n");
      scanf("%i", &selectedOption);
      switch (selectedOption)
      {
      case 1:
        sellsFile = fopen("VendasBackup.txt", "a");
        insertSellToFile(sellsFile, sellsQty, sellsIDs);
        break;
      case 2:
        // removeSales(vendasFile, &counter, codeSales);
        break;
      case 3:
        // listSallersNames(vendasFile);
        break;
      case 4:
        // listSallersDay(vendasFile);
        break;
      case 5:
        // printSallersValue(vendasFile);
        break;
      case 6:
        printf("Ate logo, volte sempre!! \n");
        break;
      }
    } while (selectedOption != 6);
    return 0;
  }
}