#pragma once
#include <string>
using std::string;

class Resource
{
public:
	Resource() : loaded_(false) {}
	virtual ~Resource() { free(); }

	virtual bool loadFromFile(string fileName, void *params) { return false; }
	virtual void free() {}

protected:
	bool loaded_;
};

