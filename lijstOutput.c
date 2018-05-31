#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "definities.h"

int usageCalc(float stock, float avgUse){
	int i;
	i = stock / avgUse;
	return i-1;
}

void dayCalc(tabelBoodschappen activeTable[], int i){
	int count = usageCalc(activeTable[i].currentStock, activeTable[i].avgUseDay);
	int j = 0;
	int monthCount = currentMonth;

	activeTable[i].emptyDay = currentDay + count;

	while(j == 0){
		if (activeTable[i].emptyDay > months[monthCount]){
			activeTable[i].emptyDay = activeTable[i].emptyDay - months[monthCount];
			monthCount++;
		}
		else{
			j++;
		}
	}

	activeTable[i].emptyMonth = monthCount+1;
}


// This function fulfilled his use in fixing the data
void convertDate(tabelBoodschappen activeTable[]){
	/*for (int i = 0; i < tableSize; i++){
		activeTable[i].buyDay = strtok(activeTable[i].buyDate, "/");
		activeTable[i].buyMonth = strtok(NULL, "/");

		activeTable[i].buyDay = atoi(activeTable[i].buyDay);
		activeTable[i].buyMonth = atoi(activeTable[i].buyMonth);

		dayCalc(activeTable, i);
	}
	*/
	printf("** CONVERTION FROM STRING DATE TO INT DATE COMPLETE");
}

void listCreate (tabelBoodschappen activeTable[]){
	tabelBoodschappen boodschappenLijst[100];
	int lijstLengte = 0;
	int lijstInterval = 7;
	char tmpString[32];


	for(int i = 0; i < tableSize; i++){
		if (currentDay + lijstInterval > months[currentMonth-1]){
			if (((currentDay + lijstInterval - months[currentMonth]) >= activeTable[i].emptyDay && currentMonth+2 >= activeTable[i].emptyMonth) || currentMonth+2 > activeTable[i].emptyMonth){
				boodschappenLijst[lijstLengte] = activeTable[i];
				lijstLengte++;
			}
		}
		else if (((currentDay + lijstInterval) >= activeTable[i].emptyDay && currentMonth+1 <= activeTable[i].emptyMonth) || currentMonth+1 > activeTable[i].emptyMonth){
			boodschappenLijst[lijstLengte] = activeTable[i];
			lijstLengte++;
		}
	}

	float totalPrice = 0;
	for (int i = 0; i < lijstLengte; i++){
		printf("%s, amount: %d (gram, ml, amount), expected cost: EUR %.2f\n", boodschappenLijst[i].name, boodschappenLijst[i].amount, boodschappenLijst[i].price);
		totalPrice += boodschappenLijst[i].price;
	}
	printf("Expected total cost: EUR %f\n\n", totalPrice);
	printf(">> Do you want to print this shopping list to a .txt document (yes/no)? ");
	txtInput(tmpString);
	if (strcmp(tmpString, "yes") == 0 || strcmp(tmpString, "y")== 0){
		listExport(boodschappenLijst, lijstLengte, totalPrice);
	}
}

void listExport(tabelBoodschappen boodschappenLijst[], int lijstLengte, double totalPrice){
	remove("boodschappenLijst.txt");
	FILE *outputFile;
	outputFile = fopen("boodschappenLijst.txt", "w");

	fprintf(outputFile, "%d\n", lijstLengte);
	for (int i = 0; i < lijstLengte; i++){
		fprintf(outputFile, "[]\t%s , %d (g/ml/amount), EST. EUR %.2f\n", boodschappenLijst[i].name, boodschappenLijst[i].amount, boodschappenLijst[i].price);
	}

	fprintf(outputFile, "Expected total cost: EUR %.2f\n\n", totalPrice);
	fprintf(outputFile, "When the purchase is completed please enter a 'x' inside the box to confirm your purchase, then your file can be imported into the program to update the table.");
	fclose(outputFile);
	printf("** SHOPPING LIST SUCCESSFULLY EXPORTED");
}

void listImport(tabelBoodschappen activeTable[]){
	FILE * inputFile;
	inputFile = fopen("boodschappenLijst.txt", "r");
	int lijstLengte, tmpAmount;
	char check[32];
	char tmpName[32];
	float tmpPrice;

	fscanf(inputFile, "%d", &lijstLengte);
	for (int i = 0; i < lijstLengte; i++){
		fscanf(inputFile, "%s\t%s , %d  (g/ml/amount), EST. EUR %f", check, tmpName, &tmpAmount, &tmpPrice);
		if (strcmp(check, "[x]") == 0){
			for (int j = 0; j < tableSize; j++){
				if (strcmp(tmpName, activeTable[j].name) == 0 && tmpAmount == activeTable[j].amount){
					activeTable[j].currentStock += tmpAmount;
					activeTable[j].buyDay = currentDay;
					activeTable[j].buyMonth = currentMonth+1;
					dayCalc(activeTable, j);
				}
			}
		}
		else if(strcmp(check, "[]") == 0){
			printf("   %s seems not to be purchased, if you do have purchased it please check the box in the document.\n", tmpName);
		}
		else{
			printf("   %s's Checkbox seems to be unproperly formatted, the box should look like: [x]");
		}
	}
}
