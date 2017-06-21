#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>   //_getch
#include <termios.h>  //_getch

//global variable

//controller les tentatives
int tentatives = 1;
//verifier si l utilisateur existe
int isExist = 0;
//nbre d utilisateur desactiver
int NbredeDesactivation = 0;



//utilisateurs et admin data
char *usernameData[]  = {"admin", "jean","joseph","junior","david","blanc" };
char *passwordData[]   = {"admin", "jean123","joseph2017","junior2014","david22","blanc35"};


//pour gerer les activations et les desactivations
char *usernameDataVerif[]  = {"admin", "jean","joseph","junior","david","blanc" };
char *passwordDataVerif[]   = {"admin", "jean123","joseph2017","junior2014","david22","blanc35"};



// ****************************************
// ************ADMIN PART******************
// ****************************************



//function getch linux
char getch(){
    char buf=0;
    struct termios old={0};
    fflush(stdout);
    if(tcgetattr(0, &old)<0)
        perror("tcsetattr()");
    old.c_lflag&=~ICANON;
    old.c_lflag&=~ECHO;
    old.c_cc[VMIN]=1;
    old.c_cc[VTIME]=0;
    if(tcsetattr(0, TCSANOW, &old)<0)
        perror("tcsetattr ICANON");
    if(read(0,&buf,1)<0)
        perror("read()");
    old.c_lflag|=ICANON;
    old.c_lflag|=ECHO;
    if(tcsetattr(0, TCSADRAIN, &old)<0)
        perror ("tcsetattr ~ICANON");
    return buf;
 }
 void ActiverSurUser(int i){
	printf("affichage des infos\n\n");
	printf("username\tpassword\n\n");
	
		printf("%s\t\t",usernameData[i-1] );
		printf("%s\n",passwordData[i-1] );
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		adminInterface();
}

void changerPasswordUser(int i){

	char newPassword[50] ;

	printf("i = %d\n", i);

	printf("Entrer nouveau mot de passe\n");
	scanf("%s",&newPassword);
	passwordDataVerif[i] = &newPassword;

	printf("succes\n");

	printf("\n\npress any key to continue");
	getch();
	system("clear");
	adminInterface();

}
void MenuchangerPasswordUser(){
	int i;
	char choix;
	printf("presser un numero pour changer le mot de passe d un utilisateu\n\n");

	for (i = 1; i < 6; ++i)
	{	
		
		printf("%d)\t", i);
		printf("%s\n",usernameData[i]);
	}

	
		scanf("%d",&choix);
		if( choix!=1 && choix!=2 && choix!=3 && choix!=4 && choix!=5){
			system("clear");
			printf("mauvais choix\n");
		    MenuchangerPasswordUser();
		}
	system("clear");
	changerPasswordUser(choix);
}

void ActiverUser(int i){

	int c=6;
	int l;
	
		for (c = 1; c < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0])); ++c)
		{
			 if (usernameDataVerif[i] == usernameData[i])
			{
				
				isExist  = 1;
				printf("compte deja activer\n");
				break;
				
			}
			
		}

		
		if (isExist==0)
		{
			while(c>i) {
			    usernameDataVerif[c] = usernameDataVerif[c-1];
     		    passwordDataVerif[c] = passwordDataVerif[c-1];
     		    c--;
			}
			usernameDataVerif[i] = usernameData[i];
			passwordDataVerif[i] = passwordData[i];
			NbredeDesactivation--;

			for (l = 1; l < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0]))-NbredeDesactivation; ++l)
		    {
		    	printf("%s\n",usernameDataVerif[l]);
		    }
		}
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		adminInterface();
}

void MenuActiverUser(){
	int i,choix;
	printf("presser un numero pour activer un utilisateur\n\n");

	for (i = 1; i < 6; ++i)
	{	
		
		printf("%d)\t", i);
		printf("%s\n",usernameData[i]);
	}

	while((!scanf("%d",&choix)) || choix > 5) {
	    system("clear");
	    printf("mauvais choix\n");
	    MenuActiverUser();
	}
	system("clear");
	isExist = 0;
	ActiverUser(choix);
}

