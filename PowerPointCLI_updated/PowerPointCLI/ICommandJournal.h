#pragma once

#include <string>

class ICommandJournal {
public:
    virtual ~ICommandJournal() = default;
    virtual void record(const std::string& commandLine) = 0;
};
