/*
 * Assignment.h
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */
#ifndef ASSIGNMENT_H_
#define ASSIGNMENT_H_


#include <map>
#include <iosfwd>
#include <string>

class Assignment {
public:
	Assignment();
	Assignment(const std::map<std::string,bool>&);
	Assignment(const std::string&);
	Assignment(const Assignment&) = delete;
	Assignment(Assignment&&) = delete;
	~Assignment();

	void set(const std::string& var, bool val);

	bool operator()(const std::string&) const;
	bool operator()(const std::string&, bool& ret) const;

	friend std::ostream& operator<<(std::ostream& ,Assignment&);
private:
	std::map<std::string,bool> map_;
};

#endif /* ASSIGNMENT_H_ */
