#include "logger.hpp"
#include <iostream>
#include <filesystem>
#include <chrono>
#include <sstream>
#include <iomanip>


Logger& logger = Logger::getInstance("logs/app.txt", LogLevel::DEBUG);


Logger::Logger(const std::string& filename , LogLevel level) : logLevel(level){
    // Create directory if not exists
    std::filesystem::path path(filename);
    if (path.has_parent_path()) {
        std::filesystem::create_directories(path.parent_path());
    }

    // Open log file
    logFile.open(filename, std::ios::out | std::ios::app);
    if (!logFile.is_open()) {
        std::cerr << "[LOGGER ERROR] Failed to open log file: " << filename << std::endl;
    } else {
        logFile << "[INFO] --- Logger initialized ---" << std::endl;
        std::cout << "[INFO] --- Logger initialized ---" << std::endl;
        logFile.flush();
    }
}

void Logger::log(const std::string &message, LogLevel level){
    if(level < logLevel) return;

    std::lock_guard<std::mutex> lock(logMutex);

    // Current timestamp in UTC
    auto now = std::chrono::system_clock::now();
    auto timeT = std::chrono::system_clock::to_time_t(now);
    std::ostringstream oss;
    oss << std::put_time(std::localtime(&timeT), "%Y-%m-%d %H:%M:%S");
    std::string timestamp = oss.str();

    std::string levelStr, colorCode;
    const std::string resetCode = "\033[0m";

    switch (level){
        case LogLevel::DEBUG: levelStr = "DEBUG"; colorCode = "\033[34m"; break;
        case LogLevel::INFO: levelStr = "INFO"; colorCode = "\033[32m"; break;
        case LogLevel::WARN: levelStr = "WARN"; colorCode = "\033[33m"; break;
        case LogLevel::ERROR: levelStr = "ERROR"; colorCode = "\033[31m"; break;
        default: levelStr = "UNKNOWN"; colorCode = "\033[37m"; break;
    }

    // Terminal logging
    std::string terminalOutput = "[" + timestamp + "]" + colorCode + "[" + levelStr + "]" + resetCode + " " + message;
    if(level == LogLevel::ERROR){
        std::cerr << terminalOutput << std::endl;
    }else{
        std::cout << terminalOutput << std::endl;
    }   

    // File logging
    if(logFile.is_open()){
        logFile << "[" + timestamp + "]" + "[" + levelStr + "]" + " " + message << std::endl;
        logFile.flush();
    }
}

Logger::~Logger(){
    if(logFile.is_open()){
        logFile << "[INFO] --- Logger terminated ---" << std::endl;
        std::cout << "[INFO] --- Logger terminated ---" << std::endl;
        logFile.close();
    }
}

void Logger::debug(const std::string& message){
    log(message, LogLevel::DEBUG);
}

void Logger::info(const std::string& message){
    log(message, LogLevel::INFO);
}

void Logger::error(const std::string& message){
    log(message, LogLevel::ERROR);
}

void Logger::warn(const std::string& message){
    log(message, LogLevel::WARN);
}
