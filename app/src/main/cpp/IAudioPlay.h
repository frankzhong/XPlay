//
// Created by 123 on 2019/2/26.
//

#ifndef XPLAY_IAUDIOPLAY_H
#define XPLAY_IAUDIOPLAY_H


#include <list>
#include "IObserver.h"
#include "XParameter.h"

class IAudioPlay: public IObserver {
public:
    //缓冲满后阻塞
    virtual void Update(XData data);
    //获取缓冲数据，如没有则阻塞
    virtual XData GetData();
    virtual bool StartPlay(XParameter out) = 0;
    virtual void Close() = 0;
    //最大缓冲
    int maxFrame = 100;
    int pts = 0;

protected:
    std::list <XData> frames;
    std::mutex framesNutex;

};


#endif //XPLAY_IAUDIOPLAY_H
