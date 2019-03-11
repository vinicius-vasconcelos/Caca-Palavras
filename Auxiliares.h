struct Selecionar
{
	char Palavra[6];
	int CI;
	int CF;
	int LI;
	int LF;	
	int achou;
};

int Sorteio(int min,int max)
{
	return rand()%(max-min)+min;
}

int testpalavra(char aux[])
{
	if(aux[0] == '\0' )
		return 0;
	for(int i = 0; i < strlen(aux); i++)
		if(aux[i] == ' ')
			return 0;
		
	return 1;
}

void PegaTema(char Tema[], int op)
{
	if(op==1)
		strcpy(Tema," FUTEBOL ");	
	else
	if(op==2)
		strcpy(Tema," CARROS  ");	
	else
	if(op==3)
		strcpy(Tema,"  TIMES  ");	
	else
	if(op==4)
		strcpy(Tema," FRUTAS ");	
	else
	if(op==5)
		strcpy(Tema,"PROFESSOR");	
	else
	if(op==6)
		strcpy(Tema,"ESPORTES ");	
	else
	if(op==7)
		strcpy(Tema,"MULHERES ");	
	else
	if(op==8)
		strcpy(Tema,"USUARIO ");	
		
	Tema[11]='\0';
}

void BlocoMenu(int CI,int CF, int LI, int LF, int CorT, int CorF)
{
	int i,j;

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
	gotoxy(CI,LI);printf("%c",201);
	gotoxy(CF,LI);printf("%c",187);
	gotoxy(CI,LF);printf("%c",200);
	gotoxy(CF,LF);printf("%c",188);
}

void verArq(char NomeArq[],int op)
{
	char palavra[100],Tema[11];
	textcolor(15);textbackground(0);
	system("cls");
	int i=0,j=0;
	
	PegaTema(Tema,op);
	
	BlocoMenu(25,55,2,24,1,2);		
	BlocoMenu(26,54,3,7,4,2);
	gotoxy(33,5);printf("Tema:%s",Tema);
	
	FILE *p = fopen(NomeArq, "r");
	
	textcolor(0);
	fgets(palavra, 10, p);
	while(!feof(p))
	{	
		if(j==32)
		{
			gotoxy(26+j,9+i);printf("++++");
		}
		else
		{
			gotoxy(26+j,9+i);printf("%s", palavra);
		}
		
		fgets(palavra, 10, p);
		if(i==14)
		{
			j+=8;
			i=0;
		}
		else
			i+=2;					
	}
	fclose(p);
	
	getch();
}

int checaArq(char aux[], FILE *p)
{
	char palaArq[8];

	rewind(p);
	fgets(palaArq, 8, p);
	while(!feof(p))
	{
		for(int i=0; i<strlen(palaArq); i++)
			if(palaArq[i] == '\n')
				palaArq[i] = '\0';
				
		if(stricmp(palaArq, aux) == 0)
			return 0;
		fgets(palaArq, 8, p);
	}
	return 1;
}
void strToupper(char aux[], char palavra[])
{
	int i;
	
	for(i=0; i<strlen(aux); i++)
		 palavra[i] = toupper(aux[i]);
	
	palavra[i] = '\0';
}

