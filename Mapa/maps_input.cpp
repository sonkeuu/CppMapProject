#include "maps_input.h"
#include <fstream>
#include <sstream>

using namespace std;

vector<City> read_cities_distances(const string& fileName) {
	ifstream file(fileName);
	string lineFromFile;
	vector<City> result;

	while (getline(file, lineFromFile)) {
		stringstream lineCheck(lineFromFile);
		string token;
		vector<string> foundWords;

		while (getline(lineCheck, token, ' ')) {
			foundWords.push_back(token);
		}

		if (foundWords.size() != 3) {
			vector<City> emptyResult;
			cout << "Error: Incorrect number of words in the lines.";
			return emptyResult;
		}

		int kmAsInt;
		string km = foundWords[2];

		try {
			kmAsInt = stoi(km, 0, 10);
		}
		catch (...) {
			vector<City> emptyResult;
			cout << "Error: Invalid distance format.";
			return emptyResult;
		}

		City cityItem;
		cityItem.CityName = foundWords[0];
		cityItem.DestinationName = foundWords[1];
		cityItem.Distance = kmAsInt;
		result.push_back(cityItem);
	}
	return result;
}

vector<City> read_cities_to_find(const string& fileName) {
	ifstream file(fileName);
	string lineFromFile;
	vector<City> result;

	while (getline(file, lineFromFile)) {
		stringstream lineCheck(lineFromFile);
		string token;
		vector<string> foundWords;

		while (getline(lineCheck, token, ' ')) {
			foundWords.push_back(token);
		}

		if (foundWords.size() != 2) {
			vector<City> emptyResult;
			cout << "Error: Incorrect number of words in the lines.";
			return emptyResult;
		}

		City cityItem;
		cityItem.CityName = foundWords[0];
		cityItem.DestinationName = foundWords[1];
		result.push_back(cityItem);
	}
	return result;
}




