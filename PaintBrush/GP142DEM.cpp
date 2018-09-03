#pragma comment(linker, "/STACK:2000000")
#pragma comment(linker, "/HEAP:2000000")
///*
// * CSE/ENGR 142 GP142_Demo
// *
// * 1/25/95
// * Author(s):         Larry Ruzzo
// * Email Address(s):  ruzzo@cs.washington.edu
// *
// * This program is a demo of some of the features of 
// * GP142 --- the CSE/ENGR 142 Graphics Package.
// * It includes simple drawing commands, keyboard and mouse 
// * interaction, and a simple animation.
// *
// * Revision history:
// * 11/18/97 Dan Boren  - Removed calls to obsolete function GP142_undo()
// *      
// */
// 
#include "GP142.h"
#include <stdio.h>
#include<dos.h>
#include<conio.h>
#include<Windows.h>
#include <math.h>
#include <iostream>
#include "circle.h"
#include "Text.h"
#include "line.h"
#include "curve.h"
#include"rectangle.h"
#include"triangle.h"
#include"polygon.h"
#include"allshapes.h"


#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
/* 
 * Function prototypes.
 */
void side_menu();
void demo_handle_kbd(char key_pressed);
void demo_handle_mouse(int x,int y);
void demo_handle_periodic(void);

void lines(shapes& obj);
void circles(shapes& obj);
void rectangles(shapes& obj);
void triangles(shapes& obj);
void polygons(shapes& obj);
void curves(shapes& obj);
void shape_selection(shapes& obj);
void load();
SHORT WINAPI GetAsyncKeyState(_In_ int vKey);

//Globally used variables
shapes s;
int tx = 0, ty = 0;
bool type_flag = false;
bool circle_flag = false;
bool open_shape_flag = false;
bool polygon_flag = false;
bool selection_flag = false;
bool stop = false;
static int key_count = 0;
int clr = 0;
COLORREF clr_hex = White;
int mouse_x, mouse_y;
char key_pressed;
int pixel_color;
bool ray_casting(int pixel_color , int m_x, int m_y);
char keys[100] ;
int t_c;


/******************************************************************************
 *
 * The Main Program
 * ----------------
 *
 * The main program takes care of initialization and cleanup, and the high-level
 * control of all actions in the program, but most of the detail work is 
 * relegated to sub-functions, so that the structure of main stays clear and 
 * simple.
 *
 */
int main(void)
{      
	
    int quit = 0;           /* has user signaled quit yet?                      */
    GP142_open();           /* Open and initialize the GP142 Graphics Window    */
    
    GP142_logging(LOG_OFF); /* logging is useful to students during debugging,  */
                            /* but annoying during the demo; turn it off.       */
	GP142_rectangleXY(WHITE, -GP142_XMAX, -GP142_YMAX, GP142_XMAX, GP142_YMAX, 0);
	GP142_printfXY(0, -100, -100, 20, "Do you want to Load Previous Diagrams?");
	GP142_printfXY(0, -150, -140, 20, "1 for Yes / Other Keys for No");
	
	switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed))
	{
	case GP142_KBD:
		GP142_rectangleXY(WHITE, -GP142_XMAX, -GP142_YMAX, GP142_XMAX, GP142_YMAX, 0);
		if (key_pressed == '1')
		{
			load();
		}
		
		break;
	}
	side_menu();
	
    /*
     * The main event loop:
     * --- ---- ----- -----
     * wait for the next user action, such as a mouse click or keyboard
     * keypress, or a periodic update event (allowing us to display the
     * next frame of an animation) and call the appropriate function to
     * handle it.  Repeat this until the user signals "quit".
     */
     
    while (!quit) {
    
        switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
            case GP142_QUIT:
                quit = 1;   /* set flag to terminate loop                */
                break;
            case GP142_MOUSE:
                demo_handle_mouse(mouse_x,mouse_y);
                break;
               
            case GP142_KBD:
                demo_handle_kbd(key_pressed);
                break;
            case GP142_PERIODIC:
                demo_handle_periodic();
                break;
            default:
                break;
        }
    }
        
    GP142_close();          /* Clean up and close graphics window           */
    
    return 0;
}