void CriaUsuario(char assunto[], int &sair)
{
	char aux[100], palavra[11];
	int TL=0, flag=0;
	
	do
	{
		textcolor(1);textbackground(2);
		gotoxy(57,15);printf("                  ");
		gotoxy(57,15);printf("Assunto:");
		fflush(stdin);
		gets(assunto);
		
		if(strlen(assunto) > 10)
		{		
			gotoxy(57,16);printf("Nome muito grande");
			getch();gotoxy(57,17);printf("                 ");		
		}
		else
			flag = 1;
		
	}while(flag == 0);
	
	flag = 0;
	FILE *arq = fopen("usu.txt", "w+");
	do
	{
		gotoxy(57,22);printf("Escreva ""sair"" para");
		gotoxy(57,23);printf("comecar !!!");
		gotoxy(57,18);printf("                 ");
		gotoxy(57,18);printf("Palavra: ");
		fflush(stdin);
		gets(aux);
		
		if(checaArq(aux, arq))
		{
			if(!testpalavra(aux)|| strlen(aux) > 6)
			{				
				gotoxy(57,20);printf("Palavra invalida !");
				getch();gotoxy(57,20);printf("                  ");
			}
			else
			{
				if(strcmp(aux, "sair") != 0)
				{
					strToupper(aux, palavra);
					fputs(palavra, arq);
					fputc('\n', arq);
					TL++;
				}
				
				if(strcmp(aux, "sair") == 0 && TL < 5)
				{
					gotoxy(57,20);printf("Falta Palavras");
					getch();gotoxy(57,20);printf("                ");
				}			
			}
		}
		else
		{
			gotoxy(57,22);printf("Palavra Repitida !");
			getch();gotoxy(57,22);printf("                  ");
		}
	
		
	}while(strcmp(aux, "sair") != 0 || TL < 5);
	
	fclose(arq);

}

int ValLetra(char L)
{
	if(toupper(L)=='A')
		return 1;
	if(toupper(L)=='B')
		return 2;
	if(toupper(L)=='C')
		return 3;
	if(toupper(L)=='D')
		return 4;
	if(toupper(L)=='E')
		return 5;
	if(toupper(L)=='F')
		return 6;
	if(toupper(L)=='G')
		return 7;
	if(toupper(L)=='H')
		return 8;
	if(toupper(L)=='I')
		return 9;
	if(toupper(L)=='J')
		return 10;
	return 0;
}

void Bloco(int n1, int num1, int n2, int num2, int CorT, int CorF)
{
	int i,j;
	int CI=25;
	int CF=27;
	int LI=5;
	int LF=7;

	for(i=1;i<n1;i++)
		LI+=2;
	
	for(i=1;i<num1;i++)
		CI+=3;
	
	for(i=1;i<n2;i++)
		LF+=2;	
		
	for(i=1;i<num2;i++)
		CF+=3;	
		
	textcolor(CorT);
	textbackground(CorF);
//	printf("LI=%d LF=%d CI=%d CF=%d",LI,LF,CI,CF);
	
	for(i=CI;i<CF;i++)
	{
		gotoxy(i,LI);printf("%c",205);
		gotoxy(i,LF);printf("%c",205);
	}

	for(i=LI;i<LF;i++)
	{
		gotoxy(CF,i);printf("%c",186);
		gotoxy(CI,i);printf("%c",186);
	}
	gotoxy(CI,LI);printf("%c",201);
	gotoxy(CF,LI);printf("%c",187);
	gotoxy(CI,LF);printf("%c",200);
	gotoxy(CF,LF);printf("%c",188);
}

void Palavras(Selecionar s[])
{	
	BlocoMenu(2,18,11,25,15,0);
	gotoxy(6,12);printf("Palavras");
	gotoxy(3,13);printf("---------------");
	textcolor(4);
	for(int i=0, j=0;i<10;i+=2)
	{
		gotoxy(7,15+i);printf("        ");
		if(s[j].achou == 0)
		{	
			gotoxy(7,15+i);printf("%s",s[j].Palavra);	
		}
		j++;
	}
	
	BlocoMenu(59,78,11,25,15,0);
	gotoxy(61,12);printf("Palavras Achadas");
	gotoxy(60,13);printf("------------------");
	textcolor(2);
	for(int i=0,j=0;i<10;i+=2)
	{
		if(s[j].achou==1)
		{
			gotoxy(66,15+i);printf("%s",s[j].Palavra);
		}	
		j++;
	}

}


