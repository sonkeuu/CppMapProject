#include <iostream>
#include <vector>
#include "maps_paths.h"

using namespace std;

void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& next) {

	int n = dist.size();
	for (int k = 0; k < n; k++) {
		for (int i = 0; i < n; i++) {
			for (int j = 0; j < n; j++) {
				if (dist[i][k] != Infinity && dist[k][j] != Infinity && dist[i][k] + dist[k][j] < dist[i][j]) {
					dist[i][j] = dist[i][k] + dist[k][j];
					next[i][j] = next[i][k];
				}
			}
		}
	}
}

vector<int> constructPath(int u, int v, const vector<vector<int>>& next) {
	if (next[u][v] == -1) return {};
	vector<int> path = { u };
	while (u != v) {
		u = next[u][v];
		path.push_back(u);
	}
	return path;
}