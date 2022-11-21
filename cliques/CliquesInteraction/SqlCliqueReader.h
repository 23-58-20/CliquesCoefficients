#pragma once
#include "../SqlReader/SqlReader.h"

class SqlCliqueReader {
public:
	SqlCliqueReader(sql::Connection* con) : sqlReader(con) {};
	sql::ResultSet* getCliques(bool surelyCoauthors);
	sql::ResultSet* getCliquesFromComponent(int componentID, bool surelyCoauthors);
	sql::ResultSet* getCliqueAuthors(int cliqueID);
	int getCliqueSize(int cliqueID);
	float getCliqueInternalCiting(int cliqueID);
	float getCliqueExternalCiting(int cliqueID);
private:
	SqlReader sqlReader;
};