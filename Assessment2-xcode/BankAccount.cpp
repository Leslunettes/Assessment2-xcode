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


Account::Account(std::string name)
{
	 // Implement me
}

Account::Account(std::string name, float balance)
{
	 // Implement me
}

Account::~Account()
{
	 // Implement me
}

float Account::balance() const
{
	 // Implement me
	return 0.0;
}

bool Account::deposit(float val)
{
	 // Implement me
	return false;
}

bool Account::withdraw(float val)
{
	 // Implement me
	return false;
}

void Account::day()
{
	 // Implement me
}

void Account::month()
{
	 // Implement me
}

string Account::name() const {
	 // Implement me
	return "";
}

string Account::type() const
{
	 // Implement me
	return "";
}

string Account::toString() const
{
	 // Implement me
	return "";
}

ostream& operator<<(ostream& o, const Account& a)
{
	o << a.toString();
	return o;
}

CurrentAccount::CurrentAccount(std::string name, float overdraft, float interest, float fee)
: Account(name)
{
	 // Implement me
}

CurrentAccount::CurrentAccount(std::string name, float balance, float overdraft, float interest, float fee)
: Account(name,balance)
{
	 // Implement me
}

// Destructor
CurrentAccount::~CurrentAccount()
{
	 // Implement me
}

SavingsAccount::SavingsAccount(std::string name, float interest)
: Account(name)
{
	 // Implement me
}

SavingsAccount::SavingsAccount(std::string name, float balance, float interest)
: Account(name,balance)
{
	 // Implement me
}

SavingsAccount::~SavingsAccount()
{
	 // Implement me
}

StockAccount::StockAccount(std::string name)
: Account(name)
{
	 // Implement me
}

StockAccount::StockAccount(std::string name, float balance)
: Account(name,balance)
{
	 // Implement me
}

StockAccount::~StockAccount()
{
	 // Implement me
}

bool StockAccount::buy (const std::string stock, float amount, float value)
{
	 // Implement me
	return false;
}

bool StockAccount::sell(const std::string stock, float amount)
{
	 // Implement me
	return false;
}

bool StockAccount::update(const std::string stock, float value)
{
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
