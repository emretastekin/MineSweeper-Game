#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

//Constants

#define N 8 //TAILLE_TABLEAU
#define count 3 //NORMALE
#define win 1 //GAGNER
#define lose -1 //PERDU
#define continuation 0 //CONTINUE

//Global Variables

int sub_tab[N+2][N+2];
char table[N+2][N+2];
int mine_num,y=0;
int f_count=0;

void sub_table(); //creer
void first_table(); //initialiser
void table_compression(); //afficher_tableau
void subtable_compression(); //afficher_soustableau
void mine_placement(); //placer
int coordinate(int line,int column); //cresuer
void search(int line,int column); //explorer
int control();//verifier

void sub_table()
{
	int i,j,mine_num;
	
	for(i=0;i<=N+1;i++)
	{
		for(j=0;j<=N+1;j++)
		{
			sub_tab[i][j]=0;
		}
	}
	
	for(i=0;i<=N;i++)
	{
		sub_tab[i][0]=1;
		sub_tab[i][N+1]=1;
		
	}
	
	for(j=0;j<=N;j++)
	{
		sub_tab[0][j]=1;
		sub_tab[N+1][j]=1;
	}
	mine_num=count;
	mine_placement();
}

void first_table()
{
	int i,j;
	
	for(i=0;i<=N+1;i++)
	{
		for(j=0;j<=N+1;j++)
		{
			table[i][j]='#';
		}
	}
	
	for(i=0;i<=N;i++)
	{
		table[i][0]='*';
		table[i][N+1]='*';
		
	}
	
	for(j=0;j<=N;j++)
	{
		table[0][j]='*';
		table[N+1][j]='*';
	}
}

void table_compression()
{
	int i,j;

	printf("\n");
	
	for(i=1;i<=N;i++)
	{
		printf("%3d",i);
	}
	printf("\n");

	for(i=1;i<=N;i++){
		printf("---");
	}
	printf("\n");
	
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			printf("%3c",table[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}
	
	for(i=1;i<=N;i++)
	{
		printf("___");
	}
}

void subtable_compression()
{
	int i,j;

	printf("\n");
	
	for(i=1;i<=N;i++)
	{
		printf("%3d",i);
	}
	printf("\n");

	for(i=1;i<=N;i++){
		printf("---");
	}
	printf("\n");
	
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			printf("%3d",sub_tab[i][j]);
		}
		printf(" |%d",i);
		printf("\n");
	}
	
	for(i=1;i<=N;i++)
	{
		printf("___");
	}
	printf("\n");
}



void mine_placement()
{   
	srand(time(NULL));
	int i,j,k,p,line,column;
	mine_num=count;
	
	for(i=1;i<=mine_num;i++)
	{
		line=1+rand()%N;
		column=1+rand()%N;
		if(sub_tab[line][column]== -1){

			i--;
		}

		sub_tab[line][column]= -1;

        for(k=-1;k<=1;k++){
            for(p=-1;p<=1;p++){
        		if(sub_tab[line][column]==-1){
                    if(sub_tab[line+k][column+p]!=-1)
                	{
                        sub_tab[line+k][column+p]++;
                    }
                }
            }
        }

    }
}



int coordinate(int line,int column)
{
	int x=0;
	
	if(sub_tab[line][column]==-1)
	{
		x=lose;
	}
	else if(sub_tab[line][column]>0)
	{
		table[line][column]=('0'+sub_tab[line][column]);
		x=control();
		x=continuation;
	}
	else
	{
		search(line,column);
	}
	
	return x;
}

void search(int line,int column)
{
	int i,j;
	table[line][column]='0'+sub_tab[line][column];
	
	for(i=-1;i<=1;i++)
	{
		for(j=-1;j<=1;j++)
		{
			if(sub_tab[line+i][column+i]>0 && table[line+i][column+j]=='#')
			{
				table[line+i][column+j]='0'+sub_tab[line+i][column+j];
			}
			else if(sub_tab[line+i][column+j]==0 && table[line+i][column+j]=='#')
			{
				search(line+i,column+j);
			}
		}
	}
}

int control()
{
	int i,j,result;
	
	for(i=1;i<=N;i++)
	{
		for(j=1;j<=N;j++)
		{
			if(table[i][j]=='D')
			{
				if(sub_tab[i][j]==-1)
				{
					y++;
				}
			}
		}
	}
	
	if(y==count)
	{
		result=win;
	}
	else
	{
		result=continuation;
	}
	
	return result;
}

int main()
{
	int progress,again;
	int line,column;
	char character;

	printf("Welcome To MineSweeper Game\n\n");
	sub_table();
	first_table();
	
	do{
		
		table_compression();
		printf("\n");
		printf("Please, enter the format: (o),line,column or (f),line,column or (e),line,colum\n"); scanf("%c,%d,%d",&character,&line,&column);
		printf("\n");
		
		if(character=='o')
		{
			progress=coordinate(line,column);
		}
		else if(character=='f')
		{
			if(mine_num>f_count)
			{
				f_count++;
				table[line][column]='D';
				progress=control();
			}
		}
		else if(character=='e')
		{
			if(f_count>0)
			{
				f_count--;
			}
			table[line][column]='#';
			progress=coordinate(line,column);
		}
		
		if(progress==lose)
		{
			printf("You losed the game\n");
			subtable_compression();
			printf("Do you want to play the game again ? [1: Yes, 0:No)\n"); scanf("%d",&again);
			
			switch(again)
			{
				case 0: 
						printf("Thanks, see you\n");
				   		return 0;
						break;
				case 1:
						f_count=0;
						progress=continuation;
						sub_table();
						first_table();
						break;
				default:
						printf("You entered wrong value\n");
						break;
				
			}
			
		}
		
		if(progress==win)
		{
			printf("Congratulations, you won\n");
			subtable_compression();
			printf("Do you want to play the game again ? [1: Yes, 0:No)\n"); scanf("%d",&again);
			
			switch(again)
			{
				case 0: 
						printf("Thanks, see you");
				   		return 0;
						break;
				case 1:
						f_count=0;
						progress=continuation;
						sub_table();
						first_table();
						break;
				default:
						printf("You entered wrong value");
						break;
				
			}
		}
		
	}while(1);
	
	return 0;
}
