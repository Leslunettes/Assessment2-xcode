/*
 * Formula.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */
#include <string>
#include <iostream>
#include"Formula.h"

using std::ostream;
using std::string;

using std::cout;
using std::cin;
using std::endl;
using std::string;

Formula::Formula() {
}

Formula::~Formula() {
}

bool Formula::valid() const {
	if (this == nullptr) {
		return false;
	} else {
		return true;
	}
}

bool Formula::evaluate(const Assignment&) const {
	// nerver used
	return false;
}

void Formula::print(ostream& stream) const {
	stream << this->name();
}

string Formula::name() const {
//never used
	return "";
}

Formula* Formula::copy() const {
// never used
	return nullptr;
}

Formula* Formula::negate() const {
// never used
	return nullptr;
}

Constant::Constant(bool value) :
		Formula(), value_(value) {
}

Constant::~Constant() {
}

string Constant::name() const {
	if (value_) {
		return "T";
	} else {
		return "F";
	}
}

bool Constant::evaluate(const Assignment&) const {
	return value_;
}

Formula* Constant::copy() const {
	Constant* newConst = new Constant(value_);
	return newConst;
}

Formula* Constant::negate() const {
	Constant* newConst = new Constant(!value_);
	return newConst;
}

Variable::Variable(const string& name) :
		Formula(), name_(name) {
}

Variable::~Variable() {
}

bool Variable::evaluate(const Assignment& assignment) const { // a verifier
	if (true) {
		return true;
	} else {
		return false;
	}
}

Formula* Variable::copy() const {
// implement me
	return nullptr;
}

Formula* Variable::negate() const {
// implement me
	return nullptr;
}

string Variable::name() const {
	return name_;
}

BinaryOperator::BinaryOperator(Formula* left, Formula* right) :
		left_(left), right_(right) {
}

BinaryOperator::~BinaryOperator() {
	if (left_) {
		delete left_;
	}
	if (right_) {
		delete right_;
	}
}

bool BinaryOperator::valid() const {
	if (this == nullptr || left_ == nullptr || right_ == nullptr) {
		return false;
	} else {
		return true;
	}
}

void BinaryOperator::print(ostream& stream) const {
	stream << "(";
	left_->print(stream);
	stream << " " << this->name() << " ";
	right_->print(stream);
	stream << ")";
}

UnaryOperator::UnaryOperator(Formula* operand) :
		Formula(), operand_(operand) {
}

UnaryOperator::~UnaryOperator() {
	if (operand_) {
		delete operand_;
	}
}

bool UnaryOperator::valid() const {
	if (this == nullptr || operand_ == nullptr) {
		return false;
	} else {
		return true;
	}
}

void UnaryOperator::print(ostream& stream) const {
	stream << "(" << this->name() << " ";
	operand_->print(stream);
	stream << ")";
}

And::And(Formula* left, Formula* right) :
		BinaryOperator(left, right) {
}

And::~And() {
}

string And::name() const {
	return "and";
}

bool And::evaluate(const Assignment& assignment) const {
	return (left_->evaluate(assignment) && right_->evaluate(assignment));
}

Formula* And::copy() const {
	And* newAnd = new And(left_, right_);
	return newAnd;
}

Formula* And::negate() const {
	Or* newAnd = new Or(left_->negate(), right_->negate());
	return newAnd;
}

Or::Or(Formula* left, Formula* right) :
		BinaryOperator(left, right) {
}

Or::~Or() {
}

string Or::name() const {
	return "or";
}

bool Or::evaluate(const Assignment& assignment) const {
	return (left_->evaluate(assignment) || right_->evaluate(assignment));
}

Formula* Or::copy() const {
	Or* newOr = new Or(left_, right_);
	return newOr;
}

Formula* Or::negate() const {
	And* newOr = new And(left_->negate(), right_->negate());
	return newOr;
}

Not::Not(Formula* operand) :
		UnaryOperator(operand) {
}

Not::~Not() {
// implement me
}

string Not::name() const {
	return "not";
}

bool Not::evaluate(const Assignment& assignment) const {
	return (!(operand_->evaluate(assignment)));
}

Formula* Not::copy() const {
	Not* newNot = new Not(operand_);
	return newNot;
}

Formula* Not::negate() const {
// not of negate = itself
	return operand_;
}

