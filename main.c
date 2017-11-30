/*
Name:Prokopios Stamelias
AM 1115201400190
*/
#include <stdio.h>
#include <stdlib.h>
#include "Session.h"

void print_options()
{
		printf("---------------------------------------\n");
		printf("Type 1  for SessionNew\n");
		printf("Type 2  for SessionNewTab\n");
		printf("Type 3  for SessionAddressShow\n");
		printf("Type 4  for SessionTabNext\n");
		printf("Type 5  for SessionTabPrev\n");
		printf("Type 6  for SessionTabMoveLeft\n");
		printf("Type 7  for SessionTabMoveRight\n");
		printf("Type 8  for SessionNewOpeningAddress\n");
		printf("Type 9  for SessionShowOpeningAddress\n");
		printf("Type 10 for SessionSiteNext\n");
		printf("Type 11 for SessionSitePrev\n");
		printf("Type 12 for SessionTabClose\n");
		printf("Type 13 for SessionClose\n");
		printf("Type 14 for SessionNewAddress\n");
		printf("Type 15 for Bonus SessionOpenNewTab\n");
		printf("Type -1 for exit Session Method\n");
		printf("---------------------------------------\n");
}
int main(int argc, char *argv[]) {
	InfoSessionPtr 	MySession=NULL;
	char str1[100],str2[100],str3[100];
	int epilogi;
	do{
		print_options();
		scanf("%d",&epilogi);
		switch(epilogi){
			case 1:
				MySession=SessionNew("http://www.di.uoa.gr/");
				break;
			case 2:
				printf("Give the Address\n");
				scanf("%s",str3);
				SessionNewTab(&MySession,str3);
				break;
			case 3:
				SessionAddressShow(MySession);
				break;
			case 4:
				SessionTabNext(&MySession);
				break;
			case 5:
				SessionTabPrev(&MySession);
				break;
			case 6:
				SessionTabMoveLeft(&MySession);
				break;
			case 7:
				SessionTabMoveRight(&MySession);
				break;
			case 8:
				printf("\nGive the Address\n");
				scanf("%s",str1);
				SessionNewOpeningAddress(&MySession,str1);
				break;
			case 9:
				SessionShowOpeningAddress(MySession);
				break;
			case 10:
				SessionSiteNext(&MySession);
				break;
			case 11:
				SessionSitePrev(&MySession);
				break;
			case 12:
				SessionTabClose(&MySession);
				break;
			case 13:
				SessionClose(&MySession);
				break;
			case 14:
				printf("Give the address of new Site\n");
				scanf("%s",str2);
				SessionNewAddress(&MySession,str2);
				break;
			default:
				SessionOpenNewTab(&MySession);
				break;
		}	
	}while(epilogi!=-1);
	return 0;
}
