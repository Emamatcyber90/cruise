#ifndef CRUISE_H
#define CRUISE_H

/* TODO: namespace C */

/* linked list of chunk information given to an external library wanting
 * to RDMA out a file from CRUISE */
typedef struct {
    off_t chunk_id;
    int location;
    void *chunk_mr;
    off_t spillover_offset;
    struct chunk_list_t *next;
} chunk_list_t;

/* mount memfs at some prefix location */
int cruise_mount(const char prefix[], size_t size, int rank);

/* get information about the chunk data region
 * for external async libraries to register during their init */
size_t cruise_get_data_region(void **ptr);

/* get a list of chunks for a given file (useful for RDMA, etc.) */
chunk_list_t* cruise_get_chunk_list(char* path);

/* debug function to print list of chunks constituting a file
 * and to test above function*/
void cruise_print_chunk_list(char* path);

#endif /* CRUISE_H */
