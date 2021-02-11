/*
	Реализация связи между двумя ПК через последовательный порт
	
	Сделал:
	Балушкин Богдан
	ПЗ1812
*/

#include <Windows.h>
#include <iostream>
#include <memory>
#include "COMPort.h"

int main(int argc, char* argv[])
{
	// Выбираем порт
	int choose;
	std::cout << "[1] - COM1" << std::endl
		<< "[2] - COM2" << std::endl
		<< "$ ";
	std::cin >> choose;

	std::unique_ptr<COMPort> port;
	try
	{
		if (choose == 1)
			port = std::make_unique<COMPort>(L"COM1");
		else if (choose == 2)
			port = std::make_unique<COMPort>(L"COM2");
		port->SetSerialParams(CBR_9600, 8, ONESTOPBIT, NOPARITY);
	}
	catch (const char* Exception) {
		std::cout << "Error: " << Exception << std::endl;
		return 0;
	}
	// Выбираем действие
	try
	{
		do
		{
			std::cout << "[1] - Read" << std::endl
				<< "[2] - Write" << std::endl
				<< "[3] - Exit" << std::endl
				<< "$ ";
			std::cin >> choose;

			if (choose == 1)
				std::cout << port->Read() << std::endl;
			else if (choose == 2)
			{
				std::string data;
				std::cout << "Enter message: ";
				std::getline(std::cin >> std::ws, data);
				port->Write(data.c_str(), sizeof(data));
			}
		} while (choose != 3);
	}
	catch (const char* Exception)
	{
		std::cout << "Error: " << Exception << std::endl;
	}
	system("pause");
	return 0;
}

