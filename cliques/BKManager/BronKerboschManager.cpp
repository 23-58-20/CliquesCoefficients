#include "BronKerboschManager.h"
#include <algorithm>

void BronKerboschManager::bronKerbosch(int componentColor, bool surelyCoauthors) {
	incidenceLists = (surelyCoauthors ?
		graphReader.getComponentIncidenceListCoauthors(componentColor) :
		graphReader.getComponentIncidenceList(componentColor));
	bronKerboshRec(componentColor, surelyCoauthors);
}

bool BronKerboschManager::checkAdjacentAllCandidates(std::unordered_set<int> verticesNot, std::unordered_set<int> candidates) {
	for (int vertexNot : verticesNot) {
		std::unordered_set<int> adjacentVerts;
		for (std::pair<int, int> elem : incidenceLists[vertexNot])
			adjacentVerts.insert(elem.first);
		std::unordered_set<int> res;
		std::set_difference(candidates.begin(), candidates.end(), adjacentVerts.begin(), adjacentVerts.end(),
			std::inserter(res, res.end()));
		if (res.size() == 0) return false;
	}
	return true;
}	

std::pair<std::unordered_set<int>, std::unordered_set<int>> BronKerboschManager::getNewCandidatesAndVerticesNot(
	std::unordered_set<int> candidates, std::unordered_set<int> verticesNot, int vertex) {
	std::unordered_set<int> adjacentVerts;
	for (std::pair<int, int> elem : incidenceLists[vertex])
		adjacentVerts.insert(elem.first);
	adjacentVerts.erase(vertex);
	std::unordered_set<int> newCandidates;
	std::unordered_set<int> newVerticesNot;
	std::set_intersection(candidates.begin(), candidates.end(), adjacentVerts.begin(), adjacentVerts.end(),
		std::inserter(newCandidates, newCandidates.end()));
	std::set_intersection(verticesNot.begin(), verticesNot.end(), adjacentVerts.begin(), adjacentVerts.end(),
		std::inserter(newVerticesNot, newVerticesNot.end()));
	return std::make_pair(newCandidates, newVerticesNot);
}


void BronKerboschManager::bronKerboshRec(int componentColor, bool surelyCoauthors) {
	std::unordered_set<int> candidates;
	for (auto x : incidenceLists) {
		candidates.insert(x.first);
	}
	std::unordered_set<int>	vertNot;
	while (candidates.size() && checkAdjacentAllCandidates(vertNot, candidates)) {
		int vertex = *(candidates.begin());
		compsub.insert(vertex);

		std::pair<std::unordered_set<int>, std::unordered_set<int>> res;
		res = getNewCandidatesAndVerticesNot(candidates, vertNot, vertex);

		if (!(res.first.size() || res.second.size()))
			cliqueWriter.writeClique(componentColor, compsub, surelyCoauthors);
		else
			extend(res.first, res.second, componentColor, surelyCoauthors);
		compsub.erase(vertex);
		candidates.erase(vertex);
		vertNot.insert(vertex);
	}
}

void BronKerboschManager::extend(std::unordered_set<int> candidates, std::unordered_set<int> vertNot, int componentColor, bool surelyCoauthors) {
	while (candidates.size() && checkAdjacentAllCandidates(vertNot, candidates)) {
		int vertex = *(candidates.begin());
		compsub.insert(vertex);

		std::pair<std::unordered_set<int>, std::unordered_set<int>> res;
		res = getNewCandidatesAndVerticesNot(candidates, vertNot, vertex);
		
		if (!(res.first.size() || res.second.size()))
			cliqueWriter.writeClique(componentColor, compsub, surelyCoauthors);
		else
			extend(res.first, res.second, componentColor, surelyCoauthors);
		compsub.erase(vertex);
		candidates.erase(vertex);
		vertNot.insert(vertex);
	}
}
