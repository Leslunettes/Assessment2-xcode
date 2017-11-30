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
							accounts[0]->day();
							if (std::to_string(accounts[0]->balance())
									== std::to_string(-1032.854980)) {
								cout << "Test 7: Passed" << endl;
							} else {
								cout
										<< "Test 7: Failed -> Balance does not match the expected output (2)"
										<< endl;
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
			cout << "Test 9a: Failed -> Check the formatting of your toString()"
					<< endl;
		}

		//SavingsAccount
		std::string savingsAccountString =
				"Savings Account of blah (65.000000) (1.000000%)";

		if (accounts[1]->toString() == savingsAccountString) {
			cout << "Test 9b: Passed" << endl;
		} else {
			cout << "Test 9b: Failed -> Check the formatting of your toString()"
					<< endl;
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
						<< endl;
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

	if (true) {
		cout << "\nForumla.cpp tests" << endl;

		//Test 1: Simple OR (pass)
		string test1_buffer = "(T or F)";
		string test1_assignment = ""; //Not needed

		BoolFormula test1_formula(test1_buffer);

		if (test1_formula.valid()) {
			if (test1_formula.evaluate(test1_assignment)) {
				cout << "Test 1: Passed" << endl;
			} else {
				cout
						<< "Test 1: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 1: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 2: Simple AND (pass)
		string test2_buffer = "(T and T)";
		string test2_assignment = ""; //Not needed

		BoolFormula test2_formula(test2_buffer);

		if (test2_formula.valid()) {
			if (test2_formula.evaluate(test2_assignment)) {
				cout << "Test 2: Passed" << endl;
			} else {
				cout
						<< "Test 2: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 2: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 3: Simple OR (fail)
		string test3_buffer = "(F or F)";
		string test3_assignment = ""; //Not needed

		BoolFormula test3_formula(test3_buffer);

		if (test3_formula.valid()) {
			if (!test3_formula.evaluate(test3_assignment)) {
				cout << "Test 3: Passed" << endl;
			} else {
				cout
						<< "Test 3: Failed -> Evaluated to be true when it should be false"
						<< endl;
			}
		} else {
			cout << "Test 3: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 4: Simple AND (fail)
		string test4_buffer = "(T and F)";
		string test4_assignment = ""; //Not needed

		BoolFormula test4_formula(test4_buffer);

		if (test4_formula.valid()) {
			if (!test4_formula.evaluate(test4_assignment)) {
				cout << "Test 4: Passed" << endl;
			} else {
				cout
						<< "Test 4: Failed -> Evaluated to be true when it should be false"
						<< endl;
			}
		} else {
			cout << "Test 4: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 5: Simple NOT
		string test5_buffer = "(not (T and F))";
		string test5_assignment = ""; //Not needed

		BoolFormula test5_formula(test5_buffer);

		if (test5_formula.valid()) {
			if (test5_formula.evaluate(test5_assignment)) {
				cout << "Test 5: Passed" << endl;
			} else {
				cout
						<< "Test 5: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 5: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 6: Simple variables
		string test6_buffer = "(A or B)";
		string test6_assignment = "A=T,B=F";

		BoolFormula test6_formula(test6_buffer);

		if (test6_formula.valid()) {
			if (test6_formula.evaluate(test6_assignment)) {
				cout << "Test 6: Passed" << endl;
			} else {
				cout
						<< "Test 6: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 6: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 7: Two nots with variables
		string test7_buffer = "(not (not (A or B)))";
		string test7_assignment = "A=T,B=F";

		BoolFormula test7_formula(test7_buffer);

		if (test7_formula.valid()) {
			if (test7_formula.evaluate(test7_assignment)) {
				cout << "Test 7: Passed" << endl;
			} else {
				cout
						<< "Test 7: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 7: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 8: or & and with variables and constants
		string test8_buffer = "((A or B) and (T or F))";
		string test8_assignment = "A=T,B=F";

		BoolFormula test8_formula(test8_buffer);

		if (test8_formula.valid()) {
			if (test8_formula.evaluate(test8_assignment)) {
				cout << "Test 8: Passed" << endl;
			} else {
				cout
						<< "Test 8: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 8: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 9: and & or with variables and constants mixed
		string test9_buffer = "((A and T) or (B or F))";
		string test9_assignment = "A=T,B=F";

		BoolFormula test9_formula(test9_buffer);

		if (test9_formula.valid()) {
			if (test9_formula.evaluate(test9_assignment)) {
				cout << "Test 9: Passed" << endl;
			} else {
				cout << "Test 9: Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 9: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 10: Complex forumla
		string test10_buffer =
				"((A and (not (F or F))) and (C and (not (not (T or B)))))";
		string test10_assignment = "A=T,B=F,C=T";

		BoolFormula test10_formula(test10_buffer);

		if (test10_formula.valid()) {
			if (test10_formula.evaluate(test10_assignment)) {
				cout << "Test 10: Passed" << endl;
			} else {
				cout
						<< "Test 10: Failed -> Evaluated to be false when it should be true"
						<< endl;
			}
		} else {
			cout << "Test 10: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 11: Basic validation test (OR)
		string test11_buffer = "(T or F"; //Missing bracket
		string test11_assignment = ""; //Not needed

		BoolFormula test11_formula(test11_buffer);

		if (!test11_formula.valid()) {
			cout << "Test 11: Passed" << endl;
		} else {
			cout << "Test 11: Failed -> Validated an invalid formula" << endl;
		}

		//Test 12: Basic validation test (AND)
		string test12_buffer = "(T and F"; //Missing bracket
		string test12_assignment = ""; //Not needed

		BoolFormula test12_formula(test12_buffer);

		if (!test12_formula.valid()) {
			cout << "Test 12: Passed" << endl;
		} else {
			cout << "Test 12: Failed -> Validated an invalid formula" << endl;
		}

		//Test 13; Basic validation test with variables
		string test13_buffer = "(A or B"; //Missing bracket
		string test13_assignment = "A=T,B=T";

		BoolFormula test13_formula(test13_buffer);

		if (!test13_formula.valid()) {
			cout << "Test 13: Passed" << endl;
		} else {
			cout << "Test 13: Failed -> Validated an invalid formula" << endl;
		}

		//Test 14: Simple mistake test with variables
		string test14_buffer = "(T or F) and (A or B)"; //Missing bracket around whole argument
		string test14_assignment = "A=T,B=F";

		BoolFormula test14_formula(test14_buffer);

		if (!test14_formula.valid()) {
			cout << "Test 14: Passed" << endl;
		} else {
			cout << "Test 14: Failed -> Validated an invalid formula" << endl;
		}

		//Test 15: Missing internal bracket.
		string test15_buffer = "((T or F and (A or B))"; //Missing bracket after F
		string test15_assignment = "A=T,B=F";

		BoolFormula test15_formula(test15_buffer);

		if (!test15_formula.valid()) {
			cout << "Test 15: Passed" << endl;
		} else {
			cout << "Test 15: Failed -> Validated an invalid formula" << endl;
		}

		//Test 16: More complex validation test
		string test16_buffer = "((F or (not (F and F))) and (not (F or Y))"; //Missing end bracket
		string test16_assignment = ""; //not needed

		BoolFormula test16_formula(test16_buffer);

		if (!test16_formula.valid()) {
			cout << "Test 16: Passed" << endl;
		} else {
			cout << "Test 16: Failed -> Validated an invalid formula" << endl;
		}

		//Test 17: Copy method - Simple (OR)
		string test17_buffer = "(T or F)";
		string test17_assignment = ""; //Not needed

		BoolFormula test17_formula(test17_buffer);

		if (test17_formula.valid()) {
			BoolFormula test17_copy(test17_formula);

			//Converting the print() method to a string
			//https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
			std::ostringstream stream;
			stream << test17_copy;
			std::string str = stream.str();

			if (str == test17_buffer) {
				cout << "Test 17: Passed" << endl;
			} else {
				cout
						<< "Test 17: Failed -> The copy does not match the original forumla"
						<< endl;
			}
		} else {
			cout << "Test 17: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 18: Copy method - Simple (AND)
		string test18_buffer = "(T and F)";
		string test18_assignment = ""; //Not needed

		BoolFormula test18_formula(test18_buffer);

		if (test18_formula.valid()) {
			BoolFormula test18_copy(test18_formula);

			//Converting the print() method to a string
			//https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
			std::ostringstream stream;
			stream << test18_copy;
			std::string str = stream.str();

			if (str == test18_buffer) {
				cout << "Test 18: Passed" << endl;
			} else {
				cout
						<< "Test 18: Failed -> The copy does not match the original forumla"
						<< endl;
			}
		} else {
			cout << "Test 18: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 19: Copy method - Simple (Not)
		string test19_buffer = "(not (T and F))";
		string test19_assignment = ""; //Not needed

		BoolFormula test19_formula(test19_buffer);

		if (test19_formula.valid()) {
			BoolFormula test19_copy(test19_formula);

			//Converting the print() method to a string
			//https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
			std::ostringstream stream;
			stream << test19_copy;
			std::string str = stream.str();

			if (str == test19_buffer) {
				cout << "Test 19: Passed" << endl;
			} else {
				cout
						<< "Test 19: Failed -> The copy does not match the original forumla"
						<< str << endl;
			}
		} else {
			cout << "Test 19: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 20: Copy method - variables
		string test20_buffer = "(A or B)";
		string test20_assignment = "A=T,B=F"; //Not needed

		//BoolFormula test20_formula(test20_buffer);

		BoolFormula *test20_formula = new BoolFormula(test20_buffer);

		if (test20_formula->valid()) {
			BoolFormula test20_copy(*test20_formula);

			//Converting the print() method to a string
			//https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
			std::ostringstream stream;
			stream << test20_copy;
			std::string str = stream.str();
			;

			if (str == test20_buffer) {
				//Making sure its a deep copy.
				delete test20_formula;
				test20_formula = NULL;

				//If you get a segmentation fault then you haven't performed a deep copy!
				if (test20_copy.valid()) {
					cout << "Test 20: Passed" << endl;
				}

			} else {
				cout
						<< "Test 20: Failed -> The copy does not match the original forumla"
						<< endl;
			}
		} else {
			cout << "Test 20: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 21: Copy method - more complex formula
		string test21_buffer =
				"((A or (not (B and F))) and (not (B and (F or T))))";
		string test21_assignment = "A=T,B=F"; //Not needed

		BoolFormula test21_formula(test21_buffer);

		if (test21_formula.valid()) {
			BoolFormula test21_copy(test21_formula);

			//Converting the print() method to a string
			//https://stackoverflow.com/questions/3513173/converting-ostream-into-standard-string
			std::ostringstream stream;
			stream << test21_copy;
			std::string str = stream.str();

			if (str == test21_buffer) {
				cout << "Test 21: Passed" << endl;
			} else {
				cout
						<< "Test 21: Failed -> The copy does not match the original forumla"
						<< endl;
			}
		} else {
			cout << "Test 21: Failed -> Could not validate for the formula"
					<< endl;
		}

		//Test 22: Negate method - simple test (T and F)
		Formula* test22_left = new Constant(true);
		Formula* test22_right = new Constant(false);
		Formula* test22_formula = new And(test22_left, test22_right);

		Formula* test22_negated = test22_formula->negate();

		std::ostringstream stream_22;
		test22_negated->print(stream_22);

		if (stream_22.str() == "(F or T)") {
			cout << "Test 22: Passed" << endl;
		} else {
			cout << "Test 22: Failed -> Negated answer does not match" << endl;
		}

		//Test 23: Negated method - more complex ((T and F) or (T and T))
		Formula* test23_left = new Constant(true);
		Formula* test23_right = new Constant(true);
		Formula* test23_andFormula = new And(test23_left, test23_right);
		Formula* test23_formula = new Or(test22_formula, test23_andFormula);

		Formula* test23_negated = test23_formula->negate();
		std::ostringstream stream_23;
		test23_negated->print(stream_23);

		if (stream_23.str() == "((F or T) and (F or F))") {
			cout << "Test 23: Passed" << endl;
		} else {
			cout << "Test 23: Failed -> Negated answer does not match" << endl;
		}

		//Test 24: Not negation test (not (T and F))
		Formula* test24_not = new Not(test22_formula);
		Formula* test24_negated = test24_not->negate();

		std::ostringstream stream_24;
		test24_negated->print(stream_24);

		if (stream_24.str() == "(T and F)") {
			cout << "Test 24: passed" << endl;
		} else {
			cout << "Test 24: Failed -> Negated answer does not match"
					<< stream_24.str() << endl;
		}

		//Test 25: Complex negation (not ((T and F) or (not (T and F))))
		Formula* test25_formula = new Or(test22_formula, test24_not);
		Formula* test25_negated = test25_formula->negate();

		std::ostringstream stream_25;
		test25_negated->print(stream_25);

		if (stream_25.str() == "((F or T) and (T and F))") {
			cout << "Test 25: passed" << endl;
		} else {
			cout << "Test 25: Failed -> Negated answer does not match" << endl;
		}

		cout << "hey hey ";
		//Test 26: Negation with variable names (A or B);

		Formula* test26_left = new Variable("A");
		Formula* test26_right = new Variable("B");
		Formula* test26_formula = new Or(test26_left, test26_right);

		Formula* test26_negated = test26_formula->negate();

		std::ostringstream stream_26;
		test26_negated->print(stream_26);

		if (stream_26.str() == "((not A) and (not B))") {
			cout << "Test 26: Passed" << endl;
		} else {
			cout << "Test 26: Failed -> Negated answer does not match" << endl;
		}

		//Test 27: More complex negation with variable names ((A or B) and (T or F))
		Formula* test27_left = new Constant(true);
		Formula* test27_right = new Constant(false);
		Formula* test27_orFormula = new Or(test27_left, test27_right);

		Formula* test27_formula = new And(test26_formula, test27_orFormula);

		Formula* test27_negated = test27_formula->negate();

		std::ostringstream stream_27;
		test27_negated->print(stream_27);

		if (stream_27.str() == "(((not A) and (not B)) or (F and T))") {
			cout << "Test 27: Passed" << endl;
		} else {
			cout << "Test 27: Failed -> Negated answer does not match" << endl;
		}

		//Test 28: Complex negation with variables (((A or B) and (T or F)) or (not (A or B)))
		Formula* test28_negatedTemp = new Not(test26_formula);
		Formula* test28_formula = new Or(test27_formula, test28_negatedTemp);

		Formula* test28_negated = test28_formula->negate();

		std::ostringstream stream_28;
		test28_negated->print(stream_28);

		if (stream_28.str()
				== "((((not A) and (not B)) or (F and T)) and (A or B))") {
			cout << "Test 28: Passed" << endl;
		} else {
			cout << "Test 28: Failed -> Negated answer does not match" << endl;
		}

		//Test 29: validity with missing expressions i.e. (T or )
		string test29_buffer = "(T or )";
		BoolFormula *test29_formula = new BoolFormula(test29_buffer);

		if (!test29_formula->valid()) {
			cout << "Test 29: Passed" << endl;
		} else {
			cout << "Test 29: Failed -> COULD validate for the formula" << endl;
		}

		//Test 30: valid is breacket missing in front i,e T or F)
		string test30_buffer = "T or )";
		BoolFormula *test30_formula = new BoolFormula(test30_buffer);

		if (!test30_formula->valid()) {
			cout << "Test 30: Passed" << endl;
		} else {
			cout << "Test 30: Failed -> COULD validate for the formula" << endl;
		}

		//Test 31: Evaluating variable formula without assignment
		string test31_buffer = "((T or F) and (A or B))";
		string test31_assignment = "";

		BoolFormula test31_formula(test31_buffer);

		if (test31_formula.valid()) {
			if (!test31_formula.evaluate(test31_assignment)) {
				cout << "Test 31: Passed" << endl;
			} else {
				cout << "Test 31: Failed -> Should evaluate to be false"
						<< endl;
			}
		} else {
			cout << "Test 31: Failed -> Validated an invalid formula" << endl;
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