void side_menu()
{
	GP142_lineXY(GREEN, -660, 450, -660, -450, 4);

	//Tool Select Panel
	GP142_printfXY(BLACK, -780, 435, 10, "Tool Selection");

	GP142_rectangleXY(BLACK, -780, 430, -690, 410, 1);
	GP142_printfXY(RED, -778, 412, 12, "Selection Tool");

	GP142_rectangleXY(BLACK, -780, 400, -740, 360, 1);
	GP142_printfXY(RED, -778, 375, 12, "Eraser");

	GP142_rectangleXY(BLACK, -730, 400, -690, 360, 1);
	GP142_printfXY(RED, -725, 375, 12, "Fill");

	GP142_rectangleXY(BLACK, -780, 350, -690, 310, 1);
	GP142_printfXY(RED, -775, 325, 12, "Save Drawing");

	GP142_rectangleXY(BLACK, -780, 300, -740, 260, 1);
	GP142_printfXY(RED, -775, 282, 12, "Open");
	GP142_printfXY(RED, -775, 265, 11, "Shape");

	GP142_rectangleXY(BLACK, -730, 300, -690, 260, 1);
	GP142_printfXY(RED, -729, 275, 11, "Polygon");

	GP142_rectangleXY(BLACK, -780, 250, -740, 210, 1);
	GP142_printfXY(RED, -775, 225, 12, "Circle");

	GP142_rectangleXY(BLACK, -730, 250, -690, 210, 1);
	GP142_printfXY(RED, -722, 225, 12, "Text");

	//Panel Separator
	GP142_lineXY(YELLOW, -800, 190, -660, 190, 4);

	//Color Pallet
	GP142_printfXY(BLACK, -780, 160, 15, "Color Palette");
	GP142_rectangleXY(BLACK, -780, 140, -690, 100, 0);
	GP142_rectangleXY(WHITE, -780, 100, -690, 60, 0);
	GP142_rectangleXY(BLACK, -780, 100, -690, 60, 1);
	GP142_rectangleXY(GREEN, -780, 60, -690, 20, 0);
	GP142_rectangleXY(YELLOW, -780, 20, -690, -20, 0);
	GP142_rectangleXY(RED, -780, -20, -690, -60, 0);
	GP142_rectangleXY(ORANGE, -780, -60, -690, -100, 0);
	GP142_rectangleXY(PURPLE, -780, -100, -690, -140, 0);
	GP142_rectangleXY(BLUE, -780, -140, -690, -180, 0);

	//Panel Separator
	GP142_lineXY(YELLOW, -800, -210, -660, -210, 4);

	//SUB-MENU of Shape Selection

}

