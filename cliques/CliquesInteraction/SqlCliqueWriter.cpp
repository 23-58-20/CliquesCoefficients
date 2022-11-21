#include "SqlCliqueWriter.h"

void SqlCliqueWriter::writeClique(int component, std::unordered_set<int> authors, bool surelyCoauthors) {
	int size = authors.size();
	addClique(component, surelyCoauthors, size);
	sql::ResultSet* lastID = sqlReader.executeGetQuery("SELECT ID FROM clique ORDER BY ID DESC LIMIT 1");
	lastID->next();
	int ID = lastID->getInt("ID");
	delete lastID;
	for (int author : authors)
		addCliqueHasAuthor(ID, author);
}

void SqlCliqueWriter::addClique(int component, bool surelyCoauthors, int size) {
	sqlWriter.prepare("INSERT INTO clique (component_ID, surely_coauthors, size) VALUES (?, ?, ?)");
	sqlWriter.prepStmt->setInt(1, component);
	sqlWriter.prepStmt->setInt(2, surelyCoauthors);
	sqlWriter.prepStmt->setInt(3, size);
	sqlWriter.prepStmt->execute();
	delete sqlWriter.prepStmt;
}
void SqlCliqueWriter::addCliqueHasAuthor(int cliqueID, int authorID) {
	sqlWriter.prepare("INSERT INTO clique_has_author (clique_ID, author_ID) VALUES (?, ?)");
	sqlWriter.prepStmt->setInt(1, cliqueID);
	sqlWriter.prepStmt->setInt(2, authorID);
	sqlWriter.prepStmt->execute();
	delete sqlWriter.prepStmt;
}
void SqlCliqueWriter::changeCitingInClique(int cliqueID, float internalCoeff, float externalCoeff) {
	sqlWriter.prepare("UPDATE clique SET internal_citing = ?, external_citing = ? WHERE id = ?");
	sqlWriter.prepStmt->setDouble(1, internalCoeff);
	sqlWriter.prepStmt->setDouble(2, externalCoeff);
	sqlWriter.prepStmt->setInt(3, cliqueID);
	sqlWriter.prepStmt->execute();
	delete sqlWriter.prepStmt;
}