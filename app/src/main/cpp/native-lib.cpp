#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"
#include "IObserver.h"
#include "IDecode.h"
#include "FFDecode.h"
#include "XEGL.h"
#include "XShader.h"
#include "IVideoView.h"
#include "GLVideoView.h"
#include "FFResample.h"
#include <android/native_window_jni.h>

class TestObs: public IObserver
{
public:
    void Update(XData d)
    {
       //XLOGI("TestObs Update data size is %d", d.size);
    }
};

IVideoView *view = NULL;
extern "C" JNIEXPORT jstring JNICALL
Java_frank_com_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    XLOGI("------------------------------------------");
    //测试
    TestObs *tobs = new TestObs();
    IDemux *de = new FFDemux();
    //de->AddObs(tobs);
    de->Open("/sdcard/v1080.mp4");

    IDecode *vdecode = new FFDecode();
    vdecode->Open(de->GetVPara());

    IDecode *adecode = new FFDecode();
    adecode->Open(de->GetAPara());

    de->AddObs(vdecode);
    de->AddObs(adecode);

    view = new GLVideoView();
    vdecode->AddObs(view);

    IResample *resample = new FFResample();
    resample->Open(de->GetAPara());
    adecode->AddObs(resample);

    de->Start();
    vdecode->Start();
    adecode->Start();
    //XSleep(3000);
    //de->Stop();
//    for(;;)
//    {
//        XData d = de->Read();
//        XLOGI("Read data size is %d", d.size);
//    }

    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_frank_com_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);

    view->SetRender(win);
    //XEGL::Get()->Init(win);
    //XShader shader;
    //shader.Init();
}