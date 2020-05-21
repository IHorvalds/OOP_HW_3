#pragma once
#include <exception>
#include <string>
#include "Typedefs.h"
class NotFoundException : std::exception
{
private:
	std::string type;
	ID id;
public:
	NotFoundException(std::string type, ID id);
	std::string what();
};

