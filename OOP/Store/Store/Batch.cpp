#include "Batch.h"

Batch::Batch() {
	setDate(Date());
	_stock = nullptr;
	setQuantity(0);
}

Batch::Batch(Stock* stockptr, const Date date, int quantity) {
	setDate(date);
	setStock(stockptr);
	setQuantity(quantity);
}

Batch::~Batch() {

}

void Batch::_copy(const Batch& other) {
	if (this != &other) {
		setDate(other.getDate());
		_locations = other.getLocations();
		setStock(other.getStock());
		setQuantity(other.getQuantity());
	}
}

Batch::Batch(const Batch& other) {
	_copy(other);
}

Batch& Batch::operator=(const Batch& other) {
	_copy(other);
	return *this;
}

bool Batch::operator== (Date date) {
	return (_date == date);
}

bool Batch::operator== (const Batch& other) {
	return (_date == other.getDate() && other.getStock() == getStock());
}

void Batch::setDate(const Date date) {
	_date = date;
}

Date Batch::getDate() const {
	return _date;
}

void Batch::setStock(Stock* stockptr) {
	_stock = stockptr;
}

Stock* Batch::getStock() const {
	return _stock;
}

void Batch::setQuantity(int quantity) {
	_quantity = quantity;
}

int Batch::getQuantity() const {
	return _quantity;
}

std::vector<Location*> Batch::getLocations() const {
	return _locations;
}

void Batch::addLocation(Location* newlocation) {
	_locations.push_back(newlocation);
}

void Batch::removeLocation(Location* removelocation) {
	auto it = std::remove_if(
		_locations.begin(),
		_locations.end(),
		[removelocation](Location* const& data) {
			if (data == removelocation) return true;
			else return false;
		}
	);

	_locations.erase(it);
}

size_t Batch::findLocation(Location* location) {
	for (size_t i = 0; i < _locations.size(); i++) {
		if (location == _locations[i])
			return i + 1;
	}

	return 0;
}

void Batch::removeQuantity(int quantity) {
	setQuantity(getQuantity() - quantity);

	for (size_t i = 0; i < _locations.size(); i++) {
		if (quantity == 0) {

		}
		int locationQty = _locations[i]->getBatch(this).second;
		
		if (locationQty >= quantity) {
			_locations[i]->getBatch(this).second -= quantity;
			_locations[i]->setVolume(_locations[i]->getVolume() - quantity);
			std::cout << quantity << " " << _stock->getMeasure() << " from batch " << getDate().getISODate()
				<< " in location " << _locations[i]->getName() << '\n';
			quantity = 0;
		}
		else {
			std::cout << locationQty << " " << _stock->getMeasure() << " from batch " << getDate().getISODate()
				<< " in location " << _locations[i]->getName() << '\n';
			quantity -= locationQty;
			_locations[i]->setVolume(_locations[i]->getVolume() - locationQty);
			_locations[i]->getBatch(this).second = 0;
		}


		if (_locations[i]->getBatch(this).second == 0) {
			_locations[i]->removeBatch(this);
			i--;
		}
	}
}

void Batch::print(std::ostream& out, int offset) {
	printElement("", offset, out);
	//printElement(_stock, 25, out);
	printElement(_date.getISODate(), 70, out);
	printElement(_quantity, 10 - offset, out, false);
	out << "\n";

	for (size_t i = 0; i < _locations.size(); i++) {
		_locations[i]->printBatch(this, out, offset + 1);
	}
}

/*BatchHolder::BatchHolder(Batch* b, int qty) {
	batch = b;
	quantity = qty;
}*/