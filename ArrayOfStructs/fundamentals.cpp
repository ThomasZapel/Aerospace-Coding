#include "fundamentals.hpp"

void insertStockInfo(stockInfo stocks[], string company_name, double stock_prices_arr[], int index) {
    // Insert stock info into array of structs
    stocks [index].company_name = company_name;

    for(int i = 0; i < 5; i++) {
        stocks[index].stock_prices_arr[i] = stock_prices_arr[i];
    }

    double sum = 0;
    for(int i = 0; i < 5; i++) {
        sum = sum + stock_prices_arr[i];
    }
    double average = sum / 5;
    stocks [index].average = average;

    return;
}

void displaySortedStocks(stockInfo stock, ofstream& file) {
    // Display info stored in array of structs
    double temp;
    for(int i = 0; i < 5; i++) {
        for(int j = i + 1; j < 5; j++) {
            if(stock.stock_prices_arr[j] < stock.stock_prices_arr[i]) {
                temp = stock.stock_prices_arr[i];
                stock.stock_prices_arr[i] = stock.stock_prices_arr[j];
                stock.stock_prices_arr[j] = temp;
            }
        }
    }    
    
    file << stock.company_name << "," << stock.average << "," << stock.stock_prices_arr[0] << "," << stock.stock_prices_arr[1] << "," << stock.stock_prices_arr[2] << "," << stock.stock_prices_arr[3] << "," << stock.stock_prices_arr[4] << "\n";
    cout << stock.company_name << "," << stock.average << "," << stock.stock_prices_arr[0] << "," << stock.stock_prices_arr[1] << "," << stock.stock_prices_arr[2] << "," << stock.stock_prices_arr[3] << "," << stock.stock_prices_arr[4] << "\n";

    return;
}