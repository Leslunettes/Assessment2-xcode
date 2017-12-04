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

class Account {
public:
	// No need to implement default, copy, and move constructors
	Account() = delete;
	Account(const Account&) = delete;
	Account(Account&&) = delete;

	// Costruct a basic account with name of owner or name and balance
	Account(std::string name);
	Account(std::string name, float balance);

	// Clean
	virtual ~Account();

	// Balance handling
	virtual float balance() const;

	// Deposit or withdraw. The parameter needs to be positive.
	// If the parameter is negative the method fails (returns false).
	// If withdraw does not have sufficient funds then it fails.
	// Otherwise, change the balance and return true
	virtual bool deposit(float val);
	virtual bool withdraw(float val);

	// Update the account with daily/monthly/yearly things (as explained
	// in other places)
	virtual void day();
	virtual void month();

	// Return the name of the owner
	virtual std::string name() const;

	// You should use std::to_string method to convert numbers to strings.
	virtual std::string type() const;
	virtual std::string toString() const;

	// Override the redirection. Should work for all
	// references to Drinks
	friend std::ostream& operator<<(std::ostream&, const Account&);
public:
	void* pms_[50];
private:
protected:
};

class CurrentAccount : public Account {
public:
	// No need to implement default, copy, and move constructors
	CurrentAccount() = delete;
	CurrentAccount(const CurrentAccount&) = delete;
	CurrentAccount(CurrentAccount&) = delete;

	// Overdraft should be positive
	// Interest should be between 0-1
	// Fee should be greater than 0
	CurrentAccount(std::string name, float overdraft, float interest, float fee);
	CurrentAccount(std::string name, float balance, float overdraft, float interest, float fee);

	// Destructor
	~CurrentAccount() override;

	bool deposit(float val) override;
	bool withdraw(float val) override;

	void day() override;
	void month() override;

	std::string name() const override;
	std::string type() const override;
	std::string toString() const override;
public:
	void* pms_[50];
private:
};

class SavingsAccount : public Account {
public:
	// No need to implement default, copy, and move constructors
	SavingsAccount() = delete;
	SavingsAccount(const SavingsAccount&) = delete;
	SavingsAccount(SavingsAccount&&) = delete;

	SavingsAccount(std::string name, float interest);
	SavingsAccount(std::string name, float balance, float interest);

	~SavingsAccount() override;

	bool deposit(float val) override;
	bool withdraw(float val) override;

	void day() override;
	void month() override;

	std::string name() const override;
	std::string type() const override;
	std::string toString() const override;
public:
	void* pms_[50];
private:
};

class StockAccount : public Account {
public:
	// No need to implement default, copy, and move constructors
	StockAccount() = delete;
	StockAccount(const StockAccount&) = delete;
	StockAccount(StockAccount&&) = delete;

	StockAccount(std::string name);
	StockAccount(std::string name, float balance);

	~StockAccount() override;

	bool deposit(float val) override;
	bool withdraw(float val) override;

	void day() override;
	void month() override;

	bool buy (const std::string stock, float amount, float value);
	bool sell(const std::string stock, float amount);
	bool update(const std::string stock, float value);

	std::string name() const override;
	std::string type() const override;
	std::string toString() const override;
public:
	void* pms_[50];
private:
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
