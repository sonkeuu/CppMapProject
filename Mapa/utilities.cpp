#include "utilities.h"
#include <string>
#include <vector>
#include "maps_input.h"

using namespace std;

string pad_left(string const& str, size_t s) {
	if (str.size() < s)
		return string(s - str.size(), ' ') + str;
	else
		return str;
}

int get_city_index(vector<string> cities, string cityToFind) {
	int size = cities.size();
	for (int i = 0; i < size; i++) {
		if (cities[i] == cityToFind) {
			return i;
		}
	}
	return -1;
}

void items_to_vector(vector<City> item, vector<string>& vector) {
	for (const City& city : item) {
		vector.push_back(city.CityName);
		vector.push_back(city.DestinationName);
	}
}

