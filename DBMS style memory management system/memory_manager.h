#ifndef MEMORY_MANAGER_H
#define MEMORY_MANAGER_H

void init_memory_manager();
void* allocate_tuple();
void free_tuple(void* ptr);
void shutdown_memory_manager();

void mm_print_stats();
void mm_write_leak_report(const char* filename);
void mm_set_debug_mode(int enabled);

// memory_manager.h
void mm_print_memory_graph();

#endif // MEMORY_MANAGER_H