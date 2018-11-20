#pragma once
#include "ArkanoidError.h"
class FileNotFoundError :
	public ArkanoidError
{
public:
	FileNotFoundError(string s);
	virtual ~FileNotFoundError();
};