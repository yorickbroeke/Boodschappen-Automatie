#define MAX 1000
#include <time.h>



typedef struct tabelBoodschappen{	// The main information structure for the Grocery table
	int id, amount;
	char name[32];
	char category[32];
	float price;
	int buyDay, buyMonth;
	int emptyDay, emptyMonth;
	float currentStock;
	float avgUseDay;
} tabelBoodschappen;

extern int months[12];

extern int tableSize;

extern int currentDay, currentMonth;
