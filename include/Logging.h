#include <stdio.h>

#include <Arduino.h>

#ifndef logSetupLogging
#define logSetupLogging() Serial.begin(9600); fdevopen([](char const p_char, FILE *p_stream) -> int { return Serial.write(p_char); }, 0);
#endif

#ifndef LOG_TAG
#define LOG_TAG
#endif

#ifdef LOG_WARN
#define logws(p_str) puts_P((char const*) F(LOG_WARN " " LOG_TAG ": " p_str));
#define logw(p_format, ...) printf_P((char const*) F(LOG_WARN " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logws
#define logw
#endif

#ifdef LOG_DEBUG
#define logds(p_str) puts_P((char const*) F(LOG_DEBUG " " LOG_TAG ": " p_str));
#define logd(p_format, ...) printf_P((char const*) F(LOG_DEBUG " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logds
#define logd
#endif

#ifdef LOG_ERROR
#define loges(p_str) puts_P((char const*) F(LOG_ERROR " " LOG_TAG ": " p_str));
#define loge(p_format, ...) printf_P((char const*) F(LOG_ERROR " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define loges
#define loge
#endif
