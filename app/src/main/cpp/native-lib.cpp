#include <jni.h>
#include <string>


//外部实现
extern "C" {
extern int bspatch_main(int argc, char *argv[]);
}


extern "C" JNIEXPORT jstring JNICALL
Java_com_zl_bsdiff_MainActivity_stringFromJNI(
        JNIEnv *env,
        jobject /* this */) {
    std::string hello = "Hello from C++";
    return env->NewStringUTF(hello.c_str());
}
extern "C"
JNIEXPORT void JNICALL
Java_com_zl_bsdiff_MainActivity_doPatchNative(JNIEnv *env, jobject instance, jstring oldApk_,
                                              jstring newApk_, jstring patch_) {
    const char *oldApk = env->GetStringUTFChars(oldApk_, 0);
    const char *newApk = env->GetStringUTFChars(newApk_, 0);
    const char *patch = env->GetStringUTFChars(patch_, 0);

    char *argv[] = {
            "bspatch",
            const_cast<char *>(oldApk),
            const_cast<char *>(newApk),
            const_cast<char *>(patch)
    };
    //函数声明实现
    bspatch_main(4, argv);

    env->ReleaseStringUTFChars(oldApk_, oldApk);
    env->ReleaseStringUTFChars(newApk_, newApk);
    env->ReleaseStringUTFChars(patch_, patch);
}