//
// Created by 123 on 2019/2/21.
//


#include "XData.h"
extern "C"{
#include <libavcodec/avcodec.h>
}

void XData::Drop() {
    if(!data) return;
    av_packet_free((AVPacket **)&data);
    data = 0;
    size = 0;
}
