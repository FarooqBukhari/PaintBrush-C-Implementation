#pragma once
#ifndef CURVE_H
#define CURVE_H

#include"openshape.h"

class curve : public openshape
{
public:
	virtual void fillcolors() {}
	void draw(vector<point> cp, int& clr, bool& flag, shapes& obj)
	{
		num_points = cp.size();
		GP142_printfXY(6, 90, 90, 10, "%d", num_points);
		color = clr;
		for (int i = 0; i < num_points-1 ; i++)
		{
			GP142_lineXY(color, cp[i].x, cp[i].y, cp[i + 1].x, cp[i + 1].y, 1);
			p_v.push_back(cp[i]);
		}
		p_v.push_back(cp[num_points-1]);
		flag = false;
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		type = 5;
		obj.draw(*this);
	}
	bool contains(point p_c) {}
};

#endif // !CURVE_H