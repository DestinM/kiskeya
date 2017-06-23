#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <unistd.h>   //_getch
#include <termios.h>  //_getch

int main(int argc, char const *argv[])
{
	/* code */
	char *nom[] = {
		"jean", "joseph"
	};

	printf("nom 3: ");
	fgets(&nom[3], sizeof(&nom[3]), stdin);
	printf("nom 4: ");
	fgets(&nom[4], sizeof(&nom[4]), stdin);
	//scanf("%s",&nom[3]);
/*	printf("nom 4: ");
	fgets(&nom[4], sizeof(&nom[3]), stdin);

*/
	//nom[3] = &entrer;

	printf("%s\n", &nom[3]);
	printf("%s\n", &nom[4]);




	return 0;
}