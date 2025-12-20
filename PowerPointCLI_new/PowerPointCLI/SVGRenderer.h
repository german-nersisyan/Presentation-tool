#pragma once
#include "Model.h"
#include <string>

class SVGRenderer {
public:
	bool renderSlide(const Model& model, int slideIndex, const std::string& filename) const;
};