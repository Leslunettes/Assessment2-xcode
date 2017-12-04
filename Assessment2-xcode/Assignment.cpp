/*
 * Assignment.cpp
 *
 *  Created on: Oct 30, 2017
 *      Author: np183
 *      Module: CO7105
 *      Department of Informatics
 *      University of Leicester
 */

#include <utility>
#include <iostream>
#include "Assignment.h"

using std::string;
using std::map;

Assignment::Assignment()
{
}

Assignment::Assignment(const string& input)
{
	map<string,bool> temp;
	if (input.size() != 0) {
		std::string::size_type end = 0-1;
		do {
			std::string::size_type start = end + 1;
			end = input.find(',',start);
			string first = input.substr(start,end-start);
			if (first.find('=') == std::string::npos) {
				return;
			}
			string varname = first.substr(0,first.find('='));
			string value = first.substr(first.find('=')+1,std::string::npos);
			if (varname.find_first_of(" \t") != std::string::npos) {
				return;
			}
			if (value.size() != 1 || (value != "T" && value != "F")) {
				return;
			}
			if (value == "T") {
				temp.insert(std::make_pair(varname,true));
			}
			else {
				temp.insert(std::make_pair(varname,false));
			}
		} while (end != std::string::npos);
		/*map_ = std::move(temp);*/
	}
}

Assignment::Assignment(const map<string,bool>& m)
: map_(m)
{}

Assignment::~Assignment() {
}

void Assignment::set(const string& var, bool val) {
	map_[var]=val;
}

bool Assignment::operator()(const string& var, bool& val) const {
	map<string,bool>::const_iterator i = map_.find(var);
	if (map_.end() == i) {
		return false;
	}
	val = (*i).second;
	return true;
}

bool Assignment::operator()(const string& var) const {
	map<string,bool>::const_iterator i = map_.find(var);
	if (map_.end() == i) {
		return false;
	}
	return (*i).second;
}

std::ostream& operator<<(std::ostream& o,Assignment& a) {
	bool first=true;
	for (map<string,bool>::iterator i=a.map_.begin() ;
		 i != a.map_.end(); ++i) {
		if (!first) {
			o << ",";
		}
		o << (i->first) << "=" << (i->second ? "T" : "F");
		first = false;
	}
	return o;
}
