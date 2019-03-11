struct tpCaixa
{
	char info;
    struct tpCaixa *ant, *prox, *cima, *baixo;
};

struct tpDescritor
{
	tpCaixa *inicio, *fim;
};

void inicializa(tpDescritor &linha, tpDescritor &coluna) // inicialiando os descritores das linhas e das colunas
{
	//descritor linha
	linha.inicio = NULL;
	linha.fim = NULL;

	//descritor coluna
	coluna.inicio = NULL;
	coluna.fim = NULL;
}

tpCaixa *novaCaixa() // criando novas caixinhas retornando instaciadas
{
	tpCaixa *caixa = new tpCaixa;

	caixa->info = '0';
	caixa->cima = NULL;
	caixa->baixo = NULL;
	caixa->ant = NULL;
	caixa->prox = NULL;

	return caixa;
}

void GeraCampo(tpDescritor &l, tpDescritor &c, tpCaixa *&cab) // instaciando minha matriz do jogo(campo)
{
	tpCaixa *caixa;
	tpCaixa *ant = NULL; // guandando sempre a linha de cima para ligar(->cima e ->baixo)

	for(int i = 0; i < TF; i++)
	{
		tpCaixa *aux = c.fim; //guardando sempre o anterior

		for(int j = 0; j < TF; j++)
		{
			if(aux == NULL)
			{
				if(i > 0) //se ja tiver uma linha criada
				{
					caixa = novaCaixa();
					aux = caixa;
					c.fim = caixa;
					caixa->cima = ant;
					ant->baixo = caixa;
					ant = ant->prox;
				}
				else
				{
					caixa = novaCaixa();
					aux = caixa;
					l.inicio = caixa;
					l.fim = caixa;
					c.inicio = caixa;
					c.fim = caixa;
				}
			}
			else
			{
				if(i > 0) // se tiver uma linha criada
				{
					caixa = novaCaixa();
					caixa->cima = ant;
					ant->baixo = caixa;
					caixa->ant = aux;
					aux->prox = caixa;
					aux = caixa;
					ant = ant->prox;
				}
				else
				{
					caixa = novaCaixa();
					caixa->ant = l.fim;
					l.fim->prox = caixa;
					l.fim = caixa;
				}
			}
		} //fim do primeiro for
		ant = c.fim;
		c.fim = NULL;
	}
	c.fim = ant;
	cab = l.inicio; // enviando a cabeça da lista
}

void Exibe(tpCaixa *campo)
{
	tpCaixa *aux1, *aux2;
	aux1 = aux2 = campo;
	while(aux1 != NULL)
	{
		while(aux2 != NULL)
		{
			printf("%c",aux2->info);
			aux2 = aux2->prox;
		}
		printf("\n");
		aux1 = aux1->baixo;
		aux2 = aux1;
	}

}

void ZeraCampo(tpCaixa *&C)
{
	tpCaixa *aux1,*aux2;
	
	aux1=aux2=C;
	while(aux1!=NULL)
	{
		while(aux2!=NULL)
		{
			aux2->info='0';
			aux2=aux2->prox;
		}
		aux1=aux1->baixo;
		aux2=aux1;
	}
		
}

void PreencheAleatorio(tpCaixa *&C)
{
	tpCaixa *aux1,*aux2;
	char l;
	aux1=aux2=C;
	while(aux1!=NULL)
	{
		while(aux2!=NULL)
		{
			if(aux2->info=='0')					
				aux2->info = TransformaLetra(Sorteio(65,91));			
			aux2=aux2->prox;
		}
		aux1=aux1->baixo;
		aux2=aux1;
	}
}

