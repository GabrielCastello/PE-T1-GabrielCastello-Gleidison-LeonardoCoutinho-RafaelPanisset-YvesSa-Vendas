# PE-T1-GabrielCastello-Gleidison-LeonardoCoutinho-RafaelPanisset-YvesSa-Vendas
PE-T1-GabrielCastello-Gleidison-LeonardoCoutinho-RafaelPanisset-YvesSa-Vendas

## Utilização do GitHub

### Para baixar o projeto: 

```git
git clone https://github.com/GabrielCastello/PE-T1-GabrielCastello-Gleidison-LeonardoCoutinho-RafaelPanisset-YvesSa-Vendas.git

cd PE-T1-GabrielCastello-Gleidison-LeonardoCoutinho-RafaelPanisset-YvesSa-Vendas
```

### Para atualizar o projeto

Estar na pasta do projeto



```git
git pull
```

### Para subir as modificações realizadas

```git
git add .

git commit -m "`breve descrição das modificações realizadas`"

git push, caso seja primeiro push git push --set-upstream origin master
```

## Objetivo do Trabalho
### Vendas
Faça um algoritmo para gerenciar registros de vendas dos funcionários de uma loja. Para cada venda armazene o código da venda (gerado aleatoriamente de 1 até 1000), o nome do vendedor (sem espaços), o valor da venda, além do dia e do mês da venda. O algoritmo deve permitir:
- [x] (1) Inserir uma venda (o código da venda não pode ser repetido);
- [x] (2) Remover uma venda pelo código da venda;
- [x] (3) Listar na tela todas as vendas de um vendedor pesquisando pelo nome do vendedor;
- [x] (4) Listar na tela todas as vendas de um vendedor em um determinado dia ou mês;
- [x] (5) Imprimir na tela o valor total de vendas de um vendedor em um determinado dia ou mês;
- [x] (6) Sair da execução do algoritmo.

Os registros de vendas têm que ser armazenados em um arquivo texto chamado “Vendas.txt”, sobre o qual as operações de (1) até (5) devem ser realizadas. Obviamente as opções de (2) até (5) só podem ocorrer se houver alguma venda inserida no arquivo. Utilize um procedimento para cada operação de (1) até (5). Utilize um menu para apresentar as opções.


Exemplo de um arquivo texto: Vendas.txt
   |            |        |    |    
-- | ---------- | ------ | -- | --
12 | BrunoSouza | 785.54 | 10 | 05
147 | CarlosSilva | 415.89 | 04 | 06
48 | IgorPereira | 1485.12 | 25 | 07
245 | LarissaCastro | 658.79 | 18 | 09
675 | MarcosMedeiros | 59.60 | 20 | 04
