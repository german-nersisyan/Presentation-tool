#pragma once
#include "Model.h"
#include "IRenderer.h"
#include <string>

class SVGRenderer : public IRenderer {
public:
	bool renderSlide(const Model& model, int slideIndex, const std::string& filename) const override;
};