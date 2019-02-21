#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"
#include "IObserver.h"

class TestObs: public IObserver
{
public:
    void Update(XData d)
    {
       XLOGI("TestObs Update data size is %d", d.size);
    }
};

extern "C" JNIEXPORT jstring JNICALL
Java_frank_com_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    XLOGI("------------------------------------------");
    //测试
    TestObs *tobs = new TestObs();
    IDemux *de = new FFDemux();
    de->AddObs(tobs);
    de->Open("/sdcard/fftest.mp4");
    de->Start();
    XSleep(3000);
    de->Stop();
//    for(;;)
//    {
//        XData d = de->Read();
//        XLOGI("Read data size is %d", d.size);
//    }

    return env->NewStringUTF(hello.c_str());
}
