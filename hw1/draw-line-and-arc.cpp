#include "line-and-arc.h"

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

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

    glColor3f(0.0f, 1.0f, 0.0f);
    drawLine(100.0f, 100.0f, 200.0f, 300.0f);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawLine_bresenham(300, 300, 200, 100);

    glColor3f(0.0f, 0.0f, 1.0f);
    drawLine_dda(400, 300, 300, 100);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawArc(400.0f, 400.0f, 0.0f, -5.0f, 50.0f, GL_LINE_STRIP, 200);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("line & arc drawing practice");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}