#pragma once
#include <stdexcept>
#include <iostream>

using namespace std;

class ArkanoidError :
	public logic_error
{
public:
	ArkanoidError(string s);
	virtual ~ArkanoidError();
};