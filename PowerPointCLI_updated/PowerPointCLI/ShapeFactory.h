#pragma once

#include <map>
#include <set>
#include <memory>
#include <string>
#include <nlohmann/json.hpp>

class IShape;

class ShapeFactory {
public:
    // Create a shape from parsed options and flags. Returns nullptr on error.
    std::shared_ptr<IShape> create(const std::map<std::string, std::string>& options,
                                   const std::set<std::string>& flags) const;

    // Create from JSON-like object (nlohmann::json)
    std::shared_ptr<IShape> fromJson(const nlohmann::json& j) const;
};
