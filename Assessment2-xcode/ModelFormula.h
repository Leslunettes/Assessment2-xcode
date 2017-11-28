/*
 * Formula.h
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */


#include <string>
#include <iosfwd>

#ifndef FORMULA
#define FORMULA 1

#include "Assignment.h"

class BoolFormula;

class Formula {
public:
  Formula();
  Formula(const Formula& other) = delete;
  Formula(Formula&& other) = delete;
  virtual ~Formula() {};

  virtual bool valid();
  virtual bool evaluate(const Assignment&);
  virtual void print(std::ostream&);
  virtual std::string name();

  virtual Formula* copy();
  virtual Formula* negate();
private:
  void* pms_[2];
};

class Constant : public Formula {
public:
  Constant() = delete;
  Constant(bool);
  Constant(const Constant&) = delete;
  Constant(Constant&&) = delete;
  virtual ~Constant();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
private:
  void* pms_[2];
};

class Variable : public Formula {
public:
  Variable() = delete;
  Variable(const std::string& name);
  Variable(const Variable&) = delete;
  Variable(Variable&&) = delete;
  virtual ~Variable();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
private:
  void* pms_[2];
};

class BinaryOperator : public Formula {
public:
  BinaryOperator() = delete;
  BinaryOperator(const BinaryOperator&) = delete;
  BinaryOperator(BinaryOperator&&) = delete;
  BinaryOperator(Formula*, Formula*);

  virtual ~BinaryOperator();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
public:
  void* pms_[2];
  /*
  Formula* left_;
  Formula* right_; */
};

class UnaryOperator : public Formula {
public:
  UnaryOperator() = delete;
  UnaryOperator(const UnaryOperator&) = delete;
  UnaryOperator(UnaryOperator&&) = delete;
  UnaryOperator(Formula*);

  virtual ~UnaryOperator();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
public:
  void* pms_[2];
  /* Formula* operand_; */
};

class And : public BinaryOperator {
public:
  And() = delete;
  And(const And&) = delete;
  And(And&&) = delete;
  And(Formula*, Formula*);

  virtual ~And();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
public:
  void* pms_[2];
};

class Or: public BinaryOperator {
public:
  Or() = delete;
  Or(const Or&) = delete;
  Or(Or&&) = delete;
  Or(Formula*, Formula*);

  virtual ~Or();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
public:
  void* pms_[2];
};

class Not : public UnaryOperator {
public:
  Not() = delete;
  Not(const Not&) = delete;
  Not(Not&&) = delete;
  Not(Formula* operand);

  virtual ~Not();

  bool valid() override;
  bool evaluate(const Assignment&) override;
  void print(std::ostream&) override;
  std::string name() override;

  Formula* copy() override;
  Formula* negate() override;
public:
  void* pms_[2];
};
  
#endif

