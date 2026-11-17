#include "line-and-arc.h"
#include "shape.h"

#include <string.h>

#define WIN_WIDTH 800
#define WIN_HEIGHT 600

typedef struct node
{
    int type;
    int filled; // 0 or 1
    float line_width;   // 3/5/10
    double color[3];    // red/green/blue/white
    double param[6];
    struct node* next;
}
node_t;

enum Shape
{
    LINE = 0,
    RECT,
    TRIANGLE
};

enum MenuOptions 
{
    COLOR_RED = 1,
    COLOR_GREEN,
    COLOR_BLUE,
    COLOR_WHITE,
    SHAPE_LINE,
    SHAPE_RECT,
    SHAPE_TRIANGLE,
    LINE_WIDTH_1,
    LINE_WIDTH_3,
    LINE_WIDTH_5,
    MODE_FILLED,
    MODE_NOT_FILLED,
    MENU_UNDO,
    MENU_CLEAR,
    MENU_EXIT
};

enum DrawState {
    IDLE,
    DRAGGING_LINE,
    WAITING_THIRD_POINT // triangle-use
};

struct node *head = NULL;
struct node tmp;
double color[3] = {1.0, 1.0, 1.0};
int filled = 0;
int type = LINE;
float line_width = 1;

int state = IDLE;

void draw(node_t* p)
{
    glColor3dv(p->color);
    glLineWidth(p->line_width);
    switch (p->type)
    {
        case LINE:
            drawLine(p->param[0], p->param[1], p->param[2], p->param[3]);
            break;
        case RECT:
            drawRect(p->param[0], p->param[1], p->param[2], p->param[3], p->filled);
            break;
        case TRIANGLE:
            if (p == &tmp && state == DRAGGING_LINE)
                drawLine(p->param[0], p->param[1], p->param[2], p->param[3]);
            else 
                drawTriangle(p->param[0], p->param[1], p->param[2], p->param[3], p->param[4], p->param[5], p->filled);
            break;
    }
}

void init_tmp()
{
    tmp.type = type;
    memcpy(&tmp.color, color, sizeof(color));
    tmp.filled = filled;
    tmp.line_width = line_width;
    tmp.next = NULL;
}

void add_node()
{
    node_t* next = (node_t*) malloc(sizeof(node_t));
    memcpy(next, &tmp, sizeof(node_t));
    if (!head) 
    {
        head = next;
        return;
    }
    node_t *p = head;
    for (; p->next; p = p->next);
    p->next = next;
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);

    node_t* p = head;
    for (; p; p = p->next)
    {
        draw(p);
    }
    if (state != IDLE)
    {
        draw(& tmp);
    }

    glutSwapBuffers();
}

void clear()
{
    node_t *p = head, *q;
    head = NULL;
    while (p)
    {
        q = p->next;
        free(p);
        p = q;
    }
}

void undo()
{
    if (!head) return;
    node_t *p = head, *q;
    for (; p->next; q = p, p = p->next);
    if (p == head) head = NULL;
    else q->next = NULL;
    free(p);
}

void processMenuEvents(int option) 
{
    switch (option) 
    {
        case COLOR_RED:
            color[0] = 1; color[1] = 0; color[2] = 0;
            break;
        case COLOR_GREEN:
            color[0] = 0; color[1] = 1; color[2] = 0;
            break;
        case COLOR_BLUE:
            color[0] = 0; color[1] = 0; color[2] = 1;
            break;
        case COLOR_WHITE:
            color[0] = 1; color[1] = 1; color[2] = 1;
            break;
        case SHAPE_LINE:
            type = LINE;
            break;
        case SHAPE_TRIANGLE:
            type = TRIANGLE;
            break;
        case SHAPE_RECT:
            type = RECT;
            break;
        case LINE_WIDTH_1:
            line_width = 1;
            break;
        case LINE_WIDTH_3:
            line_width = 3;
            break;
        case LINE_WIDTH_5:
            line_width = 5;
            break;
        case MODE_FILLED:
            filled = FILLED;
            break;
        case MODE_NOT_FILLED:
            filled = NOT_FILLED;
            break;
        case MENU_UNDO:
            undo();
            break;
        case MENU_CLEAR:
            clear();
            break;
        case MENU_EXIT:
            exit(0);
            break;
    }
    glutPostRedisplay();
}

