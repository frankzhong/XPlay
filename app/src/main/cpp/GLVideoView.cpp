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
        txt->Init(view, (XTextureType)data.format);
    }
    txt->Draw(data.datas, data.width, data.height);
}

void GLVideoView::Close() {
    mux.lock();
    if(txt)
    {
        txt->Drop();
        txt = 0;
    }
    mux.unlock();
}
