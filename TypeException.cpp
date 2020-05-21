#include "TypeException.h"

TypeException::TypeException(std::string required, std::string got) {
	required_type = required;
	error_type = got;
}

std::string TypeException::what() {
	return "Type mismatch: required " + required_type + ", got " + error_type;
}
