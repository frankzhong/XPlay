//
// Created by 123 on 2019/2/21.
//

#include "XThread.h"
#include <thread>
#include "XLog.h"
using namespace std;

void XSleep(int mis)
{
    chrono::milliseconds du(mis);
    this_thread::sleep_for(du);
}

void XThread::Start() {
    isExit = false;
    thread th(&XThread::ThreadMain, this);
    th.detach();
}

void XThread::ThreadMain() {
    isRunning = true;
    XLOGI("线程函数进入");
    Main();
    XLOGI("线程函数退出");
    isRunning = false;
}

void XThread::Stop() {
    isExit = true;
    for (int i = 0; i < 200; ++i) {
        if(!isRunning)
        {
            XLOGI("Stop 停止线程成功！");
            return;
        }
        XSleep(1);
    }
    XLOGI("Stop 停止线程超时！");
}

