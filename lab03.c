#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define R 3
#define M 2
void wektorLosowy(float wektor[], int m, float min, float max);
void wypiszJ(float tab[], int m);
void wypisz(float tab[][M], int n, int m);
void wstawWiersz(float tab[][M], float wiersz[],  int m, int nr);
void ustawWiersze(float tab[][M], int n, int m, int min, int max);
void zamienKolumny(float tab[][M], int n, int m, int k1, int k2);
void sredniaKolumn(float tab[][M], float tabSr[], int n, int m);
void sortuj(float tab[][M], float tabSr[], int n, int m);

int main()
{
    int i,j;
	srand((unsigned)time(NULL));
	float *t1;
	float *t2;
	float **t3;


	t1 = malloc(sizeof(float)*R);

	t2 = malloc(sizeof(float)*R);

	t3 = malloc(sizeof(float*)*R);
    /*t3[0] = malloc(sizeof(float)*M*R);*/
    /*for(i=0;i<R;++i)*/
    for(j=0;j<R;++j)
    {
        t3[j]=malloc(sizeof(float)*M);
    }

    t3[0][0]=997;
    t3[0][1]=996;
    t3[1][0]=995;

    wypisz(t3,R,M);


	printf("Tablica liczb losowych:\n\n");
	wektorLosowy(t1,R,0,1000);
	wypiszJ(t1,R);
	printf("\n\nTablica zer:\n\n");
	wektorLosowy(t2,R,0,0);
    wypiszJ(t2,R);

	printf("\n\nTablica z wstawionym drugim wierszem:\n\n");


	printf("\n\nTablica z ustawionymi wszystkimi wierszami:\n\n");


	printf("\n\nTablica z zamienionymi kolumnami o indeksach 0 i 2:\n\n");


	printf("\n\nSrednie wartosci w kolumnach z trzech pierwszych wierszy:\n\n");


	printf("\n\nTablica po sortowaniu:\n\n");


	printf("\n\nSrednie wartosci tablicy posortowanej:\n\n");


	printf("\n\n");
	system("pause");
	return 0;
}
void wektorLosowy(float wektor[], int m, float min, float max)
{
	int i;
	for(i=0;i<m;++i)
	{
		if(max==0) wektor[i]=0.0f;
		else wektor[i]=(float) rand() / (float) RAND_MAX;
	}
}
void wypiszJ(float tab[], int m)
{
	int i;
	for(i=0; i<m; ++i)
	{
		printf("%.2f ", tab[i]);
	}
	printf("\n");
}
void wypisz(float tab[][M], int n, int m)
{
	int i,j;
	printf("%.2f\n\n",**tab);
	for(i=0;i<n;i++){
        for(j=0;j<m;j++)
            printf( "%.2f ", *( tab + (n*i+j) ));
        printf("\n");
    }
}
