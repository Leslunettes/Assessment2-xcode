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

Formula::Formula() {
}

Formula::~Formula() {
}

bool Formula::valid() const {
// never used
	return false;
}

bool Formula::evaluate(const Assignment&) const {
	// implement me
	return false;
}

void Formula::print(ostream& stream) const {
	// implement me
}

string Formula::name() const {
//never used
	return "";
}

Formula* Formula::copy() const {
	// implement me
	return nullptr;
}

Formula* Formula::negate() const {
	// implement me
	return nullptr;
}

Constant::Constant(bool value) :
		value_(value) {
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

bool Constant::valid() const {
	if (value_) {
		return true;
	} else {
		return false;
	}
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
		name_(name) {
}

Variable::~Variable() {
}

bool Variable::valid() const { // a verifier
	if (/*name_*/true) {
		return true;
	} else {
		return false;
	}
}

string Variable::name() const {
	return name_;
}

BinaryOperator::BinaryOperator(Formula* left, Formula* right) :
		left_(left), right_(right) {
}

BinaryOperator::~BinaryOperator() {
	delete left_;
	delete right_;
}

UnaryOperator::UnaryOperator(Formula* operand) :
		operand_(operand) {
}

UnaryOperator::~UnaryOperator() {
	delete operand_;
}

And::And(Formula* left, Formula* right) :
		BinaryOperator(left, right) {
	// implement me
}

And::~And() {
	// implement me
}
string And::name() const {
	return "and";
}

bool And::valid() const {
	if (left_->valid() && right_->valid()) {
		return true;
	} else {
		return false;
	}
}

Or::Or(Formula* left, Formula* right) :
		BinaryOperator(left, right) {
	// implement me
}

Or::~Or() {
	// implement me
}
string Or::name() const {
	return "or";
}

bool Or::valid() const {
	if (left_->valid() || right_->valid()) {
		return true;
	} else {
		return false;
	}
}

Not::Not(Formula* operand) :
		UnaryOperator(operand) {
	// implement me
}

Not::~Not() {
	// implement me
}

string Not::name() const {
	return "not";
}

bool Not::valid() const {
	if (operand_->valid()) {
		return false;
	} else {
		return true;
	}
}
