#include <jni.h>
#include <string>
#include "XLog.h"
#include "IPlayer.h"
#include <android/native_window_jni.h>
#include "FFPlayBuilder.h"
#include "IPlayerProxy.h"

extern "C" JNIEXPORT jint JNI_OnLoad(JavaVM *vm, void *res)
{
    IPlayerProxy::Get()->Init(vm);
    IPlayerProxy::Get()->Open("/sdcard/v1080.mp4");
    IPlayerProxy::Get()->Start();
    return JNI_VERSION_1_4;
}

extern "C" JNIEXPORT jstring JNICALL
Java_frank_com_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}

extern "C"
JNIEXPORT void JNICALL
Java_frank_com_xplay_XPlay_InitView(JNIEnv *env, jobject instance, jobject surface) {

    ANativeWindow *win = ANativeWindow_fromSurface(env, surface);
    IPlayerProxy::Get()->InitView(win);

}