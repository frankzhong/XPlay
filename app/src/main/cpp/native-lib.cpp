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
#include "IAudioPlay.h"
#include "SLAudioPlay.h"
#include "IPlayer.h"
#include <android/native_window_jni.h>


IVideoView *view = NULL;
extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *res)
{
    FFDecode::InitHard(vm);


    XLOGI("------------------------------------------");
    //测试
//    TestObs *tobs = new TestObs();

    IPlayer::Get()->Open("/sdcard/v1080.mp4");
    IPlayer::Get()->Start();

//    de->Start();
//    vdecode->Start();
//    adecode->Start();


    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT jstring JNICALL
Java_frank_com_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

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
    IPlayer::Get()->InitView(win);

//    view->SetRender(win);
    //XEGL::Get()->Init(win);
    //XShader shader;
    //shader.Init();
}