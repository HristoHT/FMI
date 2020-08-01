#pragma once
#include <string>
#include <vector>
#include <iostream>
#include "Location.h"
#include "Stock.h"
#include "Functions.h"
#include "Date.h"

class Location;
class Stock;

class Batch
{
	Date _date;
	std::vector<Location *>  _locations;
	Stock* _stock = nullptr;
	int _quantity;

	void _copy(const Batch& other);
public:
	Batch();
	Batch(Stock* stockptr, const Date date, int quantity = 0);
	~Batch();
	Batch(const Batch& other);
	Batch& operator= (const Batch& other);

	bool operator==(const Date date);//това трябва да се използва само в клас STOCK
	bool operator==(const Batch& other);

	void setDate(const Date date);
	Date getDate() const;

	void setStock(Stock* stockptr);
	Stock* getStock() const;

	void setQuantity(int quantity);
	int getQuantity() const;

	void removeQuantity(int quantity);

	size_t findLocation(Location* location);
	std::vector<Location*> getLocations() const;
	void addLocation(Location* newlocation);
	void removeLocation(Location* removelocation);

	void print(std::ostream& out = std::cout, int offset = 1);
};