void PegaValores(int &n1, char l1, int &n2, char l2,int &num1,int &num2)
{	
	do{
		gotoxy(58,2);printf("Digite o Numero 1:");
		scanf("%d",&n1);
		
		if(n1<=0 || n1>=10)
			printf("\nNumero invalido !!");
		
	}while(n1<=0 || n1>=10 );
	
	do{
		gotoxy(58,3);printf("Digite a Letra  1: ");
		fflush(stdin);
		scanf("%c",&l1);
		
		num1=ValLetra(l1);
		
		if(num1==0)
			printf("\nLetra invalida !!");
		
	}while(num1==0);
	
	do{
		gotoxy(58,4);printf("Digite o Numero 2: ");
		scanf("%d",&n2);
		
		if(n2<1 || n2>=11 || n1>n2)
			printf("\nNumero invalido !!");
		
	}while(n2<1 || n2>=11 || n1>n2);
	
	do{
		gotoxy(58,5);printf("Digite a Letra  2: ");
		fflush(stdin);
		scanf("%c",&l2);
	
		num2=ValLetra(l2);
		
		if(num2==0 || num1>num2)
			printf("\nLetra invalida !!");
		
	}while(num2==0 || num1>num2);				
}

char TransformaLetra(int n)
{
	char l;

	if(n==65)
		l='A';
	else
	if(n==66)
		l='B';
	else
	if(n==67)
		l='C';
	else
	if(n==68)
		l='D';
	else
	if(n==69)
		l='E';
	else
	if(n==70)
		l='F';
	else
	if(n==71)
		l='G';
	else
	if(n==72)
		l='H';
	else
	if(n==73)
		l='I';
	else
	if(n==74)
		l='J';
	else
	if(n==75)
		l='K';
	else
	if(n==76)
		l='L';
	else
	if(n==77)
		l='M';
	else
	if(n==78)
		l='N';
	else
	if(n==79)
		l='O';
	else
	if(n==80)
		l='P';
	else
	if(n==81)
		l='Q';
	else
	if(n==82)
		l='R';
	else
	if(n==83)
		l='S';
	else
	if(n==84)
		l='T';
	else
	if(n==85)
		l='U';
	else
	if(n==86)
		l='V';
	else
	if(n==87)
		l='W';
	else
	if(n==88)
		l='X';
	else
	if(n==89)
		l='Y';
	else
	if(n==90)
		l='Z';

	return l;
}


int TestaPalavra(char Palavra[], char NomeArq[],Selecionar s[])
{
	FILE *p = fopen(NomeArq,"r+");
	char aux[7];
	rewind(p);
	fgets(aux,7,p);
	while(!feof(p))
	{
		for(int i = 0; i < strlen(aux); i++)
			if(aux[i] == '\n')
				aux[i] = '\0';
				
		if(stricmp(Palavra,aux) == 0)
		{	
			for(int u=0; u<5; u++)
			{
				if(strcmp(s[u].Palavra, aux) == 0 && s[u].achou == 0)
				{
					s[u].achou=1;
					fclose(p);
					return 1;
				}
			}	
		}
		fgets(aux,7,p);				
	}	
	fclose(p);
	
	return 0;
}

void LateralMenuUsuario(int op, int &sair)
{
		char Tema[11];
		int tecla;
		PegaTema(Tema,op);
			
		BlocoMenu(55,75,8,24,1,2);
		
		BlocoMenu(56,74,9,13,4,2);
		
		textcolor(1);
		gotoxy(55,8);printf("%c",204);
		gotoxy(55,24);printf("%c",202);
		textcolor(0);
		gotoxy(61,11);printf("USUARIO");
	
		sair=1;
}

void LateralMenu(char NomeArq[], int op, int &sair)
{
		char Tema[11];
		int tecla,op2;
		
		PegaTema(Tema,op);
			
		BlocoMenu(55,75,8,24,1,2);
		
		BlocoMenu(56,74,9,13,4,2);
		
		textcolor(1);
		gotoxy(55,8);printf("%c",204);
		gotoxy(55,24);printf("%c",202);
		textcolor(0);
		gotoxy(61,11);printf("%s",Tema);
	
		
		textcolor(1);textbackground(2);
		gotoxy(63,16);printf("JOGAR");
		gotoxy(60,21);printf("VER PALAVRAS");
		op2=op;
		op=1;
		do{
			textbackground(2);
			for(int i=56;i<75;i++)
			for(int j=14;j<24;j++)
			{
				gotoxy(i,j);printf(" ");
			}
			
			if(op==1)
			{
				BlocoMenu(56,74,14,18,2,1);gotoxy(63,16);printf("JOGAR");textcolor(1);textbackground(2);gotoxy(60,21);printf("VER PALAVRAS");
			}
			else
			if(op==2)
			{
				BlocoMenu(56,74,19,23,2,1);gotoxy(60,21);printf("VER PALAVRAS");textcolor(1);textbackground(2);gotoxy(63,16);printf("JOGAR");
			}
			
			fflush(stdin);
			tecla=getch();
			switch(tecla)
			{		
				case 119: //seta cima
				if(op==2)
					op--;
				break;
				
				case 115: //seta baixo
				if(op==1)
					op++;
				break; 
				
				case 13:
				if(op==1)				
					sair=1;
				else
				{
					
					verArq(NomeArq,op2);
					tecla=97;
				}		
					
				break;		
			}
		}while(tecla!=97 && sair!=1);
		
		textbackground(0);clrscr();
}

