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

using std::string;
using std::ostream;

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
	} else if (balance_ - val < 0.0) {
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
	string balance_str = std::to_string(balance());
	string output = type() + " of " + name() + " (" + balance_ + ") ";
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
	output += "(" + fee_ + "," + overdraft_ + ")";
	return output;
}

void CurrentAccount::day() {
	if (balance_ < overdraft_) {
		balance_ = balance_ - (balance_ * interest_) - 25;
	}
}

void CurrentAccount::month() { // Ne fait rien dans Account
	balance -= fee_;
}

bool CurrentAccount::withdraw(float val) {
	if (val < 0.0) {
		return false;
	} else if (balance_ - val < overdraft_) {
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
	output += "(" + interest_ + "%)";
	return output;
}

void SavingsAccount::month() {
	balance_ = balance_ + balance_ * interest_;
}

StockAccount::StockAccount(std::string name) :
		Account(name) { //finir avec stock
}

StockAccount::StockAccount(std::string name, float balance) :
		Account(name, balance) { // a finir
}

StockAccount::~StockAccount() {
	if (stocks_) {
		delete[] stocks_;
	}
}

string StockAccount::type() const {
	return "Stock Account";
}

string StockAccount::toString() const { // convertir float en balance
	string output = Account::toString();
	// A completer
	return output;
}

bool StockAccount::buy(const std::string stock, float amount, float value) {
	if (amount * value > balance()) {
		return false;
	} else {
		balance_ -= (amount * value);
		return true;
	}
	// voir les stocks et ajouter dans un tab
}

bool StockAccount::sell(const std::string stock, float amount) {

	return false;
}

bool StockAccount::update(const std::string stock, float value) {
	// Implement me
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
