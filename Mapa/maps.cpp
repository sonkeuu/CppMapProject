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
	ofstream File(file);
	//File << "Katowice Krakow 80" << endl << "Warszawaaaa Lodz 220";
	File.close();
	ifstream fFile(file);
	if (fFile.is_open()) {
		while (getline(fFile, line)) {
			cout << line << endl;
		}
		fFile.close();
		return 0;
	}
}


int main() {
	//routes_classess();

	string line;
	const char* file = "structures.txt";
	ifstream ST1(file);
	ST1.open(file);
	if (ST1.is_open()) {
		while (ST1) {
			getline(ST1, line);
			cout << line;
		}
	}
	else {
		cout << "???";
	}

	return 0;
}


//int city_type(string file) {
	//ofstream File(file);



//}