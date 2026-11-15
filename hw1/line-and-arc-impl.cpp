#include "line-and-arc.h"

void drawLine(double x0, double y0, double x1, double y1)
{
    glBegin(GL_LINES);
        glVertex2f(x0, y0);
        glVertex2f(x1, y1);
    glEnd();
}

void drawArc(double center_x, double center_y, double start_arg, double end_arg, double r, int mode, int num)
{
    double x, y;
    if (end_arg == start_arg) return;
    double step = (end_arg - start_arg) / (num - 1);
    glBegin(mode);
        for (double i = start_arg; (end_arg - i) * (end_arg - start_arg) >= 0; i += step)
        {
            x = center_x + r * cos(i);
            y = center_y + r * sin(i);
            glVertex2d(x, y);
        }
    glEnd();
}

void drawLine_dda(int x0, int y0, int x1, int y1)
{
    int dx = x1 - x0;
    int dy = y1 - y0;
    if (dx == 0 && dy == 0) return;
    int step = std::max(std::abs(dx), std::abs(dy));

    float sx = static_cast<float>(dx) / step;
    float sy = static_cast<float>(dy) / step;

    float x = static_cast<float>(x0);
    float y = static_cast<float>(y0);

    glBegin(GL_POINTS);
        for (int i = 0; i < step; i ++)
        {
            glVertex2d(static_cast<int>(std::round(x)), static_cast<int>(std::round(y)));
            x += sx;
            y += sy;
        }
    glEnd();
}

void drawLine_bresenham(int x0,int y0, int x1, int y1)
{
    int dx = abs(x0 - x1);
    int dy = abs(y0 - y1);
    int sx = (x0 < x1) ? 1 : -1;
    int sy = (y0 < y1) ? 1 : -1;
    /*
        err(u, v) = dy * u - dx * v
        if move rightward --> err + dy
        if move upward --> err - dx

        if err(u + 1/2, v + 1) < 0 : move rightward ==> equals to 2 * err(u + 1, v + 1) - dy > 0
        if err(u + 1, v + 1/2) > 0 : move upward ==> equals to 2 * err(u + 1, v + 1) + dx < 0
    */
    int err = dy - dx;  // err(u + 1, v + 1)
    /*
        if err > 0: the point is at the right-down side of the line
        if err < 0: the point is at the left-up side of the line
    */

    glBegin(GL_POINTS);
    while (1)
    {
        glVertex2i(x0, y0);
        if (x0 == x1 && y0 == y1) break;
        int err2 = err * 2;
        if (err2 - dy < 0)
        {
            err += dy;
            x0 += sx;   // u + 1
        }
        if (err2 + dx > 0)
        {
            err -= dx;
            y0 += sy;   // v + 1
        }
    }
    glEnd();
}
