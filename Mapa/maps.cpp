#include <iostream>
#include <vector>
#include <map>
#include <fstream>
#include <string>
#include <sstream>
#include <algorithm>
#include <set>
#include "maps.h"

using namespace std;

struct CityWithDistance {
	string CityName;
	string DestinationName;
	int Distance;
};



int get_city_index(vector<string> cities, string cityToFind);

string pad_left(string const& str, size_t s) {
	if (str.size() < s)
		return std::string(s - str.size(), ' ') + str;
	else
		return str;
}

void print_matrix(int* matrix, int mtx_size, vector<string>& unique_cities) {
	const int padding = 14;

	cout << pad_left("", padding);
	for (int c = 0; c < mtx_size; c++) {
		cout << pad_left(unique_cities[c], padding);
	}

	cout << endl;

	for (int i = 0; i < mtx_size; i++) {
		string cityName = pad_left(unique_cities[i], padding);
		cout << cityName;
		for (int j = 0; j < mtx_size; j++) {

			string valueAsString = to_string(*(matrix + i * mtx_size + j));
			cout << pad_left(valueAsString, padding);
		}
		cout << endl;
	}
}

int* create_matrix(int size) {
	int lenght = size * size;
	int* arr = new int[lenght];
	memset(arr, 0, sizeof(int) * lenght);
	return arr;
}

void fill_matrix(int* matrix, vector<CityWithDistance> mapItems, vector<string> uniques, int mtx_size, bool useDistance) {
	for (const CityWithDistance& city : mapItems) {

		int line = get_city_index(uniques, city.CityName);
		int column = get_city_index(uniques, city.DestinationName);
		if (line >= 0 && column >= 0) {
			int distance = useDistance ? city.Distance : (city.Distance != 0 ? 1 : 0);
			*(matrix + line * mtx_size + column) = distance;
		}
	}
}

vector<CityWithDistance> read_lines(const string &fileName) {
	ifstream file(fileName);
	string lineFromFile;
	vector<CityWithDistance> result;
		
	while (getline(file, lineFromFile)) {
		stringstream lineCheck(lineFromFile);
		string token;
		vector<string> foundWords;

		while (getline(lineCheck, token, ';')) {
			foundWords.push_back(token);
		}

		if (foundWords.size() != 3) {
			vector<CityWithDistance> emptyResult;
			cout << "Error: Incorrect number of words in the lines.";
			return emptyResult;
		}

		int kmAsInt;
		string km = foundWords[2];

		try {
			kmAsInt = stoi(km, 0, 10);
		}
		catch(...) {
			vector<CityWithDistance> emptyResult;
			cout << "Error: Invalid distance format.";
			return emptyResult;
		}

		CityWithDistance cityItem;
		cityItem.CityName = foundWords[0];
		cityItem.DestinationName = foundWords[1];
		cityItem.Distance = kmAsInt;
		result.push_back(cityItem);
	}
	return result;
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

int get_matrix_value(int* arr, int mtx_size, int source_city_index, int destination_city_index) {
	return *(arr + source_city_index * mtx_size + destination_city_index);
}

void set_matrix_value(int* arr, int mtx_size, int source_city_index, int destination_city_index, int value) {
	*(arr + source_city_index * mtx_size + destination_city_index) = value;
}

void warshall(int* arr, int mtx_size) {
	for (int x = 0; x < mtx_size; x++) {
		for (int y = 0; y < mtx_size; y++) {
			for (int z = 0; z < mtx_size; z++) {
				if (get_matrix_value(arr, mtx_size, y, z) == 0) {
					set_matrix_value(arr, mtx_size, y, z, (get_matrix_value(arr, mtx_size, y, x) * get_matrix_value(arr, mtx_size, x, z)));
					//*(arr + z + y * mtx_size) = *(arr + y + x * mtx_size)
				}
			}
		}
	}
}


void write_if_route_exists(int* matrix, int size, int source_city_index, int destination_city_index, vector<string> cities) {
	int k;
	if (get_matrix_value(matrix, size, source_city_index, destination_city_index) == 0) {
		cout << "This route does not exist." << endl;
	}
	else {
		cout << cities[source_city_index] << endl;
		k = source_city_index;
		while (k != destination_city_index) {
			k = get_matrix_value(matrix, size, k, destination_city_index);
			cout << cities[k] << endl;
		}
	}
	cout << endl;
}

void init_route(int* matrix, int size)
{
	for (int x = 0; x < size; x++) 
	{
		for (int y = 0; y < size; y++) 
		{
			if (get_matrix_value(matrix, size, x, y) != 0) 
			{
				set_matrix_value(matrix, size, x, y, y);
			}
		}
	}
}

void build_route(int* matrix, int size)
{
	for (int x = 0; x < size; x++) 
	{
		for (int y = 0; y < size; y++) 
		{
			if (get_matrix_value(matrix, size, y, x) != 0) 
			{
				for (int z = 0; z < size; z++) 
				{
					if (get_matrix_value(matrix, size, y, z) == 0 && get_matrix_value(matrix, size, x, z) != 0) 
					{
						set_matrix_value(matrix, size, y, z, get_matrix_value(matrix, size, y, x));
					}
				}
			}
		}
	}
}

void print_route(int* matrix, int size, int x, int y, vector<string> cities)
{
	int k = get_matrix_value(matrix, size, x, y);
	if (k == 0)
	{
		cout << "route not exists.";
		return;
	}

	cout << cities[x] << endl;
	cout << cities[k] << endl;
	while (k != y) 
	{
		k = get_matrix_value(matrix, size, k, y);
		cout << cities[k] << endl;
	}
}

void droga_floyd(int* matrix, int size, int i, int j, vector<string> cities)
{
	int k = get_matrix_value(matrix, size, i, j);
	if (k != 0) 
	{
		droga_floyd(matrix, size, i, k, cities);
		cout << cities[k] << endl;
		droga_floyd(matrix, size, k, j, cities);
	}
}

void print_floyd_route(int* matrix, int size, int x, int y, vector<string> cities) 
{
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (get_matrix_value(matrix, size, i, j) == 10000)
			{
				cout << cities[i] << " --> " << cities[j] << " - route not exists.";
				cout << endl;
				break;				
			} 
			else 
			{
				if (i != j) 
				{
					cout << cities[i] << " => " << cities[j] << " koszt " << get_matrix_value(matrix, size, i, j) << " Droga przez: ";
					droga_floyd(matrix, size, i, j, cities);
					cout << endl;
				}
			}
		}
	}
}

