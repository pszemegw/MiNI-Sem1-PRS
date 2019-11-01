#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <conio.h>	//_getch

//-------------------------------------------------------------
enum kolory { SZARY, BIALY, ZIELONY, CZERWONY, NIEBIESKI, FIOLET, STANDARD };
//-------------------------------------------------------------
void ustawKolor(int k)
{
	HANDLE h = GetStdHandle(STD_OUTPUT_HANDLE);

	switch (k)
	{
	case SZARY:     SetConsoleTextAttribute(h, 0x0088);	break;  //szary na szarym tle
	case BIALY:     SetConsoleTextAttribute(h, 0x008F); break;  //bia�y na szarym tle
	case ZIELONY:   SetConsoleTextAttribute(h, 0x008A); break;  //zielony na szarym tle
	case CZERWONY:  SetConsoleTextAttribute(h, 0x008C); break;  //czerwony na szarym tle
	case NIEBIESKI: SetConsoleTextAttribute(h, 0x0089); break;  //niebieski	na szarym tle
	case FIOLET:    SetConsoleTextAttribute(h, 0x0085); break;  //fioletowy na szarym tle
	case STANDARD:  SetConsoleTextAttribute(h, 0x0007);			//domy�lny (bialy na czarnym tle)
	}
}

//-------------------------------------------------------------
void goto_ij(int i, int j)	//tylko ustawia kursor na ekranie
{
	COORD c = { j,i }; SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), c);
}
//-----------------------------------------------------------
//-------------------------------------------------------------
//--------------------------------------------------------------
#define z0 '.'
#define z1 'X'

//---------------------------------------------------------------
typedef struct el {
	char z;
	int  kolor;		//kolory: SZARY, BIALY, ZIELONY, CZERWONY, NIEBIESKI, FIOLET, STANDARD
}el;

//-------------------------------------------------------------
typedef struct tab {
	el** t;	// dynamiczna tablica 2-wymiarowa
	int  m;	// wymiary: m wierszy, m kolumn (tablica kwadratowa)
} tab;


//PROTOTYPY-----------------------------------------------------
tab init(int m);
void plansza(tab p);
void wypisz(tab p);
void zwolnij(tab p);

void generuj_wzorek(tab p);
void obraz(tab p);

void malowanie(tab p);
int obrot_wlewo(tab* p);

