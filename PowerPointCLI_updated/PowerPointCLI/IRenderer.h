#pragma once

#include <string>
class Model;

class IRenderer {
public:
    virtual ~IRenderer() = default;
    virtual bool renderSlide(const Model& model, int slideIndex, const std::string& filename) const = 0;
};
