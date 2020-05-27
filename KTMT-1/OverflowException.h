#pragma once
#include <exception>

class OverflowException : public std::exception
{
public:
	OverflowException() {}
};