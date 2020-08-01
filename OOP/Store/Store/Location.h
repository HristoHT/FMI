#pragma once
#include<vector>
#include "Batch.h"

class Batch;
class Location
{
	int _volume = 0, _maxVolume = 1;
	std::vector <std::pair<Batch*, int>> _batches;
	std::string _name;

	void _copy(const Location& other);
public:
	Location();
	Location(std::string name, int maxVolume = 1);
	~Location();
	Location(const Location& other);
	Location& operator= (const Location& other);

	void setMaxVolume(int maxVolume);
	int getMaxVolume() const;

	void setVolume(int volume);
	int getVolume() const;

	void setName(std::string name);
	std::string getName() const;

	std::vector<std::pair<Batch*, int>> getBatches() const;
	void addBatch(Batch* newbatch, int quantity = 0);
	void removeBatch(Batch* removebatch);

	int getAvailableSpace();
	bool canFit(int quantity);

	size_t find(std::string date);
	size_t find(const Batch* batch);
	std::pair<Batch*, int>& getBatch(const Batch* batch);

	void print(std::ostream& out = std::cout, int offset = 1);
	void printBatch(Batch* batch, std::ostream& out = std::cout, int offset = 1);
};

