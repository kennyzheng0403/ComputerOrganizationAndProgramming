#ifndef PART2_INVESTMENTS
#define PART2_INVESTMENTS

/* DO NOT MODIFY FILE */

#include <string.h>
#include <stdio.h>

#define ERROR 0
#define SUCCESS 1
#define MAX_NAME_LENGTH 16
#define MAX_ACRONYM_LENGTH 4
#define MAX_NUM_STOCKS 64

#define UNUSED(x) ((void)x)

enum sectorType {
    CRYPTO,
    ENERGY,
    TECHNOLOGY,
};

struct stockProperties {
    char name[MAX_NAME_LENGTH];
    char acronym[MAX_ACRONYM_LENGTH];
    float price;
    int numShare;
    enum sectorType sector;
};

struct account {
    char accountName[MAX_NAME_LENGTH];
    float totalBalance;
    int totalStocksBought;
    struct stockProperties stocksArr[MAX_NUM_STOCKS];
};

struct stockInfo {
    char name[MAX_NAME_LENGTH];
    float price;
    enum sectorType sector;
};


int openAccount(char* name, float balance);
void closeAccount(void);
int createAcro(char* name, char* acro);
int buyStock(struct stockInfo stock, int shareCount);
int sellStock(struct stockInfo stock, int shareCount);
void sortStockInvest(void);
void sortStockSector(void);
float totalInvestment(void);
float sectorInvestment(enum sectorType sector);

#endif
