/*
 * DataLogger.h
 *
 *  Created on: Jan 18, 2014
 *      Author: Team2481
 */

#ifndef LOGGINGMANAGER_H_
#define LOGGINGMANAGER_H_

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include "HAL/Semaphore.hpp"
#include "Notifier.h"

class Notifier;

class LoggingManager {
private:
	std::map<std::string, std::ofstream*>* fileMap;
	std::map<std::string, std::stringstream*>* stringMap;
	std::map<std::string, MUTEX_ID*>* mutexMap;
	bool loggingEnabled;
	Notifier* fileThread;
	std::string homeDirectory;
	
public:
	LoggingManager(std::string directory = "/home/lvuser/");
	void AddLogger(std::string logName);
	virtual ~LoggingManager();
	void LogString(std::string logName, std::string dataString);
	void WriteToFile(std::string filename);
	void SetLoggingStatus(bool logEnabled);
	bool GetLoggingStatus();
	void PeriodicLogger();
	static void CallFileThread(void *logger);
	void SetWorkingDirectory(std::string dir);
	std::string GetWorkingDirectory();
};

#endif /* LOGGINGMANAGER_H_ */
