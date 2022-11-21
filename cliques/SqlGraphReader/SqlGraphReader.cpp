#include "SqlGraphReader.h"

sql::ResultSet* SqlGraphReader::getComponents() {
	return sqlReader.executeGetQuery("SELECT ID from component");
}

std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> SqlGraphReader::getIncidenceList() {
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> incidenceLists;
	sql::ResultSet* citations = sqlReader.executeGetQuery("SELECT Edge_ID FROM graph");
	while (citations->next()) {
		int citation = citations->getInt("Edge_ID");
		sql::ResultSet* authors = sqlReader.getAuthorsViaCitation(citation);
		authors->next();
		int authorID = authors->getInt("author_ID"), sourceID = authors->getInt("Src_ID");
		incidenceLists[authorID].insert(std::make_pair(sourceID, citation));
		delete authors;
	}
	return incidenceLists;
}

std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> SqlGraphReader::getEdges() {
	std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> edges;
	sql::ResultSet* citations = sqlReader.executeGetQuery("SELECT Edge_ID FROM graph");
	while (citations->next()) {
		int citation = citations->getInt("Edge_ID");
		sql::ResultSet* tryGotAuthors = sqlReader.getAuthorsViaCitation(citation);
		if (tryGotAuthors->next()) {
			int authorID = tryGotAuthors->getInt("author_ID"), sourceID = tryGotAuthors->getInt("Src_ID");
			edges.insert(std::make_pair(authorID, sourceID));
		}
		delete tryGotAuthors;
	}
	return edges;
}

std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> SqlGraphReader::getComponentEdges(int componentColor) {
	std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> edges;
	sqlReader.prepare("SELECT graph_edge_ID FROM component_has_edges where Component_ID = ?");
	sqlReader.prepStmt->setInt(1, componentColor);
	delete sqlReader.prepStmt;
	sql::ResultSet* citations = sqlReader.prepStmt->executeQuery();
	while (citations->next()) {
		int citation = citations->getInt("graph_edge_ID");
		sql::ResultSet* tryGotAuthors = sqlReader.getAuthorsViaCitation(citation);
		if (tryGotAuthors->next()) {
			int authorID = tryGotAuthors->getInt("author_ID"), sourceID = tryGotAuthors->getInt("Src_ID");
			if (edges.find(std::make_pair(sourceID, authorID)) == edges.end())
				edges.insert(std::make_pair(authorID, sourceID));
		}
		delete tryGotAuthors;
	}
	return edges;
}

std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> SqlGraphReader::getComponentIncidenceList(int componentColor) {
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> incidenceLists;
	sqlReader.prepare("SELECT graph_edge_ID FROM component_has_edges where Component_ID = ?");
	sqlReader.prepStmt->setInt(1, componentColor);
	sql::ResultSet* citations = sqlReader.prepStmt->executeQuery();
	delete sqlReader.prepStmt;
	while (citations->next()) {
		int citation = citations->getInt("graph_edge_ID");
		sql::ResultSet* authors = sqlReader.getAuthorsViaCitation(citation);
		authors->next();
		int authorID = authors->getInt("author_ID"), sourceID = authors->getInt("Src_ID");
		incidenceLists[authorID].insert(std::make_pair(sourceID, citation));
		delete authors;
	}
	return incidenceLists;
}

std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> SqlGraphReader::getComponentIncidenceListCoauthors(int componentColor) {
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> incidenceLists;
	sqlReader.prepare("SELECT graph_edge_ID FROM component_has_edges where Component_ID = ?");
	sqlReader.prepStmt->setInt(1, componentColor);
	sql::ResultSet* citations = sqlReader.prepStmt->executeQuery();
	delete sqlReader.prepStmt;
	while (citations->next()) {
		int citation = citations->getInt("graph_edge_ID");
		sql::ResultSet* authors = sqlReader.getAuthorsViaCitation(citation);
		authors->next();
		int authorID = authors->getInt("author_ID"), sourceID = authors->getInt("Src_ID");
		if (sqlReader.checkIfCoauthors(authorID, sourceID))
			incidenceLists[authorID].insert(std::make_pair(sourceID, citation));
		delete authors;
	}
	return incidenceLists;
}