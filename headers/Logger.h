#pragma once

#include <iostream>
#include <fstream>

class Logger {
    public:
        Logger(const char* msg, bool isError = false);
    private:
        const char* prefix = "[oGL Engine]";
        bool print(const char* msg);
        bool err(const char* error);
        std::ofstream logFile;
        const char* logFilePath = "log.txt";
};