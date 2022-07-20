//******* Questo programma leggerà i dettagli in Account_Details.dat e mostrerà le credenziali in una forma leggibile. **********/

#include<stdio.h>
#include<stdlib.h>

//******************* Struttura per conservare i dettagli di tutti gli intestatari presenti in Account_Details.dat *******************/

struct Intestatario
{
    char nome[50] ;
	char NumeroAccount[50];
    int pin;
    float saldo;
};

int main()
{
    FILE *fp;
    struct Intestatario s;
	fp = fopen("Account_Details.dat", "rb");

    if(fp == NULL)
    {
        printf("Errore apertura file\n");
        exit(1);
    }

    while( fread(&s, sizeof(struct Intestatario), 1, fp) == 1 )
    {
		printf("Nome: %s \n", s.nome);
        printf("Numero Account : %s \n", s. NumeroAccount);
        printf("pin: %d \n", s.pin);
        printf("Saldo Account: %.2f \n\n", s.saldo);
    }

    fclose(fp);
    return 0;
}

