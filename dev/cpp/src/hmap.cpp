/*
 *------------------------------------------------------------------
 * Hashmap
 * Check header file hmap.hpp for the description
 *------------------------------------------------------------------
 */

#include <hmap.hpp>

template <typename T> 
int hashmap<T>::entry_insert (std::string &key_name, 
                              void *value)
{
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

template <typename T> 
void * hashmap<T>::entry_delete (std::string &key_name)
{
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

template <typename T> 
void hashmap<T>::entry_iterator_delete_all (hash_entry_delete_cb cb)
{
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

template <typename T> 
void * hashmap<T>::entry_get (std::string &key_name)
{
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

template <typename T> 
bool hashmap<T>::entry_exists (std::string &key_name)
{
    bool exists = false;

    htbl_mtx.lock();

    if (htbl.find(key_name) != htbl.end()) {
        exists = true;
    }
    
    htbl_mtx.unlock();
    return exists;
}

template <typename T> 
bool hashmap<T>::is_empty (void)
{
    bool empty = false;

    htbl_mtx.lock();
    empty = htbl.empty();
    htbl_mtx.unlock();

    return empty;
}