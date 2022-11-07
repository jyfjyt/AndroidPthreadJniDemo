//
// Created by jinyf on 2022/10/26.
//

#include "Player.h"
#include "AndroidLog.h"
#include "unistd.h"

void *play_in_thread(void *arg) {


    sleep(3);

    Player *player = static_cast<Player *>(arg);

    int add_ret = (player->a + player->b);
    INFO("a+b:%d", add_ret);

    jobject jobj = player->jobj;

    JNIEnv *localEnvInThread = NULL;
    int ret = player->jVm->AttachCurrentThread(&localEnvInThread, 0);
    if (ret == JNI_OK) {
        //其实env->GetObjectClass和env->GetMethodID以及env->DeleteGlobalRef
        //都可以用player->jEnv
        //除了CallVoidMethod必须用localEnvInThread，因为他回调了jvm的方法？
        jclass jclz = localEnvInThread->GetObjectClass(player->jobj);
        jmethodID jmid = localEnvInThread->GetMethodID(jclz, "onResultShow", "(I)V");
        localEnvInThread->CallVoidMethod(jobj, jmid, add_ret);
        player->jVm->DetachCurrentThread();
//        player->jEnv->DeleteGlobalRef(jobj);
    } else {
        INFO("AttachCurrentThread ERROR!")
    }

    pthread_exit((player->t_id));
}

void Player::add(int _a, int _b) {
    this->a = _a;
    this->b = _b;

    pthread_t _tid;
    t_id = &_tid;
    pthread_create(t_id, NULL, play_in_thread, this);
}

Player::Player() {
}

Player::Player(JavaVM *_jVm, JNIEnv *_jEnv, jobject *_jobj) {
    this->jVm = _jVm;
    this->jEnv = _jEnv;
    this->jobj = _jEnv->NewGlobalRef(*_jobj);
}

Player::~Player() {

}
