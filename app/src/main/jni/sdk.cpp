//
// Created by jinyf on 2022/9/13.
//



#include <jni.h>
#include <stdio.h>
#include "AndroidLog.h"
#include "Player.h"

extern "C" {

}

JavaVM *javaVM = NULL;

extern "C"
JNIEXPORT jint JNICALL JNI_OnLoad(JavaVM *vm, void *reserved) {
    jint result = -1;
    javaVM = vm;
    JNIEnv *env;
    if (vm->GetEnv((void **) &env, JNI_VERSION_1_4) != JNI_OK) {
        return result;
    }
    return JNI_VERSION_1_4;
}


extern "C"
JNIEXPORT void JNICALL
Java_com_yfjin_pthread_MainActivity_test(JNIEnv *env, jobject thiz, jstring _s) {
    Player *player=new Player(javaVM,env,&thiz);
    player->add(22,33);
}