void load() {
	ifstream fin;
	char delimiter;
	fin.open("drawing.txt");
	if (fin.fail())
	{
		cout << "file not found" << endl;

	}
	int N_O_S;//no of shapes stored
	fin >> N_O_S;
	s.setter(N_O_S);
	int ShapeType;
	for (int i = 0; i < N_O_S; i++)
	{
		
		fin >> ShapeType;//which shape
		if (ShapeType == 1)//circle
		{
			circle_flag = true;
			int c;//color
			fin >> c;
			int n;//no of points;
			fin >> n;
			point p1, p2;
			fin >> p1.x;
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> p2.x;
			fin.ignore();
			fin >> p2.y;
			fin.ignore();
			circle circle_obj;
			circle_obj.draw(c, circle_flag,p1,p2,s );

		}
		if (ShapeType == 2)//text
		{
			t_c = 0;
			key_count = 0;
			type_flag = true;
			int c;//color
			fin >> c;
			int n;
			fin >> n;
			point p;
			fin >> p.x;//point
			fin.ignore();
			fin >> p.y;
			fin.ignore();
			char v ;
			v = fin.get();
			text text_obj;
			do
			{
				if (v == '\n' || v == 10)
					type_flag = false;
				keys[t_c] = v;
				t_c++;
				text_obj.draw(p, c, v, key_count, type_flag, s, keys, t_c);				
				v = fin.get();
			} while (type_flag != false);
		}
		if (ShapeType == 3)//line
		{

			open_shape_flag = true;
			int c;//color
			fin >> c;
			point p1, p2;
			fin >> p1.x;//point
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> p2.x;//point
			fin.ignore();
			fin >> p2.y;
			fin.ignore();
			line line_obj;
			line_obj.draw(c, open_shape_flag, p1, p2, s);
		}
		if (ShapeType == 4)//Polygon
		{
			polygon_flag = true;
			int c;//color
			fin >> c;
			int n;
			fin >> n;//no of points
			vector<point>pc;
			point p;
			for (int j = 0; j < n; j++)
			{
				fin >> p.x;
				fin.ignore();
				fin >> p.y;
				fin.ignore();
				pc.push_back(p);
			}
			polygon polygon_obj;
			polygon_obj.draw(pc, c, open_shape_flag, s);

		}

		if (ShapeType == 5)//curve
		{
			open_shape_flag = true;
			int c;//color
			fin >> c;
			int n;
			fin >> n;//no of points
			vector<point>pc;
			point p;
			for (int j = 0; j < n; j++)
			{
				fin >> p.x;
				fin.ignore();
				fin >> p.y;
				fin.ignore();
				pc.push_back(p);
			}
			curve curve_obj;
			curve_obj.draw(pc, c, open_shape_flag, s);

		}
		if (ShapeType == 6)
		{
			polygon_flag = true;
			int c;//color
			fin >> c;
			int n;
			fin >> n;//no of points
			point p1, p2, p3;
			fin >> p1.x;//point
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> p2.x;//point
			fin.ignore();
			fin >> p2.y;
			fin.ignore();
			fin >> p3.x;//point
			fin.ignore();
			fin >> p3.y;
			fin.ignore();

			triangle triangle_obj;
			triangle_obj.draw(c, polygon_flag, p1, p2,p3, s);
			
		}

		if (ShapeType == 7)
		{
			int c;//color
			fin >> c;
			int n;
			fin >> n;//no of points
			point p1, p2, p3;
			fin >> p1.x;//point
			fin.ignore();
			fin >> p1.y;
			fin.ignore();
			fin >> p2.x;//point
			fin.ignore();
			fin >> p2.y;
			fin.ignore();

			rectangle rectangle_obj;
			rectangle_obj.draw(c, polygon_flag, p1, p2, s);

		}
	}
}

void lines(shapes& obj)
{
	point p1 , p2;
	switch (GP142_await_event(&mouse_x, &mouse_y,&key_pressed)) {
		
		case GP142_MOUSE:
			p1.x = mouse_x;
			p1.y = mouse_y;
			if ((p1.x > -800 && p1.x < -658) && (p1.y < 450 && p1.y > -450))
			{
				GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
				open_shape_flag = false;
			}
			if(open_shape_flag == true)
			switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

			case GP142_MOUSE:
					p2.x = mouse_x;
					p2.y = mouse_y;
					if ((p2.x > -800 && p2.x < -658) && (p2.y < 450 && p2.y > -450))
					{
						GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
						open_shape_flag = false;
					}
					else
					{
						line line_obj;
						line_obj.draw(clr, open_shape_flag, p1, p2 , obj);
					}
			}
	}
}

