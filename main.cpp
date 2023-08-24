#include <iostream>

#include "sqlSelectQueryBuilder.h"

int main() {
	SqlSelectQueryBuilder query_builder;

	using col_vec = std::vector<std::string>;
	using whr_map = std::map<std::string, std::string>;

	col_vec columns;
	columns.push_back("name");
	columns.push_back("phone");

	whr_map where;
	where.emplace("id", "42");
	where.emplace("name", "John");


	query_builder.AddColumns(columns);
	query_builder.AddFrom("students");
	query_builder.AddWhere(where);

	query_builder.BuildQuery();

	return 0;
}