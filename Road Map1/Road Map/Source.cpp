#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include"Road_map.h"
#include <time.h>
#include<iomanip>
#include<iostream>
#include<vector>
#include<queue>
#include<functional>
#include<iomanip>
#include <string>
#include<stack>
#include <fstream>
using namespace std;
int main()
{
	char c = 'y';
		while (c == 'y')
		{
			system("CLS");
			cout << "Choose Test Cases" << endl;
			cout << " [1] Sample Test Cases" << endl;
			cout << " [2] Medium Test Cases" << endl;
			cout << " [3] Large Test Cases" << endl;
			int t; cin >> t;   // Number of Test Case
			Road_map R; // Object from Road Map
			long double x1, y1, x2, y2, r;  // point 1( X1 , Y1 ) , point 2 ( X2 , Y2 )
			queue<string>Quaryes;  // to store File Data
			string line;      // To get line from files
			ifstream Quary1;
			int Q;  // store Number of Quaries
			int x;
			if (t == 1)
			{
				cout << "Choose Map Number 1 - 5" << endl;
				cin >> x;
				if (x == 1)
				{
					R.get_node("Samples/[1] Sample Cases/map1.txt");
					Quary1.open("Samples/[1] Sample Cases/queries1.txt");
				}
				else if (x == 2)
				{
					R.get_node("Samples/[1] Sample Cases/map2.txt");
					Quary1.open("Samples/[1] Sample Cases/queries2.txt");
				}
				else if (x == 3)
				{
					R.get_node("Samples/[1] Sample Cases/map3.txt");
					Quary1.open("Samples/[1] Sample Cases/queries3.txt");
				}
				else if (x == 4)
				{
					R.get_node("Samples/[1] Sample Cases/map4.txt");
					Quary1.open("Samples/[1] Sample Cases/queries4.txt");
				}
				else if (x == 5)
				{
					R.get_node("Samples/[1] Sample Cases/map5.txt");
					Quary1.open("Samples/[1] Sample Cases/queries5.txt");
				}
			}
			else if (t == 2)
			{
				R.get_node("Samples/[2] Medium Cases/OLMap.txt");
				Quary1.open("Samples/[2] Medium Cases/OLQueries.txt");
			}
			else if (t == 3)
			{
				R.get_node("Samples/[3] Large Cases/SFMap.txt");

				Quary1.open("Samples/[3] Large Cases/SFQueries.txt");
			}
			else
			{
				cout << "Invalid Number.." << endl;
				return 0;
			}
			if (Quary1.is_open())
			{
				while (!Quary1.eof() && Quary1.peek() != std::ifstream::traits_type::eof())
				{
					Quary1 >> line;
					Quaryes.push(line);
				}
				Quary1.close();
			}
			clock_t Program_Start = clock();
			ofstream result;
			if (t == 1 && x == 1)
				result.open("Results/output_Sample1.txt");
			else if (t == 1 && x == 2)
				result.open("Results/output_Sample2.txt");
			else if (t == 1 && x == 3)
				result.open("Results/output_Sample3.txt");
			else if (t == 1 && x == 4)
				result.open("Results/output_Sample4.txt");
			else if (t == 1 && x == 5)
				result.open("Results/output_Sample5.txt");
			else if (t == 2)
				result.open("Results/output_Medium Case.txt");
			else if (t == 3)
				result.open("Results/output_Large Case.txt");
			Q = stoi(Quaryes.front());
			Quaryes.pop();
			clock_t tStart ;
			while (Q--)
			{
				tStart = clock();
				x1 = stod(Quaryes.front());
				Quaryes.pop();
				y1 = stod(Quaryes.front());
				Quaryes.pop();
				x2 = stod(Quaryes.front());
				Quaryes.pop();
				y2 = stod(Quaryes.front());
				Quaryes.pop();
				r = stod(Quaryes.front());
				Quaryes.pop();
				double shortest_time = R.Find_minimum_cost(x1, y1, x2, y2, r);
				vector<int> Path = R.construct_path();
				for (int i = 0; i < Path.size(); i++)
				if (i + 1<Path.size())result << Path[i] << " ";
				else result << Path[i];
				result << "\n";
				result << fixed << setprecision(2) << shortest_time << " mins\n";
				result << fixed << setprecision(2) << R.Walking_distance + R.vehicle_distance << " km\n";
				result << fixed << setprecision(2) << R.Walking_distance << " km\n";
				result << fixed << setprecision(2) << R.vehicle_distance << " km\n";
				result << "\n";
			}
			result << (double)(clock() - tStart) / (CLOCKS_PER_SEC) << " ms" << endl;
			result << "\n";
			result << (double)(clock() - Program_Start) / (CLOCKS_PER_SEC) << " ms" << endl;
			result.close();
			cout << "Do you want continue y/n" << endl;
			cin >> c;
			c = tolower(c);
		}
}