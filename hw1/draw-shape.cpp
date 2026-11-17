#include "shape.h"

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
    drawTriangle(100, 100, 200, 200, 300, 500, FILLED);

    glColor3f(1.0f, 0.0f, 0.0f);
    drawRect(300, 500, 400, 200, FILLED);

    glColor3f(0.0f, 0.0f, 1.0f);
    drawCircle(600, 300, 50, 200, FILLED);

    glColor3f(1.0f, 1.0f, 1.0f);
    drawRoundRect(600, 100, 700, 200, 10, 0, 20);
    drawRoundRect(600, 400, 700, 500, 30, 1, 100);

    glFlush();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("shape drawing practice");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMainLoop();

    return 0;
}