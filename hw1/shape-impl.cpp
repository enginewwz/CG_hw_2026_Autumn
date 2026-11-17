#include "line-and-arc.h"
#include "shape.h"

void drawTriangle(double x1, double y1, double x2, double y2, double x3, double y3, int filled)
{
    int mode = filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP;
    glBegin(mode);
        glVertex2d(x1, y1);
        glVertex2d(x2, y2);
        glVertex2d(x3, y3);
    glEnd();
}

void drawRect(double x1, double y1, double x2, double y2, int filled)
{
    int mode = filled ? GL_TRIANGLE_FAN : GL_LINE_LOOP;
    glBegin(mode);
        glVertex2d(x1, y1);
        glVertex2d(x1, y2);
        glVertex2d(x2, y2);
        glVertex2d(x2, y1);
    glEnd();
}

void drawCircle(double x, double y, double r, int num, int filled)
{
    int mode = filled ? GL_TRIANGLE_FAN : GL_LINE_STRIP;
    drawArc(x, y, 0, 2 * M_PI, r, mode, num);
}

void drawRoundRect(double x1, double y1, double x2, double y2, double r, int filled, int arc_num)
{
    double left_x = std::min(x1, x2);
    double right_x = std::max(x1, x2);
    double bottom_y = std::min(y1, y2);
    double upper_y = std::max(y1, y2);

    if (filled)
    {
        drawCircle(left_x + r, bottom_y + r, r, arc_num, GL_TRIANGLE_FAN);
        drawCircle(right_x - r, bottom_y + r, r, arc_num, GL_TRIANGLE_FAN);
        drawCircle(right_x - r, upper_y - r, r, arc_num, GL_TRIANGLE_FAN);
        drawCircle(left_x + r, upper_y - r, r, arc_num, GL_TRIANGLE_FAN);

        drawTriangle(left_x + r, bottom_y + r, left_x + r, bottom_y, left_x, bottom_y + r, GL_TRIANGLE_FAN);
        drawTriangle(left_x + r, upper_y - r, left_x + r, upper_y, left_x, upper_y - r, GL_TRIANGLE_FAN);
        drawTriangle(right_x - r, bottom_y + r, right_x - r, bottom_y, right_x, bottom_y + r, GL_TRIANGLE_FAN);
        drawTriangle(right_x - r, upper_y - r, right_x - r, upper_y, right_x, upper_y - r, GL_TRIANGLE_FAN);

        drawRect(left_x + r, bottom_y, right_x - r, upper_y, GL_TRIANGLE_FAN);
        drawRect(left_x, bottom_y + r, right_x, upper_y - r, GL_TRIANGLE_FAN);
    }
    else
    {
        drawLine(left_x + r, bottom_y, right_x - r, bottom_y);
        drawLine(left_x + r, upper_y, right_x - r, upper_y);
        drawLine(left_x, bottom_y + r, left_x, upper_y - r);
        drawLine(right_x, bottom_y + r, right_x, upper_y - r);
        drawArc(left_x + r, bottom_y + r, - M_PI, - M_PI_2, r, GL_LINE_STRIP, arc_num);
        drawArc(right_x - r, bottom_y + r, -M_PI_2, 0, r, GL_LINE_STRIP, arc_num);
        drawArc(right_x - r, upper_y - r, 0, M_PI_2, r, GL_LINE_STRIP, arc_num);
        drawArc(left_x + r, upper_y - r, M_PI_2, M_PI, r, GL_LINE_STRIP, arc_num);
    }
}