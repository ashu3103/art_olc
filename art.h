#ifndef LIBART_ART_H
#define LIBART_ART_H

#ifdef __cplusplus
extern "C" {
#endif

#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_PREFIX_LEN 10

typedef int (*art_callback)(uintptr_t data, char* key, uintptr_t value);

typedef void (*value_destroy_callback)(uintptr_t value);

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
libart_art_insert(struct art* t, char* key, uintptr_t value);

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
uintptr_t
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

#ifdef __cplusplus
}
#endif

#endif
 