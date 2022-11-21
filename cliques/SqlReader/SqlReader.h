#pragma once
#include "mysql_connection.h"
#include <cppconn/driver.h>
#include <cppconn/exception.h>
#include <cppconn/prepared_statement.h>
#include <stdlib.h>
#include <iostream>


class SqlReader {
public:
	SqlReader() = default;
	SqlReader(sql::Connection* con) : connection(con) { 
	stmt = con->createStatement();
	}

	void prepare(std::string query);
	sql::PreparedStatement* prepStmt;
	sql::ResultSet* executeGetQuery(std::string query);
	sql::ResultSet* getAuthorsViaCitation(int entryID);
	sql::ResultSet* getAuthorWorks(int authorID);
	sql::ResultSet* getWorkAuthors(std::string doi);
	sql::ResultSet* getReferencesFromWork(std::string doi);
	int getWorkIsReferencedCount(std::string doi);
	bool checkIfCoauthors(int authorID, int SrcID);
private:
	sql::Connection* connection;
	sql::Statement* stmt;

};