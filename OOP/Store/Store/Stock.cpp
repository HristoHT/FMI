#include "Stock.h"
#include "Date.h"
Stock::Stock() {
	setQuantity(0);
	setName("Unknown");
	setSupplier("Unknown");
	setMeasure("PCS");
	setComment(" No comment");
	_createdOn = Date();
}

Stock::Stock(const std::string name, const std::string supllier,
	const std::string measure, const std::string comment) {
	setQuantity(0);
	setName(name);
	setSupplier(supllier);
	setMeasure(measure);
	setComment(comment);
	_createdOn = Date();
}

Stock::~Stock() {
	for (size_t i = 0; i < _batches.size(); i++)
		delete _batches[i];
}

void Stock::_copy(const Stock& other) {
	if (this != &other) {
		setQuantity(other.getQuantity());
		_batches = other.getBatches();
		_createdOn = Date();
		setSupplier(other.getSupplier());
		setName(other.getName());
		setMeasure(other.getMeasure());
		setComment(other.getComment());
	}
}

Stock::Stock(const Stock& other) {
	_copy(other);
}

Stock& Stock::operator= (const Stock& other) {
	_copy(other);
	return *this;
}

Batch& Stock::operator[] (size_t i) {
	if (i < _batches.size()) {
		return *_batches[i];
	}

	throw "index is too large";
}

Batch& Stock::getBatch(size_t i) {
	if (i < _batches.size()) {
		return *_batches[i];
	}

	throw "index is too large";
}

Batch Stock::operator[] (size_t i) const {
	if (i < _batches.size()) {
		return *_batches[i];
	}

	throw "index is too large";
}

void Stock::clean(Warehouse* warehousePtr) {
	Date today;
	for (size_t i = 0; i < _batches.size(); i++) {
		std::cout << _batches[i]->getDate().getDate() << " " << today.getDate()	 << std::endl;
		if (_batches[i]->getDate() < today) {
			warehousePtr->setVolume(warehousePtr->getVolume() - _batches[i]->getQuantity());
			printElement("", 1, std::cout);
			printElement(_batches[i]->getDate().getISODate(), 10, std::cout);
			printElement(_batches[i]->getQuantity() * -1, 10, std::cout, 0);
			std::cout << '\n';
			removeQuantity(_batches[i]->getQuantity());
			i--;
		}
	}
}

void Stock::setQuantity(int quantity) {
	_quantity = quantity;
}

int Stock::getQuantity() const {
	return _quantity;
}

void Stock::setName(std::string name) {
	_name = name;
}

void Stock::setComment(std::string name) {
	_comment = name;
}

void Stock::setSupplier(std::string name) {
	_supplier = name;
}

void Stock::setMeasure(std::string name) {
	_measure = name;
}

std::string Stock::getName()const {
	return _name;
}

std::string Stock::getMeasure()const {
	return _measure;
}

std::string Stock::getComment()const {
	return _comment;
}

std::string Stock::getSupplier()const {
	return _supplier;
}

std::vector<Batch*> Stock::getBatches() const {
	return _batches;
}

bool Stock::operator== (std::string name) {
	return (_name == name);
}

bool Stock::operator== (const Stock& other) {
	return (_name == other.getName());
}

void Stock::removeQuantity(int quantity) {

	if (quantity > getQuantity()) {
		throw std::string("Nqmame dostatachno kolichestvo!");
	}

	setQuantity(getQuantity() - quantity);
	std::sort(_batches.begin(), _batches.end(), [](Batch* a, Batch* b) -> bool { return a->getDate() < b->getDate(); });
	for (size_t i = 0; i < _batches.size(); i++) {
		if (quantity == 0) break;

		int batchQuantity = _batches[i]->getQuantity();
		if (batchQuantity >= quantity) {
			removeFromBatch(_batches[i], quantity);
			quantity = 0;
		}
		else {
			removeFromBatch(_batches[i], batchQuantity);
			quantity -= batchQuantity;
		}

		if (!_batches[i]->getQuantity()) {
			removeBatch(_batches[i]);
			i--;
		}
	}
}

void Stock::removeBatch(Batch* batch) {
	std::vector<Batch*>::iterator it = std::remove_if(_batches.begin(), _batches.end(), [&batch](Batch* batchPtr)->bool { return batchPtr == batch; });
	_batches.erase(it);
}

void Stock::addBatch(Date date, int quantity) {
	size_t batchPos = find(date);

	setQuantity(_quantity + quantity);

	if (batchPos - 1 != -1) {
		_batches[batchPos - 1]->setQuantity(_batches[batchPos - 1]->getQuantity() + quantity);
	}
	else {
		_batches.push_back(new Batch(this, date, quantity));
	}
}

void Stock::removeFromBatch(Batch* batch, int quantity) {
	batch->removeQuantity(quantity);
}

size_t Stock::find(Date date) {
	for (size_t i = 0; i < _batches.size(); i++) {
		if (*_batches[i] == date)
			return i + 1;
	}

	return 0;
}

void Stock::print(std::ostream& out, int offset) {
	printElement("", offset, out);
	printElement(_name, 25, out);
	printElement(_supplier, 25, out);
	printElement(_createdOn.getISODate(), 10, out);
	printElement(_measure, 10, out);
	printElement(_quantity, 10 - offset, out, 0);
	printElement(_comment, 60, out);

	out << "\n";

	for (size_t i = 0; i < _batches.size(); i++) {
		_batches[i]->print(out, offset + 1);
	}
}