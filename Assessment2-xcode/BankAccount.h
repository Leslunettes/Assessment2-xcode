/*
 * BankAccount.h
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */

#ifndef BANKACCOUNT_H_
#define BANKACCOUNT_H_

#include <string>
#include <iosfwd>

//
// This exercise implements a simple hierarchy of bank accounts using inheritance.
// The base class is Account and there are three derived classes:
// CurrentAccount, SavingsAccount, and StockAccount.
// Each bank account supports several functions as explained below.
//
// You should add the virtual keyword where appropriate and then implement the functions
// where they are most appropriate.
// Account could be an abstract class but all other classes should be
// concrete classes.
//
// StockAccount has additional features to buy and sell stocks and update
// their prices.

class Account {
public:
	// No need to implement default, copy, and move constructors
	Account() = delete;
	Account(const Account&) = delete;
	Account(Account&&) = delete;

	// Construct a basic account with name of owner or name and balance
	// In case balance is supplied it will not be negative
	Account(std::string name);
	Account(std::string name, float balance);

	// Clean
	virtual ~Account();

	// Return the balance
	float balance() const;

	// Deposit or withdraw.
	// If the parameter is negative the method fails (returns false).
	// If withdraw does not have sufficient funds then it fails.
	// Otherwise, change the balance and return true
	// Current account can withdraw up to the overdraft limit
	// Other accounts cannot be below 0
	bool deposit(float val);
	virtual bool withdraw(float val); // différente pour curent account

	// Update the account with daily/monthly events@
	// Current account has a fee that is paid monthly
	// Current account, when in overdraft pays the interest daily
	// Current account that is below the overdraft limit pays
	// in addition 25 per day (after the interest has been added)
	// Savings account is increased by the interest given in it
	// every month
	// Stock account does not have daily / monthly events
	virtual void day() =0;// methode abstracte, ne peut rien faire dépend du type de compte
	virtual void month() =0;

	// Return the name of the owner
	std::string name() const;

	// You should use std::to_string method to convert numbers to strings.
	// The type of the account is:
	// Current Account
	// Savings Account
	// Stock Account
	virtual std::string type() const=0;

	// All accounts output:
	// "Type of account" of "name" (balance)
	// Then, current account include (fee,overdraft)
	// Savings accout (interest%)
	// Stock account a list of all the stocks: (stock,amount,value of all stocks)
	// For example:
	// Current Account of blah (604.000000) (5.000000,1000.000000)
	// Savings Account of blah (400.000000) (1.000000%)
	// Stock Account of blah (496.000000) (blah,7.000000,35.000000)
	// Stock Account of blah (210.000000) (blah,5.000000,35.000000) (sdlkfj,85.000000,255.000000)
	// If a certain stock is no longer held (it's amount is 0) it should not be printed!
	// Notice the spaces!
	//
	// Use std::to_string to convert numbers @to strings.
	virtual std::string toString() const; // a compléter avec d'autres méthodes.

	// Override the redirection. Should work for all
	// references to Drinks
	friend std::ostream& operator<<(std::ostream&, const Account&);
protected:
	float balance_;
	std::string name_;
private:
	// add private members
};

class CurrentAccount: public Account {
public:
	// No need to implement default, copy, and move constructors
	CurrentAccount() = delete;
	CurrentAccount(const CurrentAccount&) = delete;
	CurrentAccount(CurrentAccount&) = delete;

	// Create a current account.
	// You can assume that overdraft, overdraft interest, and fee are
	// non-negative.
	CurrentAccount(std::string name, float overdraft, float interest,
			float fee);
	CurrentAccount(std::string name, float balance, float overdraft,
			float interest, float fee);

	// Destructor
	virtual ~CurrentAccount();

	virtual std::string type() const;

	virtual std::string toString() const;

	virtual void day();
	virtual void month();

	virtual bool withdraw(float val);
protected:
	float overdraft_;
	float interest_;
	float fee_;

private:
	// Add private members
};

class SavingsAccount: public Account {
public:
	// No need to implement default, copy, and move constructors
	SavingsAccount() = delete;
	SavingsAccount(const SavingsAccount&) = delete;
	SavingsAccount(SavingsAccount&&) = delete;

	// A savings account has interest that is credited monthly
	SavingsAccount(std::string name, float interest);
	SavingsAccount(std::string name, float balance, float interest);

	virtual ~SavingsAccount();

	virtual std::string type() const;

	virtual std::string toString() const;

	virtual void month();
protected:
	float interest_;
private:
	// Add private members
};

class StockAccount: public Account {
public:
	// No need to implement default, copy, and move constructors
	StockAccount() = delete;
	StockAccount(const StockAccount&) = delete;
	StockAccount(StockAccount&&) = delete;

	StockAccount(std::string name);
	StockAccount(std::string name, float balance);

	virtual ~StockAccount();

	virtual std::string type() const=0;

	virtual std::string toString() const;

	// Buying, selling, and updating the value of a stock

	// In order to buy stocks the balance in the account
	// should be sufficient to buy these many stocks
	// The value parameter is per stock
	// The operation returns true on successful buy and false otherwise
	bool buy(const std::string stock, float amount, float value);

	// Sell the given amount of this stock
	// If the stock is not held in the account or the amount
	// is higher than existing amount operation should fail
	// Otherwise, operation should succeed.
	// The revenue is added to the balance
	bool sell(const std::string stock, float amount);

	// Update the value of a stock.
	// The operation succeeds if the stock was ever held in the account
	bool update(const std::string stock, float value);

protected:
	// Add protected members
	// creer tab pour les stocks avec string et quantity
private:
	items** stocks_;
};

struct items {
	std::string stock_;
	float value_;
	float amount_;
};
#endif
/*
 * BankAccount.h
 *
 *  Created on: Nov 12, 2017
 *      Author: np183
 *      Module: CO3105
 *      Department of Computer Science
 *      University of Leicester
 */
