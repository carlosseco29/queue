#ifndef EXCEPTIONS_H
#define EXCEPTIONS_H


#include <iostream>

/// @brief This class implements a TimeoutException.
///
/// Exception to be raised when a timeout occurs
class TimeoutException : public std::exception {
public:
    /// @brief The constructor for the TimeoutException
    ///
    /// This constructor initializes the exception with the given message
    ///
    /// @param msg The message for the exception
    TimeoutException(const std::string& msg) : message(msg) {}

private:
    /// @brief The message for the TimeoutException
    std::string message;
};

/// @brief This class implements a InvalidQueueSizeException. Raised when a queue
///
/// Exception to be raised when an attempt to create a Queue of invalid size (size<1) is done
class InvalidQueueSizeException : public std::exception {
public:
    /// @brief The constructor for the InvalidQueueSizeException
    ///
    /// This constructor initializes the exception with the given message
    ///
    /// @param msg The message for the exception
    InvalidQueueSizeException(const std::string& msg) : message(msg) {}

private:
    /// @brief The message for the InvalidQueueSizeException
    std::string message;

};

/// @brief This class implements a InvalidBeforeBeginUseException
class InvalidBeforeBeginUseException : public std::exception {
public:
    /// @brief The constructor for the InvalidBeforeBeginUseException
    ///
    /// This constructor initializes the exception with the given message
    ///
    /// @param msg The message for the exception
    InvalidBeforeBeginUseException(const std::string& msg) : message(msg) {}

private:
    /// @brief The message for the InvalidBeforeBeginUseException
    std::string message;
};

/// @brief This class implements a InvalidPopUseException
class InvalidPopUseException : public std::exception {
public:
    /// @brief The constructor for the InvalidPopUseException
    ///
    /// This constructor initializes the exception with the given message
    ///
    /// @param msg The message for the exception
    InvalidPopUseException(const std::string& msg) : message(msg) {}

private:
    /// @brief The message for the InvalidPopUseException
    std::string message;
};

#endif //EXCEPTIONS_H