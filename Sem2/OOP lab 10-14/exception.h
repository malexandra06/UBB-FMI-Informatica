#pragma once
#include <exception>
#include <string>
#include <utility>

class ValidatorException : public std::exception {
    std::string message;
public:
    explicit ValidatorException(std::string message)noexcept
        : message(std::move(message)) {
    }

    const char* what() const noexcept override {
        return message.c_str();
    }
};

class RepoProduseException : public std::exception {
    std::string message;
public:
    explicit RepoProduseException(std::string message)noexcept
        : message(std::move(message)) {
    }

    const char* what() const noexcept override {return message.c_str(); }
};

class ServiceException : public std::exception {
    std::string message;
public:
    explicit ServiceException(std::string message)noexcept
        : message(std::move(message)) {
    }

    const char* what() const noexcept override {return message.c_str();}
};

class RepoCosException : public std::exception {
    std::string message;
public:
    explicit RepoCosException(std::string message)noexcept
        : message(std::move(message)) {
    }

    const char* what() const noexcept override {return message.c_str();}
};