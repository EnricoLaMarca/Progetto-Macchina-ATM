//ATM Machine C Mini Project

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/**************************************** All Global variables are declared here *********************************************************/

int a=0,b=0,c=0,d=0,Chance=0;
int tempfix=0;

FILE *fp,*ftemp;



struct Intestatario
{
    char nome[50] ;
	char NumeroAccount[50];
    int pin;
    float saldo;
};
struct Intestatario s,r;

int MenuPrincipale();
int Prelevare();
int Depositare();
int RichiestaSaldo();
int TrasferimentoDenaro();
int ControlloSicurezza();
int SicurezzaPotenziata();
int VerificaCarta();
void aggiorna_file(struct Intestatario);



void aggiorna_file(struct Intestatario a){

	FILE *accounts, *temp;
	struct Intestatario b;

	accounts = fopen("Account_Details.dat","rb+");
	temp = fopen("temp.dat","wb+");

	while(fread(&b, sizeof(struct Intestatario), 1, accounts)){
		if(strcmp(b.NumeroAccount , a.NumeroAccount) != 0){
			fwrite(&b,sizeof(struct Intestatario),1,temp);
		}
	}
	fwrite(&a,sizeof(struct Intestatario),1,temp);

	fclose(accounts);
    fclose(temp);
	remove("Account_Details.dat");
    int errore = rename("temp.dat","Account_Details.dat");

	if(errore)
    tempfix=1;
}

int MenuPrincipale()
{

	int scelta;

	printf("\n\n");
	printf("\t\t***************** BENVENUTO AD ATM *******************\n");
	printf("\t\t*                                                      *\n");
	printf("\t\t*              <1>. RITIRARE DENARO                     *\n");
	printf("\t\t*              <2>. DEPOSITARE DENARO                    *\n");
	printf("\t\t*              <3>. RICHIESTA SALDO                    *\n");
	printf("\t\t*              <4>. TRASFERIMENTO DENARO                     *\n");
	printf("\t\t*                                                      *\n");
	printf("\t\t********************************************************\n\n");

	printf("Inserisci la tua scelta\n");
	scanf("%d", &scelta);

	switch(scelta)
	{
		case 1: Prelevare();
		        break;
		case 2: Depositare();
		        break;
		case 3: RichiestaSaldo();
		        break;
		case 4: TrasferimentoDenaro();
	            break;
	    default: printf("Scelta sbagliata , riprova\n\n");
	             MenuPrincipale();
	}
}

int Prelevare()
{


	int ImportoPrelevato,temp5=0;
	printf("\nInserire importo da prelevare\n");
	scanf("%d" , &ImportoPrelevato);



	printf("Sei sicuro di prelevare %d Euro ?\n ", ImportoPrelevato);
	printf("<1>. SI\n <2>. NO\n");
	scanf("%d", &temp5);

	if(temp5==1)
	{

		if(ImportoPrelevato>(s.saldo))
		{
			printf("\nNon puoi prelevare %d Euro\n\n",ImportoPrelevato);
		}

		else if(ImportoPrelevato>2000)
		{
			printf("Non puoi prelevare piu' di 10 banconote alla volta\n");
		}
		else
		{


			s.saldo -= ImportoPrelevato;

			aggiorna_file(s);

			if(tempfix==1)
			{
				printf("\nTransazione fallita!\n");
			}

			else
			{
				printf("\n\n*** Per favore, raccogli il denaro ***\n\n");
				printf("Il saldo attuale del conto e' di %.2f Euro \n\n", s.saldo);
				printf("**** GRAZIE PER AVER USATO ATM ****\n");
			}
		}
    }
	else if(temp5==2)
	{
		printf("**** GRAZIE PER AVER UASTO ATM ****\n");
	}

	else
	{

		a=1;
		SicurezzaPotenziata();
	}
}

int Depositare()
{

	int ImportoDepositato , temp1 , temp6=0;
	printf("\nInserisci l'importo da depositare\n");
	scanf("%d", &ImportoDepositato);

	printf("Sei sicuro di depositare %d Euro ?\n", ImportoDepositato);
	printf("<1>. SI\n<2>. NO\n");
	scanf("%d", &temp6);

	if(temp6==1)
	{
		if(ImportoDepositato>2000)
		printf("Non puoi depositare più di 10 banconote alla volta\n");

		else
		{

			s.saldo += ImportoDepositato;
			aggiorna_file(s);

			if(tempfix==1)
			{
				printf("\nTransazione fallita!\n");
			}

			else
			{
				printf("Il saldo è stato aggiornato \nVuoi la ricevuta?\n");
				printf("\n<1>. SI \n<2>. NO\n");
				scanf("%d", &temp1);
				if(temp1==1)
				{
					printf("Per favore, raccogli la ricevuta\n");
				}

				else if(temp1==2)
				{
					printf("Grazie per aver salvato la carta!\n\n");
					printf("**** GRAZIE PER AVER USATO ATM ****\n");
				}
				else
				{
					b=1;
					SicurezzaPotenziata();
				}
			}
		}
	}

	else if(temp6==2)
	{
		printf("**** GRAZIE PER AVER USATO ATM ****\n");
	}

	else
	{
		b=1;
		SicurezzaPotenziata();
	}
}

