#include "SqlCliqueFiller.h"

void SqlCliqueFiller::changeCliqueCitingCoeffs(int cliqueID) {
	float internal = sqlCliqueAnalyser.getInternalCiting(cliqueID);
	std::cout << "Internal coeff for clique " << cliqueID << "found" << std::endl;
	float external = sqlCliqueAnalyser.getExternalCiting(cliqueID);
	std::cout << "External coeff for clique " << cliqueID << "found" << std::endl;
	cliqueWriter.changeCitingInClique(cliqueID, internal, external);
};

void SqlCliqueFiller::updateCliquesCiting(bool surelyCoauthots) {
	sql::ResultSet* cliques = sqlReader.getCliques(surelyCoauthots);
	while (cliques->next()) {
		int cliqueID = cliques->getInt("ID");
		changeCliqueCitingCoeffs(cliqueID);

	}
	delete cliques;

}

void SqlCliqueFiller::fillCliquesAuthors() {
	if (isCliqueInDbEmpty(false)) {
		sql::ResultSet* components = graphReader.getComponents();
		while (components->next()) {
			int componentID = components->getInt("ID");
			bkManager.bronKerbosch(componentID, false);
		}
		delete components;
	}
};

void SqlCliqueFiller::fillCliquesCoauthors() {
	if (isCliqueInDbEmpty(true)) {
		sql::ResultSet* components = graphReader.getComponents();
		while (components->next()) {
			int componentID = components->getInt("ID");
			bkManager.bronKerbosch(componentID, true);
		}
		delete components;
	}
};

bool SqlCliqueFiller::isCliqueInDbEmpty(bool surelyCoauthots) {
	sql::ResultSet* cliques = sqlReader.getCliques(surelyCoauthots);
	return !bool(cliques->next());
};


