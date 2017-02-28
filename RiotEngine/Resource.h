#pragma once
#include <string>
using std::string;

class Resource
{
public:
	Resource() : loaded_(false) {}
	virtual ~Resource() {}

	virtual bool loadFromFile(string fileName) { return true; }
	virtual void free() {}
protected:
	bool loaded_;
};