void Menu(char NomeArq[],int &op, char Usuario[])
{
	
	int tecla,x=1,y=1,sair=0;
	
	textbackground(0);clrscr();
	
	
	strcpy(Usuario,"CRIAR");
	do{
		
		BlocoMenu(61,76,5,18,15,0);
		gotoxy(65,6);printf("Comandos");
		gotoxy(62,7);printf("--------------");

		textcolor(9);
		gotoxy(69,10);printf("W");
		gotoxy(68,11);printf("ASD");
		
		textcolor(6);
		gotoxy(69,9);printf("%c",24);
		gotoxy(69,12);printf("%c",25);
		gotoxy(71,11);printf("%c",26);
		gotoxy(67,11);printf("%c",27);
		

		textcolor(4);
		gotoxy(65,15);printf("ESC = Sair");
		
		BlocoMenu(25,55,2,24,1,2);
		
		BlocoMenu(26,54,3,7,4,2);
		
		gotoxy(35,5);printf("--* MENU *--");

		textcolor(1);textbackground(2);
		gotoxy(30,9);printf("FUTEBOL");
		gotoxy(30,13);printf("CARROS");
		gotoxy(30,17);printf("TIMES");
		gotoxy(30,21);printf("FRUTAS");
		gotoxy(44,9);printf("PROFESSOR");
		gotoxy(44,13);printf("ESPORTES");
		gotoxy(44,17);printf("MULHERES");
		gotoxy(44,21);printf("%s",Usuario);
		
		
		if(op==1)
		{
			BlocoMenu(26,39,8,10,2,1);gotoxy(30,9);printf("FUTEBOL");
		}
		else
		if(op==2)
		{
			BlocoMenu(26,39,12,14,2,1);gotoxy(30,13);printf("CARROS");
		}
		else
		if(op==3)
		{
			BlocoMenu(26,39,16,18,2,1);gotoxy(30,17);printf("TIMES");
		}
		else
		if(op==4)
		{
			BlocoMenu(26,39,20,22,2,1);gotoxy(30,21);printf("FRUTAS");
		}
		else
		if(op==5)
		{
			BlocoMenu(40,54,8,10,2,1);gotoxy(44,9);printf("PROFESSOR");
		}
		else
		if(op==6)
		{
			BlocoMenu(40,54,12,14,2,1);gotoxy(44,13);printf("ESPORTES");
		}
		else
		if(op==7)
		{
			BlocoMenu(40,54,16,18,2,1);gotoxy(44,17);printf("MULHERES");
		}
		else
		if(op==8)
		{
			BlocoMenu(40,54,20,22,2,1);gotoxy(44,21);printf("%s",Usuario);
		}
		
		fflush(stdin);
		tecla=getch();
		
		switch(tecla)
		{
			/*case 100: //seta direita
			break; 	
			case 97://seta esquerda
			break;	*/		
			case 119: //seta cima
			if(op>=2)
				op--;
			break;
			
			case 115: //seta baixo
			if(op<=7)
				op++;
			break; 
			
			case 100: //13
				if(op==1)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\FUTEBOL.txt");	
					LateralMenu(NomeArq,op,sair);
				}	
				else
				if(op==2)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\CARROS.txt");	
					LateralMenu(NomeArq,op,sair);
				}	
				else
				if(op==3)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\TIMES.txt");	
					LateralMenu(NomeArq,op,sair);
				}					
				else
				if(op==4)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\FRUTAS.txt");	
					LateralMenu(NomeArq,op,sair);
				}					
				else
				if(op==5)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\PROFESSORES.txt");
					LateralMenu(NomeArq,op,sair);
				}						
				else
				if(op==6)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\ESPORTES.txt");	
					LateralMenu(NomeArq,op,sair);
				}				
				else
				if(op==7)
				{
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\MULHERES.txt");
					LateralMenu(NomeArq,op,sair);
				}			
				else
				if(op==8)
				{	
				
					LateralMenuUsuario(op,sair);
					CriaUsuario(Usuario, sair);
					
					strcpy(NomeArq,"C:\\Users\\Vinicius Vasconcelos\\Downloads\\Trabalho_EDI\\CacaPalavras_Matheus_Omote_e_Vinicius\\usu.txt");										
				}				
			
			break;
			
			case 27:
			op=9;
			break;
		}
	}while(sair!=1 && op!=9);
	textcolor(15);
	textbackground(0);clrscr();
}

