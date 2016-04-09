#include "scene.h"
#include "coordmap.h"
#include "node.h"
#include "drawer.h"
#include <GL/gl.h>
#include <GL/glut.h>

using namespace std;

Scene::Scene(std::string _title, int _width, int _height)
{
    m_prevStartPoint    = Point(lim_padding, lim_padding);
    title               = _title;
    winWidth            = _width;
    winHeight           = _height;
}

// Redraw tree and scrollbar (if it exists) considering the new offset
void Scene::redraw(int offset, bool checkOutOfScope)
{
    glClear(GL_COLOR_BUFFER_BIT);

    CoordMap::get()->clear();

    // find out new position of top element
    int newPosY = m_prevStartPoint.y + offset;

    // if it motion of mouse
    if (checkOutOfScope)
    {
        // if it greater than default padding -> nothing to do here
        if (newPosY > lim_padding)
            return;

        Point lastCoords = nodeTree.getLastVisibleCoords(); // get coords of the last visible Node/Leaf
        // new position of the last visible node is too high -> nothing to do here
        if (lastCoords.y + offset < winHeight-lim_padding)
            return;
    }

    m_prevStartPoint.y += offset; // change position of top element

    // redraw tree
    nodeTree.draw(winWidth - ScrollBar::lim_barWidth, winHeight, m_prevStartPoint);

    // calculate visible and invisible parts of data in percents
    int treeHeight = nodeTree.getVisibleNodesHeight(); //height of the whole data in pixels
    int invisibleTop = (float)(lim_padding-newPosY) / treeHeight * 100;  // convert invisible top pixels into percents
    int visible = 100;

    // data can't be drawn in the one window (need scrollbar)
    if (treeHeight > winHeight)
        visible = (float)winHeight / treeHeight * 100;  // convert visible pixels into percents

    m_scroll.draw(winWidth, winHeight, invisibleTop, visible);

    glutSwapBuffers();
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
         redraw(0, false);
     }

     redraw(0, false); // the last redraw!!!
     return true;
}
