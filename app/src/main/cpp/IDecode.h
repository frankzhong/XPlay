//
// Created by 123 on 2019/2/21.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"
#include "IObserver.h"
#include <list>

//解码接口，支持硬解码
class IDecode: public IObserver{
public:
    //打开解码器
    virtual bool Open(XParameter par, bool isHard = false) = 0;

    //future 模型 发送数据到线程解码
    virtual bool SendPacket(XData pket) = 0;

    //从线程中获取解码数据
    virtual XData RecvFrame() = 0;

    //由主体notify的数据 阻塞
    virtual void Update(XData pkt);

    bool isAudio = false;

    //最大的队列缓冲
    int maxList = 100;

    //同步时间，再次打开文件要清理
    int synPts = 100;
    int pts = 0;
protected:
    virtual void Main();
    //读取缓冲
    std::list<XData> packs;
    std::mutex packsMutex;


};


#endif //XPLAY_IDECODE_H
