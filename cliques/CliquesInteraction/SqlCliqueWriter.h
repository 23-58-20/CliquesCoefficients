#pragma once
#include "../SqlReader/SqlReader.h"
#include "../SqlWriter/SqlWriter.h"
#include <unordered_set>
#include <vector>
class SqlCliqueWriter {
public:
	SqlCliqueWriter() = default;
	SqlCliqueWriter(sql::Connection* con): connection(con), sqlWriter(con), sqlReader(con) {};
	void writeClique(int component, std::unordered_set<int> authors, bool surelyCoauthors);
	void changeCitingInClique(int cliqueID, float internalCoeff, float externalCoeff);
private:
	sql::Connection* connection;
	SqlWriter sqlWriter;
	SqlReader sqlReader;
	void addClique(int component, bool surelyCoauthors, int size);
	void addCliqueHasAuthor(int cliqueID, int authorID);
};