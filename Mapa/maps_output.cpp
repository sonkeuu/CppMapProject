#include "maps_output.h"
#include <fstream>
#include <sstream>
#include "maps_paths.h"

using namespace std;

void find_routes(vector<vector<int>> dist, vector<vector<int>> next, vector<string> cities, int u_index, int v_index) {

	vector<int> path = constructPath(u_index, v_index, next);
	if (path.empty()) {
		cout << "trasa: " << cities[u_index] << " --> " << cities[v_index] << endl;
		cout << "Trasa niemozliwa do wyznaczenia." << endl;
	}
	else {
		int prev_vertex = -1;
		int total_km = 0;
		total_km = dist[u_index][v_index];
		cout << "trasa: " << cities[u_index] << " --> " << cities[v_index] << " (" << total_km << " km)";

		for (int vertex : path) {
			if (prev_vertex != -1) {
				cout << endl;
				cout << cities[prev_vertex] << " --> " << cities[vertex] << " (" << dist[prev_vertex][vertex] << " km)";
			}
			prev_vertex = vertex;
		}
	}
}