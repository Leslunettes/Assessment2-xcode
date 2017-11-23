/*
 * BankAccount.cpp
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#include <iostream>
#include "BankAccount.h"
#include <cmath>
#include <string>

using std::string;
using std::t
using std::ostream;

constexpr unsigned int INITIALSIZE = 5;

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
	// Implement me
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
}

bool Account::withdraw(float val) {
	if (val < 0.0) {
		return false;
	} else if ((balance_ - val) < 0.0) {
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
	return "";
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

	if (interest < 0) {
		interest_ = 0.0;
	} else {
		interest_ = interest;
	}

	if (fee < 0) {
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

	// fonction à ajouter.
}

// Destructor
CurrentAccount::~CurrentAccount() {
	// Implement me
}

string CurrentAccount::type() const {
	return "Current Account";
}

string CurrentAccount::toString() const { // convertir float en balance
	string output = Account::toString();
	output += "(" + fee_ + "," + overdraft_ + ")";// TO STRING??????
	return output;
}

void CurrentAccount::day() {
	if (balance_ < overdraft_) {
		balance_ = balance_ - (abs(balance_) * interest_ / 100) - 25;
		// interet est en pourcentage ou un entier?
	}
}

void CurrentAccount::month() {
	balance_ -= fee_;
}

bool CurrentAccount::withdraw(float val) {
	if (val < 0.0) {
		return false;
	} else if ((balance_ - val) < overdraft_) {
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
	if (interest < 0) {
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
	for (int i = 0; i < numberOfStocks_; i++) {
		if (stocks_[i]->amount_ != 0) {
			output += "(" + stocks_[i]->stock_ + "," + stocks_[i]->amount_ + ","
					+ stocks_[i]->value_ + ")";
		} // convertir en string les float?
	}
	return output;
}

bool StockAccount::buy(const std::string stock, float amount, float value) {
	if ((amount * value) > balance_) {
		return false;
	} else if (amount > 0.0 && value > 0.0) {
		balance_ -= (amount * value);

		int i = 0;
		for (i; i < numberOfStocks_; i++) {
			if (stocks_[i]->stock_ == stock) {
				stocks_[i]->value_ = value;
				stocks_[i]->amount_ += amount;
			}
		} // ou passer par un bool
		if (i == numberOfStocks_) {
			if (numberOfStocks_ == capacityOfStocks_) {
				capacityOfStocks_ *= 2;
				items** temp = new items*[capacityOfStocks_];
				for (int j = 0; i < numberOfStocks_; i++) {
					temp[i] = stocks_[i];
				}
				delete[] stocks_;
				stocks_ = temp;
			}
			items i;
			i.stock_ = stock;
			i.amount_ = amount;
			i.stock_ = stock;
			stocks_[numberOfStocks_] = i; // plutot l adresse?;
			balance -= (amount * value);
			numberOfStocks_++;
		}
		return true;
	} else {
		return false;
	}
	// voir les stocks et ajouter dans un tab
}

bool StockAccount::sell(const std::string stock, float amount) {
	for (int i = 0; i < numberOfStocks_; i++) {
		if (stocks_[i]->stock_ == stock) {
			if (stocks_[i]->amount_ <= amount) {
				stocks_[i]->amount_ -= amount;
				balance += (stocks_[i]->value_) * amount;
				return false;
			} else {
				return false;
			}
		} else {
			return false;
		}
	}
}

bool StockAccount::update(const std::string stock, float value) {
	for (int i = 0; i < numberOfStocks_; i++) {
		if (stocks_[i]->stock_ == stock) {
			stocks_[i]->value_ = value;
		} else {
			return false;
		}
	}

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
