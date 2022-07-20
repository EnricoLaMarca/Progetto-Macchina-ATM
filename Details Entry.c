//******************* Nuove registrazioni possono essere aggiunte in Account_Details.dat usando questo programma********************/

#include<stdio.h>
#include<string.h>
#include<stdlib.h>

struct Intestatario
{
    char nome[50];
    char NumeroAccount[50];
    int pin;
    float saldo;
} emp;

int main()
{
    FILE *fp;
    struct Intestatario s;
    fp = fopen("person.dat", "ab");

    if(fp == NULL)
    {
        printf("Errore apertura file\n");
        exit(1);
    }

    printf("Inserire il nome dell'intestatario :\n");
    fflush(stdin);
    gets(s.nome);
    printf("Inserire il numero dell'account :\n");
	fflush(stdin);
	gets(s.NumeroAccount);
	printf("Inserire PIN :\n");
    scanf("%d",&s.pin);
    printf("Inserire saldo :\n");
    scanf("%f",&s.saldo);

    fwrite(&s,sizeof(struct Intestatario),1,fp);

    fclose(fp);

	return 0;
}
