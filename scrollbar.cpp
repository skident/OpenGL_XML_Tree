#include "scrollbar.h"
#include "drawer.h"

ScrollBar::ScrollBar()
    : m_progress(0)
{

}

char ScrollBar::getProgress() const
{
    return m_progress;
}

char ScrollBar::draw(int winWidth, int winHeight, Tree tree, eActionType action)
{
    m_isVisible = true;
    m_winWidth = winWidth;
    m_winHeight = winHeight;
    int visibleSize = tree.getVisibleNodesHeight();

    if (visibleSize < winHeight)
    {
        m_isVisible = false;
        m_progress = 0;
        return m_progress;
    }

    float parts = (float)visibleSize / winHeight;
    float availableSpace = (float)winHeight - lim_ButtonHeight * 2 - lim_padding * 2;
    m_height = availableSpace / parts;

    updateProgress(action);

    m_position = lim_ButtonHeight+lim_padding + (availableSpace - m_height) * m_progress / 100;

    Drawer::DrawTriangle(Point(winWidth-lim_barWidth/2, 0), Point(winWidth-lim_barWidth, lim_ButtonHeight), Point(winWidth, lim_ButtonHeight), Color(1,1,1));
    Drawer::DrawRect(Point(winWidth- 20, m_position), Point(winWidth, m_position + m_height), Color(1,1,1));
    Drawer::DrawTriangle(Point(winWidth-lim_barWidth/2, winHeight), Point(winWidth-lim_barWidth, winHeight-lim_ButtonHeight), Point(winWidth, winHeight-lim_ButtonHeight), Color(1,1,1));

    return m_progress;
}

void ScrollBar::updateProgress(eActionType action)
{
    switch(action)
    {
    case act_clicked_down:
        m_progress += lim_stepPercent;
        if (m_progress > 100)
            m_progress = 100;
        break;

    case act_clicked_up:
        m_progress -= lim_stepPercent;
        if (m_progress < 0)
            m_progress = 0;
        break;

    default:
        break;
    }
}

ScrollBar::eActionType ScrollBar::isArrowClicked(int winWidth, int winHeight, Point clickPoint)
{
    if (!m_isVisible)
        return act_none;

    if (clickPoint.x >= winWidth-lim_barWidth && clickPoint.x <= winWidth)
    {
        int y = clickPoint.y;
        if (y >= 0 && y <= lim_ButtonHeight)
            return act_clicked_up;
        if (y >= winHeight-lim_ButtonHeight && y <= winHeight)
            return act_clicked_down;
    }

    return act_none;
}