void matrix_minimum_value(int* matrix, int* matrix_to_save_routes, int size) {
	for (int k = 0; k < size; k++)
	{
		for (int i = 0; i < size; i++)
		{
			for (int j = 0; j < size; j++)
			{

				int a = get_matrix_value(matrix, size, i, j);
				int b = get_matrix_value(matrix, size, i, k) + get_matrix_value(matrix, size, k, j);
				/*
				set_matrix_value(floyd_route_matrix, mtx_size, i, j, min(a, b));
				*/
				if (b < a)
				{
					set_matrix_value(matrix, size, i, j, b);
					set_matrix_value(matrix_to_save_routes, size, i, j, k);
				}
			}
		}
	}
}

void fill_10000(int* matrix, int size) {
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (get_matrix_value(matrix, size, x, y) == 0)
			{
				set_matrix_value(matrix, size, x, y, 10000);
			}
		}
	}
}

void fill_0(int* matrix, int size) {
	for (int x = 0; x < size; x++)
	{
		for (int y = 0; y < size; y++)
		{
			if (get_matrix_value(matrix, size, x, y) == 10000)
			{
				set_matrix_value(matrix, size, x, y, 0);
			}
		}
	}
}


void write_route(int* arr2, int mtx_size) {
	for (int x = 0; x < mtx_size; x++) {
		for (int y = 0; y < mtx_size; y++) {
			if (get_matrix_value(arr2, mtx_size, y, x) != 0) {
				for (int z = 0; z < mtx_size; z++) {
					if (get_matrix_value(arr2, mtx_size, y, z) == 0 && get_matrix_value(arr2, mtx_size, x, z) == 0) {
						set_matrix_value(arr2, mtx_size, y, z, get_matrix_value(arr2, mtx_size, y, x));
					}
				}
			}
		}
	}
}

