/*
 *------------------------------------------------------------------
 * Thread safe Hashmap API's for ordered and unordered entries.
 *
 * +----------------------+----------+----------+
 * |       Summary        | Unsorted |  Sorted  |
 * +======================+==========+==========+
 * | Thread safe          | Yes      | Yes      |
 * |                      |          |          |
 * | Multiple Key Support | No       | No       |
 * |                      |          |          |
 * | Creation 10K entries | 14ms     | 44ms     |
 * |                      |          |          |
 * | Deletion 10K entries | 11ms     | 18ms     |
 * |                      |          |          |
 * | Lookup               | ns       | us       |
 * |                      |          |          |
 * | Time Complexity      | O(1)     | O(nlogn) |
 * |                      |          |          |
 * +============================================+
 *
 *------------------------------------------------------------------
 */

#ifndef HMAP_HPP
#define HMAP_HPP

#include <iostream>
#include <string>
#include <mutex>
#include <map>
#include <unordered_map>

#ifndef EOK
#define EOK 0
#endif

typedef std::map<std::string, void *>           ordered_htbl_t;
typedef std::unordered_map<std::string, void *> unordered_htbl_t;
typedef void (*hash_entry_delete_cb)(void *data);

template <typename T>
class hashmap {
private:

    T htbl;
    std::mutex htbl_mtx;
    
public:
	/**
	 * @n
	 * Insert an entry to the hashmap.
	 *
	 * @param[in]  key_name  Key for the hashentry.
	 *
	 * @param[in]  value     Value to be inserted
	 *
	 * @retval EOK    Entry added to the hash table successfully.
	 * @retval EEXIST Entry already exist for the key.
	 *
	 */
    int entry_insert(std::string &key_name, void *value) {
    	int rc = EOK;

    	htbl_mtx.lock();

	    do {
	        if (htbl.find(key_name) != htbl.end()) {
	            /* Found an existing entry in the hash table
	             */
	            rc = EEXIST;
	            break; 
	        }

	        htbl[key_name] = value;
	    } while(0);
	    
	    htbl_mtx.unlock();

	    return rc;
    }

    /**
	 * @n
	 * Delete an entry from the hashmap. Value returned can be
	 * safely freed
	 *
	 * @param[in]  key_name    Keyname.
	 * @param[out] value       data associated with the keyname.
	 *
	 */
    void *entry_delete(std::string &key_name) {
    	void *data = NULL;

	    htbl_mtx.lock();
	    auto it = htbl.find(key_name);
	    if (it != htbl.end()) {
	        data = it->second;
	        htbl.erase(it);
	    }
	    htbl_mtx.unlock();

	    return data;
    }

	/**
	 * @n
	 * Delete all entry from the hashmap.
	 *
	 * @param[in]  hash_entry_delete_cb  User delete callback where the user can free the data pointer
	 *
	 */
    void entry_iterator_delete_all(hash_entry_delete_cb cb) {
    	void *data = NULL;

	    if (!cb) {
	        return;
	    }

	    htbl_mtx.lock();
	    for (auto it = htbl.begin(); it != htbl.end(); it++) {
	        data = it->second;
	        htbl.erase(it);
	        cb(data);
	    }
	    htbl_mtx.unlock();
    }

	/**
	 * @n
	 * Get the hashentry from the hashmap.
	 *
	 * @param[in]  key_name    Keyname.
	 *
	 * @retval Value  Value for the key.
	 *
	 */ 
    void *entry_get(std::string &key_name) {
    	void *value = NULL;

	    htbl_mtx.lock();

	    auto it = htbl.find(key_name);
	    if (it != htbl.end()) {
	        /* Found an existing entry in the hash table
	         */
	        value = it->second;
	    }
	    
	    htbl_mtx.unlock();
	    return value;
    }

	/**
	 * @n
	 * Hashentry exists in the hashmap.
	 *
	 * @param[in]  key_name    Keyname.
	 *
	 * @retval true  Hashentry exist for the key.
	 * @retval false Hashentry doesn't exist for the key.
	 *
	 */
    bool entry_exists(std::string &key_name) {
    	bool exists = false;

	    htbl_mtx.lock();

	    if (htbl.find(key_name) != htbl.end()) {
	        exists = true;
	    }
	    
	    htbl_mtx.unlock();
	    return exists;
    }

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
    bool is_empty(void) {
    	bool empty = false;

	    htbl_mtx.lock();
	    empty = htbl.empty();
	    htbl_mtx.unlock();

	    return empty;
    }
};

#endif /* HMAP_HPP */