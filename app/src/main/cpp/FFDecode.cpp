//
// Created by 123 on 2019/2/21.
//

#include "FFDecode.h"

bool FFDecode::Open(XParameter para) {
    if(!para.para) return false;
    AVCodecParameters *p = para.para;
    return true;
}
