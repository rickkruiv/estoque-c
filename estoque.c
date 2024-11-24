#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <windows.h>
#include <conio.h>
#include <string.h>

#define MAX_COMPRAS 5
#define FILE_NAME "estoque.txt"

struct Produtos
{
   char descricao[30];
   char ra[10];
   int qtdInicial;
   int qtdFinal;
   int qtdVendido;
   float valor;
   float total;
};

struct Produtos produto[MAX_COMPRAS];

void clear();
void coordenada(int linha, int coluna);
void box(int lin1, int col1, int lin2, int col2);
void gerarTabela();
void cadastrarProduto();
void listaProdutos(int indice, char descricao[30], char ra[10], float total);
void gerarTXT();
int main();

void clear()
{
#ifdef _WIN32

   system("cls");
#else
   system("clear");
#endif
}

void coordenada(int linha, int coluna)
{
   COORD coord;
   coord.X = coluna;
   coord.Y = linha;
   SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void box(int lin1, int col1, int lin2, int col2)
{
   int i, j, tamLin, tamCol;

   tamLin = lin2 - lin1;
   tamCol = col2 - col1;

   for (i = col1; i <= col2; i++)
   {
      coordenada(i, lin1);
      printf("%c", 186);
      coordenada(i, lin2);
      printf("%c", 186);
   }

   for (i = lin1; i <= lin2; i++)
   {
      coordenada(col1, i);
      printf("%c", 205);
      coordenada(col2, i);
      printf("%c", 205);
   }

   coordenada(col1, lin1);
   printf("%c", 201);
   coordenada(col2, lin1);
   printf("%c", 200);
   coordenada(col1, lin2);
   printf("%c", 187);
   coordenada(col2, lin2);
   printf("%c", 188);
}

void gerarTabela()
{

   for (int j = 0; j < 9; j++) // separações verticais
   {
      coordenada(5 + j, 33);
      printf("%c", 179);

      coordenada(5 + j, 44);
      printf("%c", 179);

      coordenada(5 + j, 52);
      printf("%c", 179);

      coordenada(5 + j, 60);
      printf("%c", 179);

      coordenada(5 + j, 70);
      printf("%c", 179);

      for (int i = 0; i < 80; i++)
      {
         if (j > 4)
         {
            break;
         }
         coordenada(6 + j * 2, 1 + i);
         printf("%c", 196);
      }
   }
}

void listaProdutos(int indice, char descricao[30], char ra[10], float total)
{
   int space = indice + 16;
   coordenada(space, 2);

   int larguraLinha = 50;

   int comprimentoDescricao = strlen(descricao) + strlen(ra);
   int espacosPontos = larguraLinha - (comprimentoDescricao + 10);

   printf("%i. %s (RA: %s)", indice + 1, descricao, ra);

   for (int i = 0; i < espacosPontos; i++)
   {
      printf(".");
   }

   printf("R$%.2f\n", total);
}

void cadastrarProduto()
{
   for (int i = 0; i < MAX_COMPRAS; i++)
   {
      int space = 5 + i * 2;
      coordenada(space, 1);
      printf("%i.", i + 1);

      coordenada(space, 4);
      fflush(stdin);
      fgets(produto[i].descricao, sizeof(produto[i].descricao), stdin);

      produto[i].descricao[strcspn(produto[i].descricao, "\n")] = '\0';

      coordenada(space, 34);
      fflush(stdin);
      fgets(produto[i].ra, 10, stdin);

      produto[i].ra[strcspn(produto[i].ra, "\n")] = '\0';

      coordenada(space, 45);
      scanf("%i", &produto[i].qtdInicial);

      do
      {
         coordenada(space, 53);
         printf("       ");
         coordenada(space, 53);
         scanf("%i", &produto[i].qtdVendido);
      } while (produto[i].qtdVendido > produto[i].qtdInicial || produto[i].qtdVendido <= 0);

      produto[i].qtdFinal = produto[i].qtdInicial - produto[i].qtdVendido;

      coordenada(space, 61);
      printf("%i", produto[i].qtdFinal);

      coordenada(space, 71);
      scanf("%f", &produto[i].valor);

      produto[i].total = produto[i].qtdVendido * produto[i].valor;
      listaProdutos(i, produto[i].descricao, produto[i].ra, produto[i].total);
   }

   gerarTXT();
}

void gerarTXT()
{
   FILE *file = fopen(FILE_NAME, "w");
   fprintf(file, "NOME                          | RA        | ESTOQUE INICIAL | ESTOQUE FINAL\n");

   for (int i = 0; i < MAX_COMPRAS; i++)
   {
      fprintf(file, "%-30s| %-10s| %-15d | %d\n", produto[i].descricao, produto[i].ra, produto[i].qtdInicial, produto[i].qtdFinal);
   }
   fclose(file);
}

int main()
{
   clear();
   gerarTabela();
   box(0, 0, 80, 25);
   box(0, 0, 80, 2);
   box(0, 0, 80, 4);

   coordenada(1, 35);
   printf("GENESTOQUE");

   coordenada(3, 2);
   printf(" DESCRICAO                     %c RA       %c qtINI %c qtVEN %c qtFINAL %c  VALOR   ", 179, 179, 179, 179, 179);

   cadastrarProduto();
}