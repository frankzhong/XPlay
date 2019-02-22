//
// Created by 123 on 2019/2/22.
//

#ifndef XPLAY_IVIDEOVIEW_H
#define XPLAY_IVIDEOVIEW_H


#include "XData.h"

class IVideoView {
public:
    virtual void SetRender(void *win) = 0;
    virtual void Render(XData data);
    virtual void Update(XData data);

};


#endif //XPLAY_IVIDEOVIEW_H
