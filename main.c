#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "definities.h"
int months[] = {31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	time_t rawTime;
	struct tm *timeString;
	int currentDay, currentMonth;

void txtInput(char tmpString[]){
	fgets(tmpString, 32, stdin);
	int c;
	char *end;

	if((end = strchr(tmpString, '\n')) != NULL){
		*end = '\0';
		return;
	}

	while((c = getchar()) != EOF && c != '\n');
}

int main(){
	char commandString[32];
	tabelBoodschappen activeTable[MAX];
	readIn(activeTable);

	time(&rawTime);
	timeString = localtime(&rawTime);
	currentDay = timeString->tm_mday;
	currentMonth = timeString->tm_mon;

	do{
		printf(">> ");
		txtInput(commandString);


		if (strcmp(commandString, "save") == 0){
			writeOut(activeTable);
		}
		else if (strcmp(commandString, "add") == 0){
			tableEntry(activeTable);
		}
		else if (strcmp(commandString, "mod") == 0){
			tableModify(activeTable);
		}
		else if (strcmp(commandString, "rmv") == 0){
			tableRemove(activeTable);
		}
		else if (strcmp(commandString, "help") == 0){
			printf("this is the commandlist\n");
		}
		else if(strcmp(commandString, "exit") == 0){
			break;
		}
		else if (strcmp(commandString, "show") == 0){
			tablePrint(activeTable);
		}
		else if (strcmp(commandString, "sort") == 0){
			printf(">> Select sorting style (name, id) ");
			int check = 0;
			while(check == 0){
				txtInput(commandString);
				if (strcmp(commandString, "name") == 0){
					stringSort(activeTable);
					check++;
				}
				else if (strcmp(commandString, "id") == 0){
					intSort(activeTable, 0, tableSize-1);
					printf("** SORTING COMPLETED");
					check++;
				}
				else{
					printf("   INVALID SORTING STYLE, PLEASE TRY AGAIN");
				}
			}
		}
		else if (strcmp(commandString, "search") == 0){
				tableSearch(activeTable);
		}
		else if (strcmp(commandString, "convert") == 0){
			convertDate(activeTable);
		}
		else if (strcmp(commandString, "export") == 0){
			listCreate(activeTable);
		}
		else if (strcmp(commandString, "import") == 0){
			listImport(activeTable);
		}
		else{
			printf("   INVALID COMMAND ENTER 'help' FOR A LIST OF COMMANDS");
		}
		printf("\n");
	}while(strcmp(commandString, "exit"));
    return 0;
}
