#include "part2-investments.h"

/*
 * Name: Kenny Zheng
 * Collaborators:
 * Please list anyone you collaborated with on this file here.
 */

struct account myAccount;
int count;

/** openAccount
 *
 * Opens a new account in the system.
 *
 * Initialize the global account struct with the name and balance passed in.
 * You will not be able to assign strings directly, see the PDF for more details.
 *
 * @param "name" the name string to copy into the global account struct.
 * @param "balance" the balance to set in the global account struct.
 * @return SUCCESS on success, ERROR on failure
 *         Failure occurs if ANY of the following are true:
 *         (1) The length of `name`, excluding NULL terminator, is too short (< 3 characters).
 *         (2) The length of `name`, excluding NULL terminator, is too long (> 15 characters).
 *         (3) `balance` is negative.
 */
int openAccount(char* name, float balance) {
    int length = strlen(name);
    if (length < 3){
        return ERROR;
    } if (length > 15){
        return ERROR;
    } if (balance < 0){
        return ERROR;
    } 
    myAccount.totalStocksBought = 0;
    strcpy(myAccount.accountName, name);
    myAccount.totalBalance = balance;

    count = 0;
    
    return SUCCESS;
}

/** closeAccount
 *
 * Closes the account in the system.
 *
 * Set the account name to "".
 * Set the total balance to 0.
 * Set the total number of stocks bought to 0.
 *
 */
void closeAccount(void) {
    strcpy(myAccount.accountName, "");
    myAccount.totalBalance = 0;
    myAccount.totalStocksBought = 0;


}

/** createAcro
 *
 * Create an acronym (stock ticker) for a given stock.
 *
 * An acronym can be generated from a stock name by using the following formula:
 * First letter + first vowel + last character.
 *
 * You may assume the name passed in contains a vowel.
 * Stock names may be uppercase, lowercase, or any mix of the two.
 *
 * @param "name" The name of the stock to create an acronym from. Do not change this string.
 * @param "acro" The string to write the outputted acronym to.
 * @return SUCCESS on success, ERROR on failure
 *         Failure occurs if ANY of the following are true:
 *         (1) `name` is NULL.
 *         (2) The length of `name`, excluding NULL terminator, is too short (< 3 characters).
 *         (3) The length of `name`, excluding NULL terminator, is too long (> 15 characters).
 */
int createAcro(char* name, char* acro) {
    int length = strlen(name);
    if (length < 3){
        return ERROR;
    } if (length > 15){
        return ERROR;
    }
    if (name[0] == 0){
        return ERROR;
    }
    acro[0] = name[0];
    acro[2] = name[length - 1];
    for (int i = 0; i < length; i++){
        if(name[i] == 'A' || name[i] == 'a' || name[i] == 'E' || name[i] == 'e' || name[i] == 'I' 
        || name[i] == 'i' || name[i] == 'O' || name[i] == 'o' || name[i] == 'U' || name[i] == 'u' ){
            acro[1] = name[i];
            break;
        }
    }
    return SUCCESS;
}

/** buyStock
 * 
 * Buy shares of a stock in the system.
 *
 * On success, you should subtract the cost of the stock from the account's balance.
 * You should also update the number of shares owned in the stock array.
 *
 * @param "stock" the stock you want to buy.
 * @param "shareCount" the number of shares to buy.
 * @return SUCCESS on success, ERROR on failure
 *         Failure occurs if ANY of the following are true:
 *         (1) You cannot afford to make the purchase requested.
 *         (2) Buying the stock would make you exceed the maximum number of stocks.
 */
int buyStock(struct stockInfo stock, int shareCount) {
    if (myAccount.totalBalance < stock.price * shareCount){
        return ERROR;
    } 
    if (myAccount.totalStocksBought + shareCount > MAX_NUM_STOCKS){
        return ERROR;
    }
    int totalValueBought = stock.price * shareCount;
    myAccount.totalBalance -= totalValueBought;
    int duplicate = 0;
    for (int i = 0; i < MAX_NUM_STOCKS; i++){
        if (strcmp(stock.name, myAccount.stocksArr[i].name) == 0){
            duplicate = 1;
            break;
        }
    }

    struct stockProperties stockP;

    if (duplicate == 0) {
        myAccount.totalStocksBought++;
        stockP.price = stock.price;
    }
    createAcro(stock.name, stockP.acronym);
    strcpy(stockP.name, stock.name);
    stockP.numShare = shareCount + 10;
    stockP.sector = stock.sector;

    myAccount.stocksArr[count] = stockP;

    count++;


   return SUCCESS;
}

