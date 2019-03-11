/*Matheus Omote RA: 101426593  && Vinicius Vasconcelos RA: 101426666*/
#include <stdio.h>
#include <ctype.h>
#include <conio2.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>

#define TF 10

#include "auxiliares.h"
#include "Lista.h"

int main()
{
	srand(time(NULL));
	tpCaixa *Campo;
	tpDescritor L,C;
	Selecionar s[5];
	
	int n1,n2,j,i=0,num1,num2,op=1,vet[5], flag=0;
	char l1,l2,Palavra[8];
	char NomeArq[100], Usuario[11];
	FILE *p;
	
	inicializa(L,C);
	GeraCampo(L,C,Campo);
	
	do{
		op=1;
		Menu(NomeArq,op,Usuario);
			
		if(op==9)
		{
			gotoxy(35, 3);printf("Creditos:");
			gotoxy(20, 7);printf("Matheus Omote           RA:101426593");
			gotoxy(20, 9);printf("Vinicius Vasconcelos    RA: 101426666");
			getch();
			
		}		
		else
		{
			sorteiaArq(NomeArq, vet);
			p = NULL;
			p = fopen(NomeArq, "r+");
			
			if(p == NULL)
			{	
				printf("\nERRO de abertura !");
				getch();
			}
			else
			{		
				int k=0;
				for(int v=0; v<5; v++)
				{
					j=0;
					fseek(p, 0, 0);
					flag=0;
					fgets(Palavra, 8, p);
					while(flag!=1)
					{
						j++;
						if(j == vet[v])
						{
							for(i = 0; i < strlen(Palavra); i++)
								if(Palavra[i] == '\n')
									Palavra[i] = '\0';
							strcpy(s[k].Palavra,Palavra);
							s[k].achou = 0;
							ColocaPalavra(Campo, Palavra);
							Quadro(Campo,1,2);
							k++;
							flag = 1;	
						}
						fgets(Palavra, 8, p);		
					}
				}
				fclose(p);
				
				PreencheAleatorio(Campo);
				Palavras(s);	
				BuscaPalavras(Campo,NomeArq,s,op,Usuario);
				
				int cont = 0;
				for(int i = 0; i < 5; i++)
					if(s[i].achou == 1)
						cont++;
				if(cont >= 5)
					Fim();
				else
					gameover();
					
				ZeraCampo(Campo);
			}				
		}	
	}while(op!=9);
}
