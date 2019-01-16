#include "Road_map.h"
#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<iomanip>
#include <string>
#include<stack>
#include <fstream>
using namespace std;
Road_map::Road_map()
{
	vehicle_distance=0;

}
long double Road_map::distance(long double X, long double Y,long double X1,long double Y1){
	return sqrt((X - X1)*(X - X1) + (Y - Y1)*(Y - Y1));
}
//Tish function wil return vector of nodes we can start and end
/*
complexity of this code
O(V)
*/
vector <int> Road_map::Get_Expected_Node(pair<long double,long double> p,long double r) // ( start or end point , Distance R) 
{
	vector <int>Expected_Nodes;
	for (int i = 0; i < nodes.size(); i++)// number of iteration is (V) * body O(1) 
		if (distance(p.first, p.second, nodes[i].second.first, nodes[i].second.second) <= (r / 1000))
			Expected_Nodes.push_back(nodes[i].first);  //O(1)
	return Expected_Nodes; // return vector of accepted Nodes
}
/* read data from file */
/*total complexity is O(E+V)*/
void Road_map::get_node(string textfile) {
	queue<string>road_map;
	string line;
	ifstream _map;
	int x, node_source, node_destination, number_of_node, number_of_edges;
	double y, z, distance, speed;
	_map.open(textfile);
	if (_map.is_open())    //O(E+V)
	{
		while (!_map.eof() && _map.peek() != std::ifstream::traits_type::eof()) //O(E+V) E-> number of edges , V-> number of vertics
		{
			_map >> line;
			road_map.push(line);
		}
		_map.close();

		number_of_node = stoi(road_map.front()); //O(number of digits of string ) = O(1)
		nodes.resize(number_of_node);            // O(1)
		road_map.pop();                          // O(1)
		int i = 0;                               // O(1)
		while (i<number_of_node)   //O(V)
		{
			x = stoi(road_map.front());   // O(1)
			road_map.pop();                //O(1)
			y = stod(road_map.front());  //O(1)
			road_map.pop();              // O(1)
			z = stod(road_map.front());  // O(1)
			road_map.pop();              // O(1)
			nodes[i] = make_pair(x, make_pair(y, z));  // { node_number, { X, Y } }
			i++;
		}
		number_of_edges = stoi(road_map.front()); // O(1)
		road_map.pop();               // O(1)
		Graph.resize(number_of_node);      // O(E)
		while (!road_map.empty()) //O(E)
		{

			node_source = stoi(road_map.front());       // O(1)
			road_map.pop();                             // O(1)
			node_destination = stoi(road_map.front());  // O(1)
			road_map.pop();                             // O(1)
			distance = stod(road_map.front());          // O(1)
			road_map.pop();                             // O(1)
			speed = stod(road_map.front());             // O(1)
			road_map.pop();                             // O(1)
														/*Constract Graph (adj list)*/
			Graph[node_source].push_back(make_pair(node_destination, make_pair(distance, speed))); // O(1)
			Graph[node_destination].push_back(make_pair(node_source, make_pair(distance, speed))); // O(1)
			if (road_map.size() == 1)  // O(1)
				break;
		}
	}
}
/* total complexity is O(E log (V) ) */

