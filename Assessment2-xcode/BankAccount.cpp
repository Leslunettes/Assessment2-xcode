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
#include <string>

using std::string;
using std::ostream;
using std::cout;
using std::cin;
using std::endl;

// for the array of items/stock
constexpr unsigned int INITIALSIZE = 5;

/*
 i tried to make a struck but it doesnt work....
 struct items {
 std::string stock_;
 float value_;
 float amount_;
 };*/

items::items(std::string stock, float value, float amount) {
	stock_ = stock;
	value_ = value;
	amount_ = amount;
}

std::string items::getStock() {
	return stock_;
}

void items::setStock(std::string stock) {
	stock_ = stock;
}

float items::getValue() {
	return value_;
}

void items::setValue(float value) {
	value_ = value;
}

float items::getAmount() {
	return amount_;
}

void items::setAmount(float amount) {
	amount_ = amount;
}

items::~items() {
}

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
}

bool Account::withdraw(float val) {
	if (val < 0.0 || ((balance_ - val) < 0.0)) { // i.e val>balance...
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

string Account::toString() const { // convertir float en balance
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
// we could call the previous constructor and just add the balance
CurrentAccount::CurrentAccount(std::string name, float balance, float overdraft, //overdraft is always a "neg" number
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

CurrentAccount::~CurrentAccount() {
	// Nothing to Delete
}

string CurrentAccount::type() const {
	return "Current Account";
}

string CurrentAccount::toString() const { // convertir float en balance
	string output = Account::toString();
	output += " (" + std::to_string(fee_) + "," + std::to_string(overdraft_)
			+ ")";
	return output;
}

void CurrentAccount::day() { // balance = balance - abs(balance) * interest /100 doesnt work because of abs?
	if (balance_ < 0.0) {
		balance_ *= (1.0 + interest_ / 100); // interet est en pourcentage ou un entier? interest is an entire
	}

	if (balance_ < (-overdraft_)) {
		balance_ = balance_ - 25.0;

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

SavingsAccount::SavingsAccount(std::string name, float balance, float interest) : // we could call the previous constructor and just add the balance
		Account(name, balance) {
	if (interest < 0.0) {
		interest_ = 0.0;
	} else {
		interest_ = interest;
	}
}

SavingsAccount::~SavingsAccount() {
	// Nothing to delete
}

string SavingsAccount::type() const {
	return "Savings Account";
}

string SavingsAccount::toString() const { // convertir float en balance
	string output = Account::toString();
	output += " (" + std::to_string(interest_) + "%)";
	return output;
}

void SavingsAccount::month() { // fonction month dans Saving Account
	balance_ *= 1.0 + interest_ / 100;
	// en pourcentage ou en entier?
}

StockAccount::StockAccount(std::string name) :
		Account(name), capacityOfStocks_(INITIALSIZE), numberOfStocks_(0), stocks_(
				new items*[capacityOfStocks_]) {
}

StockAccount::StockAccount(std::string name, float balance) : // could use the previous constructeur
		Account(name, balance), capacityOfStocks_(INITIALSIZE), numberOfStocks_(
				0), stocks_(new items*[capacityOfStocks_]) {
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
	// penser au espace
	//cout << numberOfStocks_ << endl;
	for (int i = 0; i < numberOfStocks_; i++) {
		if (stocks_[i]->getAmount() != 0) {
			output += " (" + stocks_[i]->getStock() + ","
					+ std::to_string(stocks_[i]->getAmount()) + ","
					+ std::to_string(
							stocks_[i]->getValue() * stocks_[i]->getAmount())
					+ ")";
		}
	}
	return output;
}

bool StockAccount::buy(const std::string stock, float amount, float value) {

	// No enough money to buy or no positive values
	if (((amount * value) > balance_) || (amount < 0.0) || (value < 0.0)) {
		return false;

	} else {

		// To check if stock is in our stocks
		int i;
		bool flag = true;
		for (i = 0; i < numberOfStocks_; i++) {
			if (stocks_[i]->getStock() == stock) {
				stocks_[i]->setValue(value);
				stocks_[i]->setAmount(stocks_[i]->getAmount() + amount);
				flag = false;
				break;	//?
			}
		}

		// if not in stock
		if (flag) {

			//if tab of stock too small
			if (numberOfStocks_ == capacityOfStocks_) {
				capacityOfStocks_ *= 2;
				items** temp = new items*[capacityOfStocks_];
				for (int j = 0; j < numberOfStocks_; j++) {
					temp[j] = stocks_[j];
				}
				delete[] stocks_;
				stocks_ = temp;
			}

			items* item = new items(stock, value, amount);
			//cout << std::to_string(item.value_)<< item.stock_;

			stocks_[numberOfStocks_] = item;
			numberOfStocks_++;
		}

		balance_ -= (amount * value);
		//cout << stocks_[0]->stock_ << "ok ok ok ok";
		return true;

	} // voir les stocks et ajouter dans un tab
}

bool StockAccount::sell(const std::string stock, float amount) {
// look for the stock name
	if (amount > 0.0) {
		for (int i = 0; i < numberOfStocks_; i++) {
			if (stocks_[i]->getStock() == stock) {

				// if enough stock
				if (stocks_[i]->getAmount() >= amount) {

					stocks_[i]->setAmount(stocks_[i]->getAmount() - amount);
					balance_ += stocks_[i]->getValue() * amount;
					return true;

				} else {
					return false;
				}
			}
		}
	}
	return false;
}

bool StockAccount::update(const std::string stock, float value) {
	if (value > 0.0) {
		for (int i = 0; i < numberOfStocks_; i++) {

			if (stocks_[i]->getStock() == stock) {
				stocks_[i]->setValue(value);
				return true;
			}
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
