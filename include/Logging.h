#include <stdio.h>

#include <Arduino.h>

#ifndef logSetupLoggingArduinoUno
#define logSetupLoggingArduinoUno() Serial.begin(9600); fdevopen([](char const p_char, FILE *p_stream) -> int { return Serial.write(p_char); }, 0);
#endif

#ifndef LOG_TAG
#define LOG_TAG "?"
#endif

#ifdef LOG_INFO
#define logisnf(p_str) puts_P(LOG_INFO " " LOG_TAG ": " p_str);
#define logis(p_str) puts_P((char const*) F(LOG_INFO " " LOG_TAG ": " p_str));
#define logi(p_format, ...) printf_P((char const*) F(LOG_INFO " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logisnf
#define logis
#define logi
#endif

#ifdef LOG_WARN
#define logwsnf(p_str) puts_P(LOG_WARN " " LOG_TAG ": " p_str);
#define logws(p_str) puts_P((char const*) F(LOG_WARN " " LOG_TAG ": " p_str));
#define logw(p_format, ...) printf_P((char const*) F(LOG_WARN " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logwsnf
#define logws
#define logw
#endif

#ifdef LOG_DEBUG
#define logdsnf(p_str) puts_P(LOG_DEBUG " " LOG_TAG ": " p_str);
#define logds(p_str) puts_P((char const*) F(LOG_DEBUG " " LOG_TAG ": " p_str));
#define logd(p_format, ...) printf_P((char const*) F(LOG_DEBUG " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logdsnf
#define logds
#define logd
#endif

#ifdef LOG_ERROR
#define logesnf(p_str) puts_P(LOG_ERROR " " LOG_TAG ": " p_str);
#define loges(p_str) puts_P((char const*) F(LOG_ERROR " " LOG_TAG ": " p_str));
#define loge(p_format, ...) printf_P((char const*) F(LOG_ERROR " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logesnf
#define loges
#define loge
#endif

#ifdef LOG_VERBOSE
#define logvsnf(p_str) puts_P(LOG_VERBOSE " " LOG_TAG ": " p_str);
#define logvs(p_str) puts_P((char const*) F(LOG_VERBOSE " " LOG_TAG ": " p_str));
#define logv(p_format, ...) printf_P((char const*) F(LOG_VERBOSE " " LOG_TAG ": " p_format "\n"), __VA_ARGS__);
#else
#define logvsnf
#define logvs
#define logv
#endif