void circles(shapes& obj)
{
	point p1, p2;
	switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

	case GP142_MOUSE:
		p1.x = mouse_x;
		p1.y = mouse_y;
		if ((p1.x > -800 && p1.x < -658) && (p1.y < 450 && p1.y > -450))
		{
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			circle_flag = false;
		}
		if (circle_flag == true)
			switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

			case GP142_MOUSE:
				p2.x = mouse_x;
				p2.y = mouse_y;
				if ((p2.x > -800 && p2.x < -658) && (p2.y < 450 && p2.y > -450))
				{
					GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
					circle_flag = false;
				}
				else
				{
					circle circle_obj;
					circle_obj.draw(clr, open_shape_flag, p1, p2,obj);
				}
					
			}
	}

}

void rectangles(shapes& obj)
{
	point p1, p2;
	switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

	case GP142_MOUSE:
		p1.x = mouse_x;
		p1.y = mouse_y;
		if ((p1.x > -800 && p1.x < -658) && (p1.y < 450 && p1.y > -450))
		{
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			polygon_flag = false;
		}
		if (polygon_flag == true)
			switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

			case GP142_MOUSE:
				p2.x = mouse_x;
				p2.y = mouse_y;
				if ((p2.x > -800 && p2.x < -658) && (p2.y < 450 && p2.y > -450))
				{
					GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
					polygon_flag = false;
				}
				else
				{
					rectangle rectangle_obj;
					rectangle_obj.draw(clr, polygon_flag, p1, p2,obj);
				}
				

			}
	}
}

void triangles(shapes& obj)
{
	point p1, p2, p3;
	switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

	case GP142_MOUSE:
		p1.x = mouse_x;
		p1.y = mouse_y;
		if ((p1.x > -800 && p1.x < -658) && (p1.y < 450 && p1.y > -450))
		{
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			polygon_flag = false;
		}
		if (polygon_flag == true)
			switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

			case GP142_MOUSE:
				p2.x = mouse_x;
				p2.y = mouse_y;
				if ((p2.x > -800 && p2.x < -658) && (p2.y < 450 && p2.y > -450))
				{
					GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
					polygon_flag = false;
				}
				switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

				case GP142_MOUSE:
					p3.x = mouse_x;
					p3.y = mouse_y;
					if ((p3.x > -800 && p3.x < -658) && (p3.y < 450 && p3.y > -450))
					{
						GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
						polygon_flag = false;
					}
					if (polygon_flag == true)
					{
						triangle triangle_obj;
						triangle_obj.draw(clr, polygon_flag, p1, p2,p3,obj);
					}

				}
			}
	}
}

void polygons(shapes& obj)
{
	vector<point> cp_p;
	point p;
up:
	if (polygon_flag == true)
	{
		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

		case GP142_MOUSE:
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				stop = true;
			}
			Sleep(100);
			if (stop == false)
			{
				p.x = mouse_x;
				p.y = mouse_y;
			}
			if (stop == true)
			{
				polygon poly_obj;
				poly_obj.draw(cp_p, clr, polygon_flag , obj);
				polygon_flag = false;
			}
			if ((p.x > -800 && p.x < -658) && (p.y < 450 && p.y > -450))
			{
				GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
				polygon_flag = false;
			}
			if (polygon_flag == true)
			{
				cp_p.push_back(p);
				GP142_printfXY(9, 120, -300, 10, "OH Yeah");
				goto up;
			}
		}
	}
	
}

void curves(shapes& obj)
{
	vector<point> cp_p;
	point p;
up:
	if (open_shape_flag == true)
	{
		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {

		case GP142_MOUSE:
			if (GetAsyncKeyState(VK_RBUTTON))
			{
				stop = true;
			}
			Sleep(100);
			if (stop == false)
			{
				p.x = mouse_x;
				p.y = mouse_y;
			}
			if (stop == true)
			{
				curve curve_obj;
				curve_obj.draw(cp_p, clr, open_shape_flag, obj);
				open_shape_flag = false;
			}
			if ((p.x > -800 && p.x < -658) && (p.y < 450 && p.y > -450))
			{
				GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
				open_shape_flag = false;
			}
			if (open_shape_flag == true)
			{
				cp_p.push_back(p);
				GP142_printfXY(9, 120, -300, 10, "OH Yeah");
				goto up;
			}
		}
	}
}

