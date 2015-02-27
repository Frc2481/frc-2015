/*
 * PersistedSettings.h
 *
 *  Created on: Jan 18, 2014
 *      Author: Team2481
 */

#ifndef PERSISTEDSETTINGS_H_
#define PERSISTEDSETTINGS_H_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class PersistedSettings {
private:
	std::vector<std::string> &split(const std::string &s, char delim, std::vector<std::string> &elems);
	std::vector<std::string> split(const std::string &s, char delim);
	void trim(std::string& s);
	PersistedSettings();
	
public:
	virtual ~PersistedSettings();
	void WriteToFile(std::string filename);
	void LoadFromFile(std::string filename);
	std::map<std::string, double>  data;
	static PersistedSettings &GetInstance();
	double Get(std::string name, double value = 0);
	void Set(std::string name, double value);
};

#endif /* PERSISTEDSETTINGS_H_ */
