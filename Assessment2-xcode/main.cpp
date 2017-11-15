/*
 * main.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */


#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdlib>
#include "BoolFormula.h"
#include "Assignment.h"
#include "BankAccount.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void prompt();

int main(int argc, char* argv[]) {
	// Test Bank Account
	if (true) {
		Account* accounts[3];
		accounts[0] = new CurrentAccount("blah",1000,3.0,5.0);
		accounts[1] = new SavingsAccount("blah",1.0);
		StockAccount* stockAcc = new StockAccount("blah");
		accounts[2] = stockAcc;

		for (unsigned int i=1 ; true ; ++i) {
			prompt();
			int choice;
			cin >> choice;
			switch (choice) {
			case 1: {
				float amount;
				cout << "How much would you like to deposit?" << endl;
				cin >> amount;
				if (accounts[0]->deposit(amount)) {
					cout << "Success" << endl;
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 2: {
				float amount;
				cout << "How much would you like to withdraw?" << endl;
				cin >> amount;
				if (accounts[0]->withdraw(amount)) {
					cout << "Success" << endl;
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 3: {
				float amount;
				cout << "How much would you like to transfer?" << endl;
				cin >> amount;
				if (accounts[0]->withdraw(amount)) {
					if (accounts[1]->deposit(amount)) {
						cout << "Success" << endl;
					}
					else {
						accounts[0]->deposit(amount);
						cout << "Failure" << endl;
					}
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 4: {
				float amount;
				cout << "How much would you like to transfer?" << endl;
				cin >> amount;
				if (accounts[0]->withdraw(amount)) {
					if (accounts[2]->deposit(amount)) {
						cout << "Success" << endl;
					}
					else {
						accounts[0]->deposit(amount);
						cout << "Failure" << endl;
					}
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 5: {
				float amount;
				cout << "How much would you like to transfer?" << endl;
				cin >> amount;
				if (accounts[1]->withdraw(amount)) {
					if (accounts[0]->deposit(amount)) {
						cout << "Success" << endl;
					}
					else {
						accounts[1]->deposit(amount);
						cout << "Failure" << endl;
					}
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 6: {
				float amount;
				cout << "How much would you like to transfer?" << endl;
				cin >> amount;
				if (accounts[2]->withdraw(amount)) {
					if (accounts[0]->deposit(amount)) {
						cout << "Success" << endl;
					}
					else {
						accounts[2]->deposit(amount);
						cout << "Failure" << endl;
					}
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 7: {
				cout << "Which stock would you like to buy?" << endl;
				string stock;
				cin >> stock;
				cout << "How many would you like to buy?" << endl;
				float amount;
				cin >> amount;
				cout << "What's it's current value?" << endl;
				float value;
				cin >> value;

				if (stockAcc->buy(stock,amount,value)) {
					cout << "Success" << endl;
				}
				else {
					cout << "Failure" << endl;
				}
			}
			break;
			case 8: {
				cout << "Which stock would you like to sell?" << endl;
				string stock;
				cin >> stock;
				cout << "How many would you like to sell?" << endl;
				float amount;
				cin >> amount;

				if (stockAcc->sell(stock,amount)) {
					cout << "Success" << endl;
				}
				else {
					cout << "Failure" << endl;
				}

			}
			break;
			default:
				return 0;
			}
			cout << "Your current status is:" << endl;
			for (unsigned int j=0 ; j<3 ; ++j) {
				accounts[j]->day();
				if (!i%30) {
					accounts[j]->month();
				}
				cout << *accounts[j] << endl;
			}

		}
	}

	// Test BoolFormula
	if (false) {
		if (argc != 3) {
			cout << "Expecting two parameters. A string containing a formula and an assignment!" << endl;
			cout << "The format of the assignment is \"var=val,var=val,...,var=val\", where val is either T or F" << endl;

			// For example:
			// ./main "(not (X or Y))" "X=T,Y=F"
			//

			return 1;
		}

		string buffer=argv[1];
		string assignment=argv[2];

		BoolFormula formula(buffer);
		Assignment ass(assignment);

		if (formula.valid()) {
			cout << formula << endl;
			cout << ass << endl;
			if (formula.evaluate(ass)) {
				cout << "The formula evaluates to true" << endl;
			}
			else {
				cout << "The formula evaluates to false" << endl;
			}
		}
		else {
			cout << "Could not parse the formula: " << buffer << endl;
		}
	}


	return 0;
}

void prompt()
{
	cout << "Choose an operation (one per day):" << endl;
	cout << "1) Deposit" << endl;
	cout << "2) Withdraw" << endl;
	cout << "3) Transfer to savings" << endl;
	cout << "4) Transfer to stock" << endl;
	cout << "5) Transfer from savings" << endl;
	cout << "6) Transfer from stock" << endl;
	cout << "7) Buy stock" << endl;
	cout << "8) Sell stock" << endl;
}
