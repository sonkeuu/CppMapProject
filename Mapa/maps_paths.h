#pragma once
#include <vector>
#include <iostream>

using namespace std;

const int Infinity = numeric_limits<int>::max();

void floydWarshall(vector<vector<int>>& dist, vector<vector<int>>& next); 

vector<int> constructPath(int u, int v, const vector<vector<int>>& next);