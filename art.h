#ifndef LIBART_ART_H
#define LIBART_ART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdatomic.h>
#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PREFIX_LEN 10

typedef int (*art_callback)(void* data, char* key, void * value);

typedef void (*value_destroy_callback)(void* value);

/** @struct art
 * The ART tree
 */
struct art
{
    struct art_node* root;                 /**< The root node of ART */
    uint64_t size;                         /**< The size of the ART */
};

/**
 * Initializes an adaptive radix tree
 * @param tree [out] The tree
 * @return 0 on success, 1 if otherwise
 */
int
libart_art_create(struct art** tree);

/**
 * inserts a new value into the art tree,note that the key is copied while the value is sometimes not(depending on value type)
 * @param t The tree
 * @param key The key
 * @param value The value data
 * @param type The value type
 * @return 0 if the item was successfully inserted, otherwise 1
 */
int
libart_art_insert(struct art* t, char* key, void * value);

/**
 * Check if a key exists in the ART tree
 * @param t The tree
 * @param key The key
 * @return true if the key exists, false if otherwise
 */
bool
libart_art_contains_key(struct art* t, char* key);

/**
 * Searches for a value in the ART tree
 * @param t The tree
 * @param key The key
 * @return NULL if the item was not found, otherwise the value pointer is returned
 */
void *
libart_art_search(struct art* t, char* key);

/**
 * Deletes a value from the ART tree
 * @param t The tree
 * @param key The key
 * @return 0 if success or value not found, 1 if otherwise
 */
int
libart_art_delete(struct art* t, char* key);

/**
 * Remove all the key value pairs in the ART tree
 * @param t The tree
 * @return 0 on success, 1 if otherwise
 */
int
libart_art_clear(struct art* t);

/**
 * Destroys an ART tree
 * @return 0 on success, 1 if otherwise
 */
int
libart_art_destroy(struct art* tree);

uint64_t
libart_read_lock_and_restart(struct art_node* node, bool* restart);

void
libart_check_version_and_restart(struct art_node* node, uint64_t version, bool* restart);

void
libart_read_unlock_and_restart(struct art_node* node, uint64_t version, bool* restart);

// void
// libart_read_unlock_and_restart(struct art_node* node, uint64_t version, struct art_node* locked_node);

void
libart_upgrade_to_write_unlock_and_restart(struct art_node* node, uint64_t version, bool* restart);

// void
// libart_upgrade_to_write_unlock_and_restart(struct art_node* node, uint64_t version, struct art_node* locked_node);

void
libart_write_lock_or_restart(struct art_node* node, bool* restart);

void
libart_write_unlock(struct art_node* node);

void
libart_write_unlock_obsolete(struct art_node* node);

#ifdef __cplusplus
}
#endif

#endif
 