int RichiestaSaldo()
{

	int temp2;
	printf("Vuoi controllare il saldo attuale del tuo conto ?\n");
	printf("<1>. SI \n<2>. NO\n");
	scanf("%d",&temp2);

	if(temp2==1)
	{

		printf("%.2f\n", s.saldo);
	}

	else if(temp2==2)
	{
		printf("**** GRAZIE PER AVER USATO ATM ****\n");
	}

	else
	{
		c=1;
		SicurezzaPotenziata();
	}
}

int TrasferimentoDenaro()
{
	int ImportoTrasferito=0 , temp3=0 , temp4=0;
	char ContoTrasferito[50];

	printf("Inserisci il conto in cui vuoi trasferire il denaro\n");
	fflush(stdin);
	gets(ImportoTrasferito);

	printf("\nInserire l'importo da trasferire\n");
	scanf("%d", &ImportoTrasferito);
	if(ImportoTrasferito>4000)
	{
		printf("Non puoi trasferire l'importo di %d Euro\n", ImportoTrasferito);
	}
	else if(ImportoTrasferito>s.saldo)
	{
		printf("Non puoi trasferire il denaro\n");
	}
	else
	{
		printf("Sei sicuro di voler trasferire un importo di %d Euro? \n", ImportoTrasferito);
		printf("\n<1>. SI \n<2>. NO\n");
		scanf("%d",&temp3);
		int flg = 0;
		if(temp3==1)
		{
			fp = fopen("Account_Details.dat","rb+");
			while( fread(&r, sizeof(struct Intestatario), 1, fp))
			{
				if(strcmp(ContoTrasferito , r.NumeroAccount)==0)
				{
					flg = 1;
					break;
				}
			}
			fclose(fp);

			if(flg == 1)
			{
				r.saldo = r.saldo + ImportoTrasferito;
				s.saldo = s.saldo - ImportoTrasferito;
				aggiorna_file(r);
				aggiorna_file(s);

				if(tempfix==1)
				{
					printf("Hitesh\n");
					printf("\nTransazione Fallita\n");
				}
				else
				{
					printf("\nL'importo di %d Euro e' stato trasferito con successo\n",ImportoTrasferito);
					printf("Vuoi la ricevuta?\n");
					printf("<1>. SI \n<2>. NO	 \n");
					scanf("%d",&temp4);
					if(temp4==1)
					{
						printf("Per favore, raccogli la ricevuta\n\n");
					}

					else if(temp4==2)
					{
						printf("Grazie per aver salvato la carta\n");
					}

					else
					{
						printf(" *** GRAZIE PER AVER USATO ATM ***");
			    	}
				}
			}

			else
			{
				printf("\nTransazione fallita !\n");
			}
		}
		else if(temp3==2)
		{
			printf("Transazione Cancellata\n\n");
			printf(" *** GRAZIE PER AVER USATO ATM ***");
		}

		else
		{
			d=1;
			SicurezzaPotenziata();
		}

	}
}

int ControlloSicurezza()
{
	int i=0;
	while(i<3)
	{
		int PINPersonale = 0 , tentativo=1;
		printf("Inserisci il tuo PIN\n");
		scanf("%d", &PINPersonale);
		if(PINPersonale == s.pin)
		break;

		else
        {
			printf("PIN sbagliato, riprova\n\n");
			i+=1;

			if(i==3)
			exit(0);
		}
	}

}

int SicurezzaPotenziata()
{

	Chance++;
	while(Chance!=3)
	{
		printf("\nHai fatto la scelta sbagliata, riprova\n\n ");
		if(a==1)
		{
			Prelevare();
			break;
		}

		else if(b==1)
		{
			Depositare();
			break;
		}

		else if(c==1)
		{
			RichiestaSaldo();
			break;
		}

		else if(d==1)
		{
			TrasferimentoDenaro(0);
			break;
		}
	}

	if(Chance==3)
	{
		printf("Riprova tra qualche minuto\n\n");
		printf("**** GRAZIE PER AVER USATO ATM ****\n");
	}
}

int VerificaCarta()
{

    char AcNo[50];
    int pin=0 , flag=0 , count=0  ;

    fp = fopen("Account_Details.dat", "ab+");

    if(fp == NULL)
    {
        exit(1);
    }

	printf("Inserire il numero del conto");
    fflush(stdin);
    gets(AcNo);


    while( fread(&s, sizeof(struct Intestatario), 1, fp) == 1 )
    {
		if(strcmp(AcNo , s.NumeroAccount)==0)
		{
			flag=1;
			break;
		}
	}

	fclose(fp);

	if(flag==0)
	{
		printf("Per favore inserisci un numero valido\n");
	}
	else{

		printf("\nBenvenuto/a %s\n",s.nome);

		PINMenu:
		printf("\nPer favore, inserisci il PIN\n");
		scanf("%d",&pin);

		if(pin==s.pin)
		{
			MenuPrincipale();
		}

		else
		{
			printf(" PIN sbagliato , riprova\n");
			count++;
			if(count!=3)
				goto PINMenu;
			else
				printf("\nRiprova tra qualche minuto.\n");
		}
	}
}

int main()
{
	VerificaCarta();
	return 0;
}
