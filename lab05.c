#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <windows.h>


#define KOLOR_ROZOWY 5			//kod na kolor rozowy
#define KOLOR_BIALY 15			//kod na kolor bia³y
#define WIERSZY 10              //tyle bedzie wierszy w krzyzowce
#define KOLUMN 15               //tyle bedzie kolumn w krzyzowce
#define ILE_HASEL 7             //tak dluga bedzie tablica hasel

//typ wyliczeniowy sluzacy do oznaczania kierunku czytania hasla w krzyzowce
typedef enum orientacja {LewoPrawo, GoraDol, nieokreslony} orientacja;

//struktura reprezentujaca krzyzowke
typedef struct krzyzowka
{
    char ** pola;               //pola krzyzowki, na ksztalt prostokata
    int ile_w;                  //liczba wierszy w krzyzowce
    int ile_k;                  //liczba kolumn w krzyzowce
} krzyzowka;

//struktura reprezentujaca haslo
typedef struct haslo
{
    char * tresc;               //lancuch reprezentujacy haslo
    int poz_x;                  //pozycja pierwszej litery hasla (numer wiersza) po znalezieniu w krzyzowce, na poczatku ustalana na -1
    int poz_y;                  //pozycja pierwszej litery hasla (numer kolumny) po znalezieniu w krzyzowce, na poczatku ustalana na -1
    enum orientacja kierunek;   //kierunek czytania hasla po znalezieniu w krzyzowce
} haslo;

//prototypy funkcji, Zadanie 5A:
struct krzyzowka * generuj (const int a, const int b, const char* s);
void wypisz_k (const struct krzyzowka *);
void wypisz_h (const struct haslo *h);
void znajdz (const struct krzyzowka * , struct haslo *);
void wypisz_koloruj (const struct krzyzowka *, const struct haslo [], const int);
int znajdz_ind_nh (const struct haslo [], int);
void sprzataj (struct krzyzowka *);
void kolor_printf(char);

HANDLE hConsole; //potrzebne do kolorowania, prosze nie modyfikowac

int main(int argc, const char * argv[])
{
    //Zmienne w programie:
    char * wejscie = "bkdhsniegasjkwuaeqspsibjaatschltdeoiosankiiefwosidmatopopiheakhpdfuwehifjkcnbnartysdbofbmonosimikolajtarikhrhsrohsqlytomarukasdsazscszf"; //wejscie to lancuch na podstawie ktorego stworzymy krzyzowke
    struct haslo lista_hasel[ILE_HASEL] = { {"balwan", -1, -1, nieokreslony} , {"narty", -1, -1, nieokreslony} , {"mroz", -1, -1, nieokreslony} , {"mikolaj", -1, -1, nieokreslony}, {"komin", -1, -1, nieokreslony} ,{"sanki", -1, -1, nieokreslony} , {"snieg", -1, -1, nieokreslony} }; //lista_hasel to tablica z haslami, ktorych bedziemy szukac w krzyzowce
    struct krzyzowka *przyklad_pewny; //to bedzie nazwa naszej krzyzowki
    int i; //zmienna pomocnicza do iterowania
    hConsole = GetStdHandle(STD_OUTPUT_HANDLE);		//potrzebne do kolorowania, prosze nie modyfikowac

    //Powitanie, prezentacja uzycia kolorow na konsoli
    //Ponizej wywolana zostaje funkcja, ktora wypisuje pokolorowany znak na konsole
    kolor_printf('W');kolor_printf('i');kolor_printf('t');kolor_printf('a');kolor_printf('j');
    printf(" w moim porgramie!\n");

    //Etap 1
    printf("\nEtap 1:\n\n");
    // - generowanie krzyzowki - uzupelnij

    przyklad_pewny = generuj(9,15,wejscie);
    // - wypisanie krzyzowki na konsoli - uzupelnij
    wypisz_k(przyklad_pewny);
    // - wypisanie przykladowego hasla na konsoli - uzupelnij
	wypisz_h(lista_hasel);


    //Etap 2
    printf("\nEtap 2:\n\n");
    // - poszukiwanie hasel, wypisanie hasel - uzupelnij
    for(i=0;i<ILE_HASEL;++i)
    {
        znajdz(przyklad_pewny,&lista_hasel[i]);
        wypisz_h(&lista_hasel[i]);
    }

    // - wypisanie z pokolorowanymi haslami - uzupelnij
    wypisz_koloruj(przyklad_pewny,lista_hasel,ILE_HASEL);

    //Etap 3
    // - wyszukanie najdluzszego hasla z krzyzowki - uzupelnij
    printf("Etap 3:\n\n");
    printf("Najdluzsze haslo w krzyzowce to %s\n\n", lista_hasel[znajdz_ind_nh(lista_hasel,ILE_HASEL)].tresc);
    // - sprzatanie - uzupelnij
    sprzataj(przyklad_pewny);
    system("PAUSE");
    return 0;
}

