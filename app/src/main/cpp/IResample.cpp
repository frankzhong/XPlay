//
// Created by 123 on 2019/2/26.
//

#include "IResample.h"
#include "XLog.h"

void IResample::Update(XData data) {
    XData d = this->Resample(data);
    XLOGI("IResample::Update data %d", d.size);
    if(d.size > 0)
    {
        this->Notify(d);
    }
}
