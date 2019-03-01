//
// Created by 123 on 2019/2/28.
//

#include "IPlayerProxy.h"
#include "FFPlayBuilder.h"

void IPlayerProxy::Init(void *vm) {
    mux.lock();
    if(vm)
        FFPlayBuilder::InitHard(vm);
    if(!player)
        player = FFPlayBuilder::Get()->BuilderPlayer();
    mux.unlock();
}

bool IPlayerProxy::Open(const char *path) {
    bool re = false;
    mux.lock();
    if(player)
    {
        player->isHardDecode = isHardDecode;
        re = player->Open(path);
    }

    mux.unlock();
    return re;
}

bool IPlayerProxy::Start() {
    bool re = false;
    mux.lock();
    if(player)
        re = player->Start();
    mux.unlock();
    return re;
}

void IPlayerProxy::InitView(void *win) {
    mux.lock();
    if(player)
        player->InitView(win);
    mux.unlock();
}

void IPlayerProxy::Close() {
    mux.lock();
    if(player)
        player->Close();
    mux.unlock();
}

double IPlayerProxy::playPos() {
    double pos = 0.0;
    mux.lock();
    if(player)
    {
        pos = player->PlayPos();
    }
    mux.unlock();
    return pos;
}