/** sellStock
 *
 * Sell shares of a stock in the system.
 *
 * On success, you should add the cost of the shares sold to your account's balance.
 * You should also update the number of shares owned in the stock array.
 *
 * @param "stock" the stock you want to sell.
 * @param "shareCount" the number of shares to sell.
 * @return SUCCESS on success, ERROR on failure
 *         Failure occurs if ANY of the following are true:
 *         (1) The specified stock does not exist in the account's stock array.
 *         (2) You do not have enough of the specified stock to sell.
 */
int sellStock(struct stockInfo stock, int shareCount) {
    //if (stock.name != )
    UNUSED(stock);
    UNUSED(shareCount);
    return SUCCESS;
}

/** sortStockInvest
 *
 * Sort the account's stock array by the stock's total value.
 * The array should be sorted in increasing order.
 * In other words, the stock with the lowest total value should be first in the sorted array.
 *
 * Note that each stock's total value is calculated by multiplying its price by its share count.
 *
 * It does not matter what sorting algorithm you use, but it should be a stable sort.
 * In other words, you should maintain the original order for two stocks with the same total value.
 */
void sortStockInvest(void) {
    if (myAccount.totalStocksBought != 0){
        for (int i = 1; i < myAccount.totalStocksBought;i++){
            int dupe = i;
            while (dupe > 0 && myAccount.stocksArr[dupe - 1].price * myAccount.stocksArr[dupe - 1].numShare 
            > myAccount.stocksArr[dupe].price * myAccount.stocksArr[dupe].numShare){
                struct stockProperties temp = myAccount.stocksArr[dupe];
                myAccount.stocksArr[dupe]= myAccount.stocksArr[dupe - 1];
                myAccount.stocksArr[dupe - 1] = temp;
                dupe--;
            }
        }
    }
}


/** sortStockSector
 *
 * Sort the account's stock array by the stock sector.
 *
 * The array should be sorted in the order [CRYPTO, ENERGY, TECHNOLOGY].
 * In other words, CRYPTO stocks should be first in the array; TECHNOLOGY stocks should be last.
 *
 * It does not matter what sorting algorithm you use, but it should be a stable sort.
 * In other words, you should maintain the original order for two stocks with the same sector.
 */
void sortStockSector(void) {
    if(myAccount.totalStocksBought != 0){
        for(int i = 1; i < myAccount.totalStocksBought; i++){
            int dupe = i;
            while (dupe > 0 && myAccount.stocksArr[dupe - 1].sector 
            > myAccount.stocksArr[dupe].sector){
                struct stockProperties temp = myAccount.stocksArr[dupe];
                myAccount.stocksArr[dupe] =myAccount.stocksArr[dupe - 1];
                myAccount.stocksArr[dupe - 1] = temp;
                dupe--;
            }
        }
    }
}

/** totalInvestment
 *
 * Calculate the total value of the account.
 *
 * The total value of the account is the sum of the total value of each stock.
 * The total value of each stock is its price multiplied by its share count.
 *
 * If there are no stocks in the account, the total value is 0.
 *
 * @return the total value of the account.
 */
float totalInvestment(void) {
    if(myAccount.totalStocksBought == 0){
        return 0;
    }
    float totalValueAcc = 0;
    float stockValue = 0;
    int i = 0;
    int temp = myAccount.totalStocksBought;
    while(i < temp){
        stockValue = myAccount.stocksArr[i].numShare * myAccount.stocksArr[i].price;
        totalValueAcc += stockValue;
        i++;
    }
    return totalValueAcc;
}

/** sectorInvestment
 *
 * Calculate the total value of a stock sector in the account.
 * 
 * The total value of a sector in the account is the sum of the total value of each stock belonging to that sector.
 * The total value of each stock is its price multiplied by its share count.
 *
 * If there are no stocks of that sector type in the account, the value of the sector is 0.
 *
 * @return the total value of the sector.
 */
float sectorInvestment(enum sectorType sector) {
    if(myAccount.totalStocksBought == 0){
        return 0;
    }
    float totalValueAcc = 0;
    float stockValue = 0;
    for(int i = 0; i < myAccount.totalStocksBought; i++){
        if(myAccount.stocksArr[i].sector == sector){
            stockValue = myAccount.stocksArr[i].numShare * myAccount.stocksArr[i].price;
            totalValueAcc += stockValue;
        }
    }
    return totalValueAcc;
}
