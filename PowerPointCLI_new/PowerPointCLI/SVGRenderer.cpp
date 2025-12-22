#include "SVGRenderer.h"
#include "Shapes.h"
#include <fstream>
#include <sstream>

bool SVGRenderer::renderSlide(const Model& model, int slideIndex, const std::string& filename) const {
	if (slideIndex < 0 || slideIndex >= model.getSlideCount())
		return false;

	std::ofstream out(filename);
	if (!out.is_open())
		return false;

	out << "<svg xmlns=\"http://www.w3.org/2000/svg\" width=\"800\" height=\"600\">\n";
	out << "<rect width=\"100%\" height=\"100%\" fill=\"white\" />\n";

	const auto& shapes = model.getShapes(slideIndex);

	for (const auto& shape : shapes) {

		if (shape->type() == "Rectangle") {
			auto r = std::dynamic_pointer_cast<RectangleShape>(shape);
			out << "<rect x=\"" << r->getX() << "\" "
				<< "y=\"" << r->getY() << "\" "
				<< "width=\"" << r->getWidth() << "\" "
				<< "height=\"" << r->getHeight() << "\" "
				<< "fill=\"" << (r->isFilled() ? r->getColor() : "none") << "\" "
				<< "stroke=\"" << r->getColor() << "\" />\n";
		}

		else if (shape->type() == "Square") {
			auto s = std::dynamic_pointer_cast<SquareShape>(shape);
			out << "<rect x=\"" << s->getX() << "\" "
				<< "y=\"" << s->getY() << "\" "
				<< "width=\"" << s->getSize() << "\" "
				<< "height=\"" << s->getSize() << "\" "
				<< "fill=\"" << (s->isFilled() ? s->getColor() : "none") << "\" "
				<< "stroke=\"" << s->getColor() << "\" />\n";
		}

		else if (shape->type() == "Circle") {
			auto c = std::dynamic_pointer_cast<CircleShape>(shape);
			out << "<circle cx=\"" << c->getX() << "\" "
				<< "cy=\"" << c->getY() << "\" "
				<< "r=\"" << c->getRadius() << "\" "
				<< "fill=\"" << (c->isFilled() ? "black" : "none") << "\" "
				<< "stroke=\"black\" />\n";
		}

		else if (shape->type() == "Triangle") {
			auto t = std::dynamic_pointer_cast<TriangleShape>(shape);
			int side = t->getSide();

			out << "<polygon points=\""
				<< t->getX() << "," << t->getY() << " "
				<< t->getX() + side << "," << t->getY() << " "
				<< t->getX() + side / 2 << "," << (t->getY() - side)
				<< "\" fill=\"" << (t->isFilled() ? t->getColor() : "none")
				<< "\" stroke=\"" << t->getColor() << "\" />\n";
		}
	}

	out << "</svg>\n";
	out.close();
	return true;
}