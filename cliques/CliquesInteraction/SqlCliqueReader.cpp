#include "SqlCliqueReader.h"

sql::ResultSet* SqlCliqueReader::getCliques(bool surelyCoauthors) {
	sqlReader.prepare("SELECT ID from clique where surely_coauthors = ?");
	sqlReader.prepStmt->setInt(1, int(surelyCoauthors));
	sql::ResultSet* ans = sqlReader.prepStmt->executeQuery();
	sqlReader.prepStmt->close();
	delete sqlReader.prepStmt;
	return ans;
}
sql::ResultSet* SqlCliqueReader::getCliquesFromComponent(int componentID, bool surelyCoauthors) {
	sqlReader.prepare("SELECT ID from clique where surely_coauthors = ? and component_id = ?");
	sqlReader.prepStmt->setInt(1, int(surelyCoauthors));
	sqlReader.prepStmt->setInt(2, componentID);
	sql::ResultSet* ans = sqlReader.prepStmt->executeQuery();
	sqlReader.prepStmt->close();
	delete sqlReader.prepStmt;
	return ans;
}
sql::ResultSet* SqlCliqueReader::getCliqueAuthors(int cliqueID) {
	sqlReader.prepare("SELECT author_ID from clique_has_author where clique_id = ?");
	sqlReader.prepStmt->setInt(1, cliqueID);
	sql::ResultSet* ans = sqlReader.prepStmt->executeQuery();
	sqlReader.prepStmt->close();
	delete sqlReader.prepStmt;
	return ans;
}
int SqlCliqueReader::getCliqueSize(int cliqueID) {
	sqlReader.prepare("SELECT size from clique where id = ?");
	sqlReader.prepStmt->setInt(1, cliqueID);
	sql::ResultSet* ans = sqlReader.prepStmt->executeQuery();
	sqlReader.prepStmt->close();
	delete sqlReader.prepStmt;
	ans->next();
	int size = ans->getInt("size");
	delete ans;
	return size;
}
float SqlCliqueReader::getCliqueInternalCiting(int cliqueID) {
	sqlReader.prepare("SELECT internal_citing from clique where id = ?");
	sqlReader.prepStmt->setInt(1, cliqueID);
	sql::ResultSet* ans = sqlReader.prepStmt->executeQuery();
	sqlReader.prepStmt->close();
	delete sqlReader.prepStmt;
	ans->next();
	float internalCiting = ans->getDouble("internal_citing");
	delete ans;
	return internalCiting;
}
float SqlCliqueReader::getCliqueExternalCiting(int cliqueID) {
	sqlReader.prepare("SELECT external_citing from clique where id = ?");
	sqlReader.prepStmt->setInt(1, cliqueID);
	sql::ResultSet* ans = sqlReader.prepStmt->executeQuery();
	sqlReader.prepStmt->close();
	delete sqlReader.prepStmt;
	ans->next();
	float externalCiting = ans->getDouble("external_citing");
	delete ans;
	return externalCiting;
}