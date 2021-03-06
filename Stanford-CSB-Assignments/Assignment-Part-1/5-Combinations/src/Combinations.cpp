/*
 * File: Combinations.cpp
 * ----------------------
 * Name: aotian
 * Section: CS-B
 * This file is the starter project for the recursive combinations problem.
 */

#include <iostream>
#include "console.h"
#include "simpio.h"
using namespace std;

/**
 * @brief factorial
 * @param a the number to calculate factorial
 * @return the result of the calculate the factorial a
 */
int factorial (int a){
    if(a == 0){
        return 1;
    }
    return a*(factorial(a - 1));
}

/**
 * Supporting function for correct display the result
 * @brief printSpace
 * @param n the number of iteration
 */
void printSpace(int n){
    for(int i = 0; i < n; i++){
        cout << " ";
    }
}

/**
 * @brief pascalTriangle
 * @param n the first number (number of the row)
 * @param k the seond number (number of the column/branch )
 */
void pascalTriangle(int n, int k){
    int res;
    for(int i = 0; i <= n; i++){
        printSpace(n - i);
        for(int j = 0; j <= i; j++){
            int  c = factorial(i) / (factorial(j) * factorial(i - j));
            if(i == n && j == k){
                res = c;
            }
            cout << c << " ";
        }
        cout << endl;
    }
    cout << "c(" << n << "," << k << ") = " << res << endl;
}

int main() {
    cout << "Welcome to implementing Pascal Triangle structure" << endl;
    while(true){
        int n = getInteger ("Enter first number: ");
        int k = getInteger ("Enter second number: ");
        if(k > n){
            cout << "Try again..." << endl;
        }else{
            pascalTriangle (n, k);
        }
    }
    return 0;
}
