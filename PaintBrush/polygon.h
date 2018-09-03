#pragma once
#ifndef POLYGON_H
#define POLYGON_H

#include"allshapes.h"

class polygon : public shapes
{

protected:
	
	int fillcolor ;
public:
	polygon()
	{
		fillcolor = 0;
	}
	virtual void fillcolors(){}
	void draw(vector<point> cp, int& clr, bool& flag, shapes& obj)
	{
		num_points = cp.size();
		GP142_printfXY(6, 90, 90, 10, "%d", num_points);
		fillcolor = clr;
		color = fillcolor;
		for (int i = 0; i < num_points-1; i++)
		{
			GP142_lineXY(fillcolor, cp[i].x, cp[i].y, cp[i + 1].x, cp[i + 1].y, 1);
			p_v.push_back(cp[i]);
		}
		GP142_lineXY(fillcolor, cp[num_points-1].x, cp[num_points-1].y, cp[0].x, cp[0].y, 1);
		p_v.push_back(cp[num_points-1]);
		flag = false;
		
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		type = 4;
		obj.draw(*this);
	}
	bool contains(point p) {
		////// Notes for ray casting
		////// if x is less than the line min_x and y is in the range of line's y than it will intersect
		////// if outside y range never intersect
		////// if inside y range but greater than max_x than never intersect
		////// if inside y range and inside x range than go pixel by pixel on the ray.
		//int intersections = 0;
		//for (int i = 0; i < points.size(); i++) {
		//	if (p.y >= min(points[i].y, points[i + 1].y) && p.y <= max(points[i].y, points[i + 1].y)) {
		//		if (p.x < min(points[i].x, points[i + 1].x)) {
		//			intersections++;
		//			continue;
		//		}
		//		else if (p.x >= max(points[i].x, points[i + 1].x)) {
		//			continue;
		//		}
		//		else {
		//			for (int j = p.x; j < max(points[i].x, points[i + 1].x); j++) {
		//				point currentPoint = { j, p.y };
		//				if (PointOnLine(currentPoint, points[i], points[i + 1])) {
		//					intersections++;
		//					break;
		//				}
		//			}
		//		}
		//	}
		//	else {
		//		continue;
		//	}
		//}
		//if (p.y >= min(points[0].y, points[points.size() - 1].y) && p.y <= max(points[0].y, points[points.size() - 1].y)) {
		//	if (p.x < min(points[0].x, points[points.size() - 1].x)) {
		//		intersections++;
		//	}
		//	else {
		//		for (int j = p.x; j < max(points[0].x, points[points.size() - 1].x); j++) {
		//			point currentPoint = { j, p.y };
		//			if (PointOnLine(currentPoint, points[0], points[points.size() - 1])) {
		//				intersections++;
		//				break;
		//			}
		//		}
		//	}
		//}
		//if (intersections % 2 != 0)
		//	return 1;
		//else
		//	return 0;
	}
	
};

#endif // !POLYGON_H