void Explode(int x,int y)
{
	int i,vel=200;

	for(i=0;i<1;i++)
	{
		textcolor(4);
		gotoxy(x,y);printf("X");
		_sleep(vel);
		textcolor(12);
		gotoxy(x,y);printf(" ");
		gotoxy(x,y+1);printf("X");
		gotoxy(x,y-1);printf("X");
		gotoxy(x+1,y+1);printf("X");
		gotoxy(x+1,y-1);printf("X");
		gotoxy(x+1,y);printf("X");
		gotoxy(x-1,y);printf("X");
		gotoxy(x-1,y+1);printf("X");
		gotoxy(x-1,y-1);printf("X");
		gotoxy(x+1,y+2);printf(" ");
		gotoxy(x+1,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x+2,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x-2,y+1);printf(" ");
		gotoxy(x-2,y+2);printf(" ");
		gotoxy(x-2,y-2);printf(" ");
		gotoxy(x+1,y+2);printf(" ");
		gotoxy(x+1,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x+2,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x-2,y+1);printf(" ");
		gotoxy(x-2,y+2);printf(" ");
		gotoxy(x-2,y-2);printf(" ");
		gotoxy(x-2,y);printf(" ");
		gotoxy(x+2,y);printf(" ");
		gotoxy(x-2,y+1);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x-2,y-1);printf(" ");
		gotoxy(x+2,y-1);printf(" ");
		gotoxy(x,y+2);printf(" ");
		gotoxy(x,y-2);printf(" ");
		gotoxy(x+2,y+2);printf(" ");
		gotoxy(x-1,y+2);printf(" ");
		gotoxy(x-1,y-2);printf(" ");
		_sleep(vel);
		textcolor(14);
		gotoxy(x,y+1);printf(" ");
		gotoxy(x,y-1);printf(" ");
		gotoxy(x+1,y+1);printf(" ");
		gotoxy(x+1,y-1);printf(" ");
		gotoxy(x+1,y);printf(" ");
		gotoxy(x-1,y);printf(" ");
		gotoxy(x-1,y+1);printf(" ");
		gotoxy(x-1,y-1);printf(" ");
		gotoxy(x+1,y+2);printf("X");
		gotoxy(x+1,y-2);printf("X");
		gotoxy(x+2,y+1);printf("X");
		gotoxy(x+2,y-2);printf("X");
		gotoxy(x+2,y+1);printf("X");
		gotoxy(x-2,y+1);printf("X");
		gotoxy(x-2,y+2);printf("X");
		gotoxy(x-2,y-2);printf("X");
		gotoxy(x-2,y);printf("X");
		gotoxy(x+2,y);printf("X");
		gotoxy(x-2,y+1);printf("X");
		gotoxy(x+2,y+1);printf("X");
		gotoxy(x-2,y-1);printf("X");
		gotoxy(x+2,y-1);printf("X");
		gotoxy(x,y+2);printf("X");
		gotoxy(x,y-2);printf("X");
		gotoxy(x+2,y+2);printf("X");
		gotoxy(x-1,y+2);printf("X");
		gotoxy(x-1,y-2);printf("X");
		_sleep(vel);
		gotoxy(x,y+1);printf(" ");
		gotoxy(x,y-1);printf(" ");
		gotoxy(x+1,y+1);printf(" ");
		gotoxy(x+1,y-1);printf(" ");
		gotoxy(x+1,y);printf(" ");
		gotoxy(x-1,y);printf(" ");
		gotoxy(x-1,y+1);printf(" ");
		gotoxy(x-1,y-1);printf(" ");
		gotoxy(x+1,y+2);printf(" ");
		gotoxy(x+1,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x+2,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x-2,y+1);printf(" ");
		gotoxy(x-2,y+2);printf(" ");
		gotoxy(x-2,y-2);printf(" ");
		gotoxy(x+1,y+2);printf(" ");
		gotoxy(x+1,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x+2,y-2);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x-2,y+1);printf(" ");
		gotoxy(x-2,y+2);printf(" ");
		gotoxy(x-2,y-2);printf(" ");
		gotoxy(x-2,y);printf(" ");
		gotoxy(x+2,y);printf(" ");
		gotoxy(x-2,y+1);printf(" ");
		gotoxy(x+2,y+1);printf(" ");
		gotoxy(x-2,y-1);printf(" ");
		gotoxy(x+2,y-1);printf(" ");
		gotoxy(x,y+2);printf(" ");
		gotoxy(x,y-2);printf(" ");
		gotoxy(x+2,y+2);printf(" ");
		gotoxy(x-1,y+2);printf(" ");
		gotoxy(x-1,y-2);printf(" ");
		_sleep(vel);
	}
	//textcolor(9);
	Bloco(20,60,5,24,1,2);
}

