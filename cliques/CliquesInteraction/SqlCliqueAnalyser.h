#pragma once
#include "../CliquesInteraction/SqlCliqueReader.h"
#include <unordered_set>
#include <unordered_map>

class SqlCliqueAnalyser {
public:
	SqlCliqueAnalyser(sql::Connection* con) : cliqueReader(con), sqlReader(con) {};
	float getInternalCiting(int cliqueID);
	float getExternalCiting(int cliqueID);

private:
	int countInternalLinksAuthors(int cliqueID);
	int countInternalLinksWorks(int cliqueID);
	SqlCliqueReader cliqueReader;
	SqlReader sqlReader;
	
};