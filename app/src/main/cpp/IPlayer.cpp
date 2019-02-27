//
// Created by 123 on 2019/2/27.
//

#include "IPlayer.h"
#include "IDemux.h"
#include "IDecode.h"
#include "IAudioPlay.h"
#include "IVideoView.h"
#include "IResample.h"
#include "XLog.h"


IPlayer *IPlayer::Get(unsigned char index) {
    static IPlayer p[256];
    return &p[index];
}

bool IPlayer::Open(const char *path) {
    //解封装
    if(!demux || !demux->Open(path))
    {
        XLOGE("demux->Open %s failed!", path);
        return false;
    }
    //解码 解码可能不需要返回值， 如果是解封之后就是原始数据
    if(!vdecode || !vdecode->Open(demux->GetVPara(), isHardDecode))
    {
        XLOGE("vdecode->Open %s failed!", path);
//        return false;
    }
    if(!adecode || !adecode->Open(demux->GetAPara()))
    {
        XLOGE("adecode->Open %s failed!", path);
//        return false;
    }
    //重采样 有可能不需要，解码后或者解封后可能是直接能播放的数据
    XParameter outPara = demux->GetAPara();
    if(!resample || !resample->Open(demux->GetAPara(), outPara))
    {
        XLOGE("resample->Open %s failed!", path);
//        return false;
    }

    return false;
}

bool IPlayer::Start() {
    return true;
}