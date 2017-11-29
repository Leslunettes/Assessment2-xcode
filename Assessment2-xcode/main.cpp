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
#include "ModelFormula.h"

using std::cout;
using std::cin;
using std::endl;
using std::string;

void prompt();

int main(int argc, char* argv[]) {
	/*
	 * Hello,
	 * Here are some tests that I created to help with my understanding of the coursework.
	 * Sorry I'm uploading them a bit close to the deadline, I just wanted to make sure they
	 * all compiled and matched Dr. Piterman's model solution. Like last time they may not be
	 * perfect so if you make modifications to your code just to pass the tests please do other
	 * checks as well to crosscheck your solution.
	 *
	 * If you find a bug, please let me know.
	 *
	 * Connor
	 */

	//Formula tests are default to 'false'.
	//Line: ~451
	if (true) {
		Account* accounts[3];
		accounts[0] = new CurrentAccount("blah", 1000, 3.0, 5.0);
		accounts[1] = new SavingsAccount("blah", 1.0);
		StockAccount* stockAcc = new StockAccount("blah");
		accounts[2] = stockAcc;

		cout << "\nBankAccount.cpp tests" << endl;

		//Test 1: Testing deposit method
		if (accounts[0]->deposit(100.0)) {
			if (accounts[0]->balance() == 100.0) {
				cout << "Test 1: Passed" << endl;
			} else {
				cout << "Test 1: Failed -> The balance should be 100.0" << endl;
			}
		} else {
			cout << "Test 1: Failed -> Could not deposit" << endl;
		}

		//Test 2: Testing withdraw
		if (accounts[1]->deposit(100.0)) {
			if (accounts[1]->withdraw(50.0)) {
				if (!accounts[1]->withdraw(-1)) {
					if (!accounts[1]->withdraw(51.0)) {
						if (accounts[1]->balance() == 50.0) {
							cout << "Test 2: Passed" << endl;
						} else {
							cout
									<< "Test 2: Failed -> Withdraw did not reduce the balance amount"
									<< endl;
						}
					} else {
						cout
								<< "Test 2: Failed -> Should not be able to withdraw more money than the account has"
								<< endl;
					}
				} else {
					cout
							<< "Test 2: Failed -> Should not be able to withdraw negative amounts"
							<< endl;
				}
			} else {
				cout << "Test 2: Failed -> Could not withdraw" << endl;
			}
		} else {
			cout << "Test 2: Failed -> Could not deposit into SavingsAccount"
					<< endl;
		}

		//Test 3: Transferring money from current account to savings account
		if (accounts[0]->withdraw(25.0)) {
			if (accounts[1]->deposit(25.0)) {
				if (accounts[1]->balance() == 75.0) {
					cout << "Test 3: Passed" << endl;
				} else {
					cout
							<< "Test 3: Failed -> Despoit did not add to the SavingsAccount balance"
							<< endl;
				}
			} else {
				cout
						<< "Test 3: Failed -> Could not deposit into SavingsAccounts"
						<< endl;
			}
		} else {
			cout << "Test 3: Failed -> Could not withdraw from CurrentAccount"
					<< endl;
		}

		//Test 4: Transferring money from saving account to stock account
		if (accounts[1]->withdraw(10.0)) {
			if (accounts[2]->deposit(10.0)) {
				if (accounts[2]->balance() == 10.0) {
					cout << "Test 4: Passed" << endl;
				} else {
					cout
							<< "Test 4: Failed -> Despoit did not add to the StockAccount balance"
							<< endl;
				}
			} else {
				cout << "Test 4: Failed -> Could not deposit into StockAccount"
						<< endl;
			}
		} else {
			cout << "Test 4: Failed -> Could not withdraw from SavingsAccount"
					<< endl;
		}

		//Test 5: CurrentAccount overdraft test
		if (!accounts[0]->withdraw(-1)) {
			if (accounts[0]->withdraw(100)) {
				if (accounts[0]->balance() == -25) {
					if (accounts[0]->withdraw(975)) {
						if (!accounts[0]->withdraw(1)) {
							cout << "Test 5: Passed" << endl;
						} else {
							cout
									<< "Test 5: Failed -> Should not be able to withdraw Â£1 over the Â£1000 overdraft"
									<< endl;
						}
					} else {
						cout
								<< "Test 5: Failed -> Should be able to reach the overdraft"
								<< endl;
					}
				} else {
					cout << "Test 5: Failed -> Should be -25" << endl;
				}
			} else {
				cout
						<< "Test 5: Failed -> Should be able to withdraw into the overdraft"
						<< endl;
			}
		} else {
			cout
					<< "Test 5: Failed -> Should not be able to withdraw negative amounts"
					<< endl;
		}

		//Test 6: Adding money to a negative account.
		if (accounts[0]->deposit(1000)) {
			if (accounts[0]->balance() == 0) {
				cout << "Test 6: Passed" << endl;
			} else {
				cout
						<< "Test 6: Failed -> Adding money to the CurrentAccount should make it netural"
						<< endl;
				cout
						<< "Test 6: More info -> The account had -1000 and then added 1000, so the balance should be 0"
						<< endl;
			}
		} else {
			cout << "Test 6: Failed -> Could not deposit into CurrentAccount"
					<< endl;
		}

		//Test 7: Daily charge for currentAccount (interest rate is: 3%)
		if (accounts[0]->deposit(100)) {
			accounts[0]->day();
			if (accounts[0]->balance() == 100) {
				if (accounts[0]->withdraw(1050)) {
					if (accounts[0]->balance() == -950) {
						accounts[0]->day();
						if (std::to_string(accounts[0]->balance())
								== std::to_string(-978.500000)) {
							cout << std::to_string(accounts[0]->balance())
									<< endl;
							accounts[0]->day();
							cout << std::to_string(accounts[0]->balance());
							if (std::to_string(accounts[0]->balance())
									== std::to_string(-1032.854980)) {
								cout << "Test 7: Passed" << endl;
							} else {
								cout
										<< "Test 7: Failed -> Balance does not match the expected output (2)"
										<< std::to_string(
												accounts[0]->balance()) << endl;
							}
						} else {
							cout
									<< "Test 7: Failed -> Balance does not match the expected output"
									<< endl;
						}
					} else {
						cout << "Test 7: Faild -> The balance was not reduced"
								<< endl;
					}
				} else {
					cout
							<< "Test 7: Failed -> Could not withdraw from currentAccount"
							<< endl;
				}
			} else {
				cout
						<< "Test 7: Failed -> The account is postive so day() shouldn't affect it"
						<< endl;
			}
		} else {
			cout << "Test 7: Failed -> Could not deposit into CurrentAccount"
					<< endl;
		}

		//Test 8: Monthly charge for currentAccount
		float currentBalance = accounts[0]->balance();
		accounts[0]->month();
		if (accounts[0]->balance() == currentBalance - 5.0) {
			cout << "Test 8: Passed" << endl;
		} else {
			cout
					<< "Test 8: Failed -> Monthly charge was not taken taken into affect"
					<< endl;
		}

		//Test 9: Checking the toString method for Current and Savings account (Will check stock later)
		//CurrentAccount
		std::string currentAccountString =
				"Current Account of blah (-1037.854980) (5.000000,1000.000000)";

		if (accounts[0]->toString() == currentAccountString) {
			cout << "Test 9a: Passed" << endl;
		} else {
			cout
					<< "Test 9a: Failed -> Check the formatting of your toString() : "
					<< accounts[0]->toString() << "= ?" << currentAccountString
					<< endl;
		}

		//SavingsAccount
		std::string savingsAccountString =
				"Savings Account of blah (65.000000) (1.000000%)";

		if (accounts[1]->toString() == savingsAccountString) {
			cout << "Test 9b: Passed" << endl;
		} else {
			cout << "Test 9b: Failed -> Check the formatting of your toString()"
					<< accounts[1]->toString() << endl;
		}

		//Test 10: Making sure I can buy stock
		if (!stockAcc->buy("First stock", 100.0, 5.0)) {
			if (accounts[2]->deposit(500)) {
				if (stockAcc->buy("First stock", 100.0, 5.0)) {
					if (accounts[2]->balance() == 10.0) {
						cout << "Test 10: Passed" << endl;
					} else {
						cout
								<< "Test 10: Failed -> Forgot to reduce the balance"
								<< endl;
					}
				} else {
					cout << "Test 10: Failed -> Could not purchase stock"
							<< endl;
				}
			} else {
				cout << "Test 10: Failed -> Could not deposit into StockAccount"
						<< endl;
			}
		} else {
			cout
					<< "Test 10: Failed -> Should not be able to purchase the stock due to insufficient funds"
					<< endl;
		}

		//Test 11: Selling stock
		if (!stockAcc->sell("Fake stock", 500)) {
			if (stockAcc->sell("First stock", 50)) {
				if (accounts[2]->balance() == 260.0) {
					if (!stockAcc->sell("First stock", 60)) {
						cout << "Test 11: Passed" << endl;
					} else {
						cout
								<< "Test 11: Failed -> Should not be able to sell more stock than I have"
								<< endl;
					}
				} else {
					cout
							<< "Test 11: Failed -> The profits were not added to the balance"
							<< endl;
				}
			} else {
				cout
						<< "Test 11: Failed -> Can't locate the recently added stock or just failed to sell"
						<< endl;
			}
		} else {
			cout << "Test 11: Failed -> That stock does not exist" << endl;
		}

		//Test 12: Updating stock
		if (stockAcc->update("First stock", 10.0)) {
			cout << "Test 12: Passed" << endl;
		} else {
			cout
					<< "Test 12: Failed -> Could not increase the value of the stock"
					<< endl;
		}

		//Test 13: Checking the toString method for StockAccount
		std::string firstString =
				"Stock Account of blah (260.000000) (First stock,50.000000,500.000000)";
		std::string secondString =
				"Stock Account of blah (60.000000) (First stock,50.000000,500.000000) (Second stock,10.000000,200.000000)";

		if (accounts[2]->toString() == firstString) {
			if (stockAcc->buy("Second stock", 10, 20)) {
				if (accounts[2]->toString() == secondString) {
					cout << "Test 13: Passed" << endl;
				} else {
					cout
							<< "Test 13: Failed -> Check the formatting of your toString() or the looping stock"
							<< endl;
				}
			} else {
				cout << "Test 13: Failed -> Could not purchase stock" << endl;
			}
		} else {
			cout << "Test 13: Failed -> Check the formatting of your toString()"
					<< endl << accounts[2]->toString() << "=" << firstString
					<< endl;
		}

		//Test 14: Selling a stock down to 0 and then reprinting.
		std::string thirdString =
				"Stock Account of blah (560.000000) (Second stock,10.000000,200.000000)";

		if (stockAcc->sell("First stock", 50)) {
			if (accounts[2]->toString() == thirdString) {
				cout << "Test 14: Passed" << endl;
			} else {
				cout
						<< "Test 14: Failed -> Check the formatting of your toString() or did you forget to ignore a stock that has an amount of 0"
						<< accounts[2]->toString() << endl;
			}
		} else {
			cout
					<< "Test 14: Failed -> Can't locate the stock or just failed to sell"
					<< endl;
		}

		//Test 15: Testing SavingsAccount monthly interest rate.
		accounts[1]->month(); //Calling the month() function.
		if (std::to_string(accounts[1]->balance())
				== std::to_string(65.650002)) { //Comparing two floats is a pain, so convert to string and then compare
			cout << "Test 15: Passed" << endl;
		} else {
			cout
					<< "Test 15: Failed -> Something went wrong with the monthly function"
					<< endl;
		}

		//Test 16: Buying more stock with the same name and an increased value
		//currently has (Second stock, 10.0, 200.0) meaning a value of 20.0
		std::string fourthString =
				"Stock Account of blah (510.000000) (Second stock,20.000000,100.000000)";

		if (stockAcc->buy("Second stock", 10.0, 5.0)) {
			if (accounts[2]->toString() == fourthString) {
				cout << "Test 16: Passed" << endl;
			} else {
				cout
						<< "Test 16: Failed -> Check the formatting of your toString()"
						<< endl;
			}
		} else {
			cout << "Test 16: Failed -> Could not buy more stock" << endl;
		}

		//Test 17: Buying negative stock
		if (!stockAcc->buy("First stock", -1, -1)) {
			cout << "Test 17: Passed" << endl;
		} else {
			cout
					<< "Test 17: Failed -> Should not be able to buy negative priced stock"
					<< endl;
		}

		//Test 18: Selling negative stock
		if (!stockAcc->sell("First stock", -1)) {
			cout << "Test 18: Passed" << endl;
		} else {
			cout
					<< "Test 18: Failed -> Should not be able to sell a negative amount of stock"
					<< endl;
		}

		//Test 19: Updating negative stock
		if (!stockAcc->update("First stock", -1)) {
			cout << "Test 19: Passed" << endl;
		} else {
			cout
					<< "Test 19: Failed -> Should not be able to update the stock to have a negative value"
					<< endl;
		}

		//Test20: If you buy more stock (with a changed value) but can't afford it, does the value change?
		std::string fifthString =
				"Stock Account of blah (460.000000) (Second stock,25.000000,250.000000)";

		if (stockAcc->buy("Second stock", 5.0, 10.0)) {
			if (accounts[2]->toString() == fifthString) {
				cout << "Test 20: Passed" << endl;
			} else {
				cout
						<< "Test 20: Failed -> Check the formatting of your toString() or maybe you forgot to update the value of the stock"
						<< endl;
			}
		} else {
			cout
					<< "Test 20: Failed -> Could not buy more of the stock that already exists "
					<< endl;
		}

		//Test 21: Try to buy more of the same stock but don't have enough money to buy it, what happens to the value?
		if (!stockAcc->buy("Second stock", 5.0, 100.0)) {
			if (accounts[2]->toString() == fifthString) {
				cout << "Test 21: Passed" << endl;
			} else {
				cout
						<< "Test 21: Failed -> You may have updated the value of the stock even though it wasn't purchased"
						<< endl;
			}
		} else {
			cout
					<< "Test 21: Failed -> Should not be able to buy that much stock"
					<< endl;
		}

		//Test 22: Selling more stock that have
		if (!stockAcc->sell("Second stock", 30.0)) {
			if (stockAcc->sell("Second stock", 25.0)) {
				cout << "Test 22: Passed" << endl;
			} else {
				cout << "Test 22: Failed -> Could not sell the all of the stock"
						<< endl;
			}
		} else {
			cout
					<< "Test 22: Failed -> Should not be able to sell that much stock"
					<< endl;
		}

		//Test 23: Buying first stock again and checking it prints
		std::string sixthString =
				"Stock Account of blah (660.000000) (First stock,5.000000,50.000000)";

		if (stockAcc->buy("First stock", 5.0, 10.0)) {
			if (accounts[2]->toString() == sixthString) {
				cout << "Test 22: Passed" << endl;
			} else {
				cout
						<< "Test 22: Failed -> Check your toString method or make sure you have updated the stock"
						<< endl;
			}
		} else {
			cout
					<< "Test 22: Failed -> Could not purchase the first stock again"
					<< endl;
		}

		//Test 24: (Might be a repeat) withdrawing more money when below overdraft
		if (!accounts[0]->withdraw(100.0)) {
			cout << "Test 24: Passed" << endl;
		} else {
			cout
					<< "Test 24: Failed -> Should not be able to withdraw any money when below overdraft"
					<< endl;
		}

		//Test 25: (Might be a repeat) depositing money into an account that is below the overdraft limit
		cout << accounts[0]->toString() << endl;
		cout << accounts[1]->toString() << endl;
		cout << accounts[2]->toString() << endl;
		if (accounts[0]->deposit(1040.0)) {
			if (std::to_string(accounts[0]->balance())
					== std::to_string(2.145020)) {
				cout << "Test 25: Passed" << endl;
			} else {
				cout << "Test 25: Failed -> The balance was not updated"
						<< endl;
			}
		} else {
			cout << "Test 25: Failed -> Could not deposit" << endl;
		}
		cout << accounts[0]->toString() << endl;
		cout << accounts[1]->toString() << endl;
		cout << accounts[2]->toString() << endl;
		//Test 26: Testing the type methods
		if (accounts[0]->type() == "Current Account") {
			if (accounts[1]->type() == "Savings Account") {
				if (accounts[2]->type() == "Stock Account") {
					cout << "Test 26: Passed" << endl;
				} else {
					cout << "Test 26: Failed -> Check your spelling (3)"
							<< endl;
				}
			} else {
				cout << "Test 26: Failed -> Check your spelling (2)" << endl;
			}
		} else {
			cout << "Test 26: Failed -> Check your spelling (1)" << endl;
		}

		//Test 27: Applying day() to a postive bank account
		accounts[0]->day();
		if (std::to_string(accounts[0]->balance())
				== std::to_string(2.145020)) {
			cout << "Test 27: Passed" << endl;
		} else {
			cout << "Test 27: Failed -> The balance should not have changed"
					<< endl;
			cout
					<< "Test 27: More info -> When applying the day method to a postive account, nothing should change"
					<< endl;
		}

	}

	return 0;
}

void prompt() {
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
