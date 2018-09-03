#pragma once
#ifndef CIRCLE_H
#define CIRCLE_H

#include"allshapes.h"

class circle : public shapes
{
	int r;

public:
	circle()
	{
		num_points = 2;
	}

	void draw(int& clr,bool& flag, const point& p1, const point& p2, shapes& obj)
	{
		r = sqrt(pow(p1.x - p2.x, 2) + pow(p1.y - p2.y, 2));
		GP142_circleXY(clr, p1.x, p1.y, r);
		color = clr;
		p_v.push_back(p1);
		p_v.push_back(p2);
		flag = false;
		
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		type = 1;
		obj.draw(*this);

	}
	bool contains(point p,shapes* obj)
	{
		
	}

	void change_colors()
	{

	}




};

#endif // !CIRCLE_H
