#include "SqlWriter.h"

void SqlWriter::execute(std::string query) {
	stmt->execute(query);
}

void SqlWriter::executeUpdate(std::string query) {
	stmt->executeUpdate(query);
}

void SqlWriter::prepare(std::string query) {
	prepStmt = connection->prepareStatement(query);
}