void shape_selection(shapes& obj)
{
	
	switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
	case GP142_MOUSE:
		
		if ((mouse_x > -800 && mouse_x < -658) && (mouse_y < 450 && mouse_y > -450))
		{
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			selection_flag = false;
		}
		else
		{
			
			pixel_color = GP142_GetColor(mouse_x, mouse_y);
			
			GP142_printfXY(Black, mouse_x, mouse_y, 15,"%d", pixel_color);
			//bool checker = ray_casting(pixel_color, mouse_x, mouse_y);
			//if (checker == true)
			//{
			//	//inside shape now do anything 
			//	floodFill(mouse_x, mouse_y, pixel_color,clr);

			//}
			//else
			//{
			//	//outside shape now do anything 
			//	selection_flag = false;
			//}
		}
	
	}
}

//bool ray_casting(int pixe_color , int m_x , int m_y)
//{
//	
//	int p_c;
//	
//	int xcounter = 0 , nxcounter=0 , ycounter =0, nycounter = 0;
//	for (int y = m_y; y < GP142_YMAX; y++)
//	{
//		
//		p_c = GP142_GetColor(m_x, y);
//		
//		if (GP142_GetColor(m_x, y + 1) != p_c && GP142_GetColor(m_x, y + 1) != pixe_color)
//		{
//			
//			break;
//	}
//			
//			if (p_c != pixe_color)
//				ycounter++;
//		}
//	
//		for (int y = m_y; y > -GP142_YMAX; y--)
//
//		{
//			
//			p_c = GP142_GetColor(m_x, y);
//			
//			if (GP142_GetColor(m_x, y - 1) != p_c && GP142_GetColor(m_x, y - 1) != pixe_color)
//			{
//								break;
//		}
//			if (p_c != pixe_color)
//				nycounter++;
//		}
//	
//	
//		for (int x = m_x; x < GP142_XMAX; x++)
//		{
//			
//			p_c = GP142_GetColor(x, m_y);
//			
//			if (GP142_GetColor(x +1, m_y) != p_c && GP142_GetColor(x + 1, m_y) != pixe_color)
//			{
//				
//				break;
//		}
//			if (p_c != pixe_color)
//				xcounter++;
//		}
//
//		for (int x = m_x; x > -659 ; x--)
//		{
//			
//			p_c = GP142_GetColor(x , m_y);
//			
//			if (GP142_GetColor(x - 1, m_y) != p_c && GP142_GetColor(x - 1, m_y) != pixe_color)
//			{
//				
//				break;
//			}
//			if (p_c != pixe_color)
//				nxcounter++;
//		}
//		
//
//	if (xcounter % 2 != 0 && nxcounter % 2 != 0 && nycounter % 2 != 0 && ycounter % 2 != 0)
//	{
//		GP142_printfXY(RED, 300, 300, 15, "Contained");
//		return true;
//	}
//	else
//	{
//		GP142_printfXY(RED, 300, 320, 15, "Not");
//		return false;
//	}
//}

void Fill(int x, int y, int oldcolor, int newcolor)
{

	if (GP142_GetColor(x, y) != oldcolor)
		return;
	else
	{
		GP142_pixelXY(newcolor, x, y);
		Fill(x + 1, y, oldcolor, newcolor);
		Fill(x, y + 1, oldcolor, newcolor);
		Fill(x - 1, y, oldcolor, newcolor);
		Fill(x, y - 1, oldcolor, newcolor);
	}

}

/******************************************************************************
 *
 * demo_handle_mouse
 * -----------------
 *
 * This function handles mouse clicks, echoing coordinates 
 * both to the console and in the graphics window.
 *
 */

//SUB-MENU of Shape Selection

