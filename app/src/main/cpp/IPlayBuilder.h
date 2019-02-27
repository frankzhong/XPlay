//
// Created by 123 on 2019/2/27.
//

#ifndef XPLAY_IPLAYBUILDER_H
#define XPLAY_IPLAYBUILDER_H


#include "IDemux.h"
#include "IDecode.h"
#include "IResample.h"
#include "IVideoView.h"
#include "IAudioPlay.h"
#include "IPlayer.h"

class IPlayBuilder {
public:
    virtual IPlayer *BuilderPlayer(unsigned char index=0);

protected:
    virtual IDemux *CreateDemux() = 0;
    virtual IDecode *CreateDecode() = 0;
    virtual IResample *CreateResample() = 0;
    virtual IVideoView *CreateVideoView() = 0;
    virtual IAudioPlay *CreateAudioPlay() = 0;
    virtual IPlayer *CreatePlayer(unsigned char index=0) = 0;

};


#endif //XPLAY_IPLAYBUILDER_H