//-------------------------------------------------------------
//-------------------------------------------------------------
tab init( int m)
{
    int i=0;
	tab p = { NULL,0 };
    p.m=m;
	p.t = malloc(sizeof(el*)*m);
    if(!p.t) return p;
    for(;i<m;++i)
    {
        p.t[i]=malloc(sizeof(el)*m);
        if(!p.t[i]) return p;
    }
	return p;
}
//-------------------------------------------------------------
void wypisz(tab p)
{
	int i,j;
    for(i=0; i<p.m; ++i)
    {
        for(j=0; j<p.m; ++j)
        {
            ustawKolor(p.t[i][j].kolor);
            printf("%c",p.t[i][j].z);
        }
        printf("\n");
    }

	ustawKolor(STANDARD);	//przed wyj�ciem kolor domy�lny
}
//-------------------------------------------------------------
void zwolnij(tab p)
{
	int i;
    for(i=0; i<p.m; ++i)
        free(p.t[i]);
    free(&p);

}
//-------------------------------------------------------------
void plansza(tab p)
{
    int i,j;
	//if((p==NULL) return;
    for(i=0; i<p.m; ++i)
    {
        for(j=0; j<p.m; ++j)
        {
            p.t[i][j].z=z0;
            p.t[i][j].kolor = CZERWONY;
        }
    }

}
//-------------------------------------------------------------
void generuj_wzorek(tab p)
{
	int s=p.m/2;
	int zz1=0;
	int zz0=0;
	int it=1;
	int row=s;
	int rowt;
	int col=s+1;
	p.t[s][s].z = z1;
	p.t[s][s].kolor = BIALY;
    for(col=s+1; col<p.m-1; col++)
    {
        for(row=col; row>=s-it; row--)
        {
            zz1=0;
            zz0=0;
            for(rowt=row-1;rowt<=row+1;++rowt)
            {
                if(p.t[rowt][col-1].z==z1) zz1++;
                if(p.t[rowt][col-1].z==z0) zz0++;
            }
            if(zz0==2 && zz1==1) {p.t[row][col].z=z1; p.t[row][col].kolor=BIALY;}
            else{p.t[row][col].z=z0; p.t[row][col].kolor=SZARY;}
        }
        it++;
    }
    col++;
    for(row=p.m-1; row>=0; row--)
    {

        p.t[row][p.m-1].z=z0;
        p.t[row][p.m-1].kolor=SZARY;
    }


}
//--------------------------------------------------------------
void obraz(tab p)
{
    generuj_wzorek(p);
    int i,j,it;
    it=0;
	for(i=0;i<p.m;++i)
    {
        for(j=0;j<i;++j)
        {
            p.t[i][j]=p.t[j][i];
        }
    }
    /*for(i=0;i<p.m;++i)
    {
        for(j=i;j<p.m;++j)
        {
            p.t[i][j]=p.t[j][i];
        }
        it++;
    }*/
    for(i=0;i<p.m;++i)
    {
        for(j=0;j<p.m-i;++j)
        {
            p.t[j][i]=p.t[p.m-i-1][p.m-j-1];
        }
    }

}
//---------------------------------------------------------------
void malowanie(tab p)
{
	int i,j;

	for(i=p.m/2;i>=0;--i){
        for(j=p.m-1-i;j<p.m-1;j++)
            if(p.t[i][j].z==z1) p.t[i][j].kolor=ZIELONY;

	}
	for(i=p.m/2;i<p.m-1;++i){
        for(j=p.m/2;j<=i;j++)
            if(p.t[i][j].z==z1) p.t[i][j].kolor=FIOLET;

	}
    for(i=p.m/2;i<p.m-1;++i){
        for(j=0;j<=p.m-1-i;j++)
            if(p.t[i][j].z==z1) p.t[i][j].kolor=NIEBIESKI;

	}
	for(i=0;i<=p.m/2;++i){
        for(j=i;j<=p.m/2;j++)
            if(p.t[i][j].z==z1) p.t[i][j].kolor=CZERWONY;

	}

}
//---------------------------------------------------------------
int obrot_wlewo(tab* p)
{
	//uzupe�nij

	return 1;
}
//---------------------------------------------------------------
//---------------------------------------------------------------

int main()
{
	tab	T;				//bie�acy obrazek

	int		k;			//obs�uga menu
	int		m;			//wymiary bie�acego obrazka

	//----------------------------------------------------------------------------------
	//losujemy wymiary bie�acego obrazka
	srand((unsigned)time(NULL));
	m = 60 + rand() % 10;
	if ( m % 2 ==0 ) m++;	//liczba wierszy oraz kolumn - nieparzysta (kwadratowy)
	//----------------------------------------------------------------------------------

	T = init(m);
	if (!(T.t)) 	return 1;


	plansza(T);
	//generuj_wzorek(T);
    //wypisz(T);



	do  {
				goto_ij(0, 0);

				wypisz(T);	//zobaczmy obraz

                printf("\nMENU:\n");
				printf("1 - Obraz\n");
                printf("2 - Malowanie\n");
               	printf("3 - Obrot w lewo\n");
				printf("4 - Undo\n");
				printf("0 - KONIEC\n");
                printf("Podaj numer opcji:\n");

				k = _getch()-'0';

                switch (k)
                {
					case 1:

						obraz(T);
						break;

					case 2: //malowanie

						malowanie(T);
						break;

                    case 3: //obroty w lewo
						{
							int s;

							//s=obrot_wlewo(&T);
							//if (!s) return 1;
						}
						break;

					case 4:

						break;

                }//switch

            } while (k != 0);

	zwolnij(T);

	return 0;
}
