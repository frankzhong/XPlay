//
// Created by 123 on 2019/2/27.
//

#include "FFPlayBuilder.h"
#include "FFDemux.h"
#include "FFDecode.h"
#include "FFResample.h"
#include "GLVideoView.h"
#include "SLAudioPlay.h"

IDemux *FFPlayBuilder::CreateDemux() {
    IDemux *ff = new FFDemux();
    return ff;
}

IDecode *FFPlayBuilder::CreateDecode() {
    FFDecode *ff = new FFDecode();
    return ff;
}

IResample *FFPlayBuilder::CreateResample() {
    FFResample *ff = new FFResample();
    return ff;
}

IVideoView *FFPlayBuilder::CreateVideoView() {
    GLVideoView *ff = new GLVideoView();
    return ff;
}

IAudioPlay *FFPlayBuilder::CreateAudioPlay() {
    SLAudioPlay *ff = new SLAudioPlay();
    return ff;
}

IPlayer *FFPlayBuilder::CreatePlayer(unsigned char index) {
    return IPlayer::Get(index);
}

void FFPlayBuilder::InitHard(void *vm) {
    FFDecode::InitHard(vm);
}
