#include "node.h"
#include "coordmap.h"
#include "drawer.h"

// constructor
Node::Node(bool isOpened)
    : iNode(isOpened)
    , m_isClicked(false)
{
    m_actionPercent = (m_isOpened ? 100 : 1);
}

// destructor
Node::~Node()
{

}

// setup clicked state and change status of node (need close if opened, need to open if closed)
void Node::setClicked()
{
    m_isClicked = true;
    m_status = (m_isOpened ? status_needClose : status_needOpen);
}

// clicked if m_actionPercent between 0 and 100
bool Node::clicked() const
{
    return m_isClicked;
}

Point Node::draw(Point point)
{
    m_topCoord = point;
    int visibleItemsCount = getVisibleChildrenCount();

    // nothing to do here
    if (m_isClicked && visibleItemsCount == 0)
        m_isClicked = false;


    // Draw self
    registerCoords(point, Point(m_winWidth, point.y+lim_square_size));
    Drawer::DrawNode(m_isOpened, !m_childrens.empty(), point, lim_square_size, getColor(Color::green), m_name);
    point.y += lim_node_full_height; // make offset for next node


    // Draw popup list (from 0 to 100 % or from 100 to 0 %)
    if (m_isClicked)
    {
        // Add percentage and draw self + children
        calculateActionPercent();

        int fullVisibleHeight = lim_node_full_height * visibleItemsCount;
        float currentVisibleHeight = (float)fullVisibleHeight * m_actionPercent / 100; // end of visible childrens block
        currentVisibleHeight += point.y;

        // draw childrens if they placed on visible block
        point.x += lim_left_indent;
        for (auto pNode : m_childrens)
        {
            Point tmp = pNode->draw(point);
            point.y = tmp.y;
        }
        point.x -= lim_left_indent;
        // indent to old position

        // draw black rectangle over children nodes which should be invible
        Drawer::DrawRect(Point(point.x, currentVisibleHeight), Point(m_winWidth, m_winHeight), getColor(Color::black));
        point.y = currentVisibleHeight;

        // Check is Stop animation needed
        if (m_isOpened == true && m_status == status_needClose && m_actionPercent <= 1)
        {
            m_isClicked = false;
            m_status = status_none;
            m_isOpened = !m_isOpened;
        }
        else if (m_isOpened == false && m_status == status_needOpen && m_actionPercent >= 100)
        {
            m_isClicked = false;
            m_status = status_none;
            m_isOpened = !m_isOpened;
        }

        return point;
    }

    // Draw childrens without animation
    if (m_isOpened)
    {
        point.x += lim_left_indent;
        for (auto pNode : m_childrens)
        {
            Point tmp = pNode->draw(point);
            point.y = tmp.y;
        }
        point.x -= lim_left_indent;
    }

    return point;
}

// register self in coordinates system
void Node::registerCoords(Point topLeft, Point bottomRight)
{
    CoordMap::get()->add(topLeft, bottomRight, shared_from_this());
}

// calculate animation percent
void Node::calculateActionPercent()
{
    if (m_status == status_needOpen)
        m_actionPercent += lim_step_percent;
    else if (m_status == status_needClose)
        m_actionPercent -= lim_step_percent;

    if (m_actionPercent < 1)
        m_actionPercent = 0;
    if (m_actionPercent > 100)
        m_actionPercent = 100;
}
