#pragma once
#include "../SqlReader/SqlReader.h"
#include "../SqlWriter/SqlWriter.h"
#include <boost/functional/hash.hpp>
#include <unordered_map>
#include <unordered_set>
class SqlGraphReader {
public:
	SqlGraphReader() = default;
	SqlGraphReader(sql::Connection* con) : connection(con), sqlWriter(con), sqlReader(con) {};
	sql::ResultSet* getComponents();
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> getIncidenceList();
	std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> getEdges();
	std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>> getComponentEdges(int componentColor);
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> getComponentIncidenceList(int componentColor);
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> getComponentIncidenceListCoauthors(int componentColor);
private:
	sql::Connection* connection;
	SqlWriter sqlWriter;
	SqlReader sqlReader;
};