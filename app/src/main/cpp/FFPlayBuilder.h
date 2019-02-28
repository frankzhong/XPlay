//
// Created by 123 on 2019/2/27.
//

#ifndef XPLAY_FFPLAYBUILDER_H
#define XPLAY_FFPLAYBUILDER_H

#include "IPlayBuilder.h"

class FFPlayBuilder: public IPlayBuilder {
public:
    static void InitHard(void *vm);
    static FFPlayBuilder *Get()
    {
        static FFPlayBuilder ff;
        return &ff;
    }
protected:
    FFPlayBuilder(){};
    virtual IDemux *CreateDemux();
    virtual IDecode *CreateDecode();
    virtual IResample *CreateResample();
    virtual IVideoView *CreateVideoView();
    virtual IAudioPlay *CreateAudioPlay();
    virtual IPlayer *CreatePlayer(unsigned char index=0);

};


#endif //XPLAY_FFPLAYBUILDER_H
