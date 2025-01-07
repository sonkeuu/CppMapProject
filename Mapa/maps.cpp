#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <sstream>
#include <set>
#include "maps.h"
#include "maps_input.h"
#include "maps_paths.h"
#include "utilities.h"
#include "maps_output.h"

using namespace std;

int main() {

	string FileWithDistances = "cities.txt";
	string FileWithCitiesToFind = "cities2.txt";
	string FileToSaveResult = "output.txt";

	bool toFile = true;
	ostream* out;
	ofstream outFile;
	if (toFile) {
		outFile.open(FileToSaveResult);
		if (!outFile) {
			cout << "Error opening file for writing" << endl;
			return 1;
		}
		out = &outFile;
	}
	else {
		out = &cout;
	}

	if (toFile) {
		outFile.close();
	}

	vector<City> mapItems = read_cities_distances(FileWithDistances);
	vector<string> sorted;

	items_to_vector(mapItems, sorted);

	set<string> unique(sorted.begin(), sorted.end());
	vector<string> uniques(unique.begin(), unique.end());

	int number_of_cities = uniques.size();
	vector<vector<int>> distance(number_of_cities, vector<int>(number_of_cities, Infinity));
	vector<vector<int>> next_city(number_of_cities, vector<int>(number_of_cities, -1));

	for (const City& city : mapItems) {
		int line = get_city_index(uniques, city.CityName);
		int column = get_city_index(uniques, city.DestinationName);
		if (line >= 0 && column >= 0) {
			distance[line][column] = city.Distance;
		}
	}
	
	for (int i = 0; i < number_of_cities; i++) {
		for (int j = 0; j < number_of_cities; j++) {
			if (distance[i][j] != Infinity) next_city[i][j] = j;
		}
	}

	floydWarshall(distance, next_city);

	vector<City> mapItems_2 = read_cities_to_find(FileWithCitiesToFind);
	vector<string> toFind;

	items_to_vector(mapItems_2, toFind);
		
	for (const City& city : mapItems_2) {
		int u = get_city_index(uniques, city.CityName);
		int v = get_city_index(uniques, city.DestinationName);
		find_routes(distance, next_city, uniques, u, v);
		*out << endl << endl;
	}

	return 0;
}


