//
// Created by 123 on 2019/2/21.
//

#include "IDemux.h"
#include "XLog.h"

void IDemux::Main()
{
    while (!isExit)
    {
        XData d = Read();
        //XLOGI("IDemux Read %d", d.size);
        //if(d.size <= 0) break;
    }
}
