//
// Created by 123 on 2019/2/21.
//

#ifndef XPLAY_XDATA_H
#define XPLAY_XDATA_H


struct XData {
    unsigned char *data = 0;
    int size = 0;
    bool isAudio = false;
    void Drop();
};


#endif //XPLAY_XDATA_H
