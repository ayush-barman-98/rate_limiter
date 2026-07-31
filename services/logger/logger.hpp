#pragma once
#include <string>
#include <fstream>
#include <mutex>


enum class LogLevel{
    DEBUG, 
    INFO, 
    WARN, 
    ERROR
};


//Singleton Logger class
class Logger{
    public:
    static Logger& getInstance(const std::string& filename = "logs/app.log" , LogLevel level = LogLevel::INFO) {
        static Logger instance(filename , level);
        return instance;
    }

    void debug(const std::string& message);
    void info(const std::string& message);
    void error(const std::string& message);
    void warn(const std::string& message);


    private:
    explicit Logger(const std::string& filename , LogLevel level);
    ~Logger();

    void log(const std::string &message, LogLevel level);

    std::ofstream logFile;
    std::mutex logMutex;
    LogLevel logLevel;
};

extern Logger& logger;