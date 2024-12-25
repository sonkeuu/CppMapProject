#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>

using namespace std;

struct City {
	string CityName;
	string DestinationName;
	int Distance;
};

vector<City> read_lines(const string &fileName) 
{
	ifstream file(fileName);
	string lineFromFile;
	vector<City> result;
		
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

int get_city_index(vector<string> cities, string cityToFind)
{
	int size = cities.size();
	for (int i = 0; i < size; i++) {
		if (cities[i] == cityToFind) {
			return i;
		}
	}
	return -1;
}

void matrix(const vector<string>& cities) {

	vector<vector<string>> cityMatrix(cities.size(), vector<string>(cities.size()));

	for (int i = 0; i < cities.size(); i++) {
		for (int j = 0; j < cities.size(); j++) {
			cityMatrix[i][j] = cities[i];
		}
	}

	for (const auto& row : cityMatrix) {
		for (const auto& city : row) {
			cout << city << "	";
		}
		cout << endl;
	}
	cout << endl << endl;

	for (int i = 1; i < cities.size(); i++) {
		for (int j = 1; j < cities.size(); j++) {
			cityMatrix[i][j] = "X";
		}
	}
	for (const auto& row : cityMatrix) {
		for (const auto& city : row) {
			cout << city << "		";
		}
		cout << endl;
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




	int mtx_size = uniques.size();
	int* arr = new int[mtx_size * mtx_size];

	for (int i = 0; i < mtx_size; i++) {
		for (int j = 0; j < mtx_size; j++) {
			*(arr + i * mtx_size + j) = 0;
		}
	}

	for (const City& city : mapItems) {

		int line = get_city_index(uniques, city.CityName);
		int column = get_city_index(uniques, city.DestinationName);
		if (line >= 0 && column >= 0) {
			*(arr + line * mtx_size + column) = city.Distance;
			//cout << city.Distance;
			//cout << endl;
		}

		//int line2 = get_city_index(uniques, city.DestinationName);
		//int column2 = get_city_index(uniques, city.CityName);
		//if (line2 >= 0 && column2 >= 0) {
		//	*(arr + line2 * mtx_size + column2) = city.Distance;
			//cout << city.Distance;
			//cout << endl;
		//}

	}

	cout << endl;
	for (int i = 0; i < mtx_size; i++) {
		for (int j = 0; j < mtx_size; j++) {
			cout << *(arr + i * mtx_size + j) << "	";
		}
		cout << endl;
	}



	//cout << endl << endl;

	//matrix(uniques);

	return 0;
}