void createGLUTMenus() 
{
    int colorSubMenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("red", COLOR_RED);
    glutAddMenuEntry("green", COLOR_GREEN);
    glutAddMenuEntry("blue", COLOR_BLUE);
    glutAddMenuEntry("white", COLOR_WHITE);

    int shapeSubMenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("line", SHAPE_LINE);
    glutAddMenuEntry("rectangle", SHAPE_RECT);
    glutAddMenuEntry("triangle", SHAPE_TRIANGLE);

    int linewidthSubMenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("1", LINE_WIDTH_1);
    glutAddMenuEntry("3", LINE_WIDTH_3);
    glutAddMenuEntry("5", LINE_WIDTH_5);

    int fillmodeSubMenu = glutCreateMenu(processMenuEvents);
    glutAddMenuEntry("filled", MODE_FILLED);
    glutAddMenuEntry("not filled", MODE_NOT_FILLED);

    glutCreateMenu(processMenuEvents);
    glutAddSubMenu("color", colorSubMenu);
    glutAddSubMenu("shape", shapeSubMenu);
    glutAddSubMenu("line width", linewidthSubMenu);
    glutAddSubMenu("fill mode", fillmodeSubMenu);
    glutAddMenuEntry("undo", MENU_UNDO);
    glutAddMenuEntry("clear", MENU_CLEAR);
    glutAddMenuEntry("exit", MENU_EXIT);

    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void mouseButton(int button, int botton_state, int x, int y) {
    if (button != GLUT_LEFT_BUTTON) return;

    if (state == IDLE) 
    {
        if (botton_state == GLUT_DOWN) 
        {
            init_tmp();
            tmp.param[0] = x;
            tmp.param[1] = y;
            tmp.param[2] = x;
            tmp.param[3] = y;
            state = DRAGGING_LINE;
        }
    } 
    else if (state == DRAGGING_LINE) 
    {
        if (botton_state == GLUT_UP) 
        {
            tmp.param[2] = x;
            tmp.param[3] = y;
            
            double dist = std::hypot(tmp.param[0] - x, tmp.param[1] - y);
            if (dist < 5.0f) 
            {
                state = IDLE;
            } else {
                if (tmp.type == TRIANGLE) 
                {
                    tmp.param[4] = x;
                    tmp.param[5] = y;
                    state = WAITING_THIRD_POINT;
                }
                else
                {
                    add_node();
                    state = IDLE;
                }
            }
            glutPostRedisplay();
        }
    } 
    else if (state == WAITING_THIRD_POINT) 
    {
        if (botton_state == GLUT_DOWN) {
            tmp.param[4] = x;
            tmp.param[5] = y;
            add_node();
            state = IDLE;
            glutPostRedisplay();
        }
    }
}

void mouseMotion(int x, int y) 
{
    if (state == DRAGGING_LINE) 
    {
        tmp.param[2] = x;
        tmp.param[3] = y;
        glutPostRedisplay();
    }
}

void mousePassiveMotion(int x, int y) 
{
    if (state == WAITING_THIRD_POINT) 
    {
        tmp.param[4] = x;
        tmp.param[5] = y;
        glutPostRedisplay();
    }
}

void init()
{
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, WIN_WIDTH, WIN_HEIGHT, 0.0);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void reshape(int width, int height) 
{
    if (width == 0 || height == 0) return;
    glViewport(0, 0, width, height);
    
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0, width, height, 0.0);
    
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB);
    glutInitWindowPosition(10, 10);
    glutInitWindowSize(WIN_WIDTH, WIN_HEIGHT);
    glutCreateWindow("interact practice");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape);
    glutMouseFunc(mouseButton);
    glutMotionFunc(mouseMotion);
    glutPassiveMotionFunc(mousePassiveMotion);

    createGLUTMenus();

    glutMainLoop();
    return 0;
}