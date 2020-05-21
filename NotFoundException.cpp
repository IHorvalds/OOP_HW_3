#include "NotFoundException.h"
#include <stdio.h>
#define MakeString(x) #x

NotFoundException::NotFoundException(std::string type, ID id) : type(type), id(id) {}

std::string NotFoundException::what() {
	return (std::string("No entity of type ") + type + " with id " + std::to_string(id) + " found.");
}