void ColocaPalavra(tpCaixa *&C, char Palavra[])
{
	int x, y, achou=0, lado, i, j, tam=strlen(Palavra);
	tpCaixa *aux;
	
	lado=Sorteio(1,3);
	
	if(lado==1)
	{
		do{
			aux=C;
			x=Sorteio(1,11);
			y=Sorteio(1,11);

			for(i=1;i<x;i++)
				aux=aux->prox;
					
			for(j=1;j<y;j++)
				aux=aux->baixo;
				
			i=0;
			if(aux->info=='0')
			{
				while(achou==0 && aux->prox!=NULL && aux->prox->info=='0')
				{
					aux->info=Palavra[i];
					if(i==tam-1)
						achou=1;
					i++;
					aux=aux->prox;
				}
				
				if(aux->prox==NULL || aux->prox->info!='0')	
				{
					i++;
					while(i>0)
					{
						aux->info='0';
						aux=aux->ant;
						i--;
						achou=0;
					}	
				}	
					
			}
			
		}while(achou == 0);	
	}	
	
	if(lado==2)
	{
		do{
			aux=C;
			x=Sorteio(1,11);
			y=Sorteio(1,11);
			
			
			for(i=1;i<x;i++)
				aux=aux->prox;
					
			for(j=1;j<y;j++)
				aux=aux->baixo;
				
			i=0;
			if(aux->info=='0')
			{				
				while(achou==0 && aux->baixo !=NULL && aux->baixo->info=='0')
				{
					aux->info=Palavra[i];
					if(i==tam-1)
						achou=1;
					i++;
					aux=aux->baixo;
				}
				
				if(aux->baixo==NULL || aux->baixo->info!='0')		
				{
					i++;
					while(i>0)
					{
						aux->info='0';
						aux=aux->cima;
						i--;
						achou=0;
					}	
				}
										
			}
			
		}while(achou == 0);	
	}
}

void Quadro(tpCaixa *campo, int CorT, int CorF)
{
	int i,j,x,y;
	int CI=25;
	int CF=54;
	int LI=5;
	int LF=25;
	tpCaixa *aux1, *aux2;

	textbackground(0);
	BlocoMenu(59,78,5,10,15,0);
	gotoxy(65,6);printf("Comandos");
	gotoxy(60,7);printf("------------------");
	gotoxy(68,9);printf("e");
	textcolor(9);
	gotoxy(63,8);printf("W");
	gotoxy(62,9);printf("ASD");
	gotoxy(72,9);printf("ENTER");
	
	BlocoMenu(32,48,1,3,15,0);
	textcolor(10);
	gotoxy(34,2);printf("CACA PALAVRAS");
	textcolor(15);
	textbackground(0);
	
	gotoxy(CI+1,LI-1);printf("A  B  C  D  E  F  G  H  I  J");
	for(i=0,j=1;i<20;i+=2)
	{
		gotoxy(CI-2,LI+1+i);printf("%d",j++);
	}

	textcolor(CorT);
	textbackground(CorF);

	for(i=CI+1;i<CF;i++)
	for(j=LI+1;j<LF;j++)
	{
		gotoxy(i,j);printf(" ");
	}

	for(i=CI;i<CF;i++)
	{
		gotoxy(i,LI);printf("%c",205);
		gotoxy(i,LF);printf("%c",205);
	}

	for(i=LI;i<LF;i++)
	{
		gotoxy(CI,i);printf("%c",186);
		gotoxy(CF,i);printf("%c",186);
	}

	gotoxy(CI,LI);printf("%c",201); //4 cantos
	gotoxy(CF,LI);printf("%c",187);
	gotoxy(CI,LF);printf("%c",200);
	gotoxy(CF,LF);printf("%c",188);

	textcolor(15);

	aux1 = aux2 = campo;
	for(y=LI+1; aux1!=NULL;y+=2 )
	{
		for(x=CI+1; aux2!=NULL; x+=3)
		{
			gotoxy(x,y);printf("%c",aux2->info);
			aux2 = aux2->prox;
		}
		aux1 = aux1->baixo;
		aux2 = aux1;
	}
}

