//
// Created by 123 on 2019/2/27.
//

#ifndef XPLAY_IPLAYER_H
#define XPLAY_IPLAYER_H


#include <mutex>
#include "XThread.h"
#include "XParameter.h"

class IDemux;
class IDecode;
class IResample;
class IVideoView;
class IAudioPlay;

class IPlayer: public XThread {
public:
    static IPlayer *Get(unsigned char index=0);
    virtual bool Open(const char *path);
    virtual bool Start();
    virtual void Close();
    virtual void InitView(void *win);
    //是否视频硬解码
    bool isHardDecode = true;

    //音频输出参数
    XParameter outPara;
    IDemux *demux = 0;
    IDecode *vdecode = 0;
    IDecode *adecode = 0;
    IResample *resample = 0;
    IVideoView *videoView = 0;
    IAudioPlay *audioPlay = 0;

protected:
    //用作音视频同步
    void Main();
    std::mutex mux;
    IPlayer(){};
};


#endif //XPLAY_IPLAYER_H
