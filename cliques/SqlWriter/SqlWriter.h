#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <stdlib.h>
#include <iostream>
class SqlWriter {
public:
	SqlWriter() = default;
	SqlWriter(sql::Connection* con) : connection(con) {
		stmt = con->createStatement();
	}
	void prepare(std::string query);
	sql::PreparedStatement* prepStmt;
	void execute(std::string query);
	void executeUpdate(std::string query);
private:
	sql::Connection* connection;
	sql::Statement* stmt;
};