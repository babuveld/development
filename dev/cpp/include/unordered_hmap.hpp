/*
 *------------------------------------------------------------------
 * Unordered Hashmap API's
 *
 * Includes API's operating on unordered hashmap.
 *
 * Threadsafe                        : Yes
 * Duplicate Key support             : No
 * Sorted                            : No
 * Random Lookup Time in 10K hashmap : In nanoseconds
 * Time Complexity                   : O(1)
 * 
 *------------------------------------------------------------------
 */

#ifndef UNORDERED_HMAP_HPP
#define UNORDERED_HMAP_HPP

#include <iostream>
#include <string>
#include <mutex>
#include <unordered_map>

#ifndef EOK
#define EOK 0
#endif

typedef std::unordered_map<std::string, void *> unordered_htbl_t;
typedef void (*hash_entry_delete_cb)(void *data);

class unordered_hashmap {
private:

    unordered_htbl_t htbl;
    std::mutex htbl_mtx;
    
public:
	/**
	 * @n
	 * Insert an entry to the ordered hashmap.
	 *
	 * @param[in]  key_name  Key for the hashentry.
	 *
	 * @param[in]  value     Value to be inserted
	 *
	 * @retval EOK    Entry added to the hash table successfully.
	 * @retval EEXIST Entry already exist for the key.
	 *
	 */
    int entry_insert(std::string &key_name, void *value);

    /**
	 * @n
	 * Delete an entry from the hashmap. Value returned can be
	 * safely freed
	 *
	 * @param[in]  key_name    Keyname.
	 * @param[out] value       data associated with the keyname.
	 *
	 */
    void *entry_delete(std::string &key_name);

	/**
	 * @n
	 * Delete all entry from the hashmap.
	 *
	 * @param[in]  hash_entry_delete_cb  User delete callback where the user can free the data pointer
	 *
	 */
    void entry_iterator_delete_all(hash_entry_delete_cb cb);

	/**
	 * @n
	 * Get the hashentry from the ordered hashmap.
	 *
	 * @param[in]  key_name    Keyname.
	 *
	 * @retval Value  Value for the key.
	 *
	 */ 
    void *entry_get(std::string &key_name);

	/**
	 * @n
	 * Hashentry exists in the ordered hashmap.
	 *
	 * @param[in]  key_name    Keyname.
	 *
	 * @retval true  Hashentry exist for the key.
	 * @retval false Hashentry doesn't exist for the key.
	 *
	 */
    bool entry_exists(std::string &key_name);

    /**
	 * @n
	 * Hashtable status.
	 *
	 * @param[in]  key_name    Keyname.
	 *
	 * @retval true  If hashtable is empty.
	 * @retval false If hashtable is not empty.
	 *
	 */
    bool is_empty(void);
};

#endif /* UNORDERED_HMAP_HPP */