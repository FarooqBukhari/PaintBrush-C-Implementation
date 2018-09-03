#pragma once
#ifndef TEXT_H
#define TEXT_H

#include"allshapes.h"

class text : public shapes
{
	int ending_width;
public:
	text()
	{
		ending_width = 0;
		num_points = 1;
	}
	
	void draw(point& p , int& clr , char key , int& key_c , bool& flag, shapes& obj , char k[] , int t)
	{
		const  int point_size = 15;
		/* count number of keypresses   */
		GP142_printfXY(clr, p.x + point_size*key_c,p.y, point_size, "%c", key);
		if (key_c == 0)
		{
			ending_width = p.x + point_size*key_c; 
			color = clr;
			key_c++;
		}
		else {
			ending_width = ending_width + point_size*key_c;
			key_c = (key_c + 1);
		}
		if (key == 13 || key == '\n' || key == 10)
		{
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			flag = false;
			keyss_pressed = keyss_pressed + k;
			p_v.push_back(p);
			type = 2;
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

#endif // !TEXT_H
