//
// Created by 123 on 2019/2/28.
//

#ifndef XPLAY_IPLAYERPROXY_H
#define XPLAY_IPLAYERPROXY_H


#include <mutex>
#include "IPlayer.h"

class IPlayerProxy: public IPlayer {
public:
    static IPlayerProxy*Get()
    {
        static IPlayerProxy px;
        return &px;
    }
    void Init(void *vm=0);
    virtual bool Open(const char *path);
    virtual bool Start();
    virtual void Close();
    virtual void InitView(void *win);
    virtual double playPos();

protected:
    IPlayerProxy(){};
    IPlayer *player = 0;
    std::mutex mux;

};


#endif //XPLAY_IPLAYERPROXY_H
