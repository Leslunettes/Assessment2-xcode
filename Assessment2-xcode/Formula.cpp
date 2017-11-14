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

Formula::Formula()
{
	// implement me
}

Formula::~Formula()
{
	// implement me
}

bool Formula::valid() const
{
	// implement me
	return false;
}

bool Formula::evaluate(const Assignment&) const
{
	// implement me
	return false;
}

void Formula::print(ostream& stream) const
{
	// implement me
}

string Formula::name() const
{
	// implement me
	return "";
}

Formula* Formula::copy() const
{
	// implement me
	return nullptr;
}

Formula* Formula::negate() const
{
	// implement me
	return nullptr;
}

Constant::Constant(bool value)
{
	// implement me
}

Constant::~Constant()
{
	// implement me
}

Variable::Variable(const string& name)
{
	// implement me
}

Variable::~Variable()
{
	// implement me
}

BinaryOperator::BinaryOperator(Formula* left, Formula* right) 
{
	// implement me
}

BinaryOperator::~BinaryOperator()
{
	// implement me
}

UnaryOperator::UnaryOperator(Formula* operand)
{
	// implement me
}

UnaryOperator::~UnaryOperator()
{
	// implement me
}

And::And(Formula* left,Formula* right)
  : BinaryOperator(left,right)
{
	// implement me
}

And::~And()
{
	// implement me
}

Or::Or(Formula* left, Formula* right)
  : BinaryOperator(left,right)
{
	// implement me
}

Or::~Or()
{
	// implement me
}

Not::Not(Formula* operand)
  : UnaryOperator(operand)
{
	// implement me
}

Not::~Not()
{
	// implement me
}
