#ifndef CUSTOM_EXCEPTIONS_H
#define CUSTOM_EXCEPTIONS_H

#include <stdexcept>

class InvalidMoveException : public std::runtime_error {
public:
    InvalidMoveException() : std::runtime_error("Invalid player move, Try Again: ") {}
};
// Define other custom exceptions as needed

#endif // CUSTOM_EXCEPTIONS_H
