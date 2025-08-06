// dbms_memory_manager/
// ├── main.c               // Test and simulate usage
// ├── memory_manager.h     // Header for memory manager
// ├── memory_manager.c     // Core implementation
// ├── slab.h               // Header for slab structure
// ├── slab.c               // Slab allocation/free logic
// └── Makefile             // For building the project


// #include <stdio.h>
// #include "memory_manager.h"

// int main() {
//     printf("DBMS Memory Management System Starting...\\n");

//     init_memory_manager();

//     void* tuple1 = allocate_tuple();
//     void* tuple2 = allocate_tuple();
//     void* tuple3 = allocate_tuple();

//     printf("Allocated 3 tuples.\\n");

//     free_tuple(tuple2);
//     free_tuple(tuple1);

//     void* tuple4 = allocate_tuple(); // reuse freed block

//     shutdown_memory_manager();

//     return 0;
// }






//  Where exactly is DBMS logic reflected in your project?
// Here’s where DBMS ideas are applied:

// 1. Tuple-Based Allocation
// You allocate memory in fixed-size units called "tuples" (just like a database row).

// void* t1 = allocate_tuple();  // similar to storing a row in memory
// ✅ Real DBMS: Internally, DBMS stores tuples/rows in blocks/slabs. 
// Your allocate_tuple() simulates that.

// 2. Slab Allocation Strategy
// Memory is managed in slabs (fixed-size memory regions), reused for performance.

// slabs[slab_count++] = create_slab();
// ✅ Real DBMS: Oracle, PostgreSQL, MySQL use slabs or page buffers to avoid 
// fragmentation and to optimize I/O.

// 3. Tracking Leaks and Stats (like PostgreSQL MemoryContext)
// You track how many slabs are used, how many tuples are active, and generate
//  a leak report.

// mm_print_stats();
// mm_write_leak_report("leaks.log");
// ✅ Real DBMS: During query execution or session, DBMS tracks memory contexts,
//  reclaims unused blocks, and detects leaks if any.

// 4. ASCII Graph for Live Monitoring (similar to DB health dashboard)

// mm_print_memory_graph();
// ✅ Real DBMS: Admin tools like pg_stat_activity and MySQL’s performance_schema 
// give live memory usage stats. You're mimicking that in console.

// 5. No SQL Needed
// You're not using SQL or MongoDB **because you're simulating the "engine layer" —
//  the core beneath the query processor.

// You’re not building a DBMS interface, but the DBMS memory layer (very low-level 
// internals).



// 🎯 Why is this useful?
// You are learning how:

// A DBMS allocates memory efficiently

// How it stores and releases tuples (rows)

// How it avoids fragmentation

// How it detects leaks

// How it visualizes resource usage

// 🔥 These concepts are key in DBMS internals, high-performance systems,
//  game engines, OS design, embedded systems, and real-time financial systems.




#include "memory_manager.h"
#include <stdio.h>

int main() {
    init_memory_manager();                      

    void* t1 = allocate_tuple();               
    void* t2 = allocate_tuple();
    void* t3 = allocate_tuple();

    free_tuple(t2);                             

    mm_print_stats();                           
    // mm_write_leak_report("leaks.log");          // ✅ optional debug

    shutdown_memory_manager();                  
    mm_print_memory_graph(); // Live memory ASCII graph
    return 0;
}
