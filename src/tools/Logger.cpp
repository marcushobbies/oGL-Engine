#include "Logger.h"

Logger::Logger(const char* msg, bool isError){
    bool hasWrittenToLog = (isError) ? err(msg) : print(msg);
    if(!hasWrittenToLog){
        std::clog << prefix << " Failed to write to log file. ( "<< hasWrittenToLog << " )" << std::endl; 
    }
}


bool Logger::err(const char* error){
    std::cerr << prefix << " " << error << std::endl;

    logFile.open(logFilePath);
    bool wroteToLog = logFile.is_open();
    logFile << prefix << " ERROR: " << error << std::endl;
    logFile.close();

    return wroteToLog;
}
bool Logger::print(const char* msg){
    std::cout << prefix << " " << msg << std::endl;

    logFile.open(logFilePath);
    bool wroteToLog = logFile.is_open();
    logFile << prefix << " " << msg << std::endl;
    logFile.close();

    return wroteToLog;
}