void demo_handle_mouse(int x, int y){
	tx = x;
	ty = y;
	key_count = 0;

	//Tool Selection ifs

	//Selection Tool
	if ((x < -690 && x > -780) && (y < 430 && y>410))
	{
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		GP142_printfXY(RED, -780, -350, 15, "Selection Tool");
		type_flag = false;
		open_shape_flag = false;
		selection_flag = true;
		shape_selection(s);
	}
	//Eraser
	if ((x < -740 && x > -780) && (y < 400 && y>360))
	{
		selection_flag = false;
		type_flag = false;
		open_shape_flag = false;
	}
	//Fill
	if ((x < -690 && x > -730) && (y < 400 && y>360))
	{
		int old;
		selection_flag = false;
		open_shape_flag = false;
		type_flag = false;
		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
		case GP142_MOUSE:
			old = GP142_GetColor(mouse_x,mouse_y);
			Fill(mouse_x, mouse_y, old, clr);
		}
		
	}
	//Save File
	if ((x < -690 && x > -780) && (y < 350 && y>310))
	{
		selection_flag = false;
		open_shape_flag = false;
		type_flag = false;
		s.savedrawing();
	}

	//Basic Shape Choser
	//Open Shape
	if ((x < -690 && x > -780) && (y < -230 && y>-270) || ((x < -740 && x > -780) && (y < 300 && y>260)) ||( (x < -690 && x > -780) && (y < -290 && y>-330)))
	{
		if ((x < -740 && x > -780) && (y < 300 && y>260))
		{
			selection_flag = false;
			open_shape_flag = false;
			type_flag = false;
			polygon_flag = false;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			GP142_rectangleXY(BLACK, -780, -230, -740, -270, 1);
			GP142_printfXY(RED, -770, -255, 12, "Line");
			GP142_rectangleXY(BLACK, -730, -230, -690, -270, 1);
			GP142_printfXY(RED, -725, -255, 12, "Curve");
		}
			//Line Selection
		if ((x < -740 && x > -780) && (y < -230 && y>-270))
		{
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			GP142_printfXY(RED, -780, -350, 15, "Line Selected");
			open_shape_flag = true;
			lines(s);

		}
			//Curve Selection
		if ((x < -690 && x > -730) && (y < -230 && y>-270))
		{
			open_shape_flag = true;
			stop = false;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			GP142_printfXY(RED, -780, -350, 15, "Curve Selected");
			curves(s);

		}
		
	}
	//Polygon
	if (((x < -690 && x > -730) && (y < 300 && y>260)) || 
		((x < -690 && x > -780) && (y < -410 && y>-450)) || 
		((x < -690 && x > -780) && (y < -290 && y>-330)) ||
		((x < -690 && x > -780) && (y < -350 && y>-390)))
	{
		if ((x < -690 && x > -730) && (y < 300 && y>260))
		{
			selection_flag = false;
			type_flag = false;
			open_shape_flag = false;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			
			GP142_rectangleXY(BLACK, -780, -290, -690, -330, 1);
			GP142_printfXY(RED, -760, -315, 12, "Rectangle");
			GP142_rectangleXY(BLACK, -780, -350, -690, -390, 1);
			GP142_printfXY(RED, -750, -375, 12, "Polygon");
			GP142_rectangleXY(BLACK, -780, -410, -690, -450, 1);
			GP142_printfXY(RED, -760, -435, 12, "Triangle");
			
		}
		//Rectangle Selection
		if ((x < -690 && x > -780) && (y < -290 && y>-330))
		{
			polygon_flag = true;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			GP142_printfXY(RED, -790, -350, 15, "Rectangle Selected");
			rectangles(s);
		}
		//Polygon Selection
		if ((x < -690 && x > -780) && (y < -350 && y>-390))
		{
			stop = false;
			polygon_flag = true;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			GP142_printfXY(RED, -790, -350, 15, "Polygon Selected");
			polygons(s);
			
		}
		//Triangle Selection
		if ((x < -690 && x > -780) && (y < -410 && y>-450))
		{
			polygon_flag = true;
			GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
			GP142_printfXY(RED, -790, -350, 15, "Triangle Selected");
			triangles(s);
		}
	}
	//Circle
	if ((x < -740 && x > -780) && (y < 250 && y>210))
	{
		selection_flag = false;
		polygon_flag = false;
		type_flag = false;
		open_shape_flag = false;
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		GP142_printfXY(RED, -780, -350, 15, "Circle Selected");
		circle_flag = true;
		circles(s);
	}
	//Text
	if (((x < -690 && x > -730) && (y < 250 && y>210)))
	{
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		GP142_printfXY(RED, -780, -350, 15, "Text Selected");
		key_count = 0;
		type_flag = true;
		open_shape_flag = false;
		polygon_flag = false;
		selection_flag = false;
		t_c = 0;
	}
	//Color Selector
	//Black
	if ((x < -690 && x > -780) && (y < 140 && y>100))
	{
		clr = 0;
		clr_hex = Black;
	}
	//White
	if ((x < -690 && x > -780) && (y < 100 && y>60))
	{
		clr = 1;
		clr_hex = White;
	}
	//Green
	if ((x < -690 && x > -780) && (y < 60 && y>20))
	{
		clr_hex = Green;
		clr = 3;
	}
	//Yellow
	if ((x < -690 && x > -780) && (y < 20 && y>-20))
	{
		clr_hex = Yellow;
		clr = 5;
	}
	//Red
	if ((x < -690 && x > -780) && (y < -20 && y> -60))
	{
		clr_hex = Red;
		clr = 2;
	}
	//Orange
	if ((x < -690 && x > -780) && (y < -60 && y> -100))
	{
		clr_hex = Orange;
		clr = 13;
	}
	//Purple
	if ((x < -690 && x > -780) && (y < -100 && y>-140))
	{
		clr_hex = RGB(0x99, 0x00, 0xCC);
		clr = 8;
	}
	//Blue
	if ((x < -690 && x > -780) && (y < -140 && y>-180))
	{
		clr_hex = Blue;
		clr = 4;
	}
}