void kolor_printf(char znak)
{
    SetConsoleTextAttribute(hConsole, KOLOR_ROZOWY);		//ustalenie koloru
    printf("%c",znak);										//wypisanie znaku w kolorze
    SetConsoleTextAttribute(hConsole, KOLOR_BIALY);			//powrot do oryginalnych ustawien
}
struct krzyzowka * generuj (const int a, const int b, const char* s)
{
    struct krzyzowka * k = malloc(sizeof(struct krzyzowka));
    int i,j,p;
    p=0;
    (*k).ile_w = a;
    (*k).ile_k = b;
    (*k).pola = malloc(sizeof(char*)*(*k).ile_w);

    for(i=0; i<(*k).ile_w;++i)
    {
        (*k).pola[i] = malloc(sizeof(char)*(*k).ile_k);
        for(j=0;j<k->ile_k;++j)
        {
            k->pola[i][j]=s[p];
            p++;
        }

    }

    return k;
}
void wypisz_k (const struct krzyzowka * k)
{
    int i,j;
    for(i=0;i<k->ile_w;++i)
    {
        for(j=0;j<k->ile_k;++j)
        {
            printf("%c", k->pola[i][j]);

        }
        printf("\n");
    }
}

void wypisz_h (const struct haslo *h)
{
    if(!h) return;
    printf("Haslo: %s, pozycja: (%d,%d), kierunek: ",h->tresc,h->poz_x,h->poz_y);
    switch(h->kierunek)
    {
        case nieokreslony:
        printf("nieokreslony\n"); break;
        case LewoPrawo:
        printf("LewoPrawo\n"); break;
        case GoraDol:
        printf("GoraDol\n"); break;
    }

}
void znajdz (const struct krzyzowka* k, struct haslo* h)
{
    //char *t;
    int row,col,index=0;
    //t=malloc(sizeof(char)*(krzyzowka->ile_k+krzyzowka->ile_w))
    for(row=0; row<k->ile_w; ++row)
    {
        for(col=0; col<k->ile_k; ++col)
        {
            for(index=0;index<strlen(h->tresc) && col+index< k->ile_k;index++)
            {
                if(h->tresc[index]!=k->pola[row][col+index]) break;
            }
            if(index==strlen(h->tresc))
            {
                h->poz_x=row;
                h->poz_y=col;
                h->kierunek=LewoPrawo;
                index=0;
                return;
            }
        }
    }
    for(col=0; col<k->ile_k; ++col)
    {
        for(row=0; row<k->ile_w; ++row)
        {
            for(index=0;index<strlen(h->tresc) && row+index< k->ile_w;index++)
            {
                if(h->tresc[index]!=k->pola[row+index][col]) break;
            }
            if(index==strlen(h->tresc))
            {
                h->poz_x=row;
                h->poz_y=col;
                h->kierunek=GoraDol;
                index=0;
                return;
            }
        }
    }


}

void wypisz_koloruj (const struct krzyzowka * k, const haslo h[], const int size)
{
    short **a;
    int i,j;
    int row,col,len;
    a=malloc(sizeof(short*)*k->ile_w);
    for(i=0; i<k->ile_w; ++i)
    {
        a[i]=malloc(sizeof(short)*k->ile_k);
        for(j=0;j<k->ile_k;++j)
            a[i][j]=0;
    }
    for(i=0; i<size; ++i)
    {
        len = strlen(h[i].tresc);
        switch(h[i].kierunek)
        {
        case LewoPrawo:
            for(j=(h+i)->poz_y; j<h[i].poz_y+len; ++j)
            {
                a[h[i].poz_x][j]=1;

            }

            break;
        case GoraDol:
            for(j=(h+i)->poz_x; j<h[i].poz_x+len; ++j)
            {
                a[j][h[i].poz_y]=1;

            }
            break;

        }
    }
    for(i=0;i<k->ile_w;++i)
    {
        for(j=0;j<k->ile_k;++j)
        {
            if(a[i][j]) kolor_printf(k->pola[i][j]);
            else printf("%c",k->pola[i][j]);
        }
        printf("\n");
    }
printf("\n\n");
}

int znajdz_ind_nh (const haslo h[], int size)
{
    int i;
    int longestString = 0;
    int index=-1;
    for(i=0; i<size;++i)
    {
        if(h[i].poz_x > -1 && strlen(h[i].tresc)>longestString)
         {
             longestString = strlen(h[i].tresc);
             index = i;
         }
    }
    return index;
}

void sprzataj (struct krzyzowka *k)
{
    int i;
    for(i=0; i<k->ile_w; ++i)
    {
        free(k->pola[i]);
    }
    free(k->pola);
    free(k);
}

