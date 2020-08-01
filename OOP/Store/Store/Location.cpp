#include "Location.h"

Location::Location() {
	setMaxVolume(1);
	setVolume(0);
	setName("");
}

Location::Location(std::string name, int maxVolume) {
	setMaxVolume(maxVolume);
	setVolume(0);
	setName(name);
}

Location::~Location() {

}

Location::Location(const Location& other) {
	_copy(other);
}

Location& Location::operator=(const Location& other) {
	_copy(other);
	return *this;
}

void Location::_copy(const Location& other) {
	if (this != &other) {
		setMaxVolume(other.getMaxVolume());
		setVolume(other.getVolume());
		setName(other.getName());
		_batches = getBatches();
	}
}

void Location::setName(std::string name) {
	_name = name;
}

std::string Location::getName() const {
	return _name;
}

void Location::setMaxVolume(int maxVolume) {
	_maxVolume = maxVolume;
}

int Location::getMaxVolume() const {
	return _maxVolume;
}

void Location::setVolume(int volume) {
	_volume = volume;
}

int Location::getVolume() const {
	return _volume;
}

std::vector<std::pair<Batch*, int>> Location::getBatches() const {
	return _batches;
}

void Location::addBatch(Batch* newbatch, int quantity) {
	size_t batchPos = find(newbatch);

	setVolume(getVolume() + quantity);

	if (!batchPos) {
		_batches.push_back(std::make_pair(newbatch, quantity));
	}
	else {
		batchPos -= 1;
		_batches[batchPos].second += quantity;
	}

}

std::pair<Batch*, int>& Location::getBatch(const Batch* batch) {
	size_t batchPos = find(batch);

	if (batchPos) {
		return _batches[batchPos - 1];
	}

	throw "There is no such batch";
}

void Location::removeBatch(Batch* removebatch) {
	//std::remove(_batches.begin(), _batches.end(), std::make_pair(removebatch, 0));
	removebatch->removeLocation(this);

	auto it = std::remove_if(
		_batches.begin(),
		_batches.end(),
		[removebatch](std::pair<Batch*, int> const& data) {
			if (data.first == removebatch) return true;
			else return false;
		}
	);

	_batches.erase(it);

}

int Location::getAvailableSpace() {
	return _maxVolume - _volume;
}

bool Location::canFit(int quantity) {
	return quantity <= getAvailableSpace();
}

/*size_t Location::find(std::string date) {
	for (size_t i = 0; i < _batches.size(); i++) {
		if (*_batches[i] == date)
			return i + 1r
	}

	return 0;
}*/

size_t Location::find(const Batch* batch) {
	for (size_t i = 0; i < _batches.size(); i++) {
		if (*(_batches[i].first) == *batch)
			return i + 1;
	}

	return 0;
}

void Location::print(std::ostream& out, int offset) {
	printElement("", offset, out);
	printElement("Location: " + _name, 25, out);
	printElement((std::string)"Space:" + std::to_string(_volume) + "\\" + std::to_string(_maxVolume), 10, out, 0);
	out << "\n";

	for (size_t i = 0; i < _batches.size(); i++) {
		printElement("", offset + 1, out);
		printElement(_batches[i].first->getDate().getISODate(), 25, out);
		printElement(_batches[i].first->getStock()->getName(), 25, out);
		printElement(_batches[i].second, 10, out, 0);
		out << "\n";
	}
}

void Location::printBatch(Batch* batch, std::ostream& out, int offset) {
	std::pair<Batch*, int> batchPair = _batches[find(batch) - 1];//Това идва от партида => трябва да същество локация, на която да отгожаря
	printElement("", offset, out);
	printElement(std::string("Location: ") + getName(), 70, out);
	printElement(batchPair.second, 10 - offset, out, 0);
	out << "\n";
}