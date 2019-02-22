//
// Created by 123 on 2019/2/22.
//

#ifndef XPLAY_XEGL_H
#define XPLAY_XEGL_H


class XEGL {
public:
    virtual bool Init(void *win) = 0;
    static XEGL *Get();

protected:
    XEGL(){};

};


#endif //XPLAY_XEGL_H
