#pragma once
#include <exception>
#include <string>
class TypeException : public std::exception
{
private:
	std::string required_type, error_type;
public:
	TypeException(std::string required, std::string got);
	std::string what();
};

