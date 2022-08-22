#include <iostream>

#define LOGI(format, ...) printf("[%s] "#format "\n", log_format_time(), ##__VA_ARGS__)


char *log_format_time();
