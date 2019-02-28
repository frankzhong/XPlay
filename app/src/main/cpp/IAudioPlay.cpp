//
// Created by 123 on 2019/2/26.
//

#include "IAudioPlay.h"
#include "XLog.h"

void IAudioPlay::Update(XData data) {
    XLOGI("IAudioPlay::Update %d", data.size);
    //压入缓冲队列
    if (data.size <= 0 || !data.data) return;

    while (!isExit) {
        framesNutex.lock();
        if (frames.size() > maxFrame) {
            framesNutex.unlock();
            XSleep(1);
            continue;
        }
        frames.push_back(data);
        framesNutex.unlock();
        break;
    }
}

XData IAudioPlay::GetData() {
    XData d;

    while (!isExit)
    {
        framesNutex.lock();
        if(!frames.empty())
        {
            //有数据返回
            d = frames.front();
            frames.pop_front();
            framesNutex.unlock();
            pts = d.pts;
            return d;
        }
        framesNutex.unlock();
        XSleep(1);
    }

    //未获取数据
    return d;
}
