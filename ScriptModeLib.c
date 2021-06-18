//
// Created by ttaaa on 6/3/21.
//

#include "ScriptModeLib.h"
#include "script_mode.h"
#include "fat32_lib.h"

JNIEXPORT jint JNICALL Java_ScriptModeLib_getPartition (JNIEnv *jenv, jobject jobj, jstring path) {
    struct partition_value *partition = get_partition((*jenv)->GetStringUTFChars(jenv, path, 0));
    int res = (partition) ? 0 : 1;
    if (partition) {
        close_partition(partition);
    }
    return res;
}

JNIEXPORT jstring JNICALL Java_ScriptModeLib_lsCommand(JNIEnv *jenv, jobject jobj, jstring path) {
    struct partition_value *partition = get_partition((*jenv)->GetStringUTFChars(jenv, path, 0));
    char *msg = ls_command(partition);
    close_partition(partition);
    return (*jenv)->NewStringUTF(jenv, msg);
}

JNIEXPORT jint JNICALL Java_ScriptModeLib_cdCommand(JNIEnv *jenv, jobject jobj, jstring path, jstring to) {
    struct partition_value *partition = get_partition((*jenv)->GetStringUTFChars(jenv, path, 0));
    int res = cd_command(partition, (char *) (*jenv)->GetStringUTFChars(jenv, to, 0));
    close_partition(partition);
    return res;
}

JNIEXPORT jint JNICALL Java_ScriptModeLib_cpCommand(JNIEnv *jenv, jobject jobj, jstring path, jstring source, jstring to) {
    struct partition_value *partition = get_partition((*jenv)->GetStringUTFChars(jenv, path, 0));
    int res = cp_command(partition, (char *) (*jenv)->GetStringUTFChars(jenv, source, 0), (char *) (*jenv)->GetStringUTFChars(jenv, to, 0));
    close_partition(partition);
    return res;
}

JNIEXPORT jstring JNICALL Java_ScriptModeLib_helpCommand(JNIEnv * jenv, jobject jobj) {
    char *msg = help_command();
    return (*jenv)->NewStringUTF(jenv, msg);
}
