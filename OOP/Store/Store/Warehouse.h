#pragma once
#include "Location.h"
#include "StoreOperation.h"
#include <fstream>
class Location;
class Stock;
class Warehouse
{
	std::vector<Location*> _locations;
	std::vector<Stock*> _stocks;
	std::vector<StoreOperation*> _operations;
	size_t _maxVolume = 1, _currentVolume = 0;
	std::string _name;

	void _copy(const Warehouse& other);
public:
	Warehouse();
	Warehouse(std::string name, size_t maxVolume = 1);
	~Warehouse();
	Warehouse(const Warehouse& other);
	Warehouse& operator= (const Warehouse& other);
	Location& operator[] (size_t i);
	Location operator[] (size_t i) const;

	void setMaxVolume(size_t maxVolume);
	size_t getMaxVolume() const;

	void setVolume(size_t maxVolume);
	size_t getVolume() const;

	void setName(std::string name);
	std::string getName() const;

	std::vector<Stock*> getStocks()const;
	StoreOperation* addStock(std::string name, int quantity = 0, Date batch = Date(), std::string supplier = "No supplier", std::string measure = "PCS", std::string comment = " No comment");
	size_t findStock(std::string name);
	StoreOperation* sellStock(std::string name, int qty);

	std::vector<Location*> getLocations() const;
	void addLocation(std::string name, size_t volume);
	StoreOperation* generateLocations(size_t locationCount, size_t volume = 0);
	std::vector<Location*> findLocationsToFit(int quantity);

	void clean();

	void printStocks(std::ostream& out = std::cout);
	void printLocations(std::ostream& out = std::cout);
	void print(std::ostream& out = std::cout);
	void read(std::istream& in = std::cin);
	void readFile(std::string filename = "Store");
	void writeFile(std::string filename = "Store");
	void printStockMovement(Date from, Date to, std::ostream& out = std::cout);
};

