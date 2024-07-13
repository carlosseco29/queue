#include <iostream>

class TimeoutException : public std::exception {
private:
    std::string message;

public:
    TimeoutException(const std::string& msg) : message(msg) {}
};

class InvalidQueueSizeException : public std::exception {
private:
    std::string message;

public:
    InvalidQueueSizeException(const std::string& msg) : message(msg) {}
};