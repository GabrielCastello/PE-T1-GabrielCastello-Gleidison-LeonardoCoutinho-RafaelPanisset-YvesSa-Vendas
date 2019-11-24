#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

void getSellsIDs(int *sellsIDs, int sellsQty)
{
  for (int i = 0; i < sellsQty; i++)
  {
    printf("\nID %i: %i;", i, sellsIDs[i]);
  }
}

void setSellsIDs(FILE *file, int *sellsIDs)
{
  int counter = 0, i = 0;
  while (!feof(file))
  {
    int sellID = 0;
    fscanf(file, "%i %*s %*f %*i %*i", &sellID);
    if (sellID != 0)
    {
      counter++;
      // printf("\nSellID: %i", sellID);
      sellsIDs[i] = sellID;
      i++;
    }
  }
}

int setSellsQty(FILE *file)
{
  int counter = 0;
  while (!feof(file))
  {
    int sellID = 0;
    fscanf(file, "%i %*s %*f %*i %*i", &sellID);
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

int genSellCode(int startNumber, int endNumber)
{
  return rand() % endNumber + startNumber;
}

int verifyFile(FILE *file)
{
  if (file == NULL)
  {
    printf("\nFalha na abertura do arquivo\n\n");
    return 0;
  }
  return 1;
};

int genUniqSellCode(int sellsQty, int *sellsIDs, int startNumber, int endNumber)
{
  int randomSellCode, validator = 1;
  do
  {
    randomSellCode = genSellCode(startNumber, endNumber);
    // printf("randomSellCode: %i", randomSellCode);
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

int insertSellToFile(FILE *file, int sellsQty, int *sellsIDs, int startNumber, int endNumber)
{
  char name[100];
  float value = 0;
  int month = 0, day = 0;
  printf("\nInforme o nome do vendedor: ");
  scanf(" %s", name);
  printf("\nInforme o valor da venda: ");
  scanf("%f", &value);
  printf("\nInforme o dia da venda: ");
  scanf("%i", &day);
  printf("\nInforme o mês da venda: ");
  scanf("%i", &month);
  fprintf(file, "%i %s %f %i %i\n", genUniqSellCode(sellsQty, sellsIDs, startNumber, endNumber), name, value, day, month);
  fclose(file);
}

void removeSellFromFile(char *filename)
{
  FILE *fileptr1, *fileptr2;
  char ch;
  int sellCode, delete_line, temp = 1;

  // printf("Enter file name: ");
  // scanf("%s", filename);
  //open file in read mode
  fileptr1 = fopen(filename, "r");
  ch = getc(fileptr1);
  while (ch != EOF)
  {
    printf("%c", ch);
    ch = getc(fileptr1);
  }
  //rewind
  rewind(fileptr1);
  printf("\nInforme o código da venda a ser removida:");
  scanf("%d", &sellCode);
  delete_line = 1;
  int end = 0;
  while (/* !feof(fileptr1) && */ end == 0)
  {
    char name[100];
    float value = 0;
    int fileSellCode = 0, month = 0, day = 0;
    fscanf(fileptr1, "%i %*s %*f %*i %*i", &fileSellCode);
    if (fileSellCode == sellCode)
    {
      end = 1;
    }
    else
    {
      delete_line++;
    }
  }
  rewind(fileptr1);
  printf("\nLine to delete: %i", delete_line);
  //open new file in write mode
  fileptr2 = fopen("temp.txt", "w");
  ch = 'A';
  while (ch != EOF)
  {
    ch = getc(fileptr1);
    //except the line to be deleted
    if (temp != delete_line && !feof(fileptr1))
    {
      //copy all lines in file replica.c
      putc(ch, fileptr2);
    }
    if (ch == '\n')
    {
      temp++;
    }
  }
  fclose(fileptr1);
  fclose(fileptr2);
  remove(filename);
  //rename the file replica.c to original name
  rename("temp.txt", filename);
  printf("\n The contents of file after being modified are as follows:\n");
  fileptr1 = fopen(filename, "r");
  ch = getc(fileptr1);
  while (ch != EOF)
  {
    printf("%c", ch);
    ch = getc(fileptr1);
  }
  fclose(fileptr1);
}

void listSellsBySeller(char *filename)
{
  FILE *fileptr1 = fopen(filename, "r");
  char ch = getc(fileptr1), inputName[100];
  int strValidation = 1, counter = 0;

  while (ch != EOF)
  {
    printf("%c", ch);
    ch = getc(fileptr1);
  }
  rewind(fileptr1);
  printf("\n\nInforme o nome do vendedor: ");
  scanf(" %s", inputName);
  printf("\n");
  while (!feof(fileptr1))
  {
    char name[100] = "";
    float value = 0;
    int fileSellCode = 0, month = 0, day = 0;
    fscanf(fileptr1, "%i %s %f %i %i", &fileSellCode, name, &value, &day, &month);
    strValidation = strcmp(name, inputName);
    if (strValidation == 0)
    {
      counter++;
      printf("%i %s %2.2f %i %i\n", fileSellCode, name, value, day, month);
    }
  }
  fclose(fileptr1);
  if (counter == 0)
  {
    printf("Nenhuma venda registrada para o vendedor %s!", inputName);
  }
}

void listSellsBySellerWithFilter(char *filename, int showCounter)
{
  FILE *fileptr1 = fopen(filename, "r");
  char ch = getc(fileptr1), inputName[100];
  int validation = 1, filter = 0, counter = 0;
  float sum = 0;
  while (ch != EOF)
  {
    printf("%c", ch);
    ch = getc(fileptr1);
  }
  rewind(fileptr1);
  printf("\n\nInforme o nome do vendedor: ");
  scanf(" %s", inputName);

  do
  {
    printf("\n1 - Dia | 2 - Mês");
    printf("\nInforme o filtro desejado(1 ou 2): ");
    scanf("%i", &filter);
    printf("\n");
    if (!(filter == 1 || filter == 2))
    {
      printf("\nOpção inválida!");
    }

  } while (!(filter == 1 || filter == 2));

  switch (filter)
  {
  case 1:
    printf("\nVocê selecionou a opção dia.");
    int inputDay;
    do
    {
      printf("\nInforme o dia: ");
      scanf("%i", &inputDay);
      printf("\n");
      if (!(inputDay > 0 && inputDay <= 31))
      {
        printf("\nDia inválido!");
      }
    } while (!(inputDay > 0 && inputDay <= 31));

    while (!feof(fileptr1))
    {
      char name[100];
      float value = 0;
      int fileSellCode = 0, month = 0, day = 0;
      fscanf(fileptr1, "%i %s %f %i %i", &fileSellCode, name, &value, &day, &month);
      validation = strcmp(name, inputName);
      if (validation == 0)
      {
        if (day == inputDay)
        {
          counter++;
          sum = sum + value;
          if (!showCounter)
          {
            printf("%i %s %2.2f %i %i\n", fileSellCode, name, value, day, month);
          }
        }
      }
    }
    if (counter == 0)
    {
      printf("Nenhuma venda registrada para o vendedor %s no dia(%i)!", inputName, inputDay);
    }
    if (showCounter && counter != 0)
    {
      printf("\nValor total das %i vendas do vendedor %s no dia(%i): R$: %.2f", counter, inputName, inputDay, sum);
    }
    break;
  case 2:
    printf("\nVocê selecionou a opção mês.");
    int inputMonth;
    do
    {
      printf("\nInforme o mês: ");
      scanf("%i", &inputMonth);
      printf("\n");
      if (!(inputMonth > 0 && inputMonth <= 12))
      {
        printf("\nMês inválido!");
      }
    } while (!(inputMonth > 0 && inputMonth <= 12));

    while (!feof(fileptr1))
    {
      char name[100];
      float value = 0;
      int fileSellCode = 0, month = 0, day = 0;
      fscanf(fileptr1, "%i %s %f %i %i", &fileSellCode, name, &value, &day, &month);
      validation = strcmp(name, inputName);
      if (validation == 0)
      {
        if (month == inputMonth)
        {
          counter++;
          sum = sum + value;
          if (!showCounter)
          {
            printf("%i %s %2.2f %i %i\n", fileSellCode, name, value, day, month);
          }
        }
      }
    }
    if (counter == 0)
    {
      printf("Nenhuma venda registrada para o vendedor %s no mês(%i)!", inputName, inputMonth);
    }
    if (showCounter && counter != 0)
    {
      printf("\nValor total das %i vendas do vendedor %s no mês(%i): R$: %.2f", counter, inputName, inputMonth, sum);
    }

    break;
  default:

    break;
  }
  fclose(fileptr1);
}

int main()
{
  srand(time(NULL));
  /* Abre o arquivo Vendas.txt no modo leitura "r" */
  char filename[] = "Vendas.txt";
  // FILE *sellsFile = fopen("Vendas.txt", "r");
  FILE *sellsFile = fopen(filename, "r");

  if (!verifyFile(sellsFile))
  {
    /* Cria o arquivo Vendas.txt no modo de escrita */
    printf("\nArquivo Vendas.txt não foi localizado...");
    sellsFile = fopen(filename, "w");
    fclose(sellsFile);
    sellsFile = fopen(filename, "r");
    if (verifyFile(sellsFile))
    {
      printf("\nArquivo Vendas.txt criado com sucesso.");
      // insertSellToFile(sellsFile, name, value, day, month);
    }
  }
  int sellsQty = setSellsQty(sellsFile);
  int startNumber = 1, endNumber = 1000;
  int sellsIDs[sellsQty];

  // printf("\nTotal de vendas: %i", sellsQty);
  rewind(sellsFile);
  setSellsIDs(sellsFile, sellsIDs);
  fclose(sellsFile);
  // getSellsIDs(sellsIDs, sellsQty);

  int selectedOption;
  printf("\n\nBem-vindo ao software de vendas !");
  do
  {
    selectedOption = 0;

    printf("\n\nSelecione um dos items do menu: ");
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
      sellsFile = fopen(filename, "r");
      sellsQty = setSellsQty(sellsFile);
      fclose(sellsFile);
      if (sellsQty < endNumber)
      {
        sellsFile = fopen(filename, "a");
        insertSellToFile(sellsFile, sellsQty, sellsIDs, startNumber, endNumber);
        sellsFile = fopen(filename, "r");
        sellsQty = setSellsQty(sellsFile);
        fclose(sellsFile);
      }
      else
      {
        printf("\nLimite de %i vendas atingido, para adicionar uma venda remova uma venda anterior.", endNumber);
      }

      break;
    case 2:
      if (sellsQty > 0)
      {
        removeSellFromFile(filename);
        sellsFile = fopen(filename, "r");
        sellsQty = setSellsQty(sellsFile);
        fclose(sellsFile);
      }
      else
      {
        printf("\nNenhuma venda localizada, operação não permitida");
      }
      break;
    case 3:
      if (sellsQty > 0)
      {
        listSellsBySeller(filename);
      }
      else
      {
        printf("\nNenhuma venda localizada, operação não permitida");
      }
      break;
    case 4:
      if (sellsQty > 0)
      {
        listSellsBySellerWithFilter(filename, 0);
      }
      else
      {
        printf("\nNenhuma venda localizada, operação não permitida");
      }
      break;
    case 5:
      if (sellsQty > 0)
      {
        listSellsBySellerWithFilter(filename, 1);
      }
      else
      {
        printf("\nNenhuma venda localizada, operação não permitida");
      }
      break;
    case 6:
      printf("Ate logo, volte sempre!! \n");
      break;
    }
  } while (selectedOption != 6);
  return 0;
}