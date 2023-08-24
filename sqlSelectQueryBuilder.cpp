#include "sqlSelectQueryBuilder.h"

SingleDB* SingleDB::instance = nullptr;
std::mutex SingleDB::m;

SingleDB* SingleDB::getInstance() {
	std::lock_guard<std::mutex> lock(m);
	if (instance) {
		return instance;
	}
	else {
		instance = new SingleDB();
	}
	return instance;
}
void SingleDB::makeQuery() {
	try
	{
		pqxx::work tx(conn);

		if (select.empty()) select = " * ";

		for (auto [name, phone] : tx.query<std::string, std::string>(
			"SELECT " + tx.esc(select) +
			" FROM " + tx.esc(from) +
			" WHERE " + where + "; "))
		{
			std::cout <<
				"First Name: " << name << '\n' <<
				"Phone Number: " << phone << std::endl;
		}

		tx.commit();
	}
	catch (std::exception& exc)
	{
		std::cout << exc.what() << std::endl;
	}
}

void SqlSelectQueryBuilder::BuildQuery() {
	myDB->makeQuery();
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumn(std::string&& val) noexcept {
	if (myDB->select_is_empty()) myDB->getSelect() = val;
	else myDB->getSelect() += ", " + val; 
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddColumns(const std::vector<std::string>& columns) noexcept {
	if (myDB->select_is_empty()) {
		myDB->getSelect() = columns[0];
		for (auto it = (columns.begin() + 1); it < columns.end(); ++it) {
			myDB->getSelect() += ", " + (*it);
		}
	}
	else {
		for (auto& val : columns) {
			myDB->getSelect() += ", " + val;
		}
	}
	
	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddFrom(std::string&& val) noexcept {
	myDB->getFrom() = val;

	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(std::string&& key, std::string&& val) noexcept {
	if (myDB->where_is_empty()) myDB->getWhere() = key + " = " + "\'" + val + "\'";
	else myDB->getWhere() += " AND " + key + " = " + "\'" + val + "\'";

	return *this;
}

SqlSelectQueryBuilder& SqlSelectQueryBuilder::AddWhere(const std::map<std::string, std::string>& kv) noexcept {
	for (auto& el : kv) {
		if (myDB->where_is_empty()) myDB->getWhere() = el.first + " = " + "\'" + el.second + "\'";
		else myDB->getWhere() += " AND " + el.first + " = " + "\'" + el.second + "\'";
	}
	
	return *this;
}