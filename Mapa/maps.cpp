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

int file_reader(string City1, string City2, int Distance, string line) {
	ofstream FirstFile("routes.txt");
	FirstFile << "Katowice Krakow 80" << endl << "Warszawa Lodz 220";
	FirstFile.close();
	ifstream File("routes.txt");
	if (File.is_open()) {
		while (getline(File, line)) {
			//cout << line << endl;
			vector<string> words;
			istringstream iss(line);
			string word;
			while (iss >> word) {
				words.push_back(word);
			}
			for (const auto& w : words) {
				cout << w << " ";
			}
			cout << endl;
		}
	}
	FirstFile.close();
	return 0;
}


int main() {
	string arr[3];
	string Krakow = "Kraków";
	string Katowice = "Katowice";
	//int Distance = 80
	string line;
	file_reader(Krakow, Katowice, 80, line);
	//routes_classess();

	return 0;
}


