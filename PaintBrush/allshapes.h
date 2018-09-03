#pragma once
#ifndef ALLSHAPES_H
#define ALLSHAPES_H


#include<iostream>
#include"GP142.H"
#include<fstream>
#include<string>
#include<vector>
#include<conio.h>
#include<Windows.h>


using namespace std;
struct point {
	int x, y;
};

class shapes
{
	shapes* allshapes;
protected:
	int size;
	int index;
	vector <point> p_v;
	string keyss_pressed;
	int type;
	int color;
	int num_points;
	

public:
	shapes()
	{
		allshapes = nullptr;
		size = 5;
		index = 0;
		num_points = 0;
	}

	void setter(int s)
	{
		size = s;
	}
	
	void draw(const shapes& obj)
	{
		if (index == 0)
		{
			allshapes = new shapes[size];
			allshapes[index] = obj;
			index++;
		}
		else if (index == size)
		{
			int prev_size;
			shapes* temp = new shapes[size];
			for (int i = 0; i < size; i++)
				temp[i] = allshapes[i];
			prev_size = size;
			size = size * 2;
			delete[] allshapes;
			allshapes = new shapes[size];
			for (int i = 0; i < prev_size; i++)
				allshapes[i] = temp[i];
			delete[]temp;
			allshapes[index] = obj;
			index++;
		}
		else
		{
			allshapes[index] = obj;
			index++;
		}
		GP142_printfXY(color, 0, 0, 10, "OH Yeah");
	}

	bool PointOnLine(point p, point p1, point p2) {
		int slope = p1.y - p.y / p1.x - p.x;
		int slope1 = p1.y - p2.y / p1.x - p2.x;
		if (slope - slope1<3)
		{
			if (p.x >= p1.x && p.x <= p2.x)
			{
				return true;
			}
			else
			{
				if (p.x >= p2.x && p.x <= p1.x)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else
		{
			return false;
		}
	}

	void savedrawing() {
		ofstream fout;
		fout.open("drawing.txt");
		fout << index << "\n";  // number of shapes
		for (int i = 0; i < index; i++)
		{
			fout << allshapes[i].type <<endl ;
			fout << allshapes[i].color << endl;
			fout << allshapes[i].num_points << endl;
			for (int j = 0; j < allshapes[i].num_points; j++)
			{
				fout << allshapes[i].p_v[j].x << endl;
				fout << allshapes[i].p_v[j].y;
				fout << endl;
			}
			if (allshapes[i].type == 2)
				fout << allshapes[i].keyss_pressed << endl << endl;
			else
				fout << endl;
		}
		fout.close();

	}

	~shapes(void){}
};

#endif // !ALLSHAPES_H
