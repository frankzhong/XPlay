//
// Created by 123 on 2019/2/21.
//

#ifndef XPLAY_XPARAMETER_H
#define XPLAY_XPARAMETER_H

struct AVCodecParameters;
class XParameter {
public:
    AVCodecParameters *para = 0;
    int channels = 2;
    int sample_rate = 44100;

};


#endif //XPLAY_XPARAMETER_H
