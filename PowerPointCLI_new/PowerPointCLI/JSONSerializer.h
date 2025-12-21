#pragma once
#include "Model.h"
#include <string>

class JSONSerializer {
public:
	bool save(const Model& model, const std::string& filename) const;
	bool load(Model& model, const std::string& filename) const;
};