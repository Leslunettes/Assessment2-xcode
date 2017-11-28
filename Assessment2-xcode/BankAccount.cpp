/*
 * BankAccount.cpp
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 *
 *      Student : AVP9
 */

#include <iostream>
#include "BankAccount.h"
#include <cmath>
#include <string>

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

constexpr unsigned int INITIALSIZE = 5;

// mettre au dessus? in Private?
struct items {
private :
	std::string stock_;
	float value_;
	float amount_;
};

Account::Account(std::string name) :
		name_ { name }, balance_(0.0) {
}

Account::Account(std::string name, float balance) :
		name_(name) {
	if (balance < 0.0) {
		balance_ = 0.0;
	} else {
		balance_ = balance;
	}
}

Account::~Account() {
	// Nothing to delete
}

float Account::balance() const {
	return balance_;
}

bool Account::deposit(float val) {
	if (val < 0.0) {
		return false;
	} else {
		balance_ += val;
		return true;
	}
	return true;
}

bool Account::withdraw(float val) {
	if (val < 0.0 || ((balance_ - val) < 0.0)) {
		return false;
	} else {
		balance_ -= val;
		return true;
	}
}

void Account::day() { // Ne fait rien dans Account
	// Only for Current Account and Saving Account
}

void Account::month() {	// Ne fait rien dans Account
	// Only for Current Account and Saving Account
}

string Account::name() const {
	return name_;
}

string Account::type() const {
	return ""; // abstract method
}

string Account::toString() const { // convertir float en balance????
	string balance_str = std::to_string(balance_);
	string output = type() + " of " + name() + " (" + balance_str + ")";
	return output;
}

ostream& operator<<(ostream& o, const Account& a) {
	o << a.toString();
	return o;
}

CurrentAccount::CurrentAccount(std::string name, float overdraft,
		float interest, float fee) :
		Account(name) {
	if (overdraft < 0.0) {
		overdraft_ = 0.0;
	} else {
		overdraft_ = overdraft;
	}

	if (interest < 0.0) {
		interest_ = 0.0;
	} else {
		interest_ = interest;
	}

	if (fee < 0.0) {
		fee_ = 0.0;
	} else {
		fee_ = fee;
	}
}

CurrentAccount::CurrentAccount(std::string name, float balance, float overdraft,
		float interest, float fee) :
		Account(name, balance) {
	if (overdraft < 0.0) {
		overdraft_ = 0.0;
	} else {
		overdraft_ = overdraft;
	}

	if (interest < 0.0) {
		interest_ = 0.0;
	} else {
		interest_ = interest;
	}

	if (fee < 0.0) {
		fee_ = 0.0;
	} else {
		fee_ = fee;
	}
}

// Destructor
CurrentAccount::~CurrentAccount() {
	// Nothing to Delete
}

string CurrentAccount::type() const {
	return "Current Account";
}

string CurrentAccount::toString() const { // convertir float en balance
	string output = Account::toString();
	output += "(" + std::to_string(fee_) + "," + std::to_string(overdraft_)
			+ ")"; // TO STRING??????
	return output;
}

void CurrentAccount::day() {
	if (balance_ < (-overdraft_)) {
		balance_ = balance_ - (abs(balance_) * interest_ / 100) - 25;
		// interet est en pourcentage ou un entier?
	}
}

void CurrentAccount::month() {
	balance_ -= fee_;
}

bool CurrentAccount::withdraw(float val) {
	if (val < 0.0 || ((balance_ - val) < (-overdraft_))) {
		return false;
	} else {
		balance_ -= val;
		return true;
	}
}

SavingsAccount::SavingsAccount(std::string name, float interest) :
		Account(name) {
	if (interest < 0.0) {
		interest_ = 0.0;
	} else {
		interest_ = interest;
	}
}

SavingsAccount::SavingsAccount(std::string name, float balance, float interest) :
		Account(name, balance) {
	if (interest < 0.0) {
		interest_ = 0.0;
	} else {
		interest_ = interest;
	}
}
// fonction month dans Saving Account

