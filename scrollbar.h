#ifndef SCROLLBAR_H
#define SCROLLBAR_H

#include "tree.h"

class ScrollBar
{
private:
    char m_progress;
    float m_height;
    float m_position;
    int m_winWidth;
    int m_winHeight;
    bool m_isVisible;

public:
    enum eLimits
    {
        lim_stepPercent     = 5,
        lim_ButtonHeight    = 20,
        lim_barWidth        = 20,
        lim_padding         = 2,
    };

    enum eActionType
    {
        act_none,
        act_clicked_up,
        act_clicked_down,
    };


    ScrollBar();

    char getProgress() const;

    char draw(int winWidth, int winHeight, Tree tree, eActionType action);

    void updateProgress(eActionType action);

    eActionType isArrowClicked(int winWidth, int winHeight, Point clickPoint);
};

#endif // SCROLLBAR_H

