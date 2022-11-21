#include "SqlCliqueAnalyser.h"


float SqlCliqueAnalyser::getInternalCiting(int cliqueID) {
	int cliqueSize = cliqueReader.getCliqueSize(cliqueID);
	int totalRefs = countInternalLinksAuthors(cliqueID);
	return float(totalRefs) / (cliqueSize * cliqueSize);
	
};

float SqlCliqueAnalyser::getExternalCiting(int cliqueID) {
	sql::ResultSet* cliqueAuthors = cliqueReader.getCliqueAuthors(cliqueID);
	std::unordered_map<std::string, int> cliqueWorksRefs;
	int internalLinksNum = countInternalLinksWorks(cliqueID);
	while (cliqueAuthors->next()) {
		sql::ResultSet* authorWorks = sqlReader.getAuthorWorks(cliqueAuthors->getInt("author_ID"));
		while (authorWorks->next()) {
			std::string work = authorWorks->getString("Work_DOI");
			if (cliqueWorksRefs.find(work) == cliqueWorksRefs.end()) {
				cliqueWorksRefs[work] = sqlReader.getWorkIsReferencedCount(work);
			}
		}
		delete authorWorks;
	}
	delete cliqueAuthors;
	float cliqueCoeff = 0;
	for (std::pair<std::string, int> ref : cliqueWorksRefs)
		cliqueCoeff += ref.second;
	return (cliqueCoeff - internalLinksNum) / cliqueWorksRefs.size();
};

int SqlCliqueAnalyser::countInternalLinksAuthors(int cliqueID) {
	int totalRefs = 0;
	std::unordered_set<int> authors;
	sql::ResultSet* cliqueAuthors = cliqueReader.getCliqueAuthors(cliqueID);
	while (cliqueAuthors->next()) 
		authors.insert(cliqueAuthors->getInt("author_ID"));
	if (authors.size() == 1) return 0;
	for (int cliqueAuthor: authors) {
		sql::ResultSet* authorWorks = sqlReader.getAuthorWorks(cliqueAuthor);
		while (authorWorks->next()) {
			sql::ResultSet* srcWorks = sqlReader.getReferencesFromWork(authorWorks->getString("Work_DOI"));
			while (srcWorks->next()) {
				sql::ResultSet* workAuthors = sqlReader.getWorkAuthors(srcWorks->getString("Src_DOI"));
				while (workAuthors->next()) {
					int workAuthor = workAuthors->getInt("author_ID");
					if ((authors.find(workAuthor) != authors.end()) && (workAuthor != cliqueAuthor))
						totalRefs++;
				}
				delete workAuthors;
			}
			delete srcWorks;
		}
		delete authorWorks;
	}
	delete cliqueAuthors;
	return totalRefs;
}

int SqlCliqueAnalyser::countInternalLinksWorks(int cliqueID) {
	int totalRefs = 0;
	std::unordered_set<std::string> cliqueWorks;
	sql::ResultSet* cliqueAuthors = cliqueReader.getCliqueAuthors(cliqueID);
	while (cliqueAuthors->next()) {
		sql::ResultSet* authorWorks = sqlReader.getAuthorWorks(cliqueAuthors->getInt("author_ID"));
		while (authorWorks->next())
			cliqueWorks.insert(authorWorks->getString("Work_DOI"));
		delete authorWorks;
	}
	delete cliqueAuthors;
	for (std::string work : cliqueWorks) {
		sql::ResultSet* workRefs = sqlReader.getReferencesFromWork(work);
		while (workRefs->next()) {
			std::string workRef = workRefs->getString("Src_DOI");
			for (char& sym : workRef)
				sym = tolower(sym);

			if (cliqueWorks.find(workRef) != cliqueWorks.end())
				if (workRef.compare(work) != 0)
					totalRefs++;
		}
		delete workRefs;
	}
	return totalRefs;
}