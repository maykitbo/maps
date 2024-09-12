#pragma once


#include <iostream>
#include <fstream>
#include <string>
#include <ctime>
#include <mutex>


namespace maykitbo::maps
{


enum LogType {
    MESSAGE,
    WARNING,
    ERROR
};


template<bool f>
class Log;


template<>
class Log<true>
{
    public:
        Log(const std::string& file_name)
        {
            log_file_.open("log/" + file_name, std::ios::out | std::ios::app);
            if (!log_file_.is_open())
            {
                throw std::runtime_error("Unable to open log file");
            }
        }

        ~Log()
        {
            if (log_file_.is_open())
            {
                log_file_.close();
            }
        }

        class Helper
        {
            public:
                Helper(Log& log, std::unique_lock<std::mutex>&& lock) 
                    : log_(log), lock_(std::move(lock)) {}

                template <typename T>
                Helper& operator<<(const T& message)
                {
                    log_.log_file_ << message;
                    return *this;
                }

                void operator<<(const Log& log)
                {
                    log_.log_file_ << "\n";
                    log_.log_file_.flush();
                    lock_.unlock();
                }

            private:
                Log& log_;
                std::unique_lock<std::mutex> lock_;
            };

        Helper operator<<(LogType log_type)
        {
            std::unique_lock<std::mutex> lock(mutex_);
            log_file_ << getLogPrefix(log_type);
            return Helper(*this, std::move(lock));
        }

    private:
        std::ofstream log_file_;
        std::mutex mutex_;

        std::string getLogPrefix(LogType log_type)
        {
            std::string prefix;
            switch (log_type)
            {
                case MESSAGE:
                    prefix = "[MESSAGE] ";
                    break;
                case WARNING:
                    prefix = "[WARNING] ";
                    break;
                case ERROR:
                    prefix = "[ERROR] ";
                    break;
            }

            std::time_t now = std::time(nullptr);
            char buf[20];
            std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
            return std::string(buf) + " " + prefix;
        }
};


template<>
class Log<false>
{
    public:
        Log(const std::string& file_name) {}

        template<class T>
        const Log<false> &operator<<(T m)
        {
            return *this;
        }
};


} // namespace maykitbo::maps