#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "definities.h"
#define MAX 1000

int retry = 0;
int tableSize = 0;

void readIn(tabelBoodschappen activeTable[]){		//Opening the .csv file to use in program
	FILE *inputFile;
	inputFile = fopen("boodschappenTabel.csv", "r");

	if(inputFile == NULL){
		fprintf(stderr, "\nCan't open input file\n");
		return;
	}

	fscanf(inputFile, "%d", &tableSize);
	int i;
	for(i = 0; i < tableSize; i++){
		fscanf(inputFile, "%d,%s ,%s ,%f,%d,%d/%d,%d/%d,%f,%f",
				&activeTable[i].id, activeTable[i].name, activeTable[i].category, &activeTable[i].price, &activeTable[i].amount, &activeTable[i].buyDay, &activeTable[i].buyMonth, &activeTable[i].emptyDay, &activeTable[i].emptyMonth, &activeTable[i].currentStock, &activeTable[i].avgUseDay);
	}

	fclose(inputFile);
}

void writeOut(tabelBoodschappen activeTable[]){		//saving data to .csv file
	remove("boodschappenTabel.csv");
	FILE *outputFile;
	outputFile = fopen("boodschappenTabel.csv", "w");

	fprintf(outputFile, "%d\n", tableSize);
	for(int i = 0; i < tableSize; i++){
		fprintf(outputFile, "%d,%s ,%s ,%f,%d,%d/%d,%d/%d,%f,%f\n",
				activeTable[i].id, activeTable[i].name, activeTable[i].category, activeTable[i].price, activeTable[i].amount, activeTable[i].buyDay, activeTable[i].buyMonth, activeTable[i].emptyDay, activeTable[i].emptyMonth, activeTable[i].currentStock, activeTable[i].avgUseDay);
	}
	fclose(outputFile);
	printf("** SAVE SUCCESSFULL");
}

void tableEntry(tabelBoodschappen activeTable[]){
	char tmpString[64];

	int i = tableSize;
	printf("\n\n** NEW ENTRY ON ROW %d\n", i+1);


	if(tableSize == 0){
		activeTable[i].id = 1000;
	}
	else{
		activeTable[i].id = searchHighestID(activeTable, tableSize)+1;
	}


	printf(">> name: ");
	txtInput(tmpString);
	strcpy(activeTable[i].name, &tmpString);

	printf(">> category: ");
	txtInput(tmpString);
	strcpy(activeTable[i].category, &tmpString);

	printf(">> unit price: ");
	txtInput(tmpString);
	activeTable[i].price = strtof(tmpString, NULL);

	printf(">> unit size(g/ml/quantity): ");
	txtInput(tmpString);
	activeTable[i].amount = strtol(tmpString, NULL, 10);

	printf(">> last purchased: ");
	txtInput(tmpString);

	activeTable[i].buyDay = strtok(tmpString, "/");
	activeTable[i].buyMonth = strtok(NULL, "/");
	activeTable[i].buyDay = atoi(activeTable[i].buyDay);
	activeTable[i].buyMonth = atoi(activeTable[i].buyMonth);

	printf(">> current amount: ");
	txtInput(tmpString);
	activeTable[i].currentStock = strtof(tmpString, NULL);

	printf(">> average use per day: ");
	txtInput(tmpString);
	activeTable[i].avgUseDay = strtof(tmpString, NULL);

	dayCalc(activeTable, i);



	printf("\n** PLEASE CONFIRM ENRTY");
	printf("\n   ID: %d || Name: %s || Category: %s \n   Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d \n   Stock: %.2f || Avg. Daily use: %.2f",
			activeTable[i].id, activeTable[i].name, activeTable[i].category, activeTable[i].price, activeTable[i].amount, activeTable[i].buyDay, activeTable[i].buyMonth, activeTable[i].emptyDay, activeTable[i].emptyMonth, activeTable[i].currentStock, activeTable[i].avgUseDay);
	printf("\n>> Is this correct (yes/no)? ");
	txtInput(tmpString);
	if(tmpString[0] == 'n'){
		tableEntry(activeTable);
		retry++;
	}

	if(retry > 0){
		printf("** ITEM SUCCESSFULLY ADDED TO THE TABLE");
		tableSize++;
		retry = 0;
	}

}