SavingsAccount::~SavingsAccount() {
	// Implement me
}

string SavingsAccount::type() const {
	return "Saving Account";
}

string SavingsAccount::toString() const { // convertir float en balance
	string output = Account::toString();
	output += "(" + std::to_string(interest_) + "%)";
	return output;
}

void SavingsAccount::month() {
	balance_ = balance_ + abs(balance_) * interest_ / 100;
	// en pourcentage ou en entier?
}

StockAccount::StockAccount(std::string name) :
		Account(name), capacityOfStocks_(INITIALSIZE), numberOfStocks_(0), stocks_(
				new items*[capacityOfStocks_]) { //finir avec stock à init
}

StockAccount::StockAccount(std::string name, float balance) :
		Account(name, balance), capacityOfStocks_(INITIALSIZE), numberOfStocks_(
				0), stocks_(new items*[capacityOfStocks_]) { // a finir
}

StockAccount::~StockAccount() {
	for (int i = 0; i < numberOfStocks_; i++) {
		delete stocks_[i];
	}
	if (stocks_) {
		delete[] stocks_;
	}
}

string StockAccount::type() const {
	return "Stock Account";
}

string StockAccount::toString() const { // convertir float en balance
	string output = Account::toString();

	if (numberOfStocks_){
		items temp = *stocks_[0];
	cout<< "non du dernier article :"<<std::to_tring(temp.stock_)<<endl;
	}


	/*//cout << numberOfStocks_ << endl;
	string output;
	for (int i = 0; i < numberOfStocks_; i++) {
		cout << stocks_[0]->stock_ << endl;
		if (stocks_[i]->amount_ != 0) {
			 output += "(" + std::to_string(stocks_[0]->amount_) + "**,";
			//+ std::to_string(stocks_[i]->amount_) + ","+ std::to_string(stocks_[i]->value_) + ")"
		}
		// convertir en string les float?
	}*/
	return output;
}

bool StockAccount::buy(const std::string stock, float amount, float value) {
// No enough money to buy
	if ((amount * value) > balance_) {
		return false;
	} else if ((amount > 0.0) && (value > 0.0)) {

		// To check if stock is in our stocks
		int i = 0;
		for (i; i < numberOfStocks_; i++) {
			if (stocks_[i]->stock_ == stock) {
				stocks_[i]->value_ = value;
				stocks_[i]->amount_ += amount;
			}
		}

		// if not in stock
		if (i == numberOfStocks_) {

			//if tab of stock too small
			if (numberOfStocks_ == capacityOfStocks_) {
				capacityOfStocks_ *= 2;
				items** temp = new items*[capacityOfStocks_];
				for (int j = 0; i < numberOfStocks_; i++) {
					temp[i] = stocks_[i];
				}
				delete[] stocks_;
				stocks_ = temp;
			}

			items item;
			item.amount_ = amount;
			item.stock_ = stock;
			item.value_ = value;
			//cout << std::to_string(item.value_)<< item.stock_;

			stocks_[numberOfStocks_] = &item;
			numberOfStocks_++;
		}
		balance_ -= (amount * value);
		cout << stocks_[0]->stock_ << "ok ok ok ok";
		return true;

		// no positive values
	} else {
		return false;
	}
// voir les stocks et ajouter dans un tab
}

bool StockAccount::sell(const std::string stock, float amount) {
// look for the stock name
	for (int i = 0; i < numberOfStocks_; i++) {
		if (stocks_[i]->stock_ == stock) {
			// if enough stock
			if (stocks_[i]->amount_ >= amount) {
				stocks_[i]->amount_ -= amount;
				balance_ += stocks_[i]->value_ * amount;
				return true;
			} else {
				return false;
			}
		}
	}
	return false;
}

bool StockAccount::update(const std::string stock, float value) {
	for (int i = 0; i < numberOfStocks_; i++) {
		if (stocks_[i]->stock_ == stock) {
			stocks_[i]->value_ = value;
		}
	}
	return false;
}

/*
 * BankAccount.h
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
