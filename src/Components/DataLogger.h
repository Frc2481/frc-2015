/*
 * DataLogger.h
 *
 *  Created on: Jan 18, 2014
 *      Author: Team2481
 */

#ifndef DATALOGGER_H_
#define DATALOGGER_H_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>

class DataLogger {
private:
	std::ofstream* logFile;
	
public:
	DataLogger(std::string filename, bool clearFile = false);
	void CloseFile();
	virtual ~DataLogger();
	void LogString(std::string dataString);
	void WriteToFile(std::string filename);
};

#endif /* DATALOGGER_H_ */
