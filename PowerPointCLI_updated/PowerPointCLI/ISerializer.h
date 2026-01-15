#pragma once

#include <string>

class Model;

class ISerializer {
public:
    virtual ~ISerializer() = default;
    virtual bool save(const Model& model, const std::string& filename) const = 0;
    virtual bool load(Model& model, const std::string& filename) const = 0;
};
