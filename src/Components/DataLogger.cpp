/*
 * DataLogger.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: Team2481
 */

#include "DataLogger.h"
#include "RobotParameters.h"
#include <cstdlib>

DataLogger::DataLogger(std::string filename, bool clearFile) {
	// TODO Auto-generated constructor stub
	logFile = new std::ofstream(filename.c_str(), (clearFile ? std::ios::out : (std::ios::out | std::ios::app)));
}

DataLogger::~DataLogger() {
	// TODO Auto-generated destructor stub
	logFile->close();
	delete logFile;
}

void DataLogger::CloseFile() {
	logFile->close();
}

void DataLogger::LogString(std::string dataString) {
	if(logFile != NULL && logFile->good()) {
		(*logFile) << dataString << std::endl;
		logFile->flush();
	}
}


