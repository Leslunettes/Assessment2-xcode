/*
 * BoolFormula.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */
#include <string>
#include <sstream>
#include <iostream>
#include <cstdlib>
#include "BoolFormula.h"
#include "Assignment.h"

using std::string;
using std::ostream;

const string ANDSTRING = "and";
const string ORSTRING = "or";
const string NOTSTRING = "not";

BoolFormula::BoolFormula() :
		formula_(nullptr) {
}

BoolFormula::BoolFormula(const BoolFormula& other) :
		formula_(nullptr) {
	if (other.formula_) {
		formula_ = other.formula_->copy();
	}
}

BoolFormula::BoolFormula(const string& formula) :
		formula_(nullptr) {
	formula_ = parse_(formula);
}

bool BoolFormula::valid() {
	return formula_ && formula_->valid();
}

bool BoolFormula::evaluate(const Assignment& a) {
	if (formula_) {
		return formula_->evaluate(a);
	}
	return false;
}

void BoolFormula::print(ostream& stream) const {
	if (formula_)
		formula_->print(stream);
}

ostream& operator<<(ostream& stream, const BoolFormula& formula) {
	formula.print(stream);
	return stream;
}

Formula* BoolFormula::parse_(string input) {
	input = removeSpaces_(input);

	if ("T" == input) {
		return new Constant(true);
	}

	if ("F" == input) {
		return new Constant(false);
	}

	if (input[0] != '(' && input[input.size() - 1] != ')'
			&& input.find_first_of(" \t") == std::string::npos) {
		return new Variable(input);
	}
	if (input.size() < 3 || input[0] != '(' || input[input.size() - 1] != ')') {
		return nullptr;
	}

	input = input.substr(1, input.size() - 2);
	input = removeSpaces_(input);

	string first = "", second = "", third = "";
	if (partitionToParameters_(input, first, second, third)) {
		Formula* left = parse_(first);
		Formula* right = parse_(third);
		if (!left || !right) {
			if (left)
				delete left;
			if (right)
				delete right;
		}
		if (0 == second.compare(ANDSTRING)) {
			return new And(left, right);
		} else if (0 == second.compare(ORSTRING)) {
			return new Or(left, right);
		} else {
			return 0;
		}
	} else if (partitionToParameters_(input, first, second)) {
		if (first == NOTSTRING) {
			Formula* operand = parse_(second);
			if (operand) {
				return new Not(operand);
			}
			return 0;
		} else
			return 0;
	} else
		return 0;
}

string BoolFormula::removeSpaces_(string input) {
	while (input.size() > 0 && ' ' == input[0]) {
		input = input.substr(1, input.size() - 1);
	}
	while (input.size() > 0 && ' ' == input[input.size() - 1]) {
		input = input.substr(0, input.size() - 1);
	}
	return input;
}

bool BoolFormula::partitionToParameters_(const string& input, string& first,
		string& second) {
	unsigned int parenthesisNesting = 0;
	unsigned int location = 0;
	while (location < input.size()
			&& (input[location] != ' ' || parenthesisNesting != 0)) {
		if ('(' == input[location]) {
			parenthesisNesting++;
		}
		if (')' == input[location]) {
			parenthesisNesting--;
		}

		location++;
	}

	if (input.size() == location) {
		return false;
	}

	first = input.substr(0, location);
	second = removeSpaces_(
			input.substr(location + 1, input.size() - location - 1));
	return true;
}

bool BoolFormula::partitionToParameters_(const string& input, string& first,
		string& second, string& third) {
	string temp;
	if (!partitionToParameters_(input, first, temp)
			|| !partitionToParameters_(temp, second, third))
		return false;
	return true;
}

