#pragma once
#include "Model.h"
#include "ISerializer.h"
#include <string>

class JSONSerializer : public ISerializer {
public:
	bool save(const Model& model, const std::string& filename) const override;
	bool load(Model& model, const std::string& filename) const override;
};