void floyd(int* arr, int * arr2, int mtx_size) {
	for (int k = 0; k < mtx_size; k++) {
		for (int i = 0; i < mtx_size; i++) {
			for (int j = 0; j < mtx_size; j++) {
				int arikj = (get_matrix_value(arr, mtx_size, i, k) + get_matrix_value(arr, mtx_size, k, j));
				if (arikj < get_matrix_value(arr, mtx_size, i, j)) {
					set_matrix_value(arr, mtx_size, i, j, arikj);
					set_matrix_value(arr2, mtx_size, i, j, k);
				}
			}
		}
	}
}


int main() {
	vector<CityWithDistance> mapItems = read_lines("example.txt");
	cout << mapItems.size() << " ";
	vector<string> sorted;

	for (const CityWithDistance& city : mapItems) {
		cout << city.CityName << " " << city.DestinationName << " " << city.Distance << endl;
	}
	for (const CityWithDistance& city : mapItems) {
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

	
	// start...
	int mtx_size = uniques.size();
	
	int* distances_matrix = create_matrix(mtx_size);
	fill_matrix(distances_matrix, mapItems, uniques, mtx_size, true);

	int* warshall_matrix = create_matrix(mtx_size);
	fill_matrix(warshall_matrix, mapItems, uniques, mtx_size, false);

	int* warshall_matrix_done = create_matrix(mtx_size);
	fill_matrix(warshall_matrix_done, mapItems, uniques, mtx_size, false);

	

	

	cout << endl;
	cout << "Matrix containing distances.";
	cout << endl;

	print_matrix(distances_matrix, mtx_size, uniques);

	cout << endl;

	print_matrix(warshall_matrix, mtx_size, uniques);
	
	warshall(warshall_matrix_done, mtx_size);
	cout << "warshall";
	cout << endl;
	print_matrix(warshall_matrix_done, mtx_size, uniques);

	int* route_matrix = create_matrix(mtx_size);
	fill_matrix(route_matrix, mapItems, uniques, mtx_size, true);
	init_route(route_matrix, mtx_size);
	cout << "after init_route";
	cout << endl;
	print_matrix(route_matrix, mtx_size, uniques);

	build_route(route_matrix, mtx_size);
	cout << "after build_route";
	cout << endl;
	print_matrix(route_matrix, mtx_size, uniques);
	print_route(route_matrix, mtx_size, get_city_index(uniques, "*0*"), get_city_index(uniques, "*2*"), uniques);

	// floyd from here

	delete[] route_matrix;
	delete[] distances_matrix;
	
	int* floyd_result_matrix = create_matrix(mtx_size);
	int* floyd_route_matrix = create_matrix(mtx_size);
	fill_matrix(floyd_route_matrix, mapItems, uniques, mtx_size, true);
	cout << "after fill floyd_route_matrix";
	cout << endl;
	print_matrix(floyd_route_matrix, mtx_size, uniques);
	cout << endl;
	print_matrix(floyd_result_matrix, mtx_size, uniques);


	fill_10000(floyd_route_matrix, mtx_size);
	matrix_minimum_value(floyd_route_matrix, floyd_result_matrix, mtx_size);

	


	/*
	for (int x = 0; x < mtx_size; x++)
	{
		for (int y = 0; y < mtx_size; y++)
		{
			if (get_matrix_value(floyd_route_matrix, mtx_size, x, y) == 10000)
			{
				set_matrix_value(floyd_route_matrix, mtx_size, x, y, 0);
			}
		}
	}
	*/

	cout << endl;
	print_matrix(floyd_route_matrix, mtx_size, uniques);
	cout << endl;
	print_matrix(floyd_result_matrix, mtx_size, uniques);
	cout << "XXXX";
	cout << endl;
	//fill_0(floyd_route_matrix, mtx_size);
	cout << endl;
	print_matrix(floyd_result_matrix, mtx_size, uniques);


	//print_route(floyd_result_matrix, mtx_size, get_city_index(uniques, "*0*"), get_city_index(uniques, "*2*"), uniques);
	print_floyd_route(floyd_route_matrix, mtx_size, get_city_index(uniques, "*0*"), get_city_index(uniques, "*2*"), uniques);

	//write_if_route_exists(warshall_matrix_done, mtx_size, get_city_index(uniques, "Bedzin"), get_city_index(uniques, "Czeladz"), uniques);
	

	// first algorithm here.

	return 0;
}


