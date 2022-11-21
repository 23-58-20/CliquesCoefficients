#pragma once
#include "../BKManager/BronKerboschManager.h"
#include "SqlCliqueReader.h"
#include "SqlCliqueAnalyser.h"

class SqlCliqueFiller {
public:
	SqlCliqueFiller(sql::Connection* con) : bkManager(con), graphReader(con), cliqueWriter(con), sqlReader(con), sqlCliqueAnalyser(con) {};
	void updateCliquesCiting(bool surelyCoauthots);
	void fillCliquesAuthors();
	void fillCliquesCoauthors();
private:
	bool isCliqueInDbEmpty(bool surelyCoauthots);
	void changeCliqueCitingCoeffs(int cliqueID);
	BronKerboschManager bkManager;
	SqlGraphReader graphReader;
	SqlCliqueWriter cliqueWriter;
	SqlCliqueReader sqlReader;
	SqlCliqueAnalyser sqlCliqueAnalyser;

};