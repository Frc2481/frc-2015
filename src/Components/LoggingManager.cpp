/*
 * LoggingManager.cpp
 *
 *  Created on: Jan 18, 2014
 *      Author: Team2481
 */

#include "LoggingManager.h"
#include "RobotParameters.h"
#include <cstdlib>
#include "HAL/Semaphore.hpp"
#include "HAL/HAL.hpp"
#include "Notifier.h"
#include <DriverStation.h>

LoggingManager::LoggingManager(std::string directory) {
	fileMap = new std::map<std::string, std::ofstream*>();
	stringMap = new std::map<std::string, std::stringstream*>();
	mutexMap = new std::map<std::string, MUTEX_ID*>();
	loggingEnabled = false;
	homeDirectory = directory;
	fileThread = new Notifier(LoggingManager::CallFileThread, this);
	fileThread->StartPeriodic(5.0);  //Run once every 5 seconds
}

LoggingManager::~LoggingManager() {
	loggingEnabled = false;
	for(std::map<std::string, std::ofstream*>::iterator it = fileMap->begin(); it != fileMap->end(); it++)
	{
		(*fileMap)[it->first]->close();
		delete (*fileMap)[it->first];
		delete (*stringMap)[it->first];
		takeMutex((*(*mutexMap)[it->first]));
		deleteMutex((*(*mutexMap)[it->first]));
		delete (*mutexMap)[it->first];
	}

	delete fileMap;
	delete stringMap;
	delete mutexMap;
}

void LoggingManager::AddLogger(std::string logName)
{
	if(fileMap->find(logName) == fileMap->end())
	{
		(*fileMap)[logName] = new std::ofstream(homeDirectory + logName.c_str() + ".txt", std::ios::out);
		(*stringMap)[logName] = new std::stringstream();
		(*mutexMap)[logName] = new MUTEX_ID();
		(*(*mutexMap)[logName]) = initializeMutexNormal();
	}
}

void LoggingManager::LogString(std::string logName, std::string dataString) {
	DriverStation* ds = DriverStation::GetInstance();
	if(ds->IsDisabled()) return;

	if(fileMap->find(logName) == fileMap->end())
	{
		CRITICAL_REGION((*(*mutexMap)[logName]))
		{
			(*(*stringMap)[logName]) << dataString;
		}
		END_REGION;
	}
}

void LoggingManager::SetLoggingStatus(bool logEnabled)
{
	loggingEnabled = logEnabled;
}

bool LoggingManager::GetLoggingStatus()
{
	return loggingEnabled;
}

void LoggingManager::PeriodicLogger()
{
	DriverStation* ds = DriverStation::GetInstance();
	if(!loggingEnabled || ds->IsDisabled()) return;

	for(std::map<std::string, std::ofstream*>::iterator it = fileMap->begin(); it != fileMap->end(); it++)
	{
		CRITICAL_REGION((*(*mutexMap)[it->first]))
		{
			if(it->second->good())
			{
				(*it->second) << (*stringMap)[it->first]->str();
				(*stringMap)[it->first]->clear();
				it->second->flush();
			}
		}
		END_REGION;
	}
}

void LoggingManager::CallFileThread(void *logger)
{
	LoggingManager *log = (LoggingManager*) logger;
	log->PeriodicLogger();
}

void LoggingManager::SetWorkingDirectory(std::string dir)
{
	if(dir.back() != '/') dir += "/";
	homeDirectory = dir;
}

std::string LoggingManager::GetWorkingDirectory()
{
	return homeDirectory;
}

