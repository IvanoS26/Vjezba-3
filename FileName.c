#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct cvor {
    char ime[20];
    char prezime[20];
    struct cvor* Next;
};

int UnosPocetak(char ime[], char prezime[], struct cvor* p);
int Ispis(struct cvor* p);
struct cvor* TraziPrethodnog(char prezime[], struct cvor* p);
int UnosIza(char imeT[], char prezimeT[], char ime[], char prezime[], struct cvor* p);
int UnosIspred(char imeT[], char prezimeT[], char ime[], char prezime[], struct cvor* p);
int Sort(struct cvor *p);
int IspisDatoteka(FILE* f, struct cvor* p);
int CitanjeDatoteka(FILE* f, struct cvor* p);

int main() {
    FILE* f;
    struct cvor Head1, Head2;
    Head1.Next = NULL;
    Head2.Next = NULL;

    printf("Obican unos:\n");
    UnosPocetak("Mate", "Matic", &Head1);
    UnosPocetak("Zure", "Zuric", &Head1);
    Ispis(&Head1);

    printf("Dodavanje iza:\n");
    UnosIza("Mate", "Matic", "Ivan", "Ivic", &Head1);
    Ispis(&Head1);

    printf("Dodavanje ispred:\n");
    UnosIspred("Mate", "Matic", "Duje", "Dujic", &Head1);
    Ispis(&Head1);

    printf("Sortirano:\n");
    Sort(&Head1);
    Ispis(&Head1);

    f = fopen("Osobe.txt", "w");
    if (f == NULL) {
        printf("Greska!\n");
        return -1;
    }

    IspisDatoteka(f, &Head1);
    fclose(f);

    f = fopen("Osobe.txt", "r");
    if (f == NULL) {
        printf("Greska!\n");
        return -1;
    }

    printf("Procitana datoteka:\n");
    CitanjeDatoteka(f, &Head2);
    Ispis(&Head2);
    fclose(f);

    return 0;
}

int UnosPocetak(char ime[], char prezime[], struct cvor* p) {
    struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
    if (q == NULL) {
        printf("Greska!\n");
        return 0;
    }

    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);

    q->Next = p->Next;
    p->Next = q;

    return 0;
}

int Ispis(struct cvor* p) {
   
    while (p->Next != NULL) {
        printf("\t%s %s\n", p->Next->ime, p->Next->prezime);
        p = p->Next;
    }
    printf("\n");
    return 0;
}

struct cvor* TraziPrethodnog(char prezime[], struct cvor* p) {
    while (p->Next != NULL && strcmp(p->Next->prezime, prezime) != 0) {
        p = p->Next;
    }

    if (p->Next != NULL) {
        return p;
    }

    return NULL;
}

int UnosIza(char imeT[], char prezimeT[], char ime[], char prezime[], struct cvor* p) {
    p = TraziPrethodnog(prezimeT, p);
    if (p == NULL) {
        printf("Element nije pronadjen!\n");
        return 0;
    }
    p = p->Next;

    struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
    if (q == NULL) {
        printf("Greska!\n");
        return 0;
    }

    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);

    q->Next = p->Next;
    p->Next = q;

    return 0;
}

int UnosIspred(char imeT[], char prezimeT[], char ime[], char prezime[], struct cvor* p) {
    p = TraziPrethodnog(prezimeT, p);
    if (p == NULL) {
        printf("Element nije pronadjen!\n");
        return 0;
    }

    struct cvor* q = (struct cvor*)malloc(sizeof(struct cvor));
    if (q == NULL) {
        printf("Greska!\n");
        return 0;
    }

    strcpy(q->ime, ime);
    strcpy(q->prezime, prezime);

    q->Next = p->Next;
    p->Next = q;

    return 0;
}

int Sort(struct cvor* p) {

    if (p == NULL || p->Next == NULL) {
        return 0;
    }

    struct cvor *j, *prev_j, *temp, *end;
    end = NULL;
    int swapped = 1;

    while (swapped) {
        swapped = 0;
        prev_j = p;
        j = p->Next;

        while (j->Next != end) {
            if (strcmp(j->prezime, j->Next->prezime) > 0) {

                temp = j->Next;
                prev_j->Next = temp;
                j->Next = temp->Next;
                temp->Next = j;

                j = temp;
                swapped = 1; 
            }

            prev_j = j;
            j = j->Next;
        }

        end = j;
    }

    return 0;
}

int IspisDatoteka(FILE* f, struct cvor* p) {
    while (p->Next != NULL) {
        fprintf(f,"%s %s\n", p->Next->ime, p->Next->prezime);
        p = p->Next;
    }
    return 0;
}

int CitanjeDatoteka(FILE* f, struct cvor* p) {
    char ime[20], prezime[20];
    while (fscanf(f,"%s %s", ime, prezime) == 2) {
        UnosPocetak(ime, prezime, p);
    }
    return 0;
}
