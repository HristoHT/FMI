#include "Warehouse.h"

std::vector<std::string> split(std::string str, std::string splitter) {
	std::string attr;
	std::vector<std::string> r;
	size_t pos = 0;

	while ((pos = str.find(splitter)) != std::string::npos)
	{
		attr = str.substr(0, pos);
		str.erase(0, pos + splitter.length());
		r.push_back(attr);
	}
	r.push_back(str);
	return r;
}

Warehouse::Warehouse() {
	setMaxVolume(1);
	setVolume(0);
	setName("Unknown Warehouse");
}

Warehouse::Warehouse(std::string name, size_t maxVolume) {
	setName(name);
	setMaxVolume(maxVolume);
	setVolume(0);
}

Warehouse::~Warehouse() {
	for (size_t i = 0; i < _locations.size(); i++)
		delete _locations[i];
	for (size_t i = 0; i < _stocks.size(); i++)
		delete _stocks[i];
	for (size_t i = 0; i < _operations.size(); i++)
		delete _operations[i];
}

void Warehouse::_copy(const Warehouse& other) {
	if (this != &other) {
		_locations = other.getLocations();
		_stocks = other.getStocks();
		setMaxVolume(other.getMaxVolume());
		setVolume(other.getVolume());
		setName(other.getName());
	}
}

Warehouse::Warehouse(const Warehouse& other) {
	_copy(other);
}

Warehouse& Warehouse::operator=(const Warehouse& other) {
	_copy(other);
	return *this;
}

Location& Warehouse::operator[](size_t i) {
	if (i < _locations.size()) {
		return *_locations[i];
	}

	throw "Index is too large";
}

Location Warehouse::operator[](size_t i) const {
	if (i < _locations.size()) {
		return *_locations[i];
	}

	throw "Index is too large";
}

void Warehouse::setMaxVolume(size_t maxVolume) {
	_maxVolume = maxVolume;
}

size_t Warehouse::getMaxVolume() const {
	return _maxVolume;
}

void Warehouse::setVolume(size_t maxVolume) {
	_currentVolume = maxVolume;
}

size_t Warehouse::getVolume() const {
	return _currentVolume;
}

void Warehouse::setName(std::string name) {
	_name = name;
}

std::string Warehouse::getName() const {
	return _name;
}

std::vector<Location*> Warehouse::getLocations() const {
	return _locations;
}

std::vector<Stock*> Warehouse::getStocks() const {
	return _stocks;
}

void Warehouse::addLocation(std::string name, size_t volume) {
	if (getVolume() + volume < getMaxVolume())
		_locations.push_back(new Location(name, volume));
	else throw std::string("The store is not big enought");
}

StoreOperation* Warehouse::generateLocations(size_t locationCount, size_t volume) {
	try {
		if (volume > 0) {
			if (getVolume() + volume * locationCount < getMaxVolume()) {
				for (size_t i = 0; i < locationCount; i++) {
					addLocation(std::to_string(_locations.size()), volume);
				}
			}
			else throw std::string("The store is not big enought");
		}
		else {
			volume = getMaxVolume() / locationCount;
			int sizeOfLastLocation = volume + getMaxVolume() % locationCount;

			for (size_t i = 0; i < locationCount - 1; i++) {
				addLocation(std::to_string(_locations.size()), volume);
			}
			addLocation(std::to_string(_locations.size()), sizeOfLastLocation);
		}

		StoreOperation* newOperation = new StoreOperation("LOCATION", std::to_string(locationCount) + "|" + std::to_string(volume));

		_operations.push_back(newOperation);

		return newOperation;
	}
	catch (const std::string e) {
		std::cout << e << "\n";
		return nullptr;
	}
}

StoreOperation* Warehouse::sellStock(std::string name, int qty) {
	try {
		size_t stockPos = findStock(name);

		if (stockPos) {
			stockPos--;

			_stocks[stockPos]->removeQuantity(qty);
			setVolume(getVolume() - qty);

			StoreOperation* newOperation = new StoreOperation("SELL", name + "|" + std::to_string(qty));

			_operations.push_back(newOperation);

			return newOperation;
		}
		return nullptr;
	}
	catch (const std::string e) {
		std::cout << e << "\n";
		return nullptr;
	}
}

StoreOperation* Warehouse::addStock(std::string name, int quantity, Date batch,
		std::string supplier, std::string measure, std::string comment) {
	int operationQty = quantity;
	try {
		size_t stockPos = findStock(name);

		if ((_currentVolume + quantity) > _maxVolume)
			throw (std::string)"Not enought space in the warehouse";

		setVolume(_currentVolume + quantity);

		std::vector<Location*> availableLocations = findLocationsToFit(quantity);

		if (stockPos) {
			stockPos -= 1;
		}
		else {
			stockPos = _stocks.size();
			_stocks.push_back(new Stock(name, supplier, measure, comment));
		}

		_stocks[stockPos]->addBatch(batch, quantity);

		size_t batchPos = _stocks[stockPos]->find(batch);
		batchPos--;
		//Тука би трябвало задължително да я има партидата, щото сме я добавили два реда по-нагоре
		for (size_t i = 0; i < availableLocations.size(); i++) {
			int locationAvailableQty = availableLocations[i]->getAvailableSpace();
			if (quantity > locationAvailableQty) {
				availableLocations[i]->addBatch(&_stocks[stockPos]->getBatch(batchPos), locationAvailableQty);
				quantity -= locationAvailableQty;
			}
			else {
				availableLocations[i]->addBatch(&_stocks[stockPos]->getBatch(batchPos), quantity);
			}

			//Ако партидата вече присъства на локацията не се добавя локацията към вектора с локации на партидата
			if (!_stocks[stockPos]->getBatch(batchPos).findLocation(availableLocations[i]))
				_stocks[stockPos]->getBatch(batchPos).addLocation(availableLocations[i]);
		}

		StoreOperation* newOperation = new StoreOperation("ADD", name + "|" + std::to_string(operationQty) + "|" + batch.getByElements());
		_operations.push_back(newOperation);

		return newOperation;
	}
	catch (const std::string e) {
		std::cout << e << "\n";
		return nullptr;
	}

}

