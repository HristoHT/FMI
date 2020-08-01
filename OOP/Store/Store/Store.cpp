#include <iostream>
#include "Warehouse.h"
#include "Stock.h"
#include "StoreOperation.h"
#include <cstdlib>


std::vector<std::string> split(std::string str, std::string splitter);

bool isInt(const std::string& number)
{
	return !number.empty() && std::find_if(number.begin(),
		number.end(), [](unsigned char c) { return !std::isdigit(c); }) == number.end();
}

int toInt(const std::string& number) {
	if (isInt(number)) {
		return std::stoi(number);
	}

	throw std::string("Incorect input!Try again!");
}

int main()
{
	std::string line;
	Warehouse* mystore = new Warehouse("My store", 1000);
	mystore->generateLocations(6);
	std::cout << "Demo versiq na sistema za sklad. Skladat Vi ima vmestimost 1000 i 6 lokacii, za palna versiq zaplateta abonamenta na Hristo H. Todorov.\n";
	std::string err1 = "Molq vavedete vsichki danni\n";
	std::string fyleInUsage = "store";
	while (std::getline(std::cin, line)) {
		try {
			std::vector<std::string> attr = split(line, " ");

			if (attr[0] == "print") {
				mystore->printStocks();
				std::cout << '\n';
				mystore->printLocations();
			}
			else if (attr[0] == "remove") {
				std::string stockName = attr[1];
				int stockQuantity = toInt(attr[2]);

				mystore->sellStock(stockName, stockQuantity);
			}
			else if (attr[0] == "add") {
				if (attr.size() < 6)
					throw std::string("The minimal format of the comand is: add NAME QUANTITY DD MM YYYY");

				std::string stockName = attr[1], supplier = "", measure = "PCS", comment="";
				int stockQuantity = toInt(attr[2]),
					stockDay = toInt(attr[3]),
					stockMonth = toInt(attr[4]),
					stockYear = toInt(attr[5]);

				if (attr.size() >= 7)supplier = attr[6];
				if (attr.size() >= 8)measure = attr[7];
				if (attr.size() >= 9) {
					for (size_t i = 8; i < attr.size(); i++)
						comment += " " + attr[i];
				}

				mystore->addStock(stockName, stockQuantity, Date(stockDay, stockMonth, stockYear), supplier, measure, comment);
			}
			else if (attr[0] == "log") {
				if(attr.size() < 8)
					throw std::string("The minimal format of the comand is: log DD MM YYYY to DD MM YYYY");

				int fromDay = toInt(attr[1]),
					fromMonth = toInt(attr[2]),
					fromYear = toInt(attr[3]),
					toDay = toInt(attr[5]),
					toMonth = toInt(attr[6]),
					toYear = toInt(attr[7]);

				mystore->printStockMovement(Date(fromDay, fromMonth, fromYear), Date(toDay, toMonth, toYear));
			}
			else if (attr[0] == "clean") {
				mystore->clean();
			}
			else if (attr[0] == "open") {
				delete mystore;
				mystore = new Warehouse("My store", 1000);

				if (attr.size() < 2)
					throw std::string("The command should be: open FILENAME");
				std::string fylename = attr[1];
				fyleInUsage = fylename;
				mystore->readFile(fyleInUsage);
				std::cout << "File " << fyleInUsage << ".txt readed!\n";
			}
			else if (attr.size() >= 2 && attr[0] == "save" && attr[1] == "as") {
				if(attr.size() < 3)
					throw std::string("The command should be: save as FILENAME");
				std::string fylename = attr[2];
				mystore->writeFile(fylename);
				std::cout << "File " << fylename << ".txt saved!\n";
			}
			else if (attr[0] == "save") {
				mystore->writeFile(fyleInUsage);
				std::cout << "File " << fyleInUsage << ".txt saved!\n";
			}
			else if (attr[0] == "exit") {
				exit(0);
			}
			else if (attr[0] == "close") {
				fyleInUsage = "store";
				std::cout << "File return to default (store.txt)\n";
			}
			else if (attr[0] == "help") {
				printElement("Command", 40, std::cout);
				printElement("Description", 60, std::cout);
				std::cout << "\n";
				
				printElement("print", 40, std::cout);
				printElement("Print two types of reports", 60, std::cout);
				std::cout << "\n";

				printElement("add STOCKNAME QUANTIY DD MM YYYY ", 40, std::cout);
				printElement("Add stock to the store additional parameters are SUPPLIER MEASURE COMMENT", 60, std::cout);
				std::cout << "\n";
				
				printElement("remove STOCKNAME QUANTIY ", 40, std::cout);
				printElement("Remove stock from the store", 60, std::cout);
				std::cout << "\n";
				
				printElement("log DD MM YYYY to DD MM YYYY ", 40, std::cout);
				printElement("Print stock movement in this period", 60, std::cout);
				std::cout << "\n";

				printElement("clean", 40, std::cout);
				printElement("Remove all stocks' batches which are with expired date", 60, std::cout);
				std::cout << "\n";
				
				printElement("open FILENAME(no extenssion)", 40, std::cout);
				printElement("Open a file with store operations in it", 60, std::cout);
				std::cout << "\n";

				printElement("save", 40, std::cout);
				printElement("Save in the oppened file or in the default one (store.txt)", 60, std::cout);
				std::cout << "\n";
				
				printElement("save as FILENAME", 40, std::cout);
				printElement("Save in file", 60, std::cout);
				std::cout << "\n";
				
				printElement("close", 40, std::cout);
				printElement("Return the file in the default file (store.txt)", 60, std::cout);
				std::cout << "\n";
				
				printElement("exit", 40, std::cout);
				printElement("Exit the program", 60, std::cout);
				std::cout << "\n";
			}
			else {
				std::cout << "Unknown command.Type help for all commands.\n";
			}
		}
		catch (std::string e) {
			std::cout << e << "\n";
		}
	}

}
