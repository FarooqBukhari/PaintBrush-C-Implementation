#pragma once
#ifndef LINE_H
#define LINE_H

#include"openshape.h"

class line : public openshape
{

public:
	line()
	{
		num_points = 2;
	}

	void draw(int& clr, bool& flag , const point& p1 , const point& p2, shapes& obj)
	{
		if (flag == true)
		{
			GP142_lineXY(clr, p1.x, p1.y, p2.x, p2.y, 1);
			color = clr;
			p_v.push_back(p1);
			p_v.push_back(p2);
			flag = false;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			type = 3;
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

#endif // !LINE_H
