//
// Created by 123 on 2019/2/21.
//

#include "IObserver.h"

void IObserver::AddObs(IObserver *obs)
{
    if(!obs) return;
    mux.lock();
    obss.push_back(obs);
    mux.unlock();
}

void IObserver::Notify(XData data)
{
    mux.lock();
    for (int i = 0; i < obss.size(); ++i)
    {
        obss[i]->Update(data);
    }
    mux.unlock();
}