void tableModify(tabelBoodschappen activeTable[]){
	int results;
	char searchterm[32];
	char tmpString[32];
	int positionArray[100];

	printf(">> Enter a searching style (name, category, id): ");
	txtInput(tmpString);

	if(strcmp(tmpString, "name") == 0){
		printf(">> Enter a search term: ");
		txtInput(searchterm);
		results = searchName(searchterm, activeTable, positionArray);
	}
	else if(strcmp(tmpString, "category") == 0){
		printf(">> Enter a search term: ");
		txtInput(searchterm);
		results = searchCategory(searchterm, activeTable, positionArray);
	}
	else if(strcmp(tmpString, "id") == 0){
		printf(">> Enter a search term: ");
		txtInput(searchterm);
		results = searchID(searchterm, activeTable, positionArray);
	}
	else{
		printf("   INVALID SORTING STYLE, PLEASE TRY AGAIN");
		tableRemove(activeTable);
	}



	if(results == 0){
		printf("   NO RESULTS FOUND\n");
		printf(">> Do you want to try another search? (yes/no)");
		txtInput(tmpString);
		if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
			tableRemove(activeTable);
		}
	}
	else if (results == 1){
		printf("\n  ID: %d || Name: %s || Category: %s || Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d || Stock: %.2f || Avg. Daily use: %.2f",
					 activeTable[positionArray[0]].id, activeTable[positionArray[0]].name, activeTable[positionArray[0]].category, activeTable[positionArray[0]].price, activeTable[positionArray[0]].amount, activeTable[positionArray[0]].buyDay, activeTable[positionArray[0]].buyMonth, activeTable[positionArray[0]].emptyDay, activeTable[positionArray[0]].emptyMonth, activeTable[positionArray[0]].currentStock, activeTable[positionArray[0]].avgUseDay);
		printf("\n>> Is this the item you want to modify? (yes/no)");
		txtInput(tmpString);
		if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
			printf(">> name: ");
			txtInput(tmpString);
			strcpy(activeTable[positionArray[0]].name, &tmpString);

			printf(">> category: ");
			txtInput(tmpString);
			strcpy(activeTable[positionArray[0]].category, &tmpString);

			printf(">> unit price: ");
			txtInput(tmpString);
			activeTable[positionArray[0]].price = strtof(tmpString, NULL);

			printf(">> unit size(g/ml/quantity): ");
			txtInput(tmpString);
			activeTable[positionArray[0]].amount = strtol(tmpString, NULL, 10);

			printf(">> last purchased: ");
			txtInput(tmpString);

			activeTable[positionArray[0]].buyDay = strtok(tmpString, "/");
			activeTable[positionArray[0]].buyMonth = strtok(NULL, "/");
			activeTable[positionArray[0]].buyDay = atoi(activeTable[positionArray[0]].buyDay);
			activeTable[positionArray[0]].buyMonth = atoi(activeTable[positionArray[0]].buyMonth);

			printf(">> current amount: ");
			txtInput(tmpString);
			activeTable[positionArray[0]].currentStock = strtof(tmpString, NULL);

			printf(">> average use per day: ");
			txtInput(tmpString);
			activeTable[positionArray[0]].avgUseDay = strtof(tmpString, NULL);

			dayCalc(activeTable, positionArray[0]);
			printf("** Modified entry No. %d\n", positionArray[0]);
		}
		else{
			printf(">> Do you want to try another search? (yes/no)");
			txtInput(tmpString);
			if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
				tableModify(activeTable);
			}
			else{
				printf("   NO ITEMS MODIFIED");
				return;
			}
		}
	}
	else{
		for (int i = 0; i < results; i++){
			printf("\n%d) ID: %d || Name: %s || Category: %s || Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d || Stock: %.2f || Avg. Daily use: %.2f", i+1, activeTable[positionArray[i]].id, activeTable[positionArray[i]].name, activeTable[positionArray[i]].category, activeTable[positionArray[i]].price, activeTable[positionArray[i]].amount, activeTable[positionArray[i]].buyDay, activeTable[positionArray[i]].buyMonth, activeTable[positionArray[i]].emptyDay, activeTable[positionArray[i]].emptyMonth, activeTable[positionArray[i]].currentStock, activeTable[positionArray[i]].avgUseDay);
		}
		printf("\n\n0)  None of the above");
		printf("\n>> Please select the corresponding number: ");
		txtInput(tmpString);
		int choice = atoi(tmpString)-1;

		if (choice == -1){
			printf(">> Do you want to try another search? (yes/no)");
			txtInput(tmpString);
			if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
				tableModify(activeTable);
			}
			else{
				printf("   NO ITEMS DELETED");
				return;
			}
		}
		else{
			printf("\n   ID: %d || Name: %s || Category: %s \n   Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d \n   Stock: %.2f || Avg. Daily use: %.2f",
					activeTable[positionArray[choice]].id, activeTable[positionArray[choice]].name, activeTable[positionArray[choice]].category, activeTable[positionArray[choice]].price, activeTable[positionArray[choice]].amount, activeTable[positionArray[choice]].buyDay, activeTable[positionArray[choice]].buyMonth, activeTable[positionArray[choice]].emptyDay, activeTable[positionArray[choice]].emptyMonth, activeTable[positionArray[choice]].currentStock, activeTable[positionArray[choice]].avgUseDay);
			printf("\n>> Is this the item you want to delete? (yes/no)");
			txtInput(tmpString);
			if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
				printf(">> name: ");
				txtInput(tmpString);
				strcpy(activeTable[positionArray[choice]].name, &tmpString);

				printf(">> category: ");
				txtInput(tmpString);
				strcpy(activeTable[positionArray[choice]].category, &tmpString);

				printf(">> unit price: ");
				txtInput(tmpString);
				activeTable[positionArray[choice]].price = strtof(tmpString, NULL);

				printf(">> unit size(g/ml/quantity): ");
				txtInput(tmpString);
				activeTable[positionArray[choice]].amount = strtol(tmpString, NULL, 10);

				printf(">> last purchased: ");
				txtInput(tmpString);

				activeTable[positionArray[choice]].buyDay = strtok(tmpString, "/");
				activeTable[positionArray[choice]].buyMonth = strtok(NULL, "/");
				activeTable[positionArray[choice]].buyDay = atoi(activeTable[positionArray[choice]].buyDay);
				activeTable[positionArray[choice]].buyMonth = atoi(activeTable[positionArray[choice]].buyMonth);

				printf(">> current amount: ");
				txtInput(tmpString);
				activeTable[positionArray[choice]].currentStock = strtof(tmpString, NULL);

				printf(">> average use per day: ");
				txtInput(tmpString);
				activeTable[positionArray[choice]].avgUseDay = strtof(tmpString, NULL);

				dayCalc(activeTable, positionArray[choice]);
				printf("** Modified entry No. %d\n", positionArray[choice]);
			}
			else{
				printf(">> Do you want to try another search? (yes/no)");
				txtInput(tmpString);
				if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
					tableRemove(activeTable);
					printf("   ITEM REMOVED FROM LIST");
				}
				else{
					printf("   NO ITEMS MODIFY");
					return;
				}
			}
		}
	}
}

