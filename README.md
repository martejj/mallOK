# MallOK

A wrapper for malloc that allows for detection tracing of memory leaks. Macros overwrite all malloc() and free() calls with calls to mallok's malloc() and free() functions. 

### Planned extensions include:

[] Macros for realloc() and calloc().
[] More efficient data structures than a linked list (Red-Black Tree)
[] Attempt at own allocator so that free'd status can be stored as metadata rather than an extra structure.
