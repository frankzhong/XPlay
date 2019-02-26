//
// Created by 123 on 2019/2/26.
//

#include "IResample.h"

void IResample::Update(XData data) {
    XData d = this->Resample(data);
    if(d.size > 0)
    {
        this->Notify(d);
    }
    IObserver::Update(data);
}