void DesactiverUser(int i){

	int c,l;
	NbredeDesactivation++;
	
	for ( c = i  ; c < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0])) - NbredeDesactivation ; c++ )
	{
         usernameDataVerif[c] = usernameDataVerif[c+1];
     	 passwordDataVerif[c] = passwordDataVerif[c+1];
    }
    printf("desactivation reussie\n\n");
    for (l = 1; l < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0]))-NbredeDesactivation; ++l)
    {
    	printf("%s\n",usernameDataVerif[l]);
    }
	printf("\n\npress any key to continue");
	getch();
	system("clear");
	adminInterface();
}

void MenuDesactiverUser(){
	int i;
	char choix;
	printf("presser un numero pour desactiver un utilisateur\n\n");

	for (i = 1; i < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0]))-NbredeDesactivation; ++i)
	{	
		
		printf("%d)\t", i);
		printf("%s\n",usernameDataVerif[i]);
	}

	scanf("%s",&choix);
	if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5'){
		system("clear");
		printf("mauvais choix\n");
	    MenuDesactiverUser();
	}
	system("clear");
	DesactiverUser(choix-'0');
}

void listeUtilisateur(){
	int i;
	printf("affichage de la liste des utilisateurs\n\n");

	for (i = 1; i < 6; ++i)
	{
		printf("%s\n",usernameData[i] );
	}
	printf("\n\npress any key to continue");
	getch();
	system("clear");
	adminInterface();
}

void InfoSurUser(int i){
	printf("affichage des infos\n\n");
	printf("status\tusername\tpassword\n\n");

		int c = 1;
		for (c = 1; c < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0])); ++c)
		{
			 if (usernameDataVerif[i] == usernameData[i])
			{
				
				printf("actif\t");
				break;
				
			} else {
				printf("inactif\t");
				break;
			}
			
		}

	
		printf("%s\t\t",usernameDataVerif[i] );
		printf("%s\n",passwordDataVerif[i] );
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		adminInterface();
}

void MenuInfoSurUser(){
	int i;
	char choix;
	printf("presser un numero pour avoir plus d info sur un utilisateur\n\n");

	for (i = 1; i < 6; ++i)
	{	
		
		printf("(%d)\t", i);
		printf("%s\n",usernameData[i]);
	}

	scanf("%s",&choix);
	if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5'){
		system("clear");
		printf("mauvais choix\n");
		MenuInfoSurUser();
	}
	system("clear");
	InfoSurUser(choix-'0');
}

void adminInterface(){
	char choix;
	printf("\t\t\t\t\t\t\t\t\tNom de l’Institution financière\n");
	printf("\t\t\t\t\t\t\t\t\tInterface administrateur\n\n\n\n");
	printf("\t\t\t\t\t-----------------------------------------------------------------------------------------------\n\n");
	printf("\tPressez\n\n\n");
	printf("(1) Afficher la liste des utilisateurs\n");
	printf("(2) Afficher les informations sur un utilisateur:\n");
	printf("(3) Activer le compte d un utilisateur:\n");
	printf("(4) Desactiver le compte d un utilisateur:\n");
	printf("(5) changer le mot de passe d un utilisateur:\n");
	printf("(6) Sortir du systeme:\n");


	scanf("%s",&choix);
	if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6'){
		system("clear");
		printf("mauvais choix\n");
		adminInterface();
	}

	switch (choix){
		case '1':{
			system("clear");
			listeUtilisateur();
		}
		break;
		case '2':{
			system("clear");
			MenuInfoSurUser();
		}
		break;
		case '3':{
			system("clear");
			MenuActiverUser();
		}
		break;
		case '4':{
			system("clear");
			MenuDesactiverUser();
		}
		break;
		case '5':{
			system("clear");
			MenuchangerPasswordUser();
		}
		break;
		case '6':{
			system("clear");
			isExist = 0;
			login();
		}
		break;
	}

}



// ****************************************
// ************USER PART******************
// ****************************************


//client data 

char *NomPrenom[] = {"Joseph Emmanuel"};	
char *ID[]	={"123-456-789-0"};
char *Adresse[] = {	 "Ave JP II #218,Turg,P-au-P"};
char *Telephone[]	= {"50939999999"};
char *Email[] = {"abc@abc.com"};
char *NoCarte[]	={	 "8763-3546-7876-3456"}	;
double LimiteDeCredit[]={100.0};
double Disponibilite[]	={74157.5};
double Dette[]={25832.0};
double Interet[]={832.50};
double Penaliter[] ={0.0};
double MinimumApayer[]	={1549.95};


