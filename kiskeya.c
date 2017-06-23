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

	
	printf("%s\t\t",usernameData[i] );
	printf("%s\n",passwordData[i] );
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



//pr controler les ajous pour les clients
int NbreAjoutPourClient  = -1;

//client data 
char *nom[];
char *Prenom[];	
int id[];
char *adresse[];
char *telephone[];
char *email[];
long noCarte[];
double limiteCredit[9];
double disponibilite[9];
double dette[9];
double interet[9];
double penaliter[9];
double minimumApayer[9];
double achat[9];




void EffectuerBilling(int i){
	if (achat[i-1] != 0)
	{
		dette [i-1] = achat [i-1] + interet[i-1] + penaliter [i-1]; 
		disponibilite[i-1] = limiteCredit[i-1] - dette[i-1];
		penaliter [ i-1] = 0.03 * dette [i-1];
		interet[i-1] = 0.0333 * dette[i-1];
		minimumApayer[i-1] = 0.06 * dette [i-1];
		achat[i-1] = 0;
		printf("Billing reussie\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{
		printf("Billing deja effectuer sur l achat\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
}
void MenuEffectuerBilling(){
	char choix;
	if(NbreAjoutPourClient==-1){

		printf("il n existe pas encore de client\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{


		
		if(NbreAjoutPourClient!=-1){
			printf("presser un numero pour effectuer un billing\n\n");
			printf("\tnom\t\tPrenom\t\tId\n");

			int i;

			for (i = 0; i < NbreAjoutPourClient+1; ++i)
			{
				printf("(%d)\t",i+1 );
				printf("%s\t\t",&nom[i] );
				printf("%s\t\t",&Prenom[i] );
				printf("%d\n",id[i] );
			}
			scanf("%s",&choix);

			while( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6' && choix!='7' && choix!='8' && choix!='9'){
				system("clear");
				printf("mauvais choix\n");
				MenuEffectuerBilling();
			}
			system("clear");
			EffectuerBilling(choix-'0');
		}
	}
}
void PasserRenverssement(int i){
	double montant;
	printf("Entrer le montant:");
	scanf("%lf",&montant);
	disponibilite[i-1] -= montant;
	printf("%d\n",i-1 );
	printf("%lf\n", disponibilite[i-1]);
	printf("renversement reussie\n");

	printf("\n\npress any key to continue");
	getch();
	system("clear");
	userInterface();
}
void MenuPasserRenversement(){
	char choix;
	if(NbreAjoutPourClient==-1){

		printf("il n existe pas encore de client\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{
		
		if(NbreAjoutPourClient!=-1){
			printf("presser un numero pour passer un paiement\n\n");
			printf("\tnom\t\tPrenom\t\tId\n");

			int i;

			for (i = 0; i < NbreAjoutPourClient+1; ++i)
			{
				printf("(%d)\t",i+1 );
				printf("%s\t\t",&nom[i] );
				printf("%s\t\t",&Prenom[i] );
				printf("%d\n",id[i] );
			}
			scanf("%s",&choix);
			if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6' && choix!='7' && choix!='8' && choix!='9'){
				system("clear");
				printf("mauvais choix\n");
				MenuPasserRenversement();
			}
			system("clear");
			PasserRenverssement(choix-'0');
		}
	}
}
void PasserPaiement(int i){
	double montant;
	printf("Entrer le montant:");
	scanf("%lf",&montant);

	achat[i-1] = montant;
	
	disponibilite[i-1] += montant;
	printf("%lf\n", disponibilite[i-1]);
	printf("paiement reussie\n");

	printf("\n\npress any key to continue");
	getch();
	system("clear");
	userInterface();
}
void MenuPasserPaiement(){
	char choix;
	if(NbreAjoutPourClient==-1){

		printf("il n existe pas encore de client\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{
		
		if(NbreAjoutPourClient!=-1){
			printf("presser un numero pour passer un paiement\n\n");
			printf("\tnom\t\tPrenom\t\tId\n");

			int i;

			for (i = 0; i < NbreAjoutPourClient+1; ++i)
			{
				printf("(%d)\t",i+1 );
				printf("%s\t\t",&nom[i] );
				printf("%s\t\t",&Prenom[i] );
				printf("%d\n",id[i] );
			}
			scanf("%s",&choix);
			if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6' && choix!='7' && choix!='8' && choix!='9'){
				system("clear");
				printf("mauvais choix\n");
				MenuPasserPaiement();
			}
			system("clear");
			PasserPaiement(choix-'0');
		}
	}
}
void AjouterClient(){
	NbreAjoutPourClient++;
	if (NbreAjoutPourClient!=10)
	{
		printf("\nAjout d u n client\n\n");
		printf("Entrer son nom:");
		scanf("%s",&nom[NbreAjoutPourClient]);
		printf("Entrer son Prenom:");
		scanf("%s",&Prenom[NbreAjoutPourClient]);
		// fgets(&Prenom[NbreAjoutPourClient], sizeof(&Prenom[NbreAjoutPourClient]), stdin);
		printf("Entrer l adresse:");
		scanf("%s",&adresse[NbreAjoutPourClient]);
		printf("Entrer l telephone:");
		scanf("%s",&telephone[NbreAjoutPourClient]);
		printf("Entrer l email:");
		scanf("%s",&email[NbreAjoutPourClient]);

		noCarte[NbreAjoutPourClient] = NbreAjoutPourClient +99;

		limiteCredit[NbreAjoutPourClient] = 0.0;

		disponibilite[NbreAjoutPourClient] = 0.0;

		dette[NbreAjoutPourClient] = 0.0;

		interet[NbreAjoutPourClient] = 0.0;

		penaliter[NbreAjoutPourClient] = 0.0;

		minimumApayer[NbreAjoutPourClient] = 0.0;

		id[NbreAjoutPourClient] = NbreAjoutPourClient+1;
		

		printf("\n\nInscription reussie\n");

		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{
		printf("systeme concue pour 10 clients seulement\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	

}

void InfoSurClient(int i){
	printf("affichage des infos\n\n");
	printf("nom\tprenom\tid\tadresse\ttelephone\temail\tnoCarte\tlimiteCredit\tdisponibilite\tdette\t\tinteret\t\tpenaliter\tminimumApayer\n\n");
	
	printf("%s\t",&nom[i-1] );
	printf("%s\t",&Prenom[i-1] );
	printf("%d\t",id[i-1] );
	printf("%s\t",&adresse[i-1] );
	printf("%s\t\t",&telephone[i-1] );
	printf("%s\t",&email[i-1] );
	printf("%ld\t",noCarte[i-1] );
	printf("%lf\t",limiteCredit[i-1] );
	printf("%lf\t",disponibilite[i-1] );
	printf("%lf\t",dette[i-1] );
	printf("%lf\t",interet[i-1] );
	printf("%lf\t",penaliter[i-1] );
	printf("%lf\n",minimumApayer[i-1] );
	printf("\n\npress any key to continue");
	getch();
	system("clear");
	userInterface();
}

void MenuInfoSurClient(){
	char choix;
	if(NbreAjoutPourClient==-1){

		printf("il n existe pas encore de client\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{
		
		if(NbreAjoutPourClient!=-1){
			printf("presser un numero pour afficher plus d information\n\n");
			printf("\tnom\t\tPrenom\t\tId\n");

			int i;

			for (i = 0; i < NbreAjoutPourClient+1; ++i)
			{
				printf("(%d)\t",i+1 );
				printf("%s\t\t",&nom[i] );
				printf("%s\t\t",&Prenom[i] );
				printf("%d\n",id[i] );
			}
			scanf("%s",&choix);
			if( choix!='1' && choix!='2' && choix!='3' && choix!='4' && choix!='5' && choix!='6' && choix!='7' && choix!='8' && choix!='9'){
				system("clear");
				printf("mauvais choix\n");
				MenuInfoSurClient();
			}
			system("clear");
			InfoSurClient(choix-'0');
		}
	}
	
}


void listeClient(){
	if(NbreAjoutPourClient==-1){

		printf("il n existe pas encore de client\n");
		printf("\n\npress any key to continue");
		getch();
		system("clear");
		userInterface();
	}
	else{
		
		if(NbreAjoutPourClient!=-1){
			printf("affichage de la liste des clients\n\n");
			printf("nom\t\tPrenom\t\t\tId\n\n");

			int i;

			for (i = 0; i < NbreAjoutPourClient+1; ++i)
			{
				printf("%s\t\t",&nom[i] );
				printf("%s\t\t\t",&Prenom[i] );
				printf("%d\n",id[i] );
			}
			printf("\n\npress any key to continue");
			getch();
			system("clear");
			userInterface();
		}
	}

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
			MenuEffectuerBilling();
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

void initAchat(){
	int i;
	for (i = 0; i < 9; ++i)
	{
		achat[i] = 0;
	}
}



int main(int argc, char const *argv[])
{
	initAchat();
	
	login();
	return 0;
}