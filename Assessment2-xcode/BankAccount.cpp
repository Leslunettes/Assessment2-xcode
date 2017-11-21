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


Account::Account(std::string name) : name_{name}, balance_(0)
{
}

Account::Account(std::string name, float balance) : name_(name)
{
    if (balance<0){
        balance_=0;
    }else{
        balance_=balance;
    }
}

Account::~Account()
{
    // Implement me
}

float Account::balance() const
{
    return balance_;
}

bool Account::deposit(float val)
{
    if (val<0){
        return false;
    } else{
        balance_+=val;
        return true;
    }
}

bool Account::withdraw(float val)
{
    if (val<0) {
        return false;
    }else if (balance_-val<0){
        return false;
    }else{
        balance_ -= val;
        return true;
    }
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
    return name_;
}

string Account::type() const
{
    // Implement me
    return "";
}

string Account::toString() const
{// convertir float en balance
    string balance_str = std::to_string(balance());
    string output =  type() + " of "+ name() +" ("+balance_str+") ";
    return output ;
}

ostream& operator<<(ostream& o, const Account& a)
{
    o << a.toString();
    return o;
}

CurrentAccount::CurrentAccount(std::string name, float overdraft, float interest, float fee)
: Account(name)
{
    if (overdraft<0){
        overdraft_=0;
    } else {
        overdraft_=overdraft;
    }
    
    if (interest<0){
        interest_=0;
    } else {
        interest_=interest;
    }
    
    if(fee<0){
        fee_=0;
    }else{
        fee_=fee;
    }
}

CurrentAccount::CurrentAccount(std::string name, float balance, float overdraft, float interest, float fee)
: Account(name,balance)
{
    if (overdraft<0){
        overdraft_=0;
    } else {
        overdraft_=overdraft;
    }
    
    if (interest<0){
        interest_=0;
    } else {
        interest_=interest;
    }
    
    if(fee<0){
        fee_=0;
    }else{
        fee_=fee;
    }
    
    // fonction à ajouter.
}

// Destructor
CurrentAccount::~CurrentAccount()
{
    // Implement me
}

SavingsAccount::SavingsAccount(std::string name, float interest)
: Account(name)
{
    if(interest<0){
        interest_=0;
    }else{
        interest_=interest;
    }
}

SavingsAccount::SavingsAccount(std::string name, float balance, float interest)
: Account(name,balance)
{
    if(interest<0){
        interest_=0;
    }else{
        interest_=interest;
    }
}
// fonction month dans Saving Account

SavingsAccount::~SavingsAccount()
{
    // Implement me
}

StockAccount::StockAccount(std::string name)
: Account(name)
{
}

StockAccount::StockAccount(std::string name, float balance)
: Account(name,balance)
{
}

StockAccount::~StockAccount()
{
}

bool StockAccount::buy (const std::string stock, float amount, float value)
{
    if (amount*value>balance()){
        return false;
    }else{
        balance_-=(amount*value);
        return true;
    }
    // voir les stocks et ajouter dans un tab
}

bool StockAccount::sell(const std::string stock, float amount)
{
    
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