void gameover(void) // FIM DE JOGO
{
    system("cls");
	gotoxy(25,4);printf("xxxxxx xxxxxx xxx  xxx xxxxxx");
	gotoxy(25,5);printf("xx     xx  xx xxxxxxxx xx    ");
	gotoxy(25,6);printf("xx xxx xxxxxx xx xx xx xxxxxx");
	gotoxy(25,7);printf("xx  xx xx  xx xx xx xx xx    ");
	gotoxy(25,8);printf("xxxxxx xx  xx xx xx xx xxxxxx");
	
	gotoxy(25,10);printf("xxxxxx xx  xx xxxxxx xxxxxx ");
	gotoxy(25,11);printf("xxxxxx xx  xx xx     xx  xx ");
	gotoxy(25,12);printf("xx  xx xx  xx xxxxxx xxxxxx ");
	gotoxy(25,13);printf("xxxxxx  x  x  xx     xx  xxx");
	gotoxy(25,14);printf("xxxxxx   xx   xxxxxx xx   xxx");
	getch();
}

void Fim()
{
	int x,y;
	textcolor(15);
	textbackground(0);
	do{
		
		x=Sorteio(3,77);
		y=Sorteio(3,22);
		textbackground(0);textcolor(15);clrscr();
		gotoxy(40,13);printf("PARABENS !!!");
		if(x!=35 && y!=13)
			Explode(x,y);
		
	}while(!kbhit());
	getch();
}

void sorteiaArq(char NomeArq[], int vet[])
{
	int TL=0, aux, achou=0, tl=0;
	char palavra[8];
	
	FILE *arq = fopen(NomeArq, "r");
	
	fgets(palavra, 8, arq);
	TL++;
	while(!feof(arq))
	{
		TL++;
		fgets(palavra, 8, arq);
	}
	fclose(arq);
	
	for(int i = 0; i<5; i++)
	{
		achou = 0;
		aux = Sorteio(1, TL);
		
		for(int j=0; j<tl && achou !=1; j++)
			if(vet[j] == aux)
				achou = 1;
				
		if(achou != 1)
		{
			vet[i] = aux;
			tl++;
		}
		else
			i--;		
	}
}
