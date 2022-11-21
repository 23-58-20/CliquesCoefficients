#include "SqlReader.h"

sql::ResultSet* SqlReader::executeGetQuery(std::string query) {
	return stmt->executeQuery(query); 
};

sql::ResultSet* SqlReader::getAuthorsViaCitation(int entryID) {
	prepare("SELECT author_ID, Src_ID FROM author_cites_author WHERE ID = ?");
	prepStmt->setInt(1, entryID);
	sql::ResultSet* ans =  prepStmt->executeQuery();
	prepStmt->close();
	delete prepStmt;
	return ans;
	
};

sql::ResultSet* SqlReader::getAuthorWorks(int authorID) {
	prepare("SELECT Work_DOI FROM author_has_work WHERE Author_ID = ?");
	prepStmt->setInt(1, authorID);
	sql::ResultSet* ans = prepStmt->executeQuery();
	prepStmt->close();
	delete prepStmt;
	return ans;
};

sql::ResultSet* SqlReader::getWorkAuthors(std::string doi) {
	prepare("SELECT author_ID FROM author_has_work WHERE work_DOI = ?");
	prepStmt->setString(1, doi);
	sql::ResultSet* ans = prepStmt->executeQuery();
	prepStmt->close();
	delete prepStmt;
	return ans;
};

sql::ResultSet* SqlReader::getReferencesFromWork(std::string doi) {
	prepare("SELECT Src_DOI FROM work_cites_work WHERE Work_DOI = ?");
	prepStmt->setString(1, doi);
	sql::ResultSet* ans = prepStmt->executeQuery();
	prepStmt->close();
	delete prepStmt;
	return ans;
};

int SqlReader::getWorkIsReferencedCount(std::string doi) {
	prepare("SELECT count(ID) FROM work_cites_work WHERE Src_DOI = ?");
	prepStmt->setString(1, doi);
	sql::ResultSet* ans = prepStmt->executeQuery();
	ans->next();
	int count = ans->getInt("count(ID)");
	prepStmt->close();
	delete prepStmt;
	delete ans;
	return count;
}

bool SqlReader::checkIfCoauthors(int authorID, int SrcID) {
	if (authorID == SrcID)
		return true;
	sql::ResultSet* authorWorks = getAuthorWorks(authorID);
	while (authorWorks->next()) {
		std::string work = authorWorks->getString("Work_DOI");
		sql::ResultSet* workAuthors = getWorkAuthors(work);
		while (workAuthors->next()) {
			int author = workAuthors->getInt("author_ID");
			if (author == SrcID)
				return true;
		}
	}
	return false;
}

void SqlReader::prepare(std::string query) {
	prepStmt = connection->prepareStatement(query);
}