vector< pair<long double,long double> > Road_map::dijkstra(int source,set<int>&End){
	priority_queue<pair<pair<long double, long double>, int >, vector<pair < pair<long double, long double>, int >>, greater<pair<pair<long double, long double>, int>> >q;
	parent.resize(nodes.size() + 5); //O(1)
	for (int i = 0; i < nodes.size() + 5; i++)parent[i] = -10;//O(v) exact
	vector< pair<long double, long double >  >cost (nodes.size());
	for (int i = 0; i < nodes.size(); i++)//O(v) exact
		cost[i] = make_pair(1e18, 1e18); //O(1) 
	bool *visited = new bool[nodes.size()];
	for (int i = 0; i < nodes.size(); i++) //O(v) exact
		visited[i] = false;
	q.push(make_pair(make_pair(0,0), source)); //O(log v) 
	cost[source] = make_pair(0,0);
	while (!q.empty()&&End.size()){ //O(v) 
		pair<pair<long double,long double > , int > selected_node = q.top();
		q.pop(); //O(1) 
		if (visited[selected_node.second] == true) continue;  //O(1) 
		visited[selected_node.second] = true; //O(1) 
		End.erase(selected_node.second);
		parent[source] = -1; //O(1) 
		for (int i = 0; i < Graph[selected_node.second].size(); i++){ //O(E log(v) ) 
			// cost_edge = cost to move from parent node to child 
			if (visited[Graph[selected_node.second][i].first] == false && cost[selected_node.second].first + Graph[selected_node.second][i].second.first / Graph[selected_node.second][i].second.second <= cost[Graph[selected_node.second][i].first].first){
				cost[Graph[selected_node.second][i].first] = make_pair(cost[selected_node.second].first + Graph[selected_node.second][i].second.first / Graph[selected_node.second][i].second.second, cost[selected_node.second].second + Graph[selected_node.second][i].second.first);
				q.push(make_pair(make_pair(cost[selected_node.second].first + Graph[selected_node.second][i].second.first / Graph[selected_node.second][i].second.second, cost[selected_node.second].second + Graph[selected_node.second][i].second.first), Graph[selected_node.second][i].first));
				parent[Graph[selected_node.second][i].first] = selected_node.second; //O(1) 
			}
		}
	}
	return cost;
}

long double Road_map::Find_minimum_cost(long double X,long double Y,long double X1,long double Y1,long double R){
	long double Best_time = 1e18; //O(1)
	int end_node;
	long double time_begin/* cost from start position to start node  */, time_end/* time form end node to end position */;
	vector<int>Start = Get_Expected_Node(make_pair(X, Y), R);  //O(V) (Exact) possible start nodes  
	vector<int>End = Get_Expected_Node(make_pair(X1, Y1), R);  //O(V) (Exact) possible end nodes 
	for (int i = 0; i < Start.size(); i++){   //O(V)  build dijkstra from all start nodes -> get best time from start node to all end nodes 
		time_begin = distance(X, Y, nodes[Start[i]].second.first, nodes[Start[i]].second.second) / 5 * 60; //O(1)  can walk 5 (Kh/H) .. convert to minutes    
		vector< pair<long double, long double> > all_node_cost (nodes.size());
		/////////////////////////
		set<int>st;
		for (int h = 0; h < End.size(); h++)
			st.insert(End[h]);
		/////////////////////////
		all_node_cost = dijkstra(Start[i],st);    //O(E log(V) ) cost from start node [i] to all end nodes
		long double best_node_time = 1e18; //O(1)
		for (int j = 0; j < End.size(); j++){ //O(v)
			destination_parent = End[j]; //O(1)
			time_end = distance(X1, Y1, nodes[End[j]].second.first, nodes[End[j]].second.second) / 5 * 60; // O(1)  (Exact)
			if (best_node_time > all_node_cost[End[j]].first * 60 + time_end){ //O(1)
				best_node_time = all_node_cost[End[j]].first * 60 + time_end;//O(1)
				Path.resize(nodes.size() + 5);//O(1)
				destination_path = destination_parent;//O(1)
				end_node = End[j];//O(1)
			}
		}
		if (Best_time > best_node_time + time_begin){//O(v)
			Best_time = best_node_time + time_begin;//O(1)
			Walking_distance = distance(X, Y, nodes[Start[i]].second.first, nodes[Start[i]].second.second)//O(1)
				+ distance(X1, Y1, nodes[end_node].second.first, nodes[end_node].second.second);
			vehicle_distance = all_node_cost[end_node].second;//O(1)
			Path.clear();//O(1)
			Path = parent;//O(1)
		}
	}
	return Best_time;
}
/* total complexity will be O(V) */
vector<int> Road_map::construct_path(){
	vector<int>ans; //O(1)
	stack<int>st; //O(1)
	st.push(destination_path); //O(1)
	int cur = destination_path; //O(1)
	while (Path[cur] != -1){ //O(v)
		st.push(Path[cur]); //O(1)
		cur = Path[cur]; //O(1)
	}
	while (!st.empty()){ //O(v)
		ans.push_back(st.top()); //O(1)
		st.pop(); //O(1)
	}
	return ans;
}
Road_map::~Road_map()
{
}
