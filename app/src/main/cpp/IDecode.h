//
// Created by 123 on 2019/2/21.
//

#ifndef XPLAY_IDECODE_H
#define XPLAY_IDECODE_H

#include "XParameter.h"

//解码接口，支持硬解码
class IDecode {
public:
    //打开解码器
    virtual bool Open(XParameter par) = 0;
};


#endif //XPLAY_IDECODE_H
