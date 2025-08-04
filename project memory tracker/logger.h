#ifndef LOGGER_H
#define LOGGER_H

#include <stddef.h>

void log_event(const char* event_type, void* ptr, size_t size, const char* details);
void log_session_start();

#endif 
