#pragma once
#include <string>
#include <map>
#include <set>

class ICommand {
public:
	virtual ~ICommand() = default;
	virtual void execute() = 0;
};