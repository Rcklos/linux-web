#include <iostream>

#define LOG(fmt, ...) printf(fmt"\n", ##__VA_ARGS__)
#define LOGI(format, ...) LOG("[INFO] [%s] " format, \
    log_format_time(), ##__VA_ARGS__)

// void log_(const char *format, ...);
// void LOGI(const char *fmt, ...);
char *log_format_time();
