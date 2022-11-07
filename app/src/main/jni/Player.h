//
// Created by jinyf on 2022/10/26.
//

#ifndef BITMAPJNI_PLAYER_H
#define BITMAPJNI_PLAYER_H

#include <jni.h>
#include <pthread.h>

class Player {

public:

    pthread_t *t_id;

    JavaVM *jVm;
    JNIEnv *jEnv;
    jobject jobj;

    int a;
    int b;

    //jobj要用指针，否则无法值传递
    Player(JavaVM *jVm, JNIEnv *jEnv, jobject *jobj);
    Player();

    ~Player();

    void add(int a, int b);
};


#endif //BITMAPJNI_PLAYER_H
