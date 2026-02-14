#include "Logger.hpp"
#include <iostream>
#include <cstdarg>
#include <cstdio>
#include <string>
#include <chrono>

namespace 
{
    const auto startTime = std::chrono::high_resolution_clock::now();
}

double getLogTime() 
{
    auto now = std::chrono::high_resolution_clock::now();
    return std::chrono::duration_cast<std::chrono::duration<double>>(now - startTime).count();
}

void Log(LogLevel level, const char* file, int line, const char* function, const char* format, ...) 
{
    std::string levelStr;
    switch (level) 
    {
        case LogLevel::INFO:
            levelStr = "INFO";
            break;
        case LogLevel::DBG:
            levelStr = "DBG";
            break;
        case LogLevel::WARNING:
            levelStr = "WARNING";
            break;
        case LogLevel::ERROR:
            levelStr = "ERROR";
            break;
    }
    
    char message[1024];
    va_list args;
    va_start(args, format);
    vsnprintf(message, sizeof(message), format, args);
    va_end(args);

    // Log format: [TIME] [LEVEL] [FILE:LINE:FUNCTION] MESSAGE
    std::cout << "[" << getLogTime() << "s] [" << levelStr << "] [" << file << ":" << line << ":" << function << "] " << message << std::endl;
}
