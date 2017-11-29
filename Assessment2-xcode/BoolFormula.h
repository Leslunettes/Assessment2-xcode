/*
 * BoolFormula.h
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */

#include <string>
#include <iosfwd>
#include "Formula.h"
#include "Assignment.h"
#include "ModelFormula.h"

#ifndef BOOLFORMULA
#define BOOLFORMULA 1

class BoolFormula {
public:
  BoolFormula();
  BoolFormula(const BoolFormula&);
  BoolFormula(const std::string&);

  bool valid();
  bool evaluate(const Assignment&);
  void print(std::ostream&) const;

  friend std::ostream& operator<<(std::ostream&, const BoolFormula&);
private:
  Formula* formula_;

  Formula* parse_(std::string);
  std::string removeSpaces_(std::string);
  bool partitionToParameters_(const std::string&,std::string&,std::string&);
  bool partitionToParameters_(const std::string&,std::string&,std::string&,std::string&);
};

#endif

