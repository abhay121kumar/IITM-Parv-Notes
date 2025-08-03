#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <string.h>

#define LOG_FILE "memory_log.txt"

void log_event(const char* event_type, void* ptr, size_t size, const char* details) {
    FILE* file = fopen(LOG_FILE, "a");
    if (!file) return;

    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    timestamp[strlen(timestamp)-1] = '\0'; // Remove newline

    fprintf(file, "[%s] %s: Addr=%p | Size=%zu | %s\n", 
            timestamp, event_type, ptr, size, details);
    fclose(file);
}
