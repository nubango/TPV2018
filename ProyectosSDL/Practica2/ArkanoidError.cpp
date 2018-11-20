#include "checkML.h"
#include "ArkanoidError.h"

ArkanoidError::ArkanoidError(string s) : logic_error(s)
{
}

ArkanoidError::~ArkanoidError()
{
}