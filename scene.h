#ifndef SCENE_H
#define SCENE_H

#include "scrollbar.h"
#include "inode.h"

class Scene
{
private:
    ScrollBar   m_scroll;           //! scrollbar object
    Point       m_prevStartPoint;   //! previous start point (using for redraw all nodes on the same positions)
    Point       m_defaultPoint;     //! default position for first node

public:
    std::string title;              //! title of window
    int         winWidth;           //! width of window for redraw nodes and scrollbar when window's width will be changed
    int         winHeight;          //! height of window redraw nodes and scrollbar when window's height will be changed
    Tree        nodeTree;           //! Tree of nodes

    //! Constructor
    //! \param title name of window
    //! \param width width of window
    //! \param height height of window
    Scene(std::string title, int width = 800, int height = 600);

    //! Redraw all nodes and scroll bar
    void redraw(ScrollBar::eActionType scrollAction = ScrollBar::act_none);

    //! Check is click was on scrollbar arrow
    //! \param clicked coordinates of mouse click
    bool isArrowClicked(Point clicked);

    //! Check is click was on some node from nodeTree
    //! \param clicked coordinates of mouse click
    bool isNodeClicked(Point clicked);
};


#endif // SCENE_H
