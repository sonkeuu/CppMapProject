#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

struct City {
	string CityName;
	string DestinationName;
	int Distance;
};

vector<City> read_cities_distances(const string& fileName);

vector<City> read_cities_to_find(const string& fileName);

