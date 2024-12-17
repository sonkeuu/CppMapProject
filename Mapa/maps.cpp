#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>

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

int file_reader(string line, string file) {
	ifstream inputFile("example.txt");
	if (!inputFile.is_open()) {
		cerr << "Unable to open file" << endl;
		return 1;
	}

	ostringstream buffer;
	buffer << inputFile.rdbuf(); // Read entire file into buffer
	cout << buffer.str();   // Print the content

	inputFile.close();

	return 0;
}

int file_wbw_reader(string line, string file) {
	ifstream inputFile("example.txt");
	if (!inputFile.is_open()) {
		cerr << "Unable to open file" << endl;
		return 1;
	}

	string word;
	while (inputFile >> word) { // Read word by word
		cout << word << endl;
	}

	inputFile.close();
}

int file_lbl_reader(string line, const string& file, vector<string>& words) {
	ifstream inputFile(file); // Open the file
	if (!inputFile.is_open()) {            // Check if the file is open
		cerr << "Unable to open file" << endl;
		return 1; // Exit with error code
	}


	while (getline(inputFile, line)) { // Read line by line
		cout << line << endl;
		stringstream ss(line);
		string word;
		while (ss >> word) {
			words.push_back(word);
			cout << word << " ";
			cout << "koniec linii.";
		}
	}

		inputFile.close(); // Close the file
	}

vector<City> read_lines(string fileName) 
{
	ifstream file(fileName);
	string lineFromFile;
	vector<City> result;
	const char* del = ";";
	
	while (getline(file, lineFromFile))
	{
		//const char* line = lineFromFile.c_str(); // Tablica char (const char*)
		//cout << line << endl;

		// to do optymalizacji pozniej.
		char* line = new char[lineFromFile.length() + 1];
		strcpy_s(line, lineFromFile.length() + 1, lineFromFile.c_str());
		
		char* next_token1 = NULL;
		char* token1 = NULL;
		vector<char*> foundWords;

		token1 = strtok_s(line, del, &next_token1);
		while ((token1 != NULL)) 
		{
			foundWords.push_back(token1);
			token1 = strtok_s(NULL, del, &next_token1);
		}

		if (foundWords.size() != 3) 
		{
			vector<City> emptyResult;
			return emptyResult;
		}

		int kmAsInt;
		char* km = foundWords[2];
		try 
		{
			kmAsInt = stoi(km, 0, 10);
		}
		catch(...)
		{
			vector<City> emptyResult;
			return emptyResult;
		}

		City city_item;
		city_item.CityName = foundWords[0];
		city_item.DestinationName = foundWords[1];
		city_item.Distance = kmAsInt;
		result.push_back(city_item);
	}

	return result;
}

int main() {
	vector<City> mapItems = read_lines("exampleCities.txt");
	//cout << mapItems.size() << " ";
	for (City city : mapItems)
	{
		cout << city.CityName << " " << city.DestinationName << " " << city.Distance << endl;
	}

	return 0;
}