void BuscaPalavras(tpCaixa *C, char NomeArq[], Selecionar s[],int op, char Usuario[])
{
	tpCaixa *aux;
	
	int tecla,i,TL=0;
	int CI=1;
	int CF=1;
	int LI=1;
	int LF=1;
	char Palavra[11],Tema[11];

	aux=C;
	PegaTema(Tema,op);
	
	
	if(op!=8)
		strcpy(Usuario,Tema);
	
	do{	
		
		BlocoMenu(2,18,5,10,15,0);
		gotoxy(8,6);printf("Tema");
		gotoxy(3,7);printf("---------------");
		textcolor(14);
		
		gotoxy(5,8);printf("%s",Usuario);
	
			
		Quadro(C,1,2);
		Bloco(LI,CI,LF,CF,1,2);
		
		for(i=0;i<TL;i++)
			Bloco(s[i].LI,s[i].CI,s[i].LF,s[i].CF,4,2);
		
		fflush(stdin);
		op=getch();
	
		switch(op)
		{
			case 100: //seta direita
				if(aux->prox!=NULL)
				{
					CI++; CF++; aux=aux->prox;
				}
			 break; 
			
			case 97://seta esquerda
				if(aux->ant!=NULL)
				{
					CI--; CF--; aux=aux->ant;
				}
			 break;	
			
			case 119: //seta cima
				if(aux->cima!=NULL)
				{
					LI--; LF--; aux=aux->cima;
				}
			break;
			
			case 115: //seta baixo
				if(aux->baixo!=NULL)
				{
					LI++; LF++; aux=aux->baixo;
				}
			 break; 
			 
			case 13: // enter
			 
				Bloco(LI,CI,LF,CF,0,2);
				fflush(stdin);
				tecla=getch();
				
				 switch(tecla)  
				 {
				 	case 100:   //seta direita
				 					 
					 	s[TL].CI=CI;
					 	s[TL].LI=LI;
					 	s[TL].LF=LF;
					 	s[TL].CF=CF;
					 	
					 	i=0;
					 	do{
					 		if(tecla==100 && aux->prox!=NULL)
					 		{			 			
					 			Palavra[i++]=aux->info;
					 			CI++;CF++; aux=aux->prox;
					 			s[TL].CF++;
					 		}
					 		else
					 		if(tecla==97 && i>0)
					 		{
					 			i--;
					 			aux=aux->ant;
					 			CI--;CF--;
					 			s[TL].CF--;
					 		}
					 				
					 		Quadro(C,1,2);
							Bloco(s[TL].LI,s[TL].CI,s[TL].LF,s[TL].CF,0,2);
					 		
					 		fflush(stdin);
					 		tecla=getch();
					 	}while(tecla!=13);
					 	Palavra[i++]=aux->info;
					 	Palavra[i]='\0';
					 	
				
					 	if(TestaPalavra(Palavra,NomeArq,s)==1)
						 	TL++;	 				 	
			 		break;
			 			 	
			 		case 115:  //seta baixo
			 	
					 	s[TL].CI=CI;
					 	s[TL].LI=LI;
					 	s[TL].LF=LF;
					 	s[TL].CF=CF;
					 	i=0;
					 	do{
					 		if(tecla==115 && aux->baixo!=NULL)
					 		{			 			
					 			Palavra[i++]=aux->info;
					 			LI++;LF++; aux=aux->baixo;
					 			s[TL].LF++;
					 		}
					 		else
					 		if(tecla==119 && i>0)
					 		{
					 			i--;
					 			aux=aux->cima;
					 			LI--;LF--;
					 			s[TL].LF--;
					 		}
					 				
					 		Quadro(C,1,2);
							Bloco(s[TL].LI,s[TL].CI,s[TL].LF,s[TL].CF,0,2);
					 		
					 		fflush(stdin);
					 		tecla=getch();
					 	}while(tecla!=13);
					 	Palavra[i++]=aux->info;
					 	Palavra[i]='\0';
					 	
					 
					 	TestaPalavra(Palavra,NomeArq,s);
						 	
					break;	
			 	}	
				 		 
			 break;
			 
			 case 27:
			 	op=0;
			 break;	
		}
		Palavras(s);
		TL=0;
		for(i=0;i<5;i++)
			if(s[i].achou==1)
				TL++;
		if(TL==5)
		{
			for(i=0;i<TL;i++)
				Bloco(s[i].LI,s[i].CI,s[i].LF,s[i].CF,4,2);
			getch();
			op=0;
		}		
						
	}while(op!=0);
}
