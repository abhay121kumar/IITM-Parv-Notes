#include "logger.h"
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>
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

static int session_logged = 0;  // 🔐 Track whether already printed

void log_session_start() {
    if (session_logged) return;  // ✅ Only log once
    session_logged = 1;

    time_t now = time(NULL);
    char* timestamp = ctime(&now);
    FILE* f = fopen("memory_log.txt", "a");
    fprintf(f, "\n==================== NEW PROGRAM RUN ====================\n");
    fprintf(f, "Timestamp: %s", timestamp);
    fprintf(f, "=========================================================\n");
    fclose(f);
}

