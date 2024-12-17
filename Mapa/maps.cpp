#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <map>
#include <algorithm>
#include <set>

using namespace std;

struct City {
	string CityName;
	string DestinationName;
	int Distance;
} route1, route2, route3, route4, route5, route6;


int routes_classess() {
	route1.CityName = "Krakow";
	route1.DestinationName = "Gliwice";
	route1.Distance = 120;

	route2.CityName = "Katowice";
	route2.DestinationName = "Warszawa";
	route2.Distance = 250;

	cout << route1.CityName << " ---> " << route1.DestinationName << "	" << route1.Distance << endl;
	cout << route2.CityName << " ---> " << route2.DestinationName << "	" << route2.Distance << endl;
	cout << "Full route: " << route1.Distance + route2.Distance;

	return 0;
}


vector<City> read_lines(const string &fileName) 
{
	ifstream file(fileName);
	string lineFromFile;
	vector<City> result;
	const char* del = ";";	
	
	while (getline(file, lineFromFile))
	{
		stringstream lineCheck(lineFromFile);
		string token;
		vector<string> foundWords;

		while (getline(lineCheck, token, ';')) {
			foundWords.push_back(token);
		}

		// to do optymalizacji pozniej.
		/*char* line = new char[lineFromFile.length() + 1];
		strcpy_s(line, lineFromFile.length() + 1, lineFromFile.c_str());
		
		char* next_token1 = NULL;
		char* token1 = NULL;

		token1 = strtok_s(line, del, &next_token1);
		while ((token1 != NULL)) 
		{
			foundWords.push_back(token1);
			token1 = strtok_s(NULL, del, &next_token1);
		}
		*/

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
		catch(...) {
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

void matrix(const vector<string>& cities) {

	vector<vector<string>> cityMatrix;

	for (int i = 0; i < cities.size(); i++) {

	}

}

int main() {
	vector<City> mapItems = read_lines("exampleCities.txt");
	cout << mapItems.size() << " ";
	vector<string> sorted;

	for (const City& city : mapItems) {
		cout << city.CityName << " " << city.DestinationName << " " << city.Distance << endl;
	}
	for (const City& city : mapItems) {
		sorted.push_back(city.CityName);
		sorted.push_back(city.DestinationName);
	}
	for (const auto& srt : sorted) {
		cout << srt << "; ";
	}
	cout << endl;

	set<string> unique(sorted.begin(), sorted.end());
	vector<string> uniques(unique.begin(), unique.end());

	for (const auto& srt : uniques) {
		cout << srt << "; ";
	}

	return 0;
	}
