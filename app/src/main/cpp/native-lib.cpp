#include <jni.h>
#include <string>
#include "XLog.h"
#include "IPlayer.h"
#include <android/native_window_jni.h>
#include "FFPlayBuilder.h"

static IPlayer *player = NULL;
extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *res)
{
    //FFDecode::InitHard(vm);

    FFPlayBuilder::InitHard(vm);


    XLOGI("------------------------------------------");

    player = FFPlayBuilder::Get()->BuilderPlayer();


    player->Open("/sdcard/v1080.mp4");
    player->Start();


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
    if(player)
        player->InitView(win);

//    view->SetRender(win);
    //XEGL::Get()->Init(win);
    //XShader shader;
    //shader.Init();
}