/******************************************************************************
 *
 * demo_handle_kbd
 * ---------------
 *
 * This function handles keyboard keystrokes.
 * Characters are simply echoed along the top of the 
 * graphics window.  They wrap around when it's about to 
 * go off screen, but overwritten characters are NOT erased.
 *
 */
void demo_handle_kbd(char c)
{

	
	if ((tx > -800 && tx < -658) && (ty < 450 && ty > -450))
	{
		GP142_rectangleXY(WHITE, -800, -215, -665, -450, 0);
		type_flag = false;
	}
	if (type_flag == true)
	{
		keys[t_c] = c;
		t_c++;
		point p;
		p.x = tx;
		p.y = ty;
		text text_obj;
		text_obj.draw(p , clr, c,key_count,type_flag,s , keys , t_c);
	}
}

/******************************************************************************
 *
 * demo_handle_periodic
 * --------------------
 *
 * GP142_await_event() periodically (say, 10-20 times per second) returns a
 * "clock tick" event.  It can be used to do simple animations.  In this
 * demo, the animation is to move a "clock hand" (a blue arrow) around an
 * oval "clock face".  Every tick event calls demo_handle_periodic, which
 * redraws the arrow degrees_per_frame further around the clock face.
 *
 * Since this clock overlaps the circle drawn by demo_draw_circle_overhanging(),
 * on every clock tick we must: 1) Erase the last hand 2) redraw this circle
 * 3) drawing or redrawing the outline of the clock face, and finally, 4) drawing
 * or redrawing the hand in its new position.
 */
void demo_handle_periodic(void)
{
	const double degrees_per_frame = -10.0;
	const double ell_a = 50.0;     /* ellipse x radius */
	const double ell_b = 20.0;     /* ellipse y radius */
	const int    center_x = 65;       /* ellipse x center */
	const int    center_y = 60;       /* ellipse y center */

	static int t = 0;                 /* count number of calls ("time") */
	double theta, radius;

	if (t == 0) {
		t++;
	}

}
