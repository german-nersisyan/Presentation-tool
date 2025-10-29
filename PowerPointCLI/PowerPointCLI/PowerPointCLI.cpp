// PowerPointCLI.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <memory>
#include "Tokenizer.h"
#include "Parser.h"
#include "Commands.h"
#include "Shapes.h"
#include "RectangleShape.h"

int main() {
	Tokenizer tokenizer;
	Parser parser;
	Shapes slideShapes;

	std::string input;
	std::cout << "Enter command: ";
	std::getline(std::cin, input);

	try {
		auto tokens = tokenizer.tokenize(input);
		auto data = parser.parse(tokens);

		std::unique_ptr<ICommand> command;

		if (data.name == "add-slide") {
			command = std::make_unique<AddSlideCommand>(data.options, data.flags);
		}
		else if (data.name == "remove-slide") {
			command = std::make_unique<RemoveSlideCommand>(data.options);
		}
		else if (data.name == "add-shape") {
			command = std::make_unique<AddShapeCommand>(data.options, data.flags, slideShapes);
		}
		else {
			throw std::runtime_error("Unknown command: " + data.name);
		}

		command->execute();

		std::cout << "\nAll shapes in slide: " << slideShapes.count() << "\n";
		slideShapes.drawAll();

	}
	catch (const std::exception& ex) {
		std::cerr << "Error: " << ex.what() << "\n";
	}
}

// Запуск программы: CTRL+F5 или меню "Отладка" > "Запуск без отладки"
// Отладка программы: F5 или меню "Отладка" > "Запустить отладку"

// Советы по началу работы 
//   1. В окне обозревателя решений можно добавлять файлы и управлять ими.
//   2. В окне Team Explorer можно подключиться к системе управления версиями.
//   3. В окне "Выходные данные" можно просматривать выходные данные сборки и другие сообщения.
//   4. В окне "Список ошибок" можно просматривать ошибки.
//   5. Последовательно выберите пункты меню "Проект" > "Добавить новый элемент", чтобы создать файлы кода, или "Проект" > "Добавить существующий элемент", чтобы добавить в проект существующие файлы кода.
//   6. Чтобы снова открыть этот проект позже, выберите пункты меню "Файл" > "Открыть" > "Проект" и выберите SLN-файл.
