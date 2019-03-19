/*
 *------------------------------------------------------------------
 * Unordered Hashmap
 * Check header file unorederd_hmap.hpp for the description
 *------------------------------------------------------------------
 */

#include <unordered_hmap.hpp>

int
unordered_hashmap::entry_insert (std::string &key_name, 
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

void *
unordered_hashmap::entry_delete (std::string &key_name)
{
    void *data = NULL;
    unordered_htbl_t::iterator it;

    htbl_mtx.lock();
    it = htbl.find(key_name);
    if (it != htbl.end()) {
        data = it->second;
        htbl.erase(it);
    }
    htbl_mtx.unlock();

    return data;
}

void 
unordered_hashmap::entry_iterator_delete_all (hash_entry_delete_cb cb)
{
    void *data = NULL;
    unordered_htbl_t::iterator it;

    if (!cb) {
        return;
    }

    htbl_mtx.lock();
    for (it = htbl.begin(); it != htbl.end(); it++) {
        data = it->second;
        htbl.erase(it);
        cb(data);
    }
    htbl_mtx.unlock();
}

void *
unordered_hashmap::entry_get (std::string &key_name)
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

bool
unordered_hashmap::entry_exists (std::string &key_name)
{
    bool exists = false;

    htbl_mtx.lock();

    if (htbl.find(key_name) != htbl.end()) {
        exists = true;
    }
    
    htbl_mtx.unlock();
    return exists;
}

bool
unordered_hashmap::is_empty (void)
{
    bool empty = false;

    htbl_mtx.lock();
    empty = htbl.empty();
    htbl_mtx.unlock();

    return empty;
}

/* Test code for testing above API's
 */
// int main (int argc, 
//           char const *argv[])
// {



    // int rc = EOK;
    // rc = hashmap_entry_insert(key1, new std::string);
    // if (rc != EEXIST) {
    //     std::cout << "TC2: FAILED: hashmap_entry_insert failed" << std:endl;
    // } else {
    //     std::cout << "TC2: PASSED: hashmap_entry_insert passed" << std:endl;
    // }

//     std::string key2 = "key2";
//     rc = hashmap_entry_insert(key2, new std::string);
//     if (rc != EOK) {
//         std::cout << "TC3: FAILED: hashmap_entry_insert failed" << std:endl;
//     } else {
//         std::cout << "TC3: PASSED: hashmap_entry_insert passed" << std:endl;
//     }

//     std::string key2 = "key3";
//     rc = hashmap_entry_insert(key2, new std::string);
//     if (rc != EOK) {
//         std::cout << "TC4: FAILED: hashmap_entry_insert failed" << std:endl;
//     } else {
//         std::cout << "TC4: PASSED: hashmap_entry_insert passed" << std:endl;
//     }

//     if (hashmap_entry_get(key2)) {
//         std::cout << "TC5: PASSED: Key found hashmap_entry_get" << std:endl;
//     } else {
//         std::cout << "TC5: FAILED: Key not found hashmap_entry_get" << std:endl;
//     }

//     if (hashmap_entry_exists(key3)) {
//         std::cout << "TC6: PASSED: Key found hashmap_entry_exists" << std:endl;
//     } else {
//         std::cout << "TC6: FAILED: Key not found hashmap_entry_exists" << std:endl;
//     }

//     hashmap_entry_delete(key1);
//     if (hashmap_entry_exists(key1)) {
//         std::cout << "TC7: FAILED: hashmap_entry_delete" << std:endl;
//     } else {
//         std::cout << "TC7: PASSED: hashmap_entry_delete passed" << std:endl;
//     }

//     // hashmap_entry_delete_all();
//     // if (hashmap_entry_exists(key2)) {
//     //     std::cout << "TC8: FAILED: hashmap_entry_delete_all" << std:endl;
//     // } else {
//     //     std::cout << "TC8: PASSED: hashmap_entry_delete_all passed" << std:endl;
//     // }
//     // if (hashmap_entry_exists(key3)) {
//     //     std::cout << "TC9: FAILED: hashmap_entry_delete_all" << std:endl;
//     // } else {
//     //     std::cout << "TC9: PASSED: hashmap_entry_delete_all passed" << std:endl;
//     // }

//     /* Performance Test
//      * Create 10K entries and check time it takes to to exist, insert, GET, Delete, Delete All,
//      */

//     /* Negative Tests
//      */
    
//     /* TC1: hashmap_entry_exists()
//      *  Check if the entry exist
//      */
//     std::string no_key = "No-Key";
//     if (!hashmap_entry_exists(no_key)) {
//         std::cout << "TC1: PASSED: Key not found hashmap_entry_exists" << std:endl;
//     } else {
//         std::cout << "TC1: FAILED: Key found hashmap_entry_exists" << std:endl;
//     }

//     /* TC2: hashmap_entry_get()
//      *  Get a non-existing entry
//      */
//     if (!hashmap_entry_get(no_key)) {
//         std::cout << "TC2: PASSED: Key not found hashmap_entry_get" << std:endl;
//     } else {
//         std::cout << "TC2: FAILED: Key found hashmap_entry_get" << std:endl;
//     }

//     /* TC3: hashmap_entry_delete()
//      * Delete non-existing Key
//      */
//     hashmap_entry_delete(no_key);
//     std::cout << "TC3: PASSED: hashmap_entry_delete" << std:endl;

//     /* TC4: hashmap_entry_delete_all()
//      * Delete all hashmap entry
//      */
//     // hashmap_entry_delete_all();
//     // std::cout << "TC4: PASSED: hashmap_entry_delete_all" << std:endl;

//     return 0;
// }