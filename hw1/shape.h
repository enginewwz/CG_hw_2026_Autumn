#ifndef SHAPE
#define SHAPE

#include <GL/gl.h>
#include <GL/glut.h>
#include <stdlib.h>
#include <math.h>

#define FILLED 1
#define NOT_FILLED 0

void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int filled);
void drawRect(double x1, double y1, double x2, double y2, int filled);
void drawCircle(double x, double y, double r, int num, int filled);
void drawRoundRect(double x1, double y1, double x2, double y2, double r, int filled, int arc_num);

#endif