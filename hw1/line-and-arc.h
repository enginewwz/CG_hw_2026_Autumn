#ifndef LINE_AND_ARC
#define LINE_AND_ARC

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

void drawLine(double x0, double y0, double x1, double y1);
void drawLine_dda(int x0, int y0, int x1, int y1);
void drawArc(double center_x, double center_y, double start_arg, double end_arg, double r, int mode, int num);
void drawLine_bresenham(int x0,int y0, int x1, int y1);

#endif