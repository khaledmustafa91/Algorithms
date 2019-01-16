#pragma once
#include<iostream>
#include<vector>
#include<set>
using namespace std;
class Road_map
{
	vector<pair<int, pair<long double,long double>>>nodes;
	vector<vector<pair<int, pair<long double,long double> > > >Graph; // { child, { distance,speed }
	vector<int>parent;
	int destination_parent; 
	int destination_path;
	vector<int>Path;
public:
	Road_map();
	void get_node(string textfile);
	long double Walking_distance;
	long double vehicle_distance;

	vector<int> Get_Expected_Node(pair<long double,long double>,long double);
	vector< pair<long double,long double> >dijkstra(int source,set<int>&);
	long double distance(long double,long double,long double,long double);
	long double Find_minimum_cost(long double,long double,long double,long double,long double);  // (X,Y)->source  ; (X1,Y1) -> destination ; R
	vector<int> construct_path();
	~Road_map();
};