void PasserRenverssement(int i){

}
void MenuPasserRenversement(){
	int i,transformToInt;
	char choix;
	printf("presser un numero pour avoir plus d info sur un client\n\n");

	for (i = 0; i <  (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])); ++i)
	{	
		
		printf("(%d)\t", i+1);
		printf("%s\n",NomPrenom[i]);
	}

	scanf("%s",&choix);
	transformToInt = choix - '0';
	if( transformToInt > (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])) || transformToInt == 0){
		system("clear");
		printf("mauvais choix\n");
	}
	system("clear");
	PasserRenverssement(transformToInt);
}
void PasserPaiement(int i){

}
void MenuPasserPaiement(){
	int i,transformToInt;
	char choix;
	printf("presser un numero pour avoir plus d info sur un client\n\n");

	for (i = 0; i <  (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])); ++i)
	{	
		
		printf("(%d)\t", i+1);
		printf("%s\n",NomPrenom[i]);
	}

	scanf("%s",&choix);
	transformToInt = choix - '0';
	if( transformToInt > (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])) || transformToInt == 0){
		system("clear");
		printf("mauvais choix\n");
	}
	system("clear");
	PasserPaiement(transformToInt);
}
void AjouterClient(){
	char nom[50];
	char prenom[50];
	printf("\nAjout d u n client\n\n");
	printf("Entrer son nom\n");
	scanf("%s",&NomPrenom[(int)(sizeof(NomPrenom)/sizeof(NomPrenom[0]))+1]);
	printf("Entrer l Adresse\n");
	scanf("%s",&Adresse[(int)(sizeof(Adresse)/sizeof(Adresse[0]))+1]);
	printf("Entrer l Telephone\n");
	scanf("%s",&Telephone[(int)(sizeof(Telephone)/sizeof(Telephone[0]))+1]);
	printf("Entrer l email\n");
	scanf("%s",&Email[(int)(sizeof(Email)/sizeof(Email[0]))+1]);
	printf("Entrer l NoCarte\n");
	scanf("%s",&NoCarte[(int)(sizeof(NoCarte)/sizeof(NoCarte[0]))+1]);

	LimiteDeCredit[(int)(sizeof(LimiteDeCredit)/sizeof(LimiteDeCredit[0]))] = 0.0;

	Disponibilite[(int)(sizeof(Disponibilite)/sizeof(Disponibilite[0]))] = 0.0;

	Dette[(int)(sizeof(Dette)/sizeof(Dette[0]))] = 0.0;

	Interet[(int)(sizeof(Interet)/sizeof(Interet[0]))] = 0.0;

	Penaliter[(int)(sizeof(Penaliter)/sizeof(Penaliter[0]))] = 0.0;

	MinimumApayer[(int)(sizeof(MinimumApayer)/sizeof(MinimumApayer[0]))] = 0.0;

	printf("Inscription reussie\n");
	printf("\n\npress any key to continue");
	getch();
	system("clear");
	userInterface();

}

void InfoSurClient(int i){
	printf("affichage des infos\n\n");
	printf("nom\tprenom\tID\t\tAdresse\t\t\t\tTelephone\tEmail\t\tNoCarte\t\t\tLimiteDeCredit\tDisponibilite\tDette\tInteret\tPenaliter\tMinimumApayer\n\n");
	
		printf("%s\t",NomPrenom[i-1] );
		printf("%s\t",ID[i-1] );
		printf("%s\t",Adresse[i-1] );
		printf("%s\t",Telephone[i-1] );
		printf("%s\t",Email[i-1] );
		printf("%s\t",NoCarte[i-1] );
		printf("%f\t",LimiteDeCredit[i-1] );
		printf("%f\t",Disponibilite[i-1] );
		printf("%f\t",Dette[i-1] );
		printf("%f\t",Interet[i-1] );
		printf("%f\t",Penaliter[i-1] );
		printf("%f\n",MinimumApayer[i-1] );
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
}

