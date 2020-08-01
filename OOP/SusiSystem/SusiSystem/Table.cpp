#include "Table.h"

Table::Table(std::vector<std::string> columns) {
	_columns = { columns };
	for (size_t i = 0; i < columns.size(); i++)
		_len.push_back(columns[i].size());
}
Table::Row::Row(std::vector<std::string> row) : _row(row) {}
void Table::push(std::vector<std::string> row) {
	for (size_t i = 0; i < row.size(); i++)
		if (row[i].size() > _len[i])_len[i] = row[i].size();
	_data.push_back({ row });
}

void Table::Row::print(std::vector<size_t> len) {
	std::cout << "|";
	for (size_t i = 0; i < len.size(); i++) {
		if (_row.size() > i)printElement(_row[i], len[i] + 1);
		else printElement("", len[i] + 1);
		std::cout << "|";
	}
	std::cout << '\n';
}
void Table::print() {
	_columns.print(_len);
	for (size_t i = 0; i < _data.size(); i++) {
		_data[i].print(_len);
	}
}