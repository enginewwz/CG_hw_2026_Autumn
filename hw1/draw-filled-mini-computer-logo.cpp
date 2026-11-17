#include "shape.h"
#include "line-and-arc.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void init()
{
    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIN_WIDTH, 0.0, WIN_HEIGHT);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int w, int h) 
{
    if (h == 0) h = 1;
    glViewport(0, 0, w, h);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, w, 0.0, h);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glLineWidth(2.0f);

    glColor3f(0.5, 0.5, 0.5);
    drawRoundRect(200, 100, 300, 130, 10, FILLED, 20);
    drawRect(225, 120, 275, 140, FILLED);
    glColor3f(0.75, 0.75, 0.75);
    drawRect(150, 140, 350, 300, FILLED);
    glColor3f(0.64, 0.84, 0.93);
    drawRoundRect(160, 150, 340, 290, 20, FILLED, 100);
    glColor3f(1, 0, 0);
    drawTriangle(210, 190, 290, 190, 250, 250, FILLED);
    glColor3f(1, 1, 0);
    drawCircle(250, 210, 15, 100, FILLED);
    

    glColor3f(0, 0, 0);
    {
        double left_x = 200.0;
        double bottom_y = 100.0;
        double right_x = 300.0;
        double upper_y = 130.0;
        double r = 10.0;
        double arc_num = 20;

        drawLine(left_x + r, bottom_y, right_x - r, bottom_y);
        drawLine(left_x + r, upper_y, 225.0, upper_y);
        drawLine(275.0, upper_y, right_x - r, upper_y);
        drawLine(left_x, bottom_y + r, left_x, upper_y - r);
        drawLine(right_x, bottom_y + r, right_x, upper_y - r);
        drawArc(left_x + r, bottom_y + r, - M_PI, - M_PI_2, r, NOT_FILLED, arc_num);
        drawArc(right_x - r, bottom_y + r, -M_PI_2, 0, r, NOT_FILLED, arc_num);
        drawArc(right_x - r, upper_y - r, 0, M_PI_2, r, NOT_FILLED, arc_num);
        drawArc(left_x + r, upper_y - r, M_PI_2, M_PI, r, NOT_FILLED, arc_num);
    }
    drawRect(225, 120, 275, 140, NOT_FILLED);
    drawRect(150, 140, 350, 300, NOT_FILLED);
    drawRoundRect(160, 150, 340, 290, 20, NOT_FILLED, 100);
    drawCircle(250, 210, 15, 100, NOT_FILLED);
    drawTriangle(210, 190, 290, 190, 250, 250, NOT_FILLED);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("filled mini-computer logo drawing practice");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}