void tableRemove(tabelBoodschappen activeTable[]){
	int results;
	char searchterm[32];
	char tmpString[32];
	int positionArray[100];

	printf(">> Enter a searching style (name, category, id): ");
	txtInput(tmpString);

	if(strcmp(tmpString, "name") == 0){
		printf(">> Enter a search term: ");
		txtInput(searchterm);
		results = searchName(searchterm, activeTable, positionArray);
	}
	else if(strcmp(tmpString, "category") == 0){
		printf(">> Enter a search term: ");
		txtInput(searchterm);
		results = searchCategory(searchterm, activeTable, positionArray);
	}
	else if(strcmp(tmpString, "id") == 0){
		printf(">> Enter a search term: ");
		txtInput(searchterm);
		results = searchID(searchterm, activeTable, positionArray);
	}
	else{
		printf("   INVALID SORTING STYLE, PLEASE TRY AGAIN");
		tableRemove(activeTable);
	}



	if(results == 0){
		printf("   NO RESULTS FOUND\n");
		printf(">> Do you want to try another search? (yes/no)");
		txtInput(tmpString);
		if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
			tableRemove(activeTable);
		}
	}
	else if (results == 1){
			printf("\n  ID: %d || Name: %s || Category: %s || Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d || Stock: %.2f || Avg. Daily use: %.2f",
					 activeTable[positionArray[0]].id, activeTable[positionArray[0]].name, activeTable[positionArray[0]].category, activeTable[positionArray[0]].price, activeTable[positionArray[0]].amount, activeTable[positionArray[0]].buyDay, activeTable[positionArray[0]].buyMonth, activeTable[positionArray[0]].emptyDay, activeTable[positionArray[0]].emptyMonth, activeTable[positionArray[0]].currentStock, activeTable[positionArray[0]].avgUseDay);
		printf("\n>> Is this the item you want to delete? (yes/no)");
		txtInput(tmpString);
		if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
			int position = positionArray[0];
			removeItem(activeTable, position);
			printf("   ITEM REMOVED FROM LIST");
		}
		else{
			printf(">> Do you want to try another search? (yes/no)");
			txtInput(tmpString);
			if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
				tableRemove(activeTable);
			}
			else{
				printf("   NO ITEMS DELETED");
				return;
			}
		}
	}
	else{
		for (int i = 0; i < results; i++){
			printf("\n%d) ID: %d || Name: %s || Category: %s || Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d || Stock: %.2f || Avg. Daily use: %.2f", i+1, activeTable[positionArray[i]].id, activeTable[positionArray[i]].name, activeTable[positionArray[i]].category, activeTable[positionArray[i]].price, activeTable[positionArray[i]].amount, activeTable[positionArray[i]].buyDay, activeTable[positionArray[i]].buyMonth, activeTable[positionArray[i]].emptyDay, activeTable[positionArray[i]].emptyMonth, activeTable[positionArray[i]].currentStock, activeTable[positionArray[i]].avgUseDay);
		}
		printf("\n\n0)  None of the above");
		printf("\n>> Please select the corresponding number: ");
		txtInput(tmpString);
		int choice = atoi(tmpString)-1;

		if (choice == -1){
			printf(">> Do you want to try another search? (yes/no)");
			txtInput(tmpString);
			if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
				tableRemove(activeTable);
			}
			else{
				printf("   NO ITEMS DELETED");
				return;
			}
		}
		else{
			printf("%d", choice);
			printf("\n   ID: %d || Name: %s || Category: %s \n   Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d \n   Stock: %.2f || Avg. Daily use: %.2f",
					activeTable[positionArray[choice]].id, activeTable[positionArray[choice]].name, activeTable[positionArray[choice]].category, activeTable[positionArray[choice]].price, activeTable[positionArray[choice]].amount, activeTable[positionArray[choice]].buyDay, activeTable[positionArray[choice]].buyMonth, activeTable[positionArray[choice]].emptyDay, activeTable[positionArray[choice]].emptyMonth, activeTable[positionArray[choice]].currentStock, activeTable[positionArray[choice]].avgUseDay);
			printf("\n>> Is this the item you want to delete? (yes/no)");
			txtInput(tmpString);
			if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
				removeItem(activeTable[positionArray[choice]]);
			}
			else{
				printf(">> Do you want to try another search? (yes/no)");
				txtInput(tmpString);
				if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y") == 0){
					tableRemove(activeTable);
					printf("   ITEM REMOVED FROM LIST");
				}
				else{
					printf("   NO ITEMS DELETED");
					return;
				}
			}
		}
	}
}

