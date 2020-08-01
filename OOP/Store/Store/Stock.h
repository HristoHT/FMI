#pragma once
#include "Batch.h"
#include "Functions.h"
#include "Date.h"
#include <iostream>
#include <algorithm>
#include "Warehouse.h";
class Batch;
class Warehouse;
class Stock
{
	std::string _name, _supplier, _measure, _comment;
	std::vector <Batch*> _batches;
	int _quantity;
	Date _createdOn;

	void _copy(const Stock& other);

public:
	Stock();
	Stock(const std::string name, const std::string supllier = "No supplier",
		const std::string measure = "PCS", const std::string comment = " No comment");
	~Stock();
	Stock(const Stock& other);
	Stock& operator= (const Stock& other);
	Batch& operator[] (size_t i);
	Batch operator[] (size_t i) const;
	Batch& getBatch(size_t i);

	bool operator== (std::string name);
	bool operator== (const Stock& other);

	void setQuantity(int quantity);
	int getQuantity() const;
	void removeQuantity(int quantity);
	void removeBatch(Batch* batch);

	Date getCreatedOn() const;

	void setName(std::string name);
	std::string getName() const;

	void setMeasure(std::string name);
	std::string getMeasure() const;

	void setComment(std::string name);
	std::string getComment() const;

	void setSupplier(std::string name);
	std::string getSupplier() const;

	std::vector<Batch*> getBatches() const;
	void addBatch(Date date, int quantity);
	void removeFromBatch(Batch* batch, int quantity);
	void clean(Warehouse* warehousePtr);

	size_t find(Date date);

	void print(std::ostream& out = std::cout, int offset = 1);
};

