#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


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

class InvalidBeforeBeginUseException : public std::exception {
private:
    std::string message;

public:
    InvalidBeforeBeginUseException(const std::string& msg) : message(msg) {}
};

class InvalidPopUseException : public std::exception {
private:
    std::string message;

public:
    InvalidPopUseException(const std::string& msg) : message(msg) {}
};

#endif //EXCEPTIONS_H