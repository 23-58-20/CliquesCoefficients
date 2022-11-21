#pragma once
#include "../SqlGraphReader/SqlGraphReader.h"
#include "../CliquesInteraction/SqlCliqueWriter.h"

class BronKerboschManager {
public:
	BronKerboschManager(sql::Connection* con) : connection(con), graphReader(con), cliqueWriter(con) {};
	void bronKerbosch(int componentColor, bool surelyCoauthors);

private:
	void bronKerboshRec(int componentColor, bool surelyCoauthors);
	void extend(std::unordered_set<int> candidates, std::unordered_set<int> verticesNot, int componentColor, bool surelyCoauthors);
	bool checkAdjacentAllCandidates(std::unordered_set<int> verticesNot, std::unordered_set<int> candidates);
	std::pair<std::unordered_set<int>, std::unordered_set<int>> getNewCandidatesAndVerticesNot(
		std::unordered_set<int> candidates, std::unordered_set<int> verticesNot, int vertex);
	sql::Connection* connection;
	SqlGraphReader graphReader;
	SqlCliqueWriter cliqueWriter;
	std::unordered_map<int, std::unordered_set<std::pair<int, int>, boost::hash<std::pair<int, int>>>> incidenceLists;
	std::unordered_set<int> compsub;
};