//
// Created by ttaaa on 6/3/21.
//
#include "ListModeLib.h"
#include "list_mode.h"

JNIEXPORT jstring JNICALL Java_ListModeLib_runListMode(JNIEnv *jenv, jobject jobj) {
    char *msg = run_list_mode();
    return (*jenv)->NewStringUTF(jenv, msg);
}