void tableSearch(tabelBoodschappen activeTable[]){
	char searchTerm[32];
	char commandString[32];
	int positionArray[100];
	int results;

	printf(">> Select search style (name, id, category) ");
	txtInput(commandString);
	printf(">> Please enter a search term: ");
	txtInput(searchTerm);
	if (strcmp(commandString, "name") == 0){
		results = searchName(searchTerm, activeTable, positionArray);
	}
	else if (strcmp(commandString, "id") == 0){
		results = searchID(searchTerm, activeTable, positionArray);
	}
	else if (strcmp(commandString, "category") == 0){
		results = searchCategory(searchTerm, activeTable, positionArray);
	}
	else{
		printf("   INVALID SEARCHING STYLE, PLEASE TRY AGAIN");
		tableSearch(activeTable);
	}

	printf("** SEARCH RESULTS");
	for (int i = 0; i < results; i++){
			printf("\n%d) ID: %d || Name: %s || Category: %s || Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d || Stock: %.2f || Avg. Daily use: %.2f", i+1, activeTable[positionArray[i]].id, activeTable[positionArray[i]].name, activeTable[positionArray[i]].category, activeTable[positionArray[i]].price, activeTable[positionArray[i]].amount, activeTable[positionArray[i]].buyDay, activeTable[positionArray[i]].buyMonth, activeTable[positionArray[i]].emptyDay, activeTable[positionArray[i]].emptyMonth, activeTable[positionArray[i]].currentStock, activeTable[positionArray[i]].avgUseDay);
			printf("\n");
		}
}

void tablePrint(tabelBoodschappen activeTable[]){
	printf("** GROCERY TABLE		SIZE: %d", tableSize);
	for (int i = 0; i < tableSize; i++){
		printf("\n   ID: %d || Name: %s || Category: %s \n   Unit Price: EUR %.2f || Unit Amount: %d (gram/ml/quantity) \n   Buy date: %d/%d || Repurchase date: %d/%d \n   Stock: %.2f || Avg. Daily use: %.2f",
				activeTable[i].id, activeTable[i].name, activeTable[i].category, activeTable[i].price, activeTable[i].amount, activeTable[i].buyDay, activeTable[i].buyMonth, activeTable[i].emptyDay, activeTable[i].emptyMonth, activeTable[i].currentStock, activeTable[i].avgUseDay);
		printf("\n");
	}
}

