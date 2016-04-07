#include "scene.h"
#include "coordmap.h"
#include "node.h"
#include "drawer.h"
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

Scene::Scene(std::string _title, int _width, int _height)
{
    m_defaultPoint.assign(25, 25);
    m_prevStartPoint    = m_defaultPoint;
    title               = _title;
    winWidth            = _width;
    winHeight           = _height;
}

void Scene::redraw(ScrollBar::eActionType scrollAction)
{
    CoordMap::get()->clear();

    glClear(GL_COLOR_BUFFER_BIT);

    Point startPoint;
    char progress = m_scroll.draw(winWidth, winHeight, nodeTree, scrollAction);

     if (scrollAction == ScrollBar::act_none)
        startPoint = m_prevStartPoint;
    else
    {
        float offsetY = (nodeTree.getVisibleNodesHeight() - winHeight+m_defaultPoint.y) * progress / 100;
        startPoint.assign(m_defaultPoint.x, m_defaultPoint.y - offsetY);
    }
    nodeTree.draw(winWidth - ScrollBar::lim_barWidth, winHeight, startPoint);

    m_prevStartPoint = startPoint;

    glutSwapBuffers();
}

bool Scene::isArrowClicked(Point clicked)
{
    ScrollBar::eActionType arrow = m_scroll.isArrowClicked(winWidth, winHeight, clicked);
    if (arrow != ScrollBar::act_none)
    {
        redraw(arrow);
        return true;
    }
    return false;
}

bool Scene::isNodeClicked(Point clicked)
{
    shared_ptr<iNode> node = CoordMap::get()->find(clicked);
//        shared_ptr<iNode> node = nodeTree.findOwner(Point(x,y));

    shared_ptr<Node> cnode = dynamic_pointer_cast<Node>(node);
     if (!cnode.get())
         return false;

     cnode->setClicked();

     while(cnode->clicked())
     {
         redraw();
     }

     redraw(); // the last redraw!!!
     return true;
}