void MenuInfoSurClient(){
	int i,transformToInt;
	char choix;
	printf("presser un numero pour avoir plus d info sur un client\n\n");

	for (i = 0; i <  (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])); ++i)
	{	
		
		printf("(%d)\t", i+1);
		printf("%s\n",NomPrenom[i]);
	}

	scanf("%s",&choix);
	transformToInt = choix - '0';
	if( transformToInt > (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])) || transformToInt == 0){
		system("clear");
		printf("mauvais choix\n");
	}
	system("clear");
	InfoSurClient(transformToInt);
}


void listeClient(){
	int i;
	printf("affichage de la liste des clients\n\n");

	for (i = 0; i < (int)(sizeof(NomPrenom)/sizeof(NomPrenom[0])); ++i)
	{
		printf("%s\n",NomPrenom[i] );
	}
	printf("\n\npress any key to continue");
	getch();
	system("clear");
	userInterface();
}

void userInterface(){
	char choix;
	printf("\t\t\t\t\t\t\t\t\tNom de l’Institution financière\n");
	printf("\t\t\t\t\t\t\t\t\tInterface utilisateur\n\n\n\n");
	printf("\t\t\t\t\t-----------------------------------------------------------------------------------------------\n\n");
	printf("\tPressez\n\n\n");
	printf("(1) Afficher la liste des clients\n");
	printf("(2) Afficher les informations sur un clients:\n");
	printf("(3) Ajouter un nouveau client:\n");
	printf("(4) Passer un paiement:\n");
	printf("(5) Passer un renversement:\n");
	printf("(6) Effectuer un billing:\n");
	printf("(7) Sortir du systeme:\n");

	scanf("%s",&choix);
	if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6' && choix!='7'){
		system("clear");
		printf("mauvais choix\n");
		userInterface();
	}

	switch (choix){
		case '1':{
			system("clear");
			listeClient();
		}
		break;
		case '2':{
			system("clear");
			MenuInfoSurClient();
		}
		break;
		case '3':{
			system("clear");
			AjouterClient();
		}
		break;
		case '4':{
			system("clear");
			MenuPasserPaiement();
		}
		break;
		case '5':{
			system("clear");
			MenuPasserRenversement();
		}
		break;
		case '6':{
			system("clear");
			// EffectuerBilling();
		}
		break;
		case '7':{
			system("clear");
			login();
			isExist = 0;
		}
		break;
	}
}

void login(){
	
	char username[50],password[50];
	printf("\t\t\t\t\t\t\t\t\tNom de l’Institution financière\n");
	printf("\t\t\t\t\t\t\t\t\t\tAuthentification\n\n\n\n");
	printf("\t\t\t\t\t-----------------------------------------------------------------------------------------------\n\n");
	printf("\t\t\t\t\t\t\tSaisissez votre mot de passe et appuyez sur entrer !\n\n\n");
	printf("Nom utilisateur:");
	scanf("%s", &username);
	printf("Mot de passe:");
	scanf("%s", &password);



	int i ;

	

	if(tentatives<3) {


		// do
		// {
		// 	printf("mauvais identifiant\n");
		// 	tentatives++;
		// 	login();
		// } while (strlen(username) > 50 || strlen(password) > 50);


		for (i = 0; i < (int)(sizeof(usernameDataVerif)/sizeof(usernameDataVerif[0])); ++i)
		{
			 if ( (strcmp(username,usernameDataVerif[i]) == 0) && (strcmp(password,passwordDataVerif[i]) == 0) )
			{
				if ((strcmp(username,usernameDataVerif[0]) == 0) && (strcmp(password,passwordDataVerif[0]) == 0))
				{
					tentatives = 1;
					isExist  = 1;
					system("clear");
					adminInterface();
				}
				else{
					isExist  = 1;
					tentatives =1;
					system("clear");
					userInterface();
				}
			}
			
		}

		if (isExist==0)
		{
			system("clear");
			printf("\n\nmauvais identifiant\n");
			tentatives++;
			login();
		}
		
		  
	}

	else
	{
		printf("desactivation\n");
	}
		

}



int main(int argc, char const *argv[])
{
	
	 login();
	return 0;
}