void Warehouse::clean() {
	printElement("Batch", 10, std::cout);
	printElement("Quantity", 10, std::cout);
	std::cout << '\n';
	for (size_t i = 0; i < _stocks.size(); i++) {
		_stocks[i]->clean(this);
	}
}

size_t Warehouse::findStock(std::string name) {
	for (size_t i = 0; i < _stocks.size(); i++) {
		if (_stocks[i]->getName() == name)
			return i + 1;
	}

	return 0;
}

std::vector<Location*> Warehouse::findLocationsToFit(int quantity) {
	std::vector<Location*> availableLocations;
	int spreadedQuantity = 0;

	for (size_t i = 0; i < _locations.size(); i++) {
		if (_locations[i]->canFit(quantity))
			return std::vector<Location*> {_locations[i]};

		if (_locations[i]->getAvailableSpace() > 0 && spreadedQuantity < quantity) {
			spreadedQuantity += _locations[i]->getAvailableSpace();
			availableLocations.push_back(_locations[i]);
		}
	}

	return availableLocations;
}

void Warehouse::printStocks(std::ostream& out) {
	printElement("Store: " + _name, 30, out);
	printElement((std::string)"Space:" + std::to_string(_currentVolume) + "\\" + std::to_string(_maxVolume), 10, out, 0);
	out << "\n";

	for (size_t i = 0; i < _stocks.size(); i++) {
		_stocks[i]->print(out);
	}
}

void Warehouse::printLocations(std::ostream& out) {
	printElement("Store: " + _name, 30, out);
	printElement((std::string)"Space:" + std::to_string(_currentVolume) + "\\" + std::to_string(_maxVolume), 10, out, 0);
	out << "\n";

	for (size_t i = 0; i < _locations.size(); i++) {
		_locations[i]->print(out);
		out << "\n";
	}
}

void Warehouse::print(std::ostream& out) {
	for (size_t i = 0; i < _operations.size(); i++) {
		_operations[i]->print(out);
	}
}

void Warehouse::read(std::istream& in) {
	std::string line;

	while (std::getline(in, line))
	{
		std::vector<std::string> attributes = split(line, "|");

		int operationYear = std::stoi(attributes[1]),
			operationMonth = std::stoi(attributes[2]),
			operationDay = std::stoi(attributes[3]);
		StoreOperation* loadedOperation = nullptr;

		if (attributes[0] == "ADD") {
			int stockQuantity = std::stoi(attributes[5]),
				stockYear = std::stoi(attributes[6]),
				stockMonth = std::stoi(attributes[7]),
				stockDay = std::stoi(attributes[8]);

			std::string stockName = attributes[4];

			loadedOperation = addStock(stockName, stockQuantity, Date(stockDay, stockMonth, stockYear));
		}
		else if (attributes[0] == "SELL") {
			std::string stockName = attributes[4];
			int stockQuantity = std::stoi(attributes[5]);

			loadedOperation = sellStock(stockName, stockQuantity);
		}
		else if (attributes[0] == "LOCATION") {
			int locationCount = std::stoi(attributes[4]),
				locationVolume = std::stoi(attributes[5]);

			loadedOperation = generateLocations(locationCount, locationVolume);
		}

		if (loadedOperation)
			loadedOperation->_date = Date(operationDay, operationMonth, operationYear);
	}
}

void Warehouse::writeFile(std::string filename) {
	std::ofstream file;
	file.open(filename + ".txt");
	if (!file)
		throw std::string("Problem occured opening the file!");
	print(file);
	file.close();
}

void Warehouse::readFile(std::string filename) {
	std::ifstream file;
	file.open(filename + ".txt");
	if (!file)
		throw std::string("Problem occured opening the file!");
	read(file);
	file.close();
}

void Warehouse::printStockMovement(Date from, Date to, std::ostream& out) {
	printElement("Stock", 30, out);
	printElement("Quantity", 10, out, 0);
	out << "\n";
	for (size_t i = 0; i < _operations.size(); i++) {
		if (_operations[i]->_date >= from && _operations[i]->_date <= to) {
			std::vector<std::string> attr = split(_operations[i]->_content, "|");
			if (_operations[i]->_type == "ADD" || _operations[i]->_type == "SELL") {
				printElement(attr[0], 30, out);
				printElement((_operations[i]->_type != "ADD" ? "-" : "+") + attr[1], 10, out, 0);
				out << "\n";
			}
		}
	}
}
