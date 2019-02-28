//
// Created by 123 on 2019/2/26.
//

#ifndef XPLAY_SLAUDIOPLAY_H
#define XPLAY_SLAUDIOPLAY_H


#include "IAudioPlay.h"

class SLAudioPlay: public IAudioPlay {
public:
    virtual bool StartPlay(XParameter out);
    void PlayCall(void *bufq);
    virtual void Close();
    SLAudioPlay();
    virtual ~SLAudioPlay();

protected:
    unsigned char *buf = 0;
    std::mutex mux;
};


#endif //XPLAY_SLAUDIOPLAY_H
