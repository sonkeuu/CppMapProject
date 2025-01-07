#pragma once
#include <string>
#include <vector>
#include "maps_input.h"

using namespace std;

string pad_left(string const& str, size_t s); 

int get_city_index(vector<string> cities, string cityToFind);

void items_to_vector(vector<City> item, vector<string>& vector);
