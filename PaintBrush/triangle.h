#pragma once
#ifndef TRIANGLE_H
#define TRIANGLE_H

#include"polygon.h"

class triangle : public polygon
{
	
public:
	triangle()
	{
		num_points = 3;
	}

	void draw(int& clr, bool& flag, const point& p1, const point& p2, const point& p3, shapes& obj)
	{
		if (flag == true)
		{
			GP142_lineXY(clr, p1.x, p1.y, p2.x, p2.y, 1);
			GP142_lineXY(clr, p2.x, p2.y, p3.x, p3.y, 1);
			GP142_lineXY(clr, p3.x, p3.y, p1.x, p1.y, 1);
			color = clr;
			//floodFill((p1.x + p2.x + p3.x) / 3, (p1.y + p2.y + p3.y) / 3, color, WHITE);
			p_v.push_back(p1);
			p_v.push_back(p2);
			p_v.push_back(p3);
			flag = false;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			type = 6;
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

#endif // !TRIANGLE_H
