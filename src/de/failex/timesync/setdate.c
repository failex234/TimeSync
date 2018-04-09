#include <jni.h>
#include "setdate.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#ifdef __WIN32
#include <windows.h>
#elif defined(__linux__)
#include <errno.h>
#include <sys/time.h>
#endif

JNIEXPORT jboolean JNICALL Java_de_failex_timesync_TimeSync_isprivileged(JNIEnv *env, jclass clazz) {
#ifdef __WIN32
    int isadmin = 0;
    HANDLE hToken = NULL;

    if (OpenProcessToken(GetCurrentProcess(), TOKEN_QUERY, &hToken)) {
        TOKEN_ELEVATION Elevation;
        DWORD cbSize = sizeof(TOKEN_ELEVATION);

        if (GetTokenInformation(hToken, TokenElevation, &Elevation, sizeof(Elevation), &cbSize)) {
            isadmin = Elevation.TokenIsElevated;
        }
    }

    if (isadmin) {
        CloseHandle(hToken);
    }

    return isadmin;

#elif defined(__linux__)
    return getuid() == 0 ? 1 : 0;
#endif
}

JNIEXPORT jboolean JNICALL Java_de_failex_timesync_TimeSync_setdate(JNIEnv *env, jclass clazz, jint day, jint month, jint year, jint hour, jint minute, jint second, jlong epoch) {

#ifdef __WIN32

    //Create an empty SYSTEMTIME struct;
    SYSTEMTIME st;

    //Get premade / current SYSTEMTIME struct so we don't have to make our own
    GetLocalTime(&st);
    printf("(JNI) Windows detected!\n");
    printf("(JNI) Current Windows time is %02d.%02d.%d %02d:%02d:%02d\n", st.wDay, st.wMonth, st.wYear, st.wHour, st.wMinute, st.wSecond);
    printf("(JNI) Setting time to %02d.%02d.%d %02d:%02d:%02d... (%I64d)\n", day, month, year, hour, minute, second, epoch);

    //SET SYSTEMTIME struct to wanted values
    st.wDay = day;
    st.wMonth = month;
    st.wYear = year;
    st.wHour = hour;
    st.wMinute = minute;
    st.wSecond = second;

    int returned = SetLocalTime(&st);

    if (returned == 0) {
        //Saves error code
        DWORD dw = GetLastError();

        //Format error message somehow to a string. Taken from https://msdn.microsoft.com/en-us/library/windows/desktop/ms680582(v=vs.85).aspx
        LPVOID lpDisplayBuf;
        LPVOID lpMsgBuf;
        FormatMessage(FORMAT_MESSAGE_ALLOCATE_BUFFER | FORMAT_MESSAGE_FROM_SYSTEM | FORMAT_MESSAGE_IGNORE_INSERTS, NULL, dw, MAKELANGID(LANG_NEUTRAL, SUBLANG_DEFAULT), (LPTSTR) &lpMsgBuf, 0, NULL );

        printf("(JNI) SetLocalTime failed with error %d: %s\n", dw, lpMsgBuf);
        return 0;
    } else {
        printf("(JNI) Successfully set date!\n");
    }
#elif defined(__linux__)
    printf("(JNI) GNU/Linux detected!\n");

    //Get existing structs so we don't have to give every variable a value
    timeval time;
    timezone zone;

    int getreturn = gettimeofday(&time, &zone);

    //gettimeofday failed
    if (getreturn == -1) {
        int err = errno;
        printf("(JNI) Can't get system time: %s\n", errno(err))
        return 0;
    }

    //Set new time
    timeval.time_t = epoch;

    int setreturn = gettimeofday(&time, &zone);

    //settimeofday failed
    if (setreturn == -1) {
        int err = errno;
        printf("(JNI) Can't set system time: %s\n", errno(err));
        return 0;
    }

    return 1;

#else
    printf("(JNI) Unknown system, unable to set time!\n");
    return 0;
#endif
}