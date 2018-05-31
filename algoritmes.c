#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "definities.h"

int searchHighestID(tabelBoodschappen activeTable[]){
	int top = 0;

	for (int i = 0; i < tableSize; i++){
			if (activeTable[i].id > top){
				top = activeTable[i].id;
			}
	}
	return top;
}

int	searchName(char *term, tabelBoodschappen activeTable[], int positions[]){
	int count = 0;
	for (int i = 0; i < tableSize; i++){
		if (strcmp(term, activeTable[i].name) == 0){
			positions[count] = i;
			count++;
		}
	}
	return count;

}

int	searchCategory(char *term, tabelBoodschappen activeTable[], int positions[]){
	int count = 0;
	for (int i = 0; i < tableSize; i++){
		if (strcmp(term, activeTable[i].category) == 0){
			positions[count] = i;
			count++;
		}
	}
	return count;

}

int	searchID(char *term, tabelBoodschappen activeTable[], int positions[]){
	int count = 0;
    int iTerm = atoi(term);
	for (int i = 0; i < tableSize; i++){
		if (iTerm == activeTable[i].id){
			positions[count] = i;
			count++;
		}
	}
	return count;

}

void removeItem(tabelBoodschappen activeTable[], int position){
	for (int i = position; i < tableSize-1; i++){
		activeTable[i] = activeTable[i+1];

	}
	tableSize--;
}

void stringSort(tabelBoodschappen activeTable[]){		// Radix Sort
	int i, maxLen;
	tabelBoodschappen tmpArray[MAX];

	maxLen = 0;

	for (i = 0; i < tableSize; i++){
		if (strlen(activeTable[i].name) > maxLen){
			maxLen = strlen(activeTable[i].name);
		}
	}

	while(maxLen > 0){
		int characterCounter[127] = {0};

		for (i = 0; i < tableSize; i++){
			int intC = activeTable[i].name[maxLen-1];
			characterCounter[intC]++;
		}
		for (i = 1; i < 127; i++){
			characterCounter[i] = characterCounter[i] + characterCounter[i-1];
		}

		for (i = tableSize -1; i >= 0; i--){
			int intC = activeTable[i].name[maxLen-1];

			tmpArray[characterCounter[intC]-1] = activeTable[i];

			characterCounter[intC]--;


		}

		for (i = 0; i < tableSize; i++){

			activeTable[i] = tmpArray[i];
		}
		maxLen--;
	}
	printf("** SORTING COMPLETED");

}

void intSort(tabelBoodschappen activeTable[], int left, int right){	// Quick sort

	int bot = left;
	int top = right;

	tabelBoodschappen tmpTable;
	int mid = activeTable[(bot + top) / 2].id;

	while (bot <= top){
		while (activeTable[bot].id <  mid){
			bot++;
		}
		while (activeTable[top].id > mid){
			top--;
		}
		if (bot <= top){
			tmpTable = activeTable[bot];
			activeTable[bot] = activeTable[top];
			activeTable[top] = tmpTable;
			bot++;
			top--;
		}
	}

	if (left < top){
		intSort(activeTable, left, top);
	}
	if (right > bot){
		intSort(activeTable, bot, right);
	}
}


