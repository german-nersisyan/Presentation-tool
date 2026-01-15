#include "ShapeFactory.h"
#include "Shapes.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

std::shared_ptr<IShape> ShapeFactory::create(const std::map<std::string, std::string>& options,
                                              const std::set<std::string>& flags) const {
    std::string type = options.count("-type") ? options.at("-type") : "rectangle";
    std::string color = options.count("-color") ? options.at("-color") : "black";
    bool filled = flags.count("-filled") > 0;

    int x = options.count("-x") ? std::stoi(options.at("-x")) : 0;
    int y = options.count("-y") ? std::stoi(options.at("-y")) : 0;

    if (type == "rectangle") {
        int w = options.count("-width") ? std::stoi(options.at("-width")) : 100;
        int h = options.count("-height") ? std::stoi(options.at("-height")) : 50;
        return std::make_shared<RectangleShape>(w, h, x, y, color, filled);
    }
    else if (type == "square") {
        int s = options.count("-size") ? std::stoi(options.at("-size")) : 50;
        return std::make_shared<SquareShape>(s, x, y, color, filled);
    }
    else if (type == "triangle") {
        int s = options.count("-side") ? std::stoi(options.at("-side")) : 50;
        return std::make_shared<TriangleShape>(s, x, y, color, filled);
    }
    else if (type == "circle") {
        int r = options.count("-radius") ? std::stoi(options.at("-radius")) : 25;
        return std::make_shared<CircleShape>(r, x, y, color, filled);
    }

    return nullptr;
}

std::shared_ptr<IShape> ShapeFactory::fromJson(const json& sh) const {
    if (!sh.contains("type")) return nullptr;
    std::string type = sh["type"].get<std::string>();

    if (type == "Rectangle") {
        int x = sh.contains("x") ? sh["x"].get<int>() : 0;
        int y = sh.contains("y") ? sh["y"].get<int>() : 0;
        int w = sh.contains("width") ? sh["width"].get<int>() : 100;
        int h = sh.contains("height") ? sh["height"].get<int>() : 50;
        std::string color = sh.contains("color") ? sh["color"].get<std::string>() : "black";
        bool filled = sh.contains("filled") ? sh["filled"].get<bool>() : false;
        return std::make_shared<RectangleShape>(w, h, x, y, color, filled);
    }
    else if (type == "Square") {
        int x = sh.contains("x") ? sh["x"].get<int>() : 0;
        int y = sh.contains("y") ? sh["y"].get<int>() : 0;
        int s = sh.contains("size") ? sh["size"].get<int>() : 50;
        std::string color = sh.contains("color") ? sh["color"].get<std::string>() : "black";
        bool filled = sh.contains("filled") ? sh["filled"].get<bool>() : false;
        return std::make_shared<SquareShape>(s, x, y, color, filled);
    }
    else if (type == "Circle") {
        int x = sh.contains("x") ? sh["x"].get<int>() : 0;
        int y = sh.contains("y") ? sh["y"].get<int>() : 0;
        int r = sh.contains("radius") ? sh["radius"].get<int>() : 25;
        bool filled = sh.contains("filled") ? sh["filled"].get<bool>() : false;
        std::string color = sh.contains("color") ? sh["color"].get<std::string>() : "black";
        return std::make_shared<CircleShape>(r, x, y, color, filled);
    }
    else if (type == "Triangle") {
        int x = sh.contains("x") ? sh["x"].get<int>() : 0;
        int y = sh.contains("y") ? sh["y"].get<int>() : 0;
        int s = sh.contains("side") ? sh["side"].get<int>() : 50;
        std::string color = sh.contains("color") ? sh["color"].get<std::string>() : "black";
        bool filled = sh.contains("filled") ? sh["filled"].get<bool>() : false;
        return std::make_shared<TriangleShape>(s, x, y, color, filled);
    }

    return nullptr;
}
