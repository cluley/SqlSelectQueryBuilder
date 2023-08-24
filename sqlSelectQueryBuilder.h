#pragma once

#include <iostream>
#include <mutex>
#include <pqxx/pqxx>

class SingleDB {
public:
	SingleDB(const SingleDB& s) = delete;
	void operator=(const SingleDB& s) = delete;

	static SingleDB* getInstance();

	void makeQuery();

	std::string& getSelect() { return select; }
	std::string& getFrom() { return from; }
	std::string& getWhere() { return where; }

	bool select_is_empty() { return select.empty(); }
	bool from_is_empty() { return from.empty(); }
	bool where_is_empty() { return where.empty(); }
private:
	explicit SingleDB() = default;

	pqxx::connection conn{
		"host=127.0.0.1 "
			"port=5432 "
			"user=XXXX "
			"dbname=XXXX "
			"password=XXXX"
	};
	std::string select{};
	std::string from{};
	std::string where{};

	static SingleDB* instance;
	static std::mutex m;
};

class SqlSelectQueryBuilder {
public:
	void BuildQuery();

	SqlSelectQueryBuilder& AddColumn(std::string&& val) noexcept;
	SqlSelectQueryBuilder& AddColumns(const std::vector<std::string>& columns) noexcept;

	SqlSelectQueryBuilder& AddFrom(std::string&& val) noexcept;

	SqlSelectQueryBuilder& AddWhere(std::string&& key, std::string&& val) noexcept;
	SqlSelectQueryBuilder& AddWhere(const std::map<std::string, std::string>& kv) noexcept;
private:
	SingleDB* myDB = SingleDB::getInstance();
};