#include <jni.h>
#include <string>
#include "FFDemux.h"
#include "XLog.h"

extern "C" JNIEXPORT jstring JNICALL
Java_frank_com_xplay_MainActivity_stringFromJNI(
        JNIEnv* env,
        jobject /* this */) {
    std::string hello = "Hello from C++";

    XLOGI("------------------------------------------");
    IDemux *de = new FFDemux();
    de->Open("/sdcard/fftest.mp4");

    return env->NewStringUTF(hello.c_str());
}
