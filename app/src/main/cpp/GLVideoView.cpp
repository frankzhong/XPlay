//
// Created by 123 on 2019/2/22.
//

#include "GLVideoView.h"
#include "XTexture.h"

void GLVideoView::SetRender(void *win) {
    view = win;
}

void GLVideoView::Render(XData data) {
    if(!view) return;
    if(!txt)
    {
        txt = XTexture::Create();
        txt->Init(view);
    }
    txt->Draw(data.datas, data.width, data.height);
}