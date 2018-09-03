#pragma once
#ifndef RECTANGLE_H
#define RECTANGLE_H

#include"polygon.h"

class rectangle : public polygon
{
	
public:
	rectangle()
	{
		num_points = 2;
	}

	void draw(int& clr, bool& flag, const point& p1, const point& p2, shapes& obj)
	{
		if (flag == true)
		{
			GP142_lineXY(clr, p1.x, p1.y, p2.x, p1.y, 1);
			GP142_lineXY(clr, p2.x, p1.y, p2.x, p2.y, 1);
			GP142_lineXY(clr, p2.x, p2.y, p1.x, p2.y, 1);
			GP142_lineXY(clr, p1.x, p2.y, p1.x, p1.y, 1);
			color = clr;
			p_v.push_back(p1);
			p_v.push_back(p2);
			flag = false;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			type = 7;
			obj.draw(*this);
		}

	}
	bool contains(point p_c)
	{

	}

	void change_colors()
	{

	}




};

#endif // !RECTANGLE_H
