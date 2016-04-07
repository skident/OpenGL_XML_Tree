#include <GL/glut.h>
#include <GL/gl.h>

#include "config.h"
#include "tree.h"
#include "scene.h"


Scene window("Xml tree");

void draw()
{
    window.redraw();
}

void redraw(ScrollBar::eActionType scrollAction)
{
    window.redraw(scrollAction);
}

// mouse
// The GLUT mouse function
void mouse(int button, int state, int x, int y)
{
    if (button == GLUT_LEFT_BUTTON && state == GLUT_DOWN)
    {
        Point clicked(x, y);

        // check is click was on scrollbar
        if (window.isArrowClicked(clicked))
            return;

        // Chek is click was on node
        if (window.isNodeClicked(clicked))
            return;
    }
}



void reshape(int w, int h)
{
    window.winWidth = w;
    window.winHeight = h;

    glViewport(0, 0, w, h);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0.0f, w, h, 0.0f, 0.0f, 1.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}


void createWindow(int argc, char** argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE|GLUT_RGBA);
    glutInitWindowSize(window.winWidth, window.winHeight);
    glutInitWindowPosition(200, 0);
    glutCreateWindow(window.title.c_str());
    glutDisplayFunc(draw);
    glutMouseFunc(mouse);
//    glutTimerFunc(Settings::delay, Timer, 0);
//    glutSpecialFunc(keyboard);

    glutReshapeFunc(reshape);

    glClear(GL_COLOR_BUFFER_BIT);

    glutMainLoop();
}

int main(int argc, char** argv)
{
    Config conf(window.nodeTree);

    bool isLoaded = false;
    if (argc > 1)
        isLoaded = conf.loadDocument(argv[1]);

    if (!isLoaded)
        conf.loadDocument("content.xml");

    createWindow(argc, argv);

    return 0;
}
