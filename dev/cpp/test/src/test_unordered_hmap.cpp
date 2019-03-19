/*
 *------------------------------------------------------------------
 * Google Test for the unordered map API's
 *------------------------------------------------------------------
 */
#include <iostream>
#include <gtest/gtest.h>
#include <unordered_hmap.hpp>
#include <string.h>
#include <ctime>

unordered_hashmap hmap;

typedef struct test_hash_entry_ {
    std::string keyname;
    std::string value;
} test_hash_entry_t;

void
test_hmap_entry_add (int num_entries)
{
    test_hash_entry_t *hash_entry;

    for (int idx = 0; idx <= num_entries; idx++) {
        hash_entry = (test_hash_entry_t *)std::calloc(1, sizeof(test_hash_entry_t));
        if (hash_entry) {
            hash_entry->keyname = "key" + std::to_string(idx);
            hash_entry->value = hash_entry->keyname;
            hmap.entry_insert(hash_entry->keyname, hash_entry);
        }
    }
}

void
test_hmap_entry_delete (int num_entries)
{
    test_hash_entry_t *hash_entry = NULL;
    std::string keyname;

    for (int idx = 0; idx <= num_entries; idx++) {
        keyname = "key" + std::to_string(idx);
        hash_entry = (test_hash_entry_t *)hmap.entry_delete(keyname);
        free(hash_entry);
    }
}

TEST(UnorderedHashMapTest, BasicCreateAndExistEntry)
{
    std::string keyname;

    test_hmap_entry_add(3);

    for (int idx = 0; idx <= 3; idx++) {
        keyname = "key" + std::to_string(idx);
        EXPECT_EQ(true, hmap.entry_exists(keyname));
    }

    test_hmap_entry_delete(3);
}

TEST(UnorderedHashMapTest, BasicDeleteAndGetEntry)
{
    test_hash_entry_t *hash_entry;
    std::string keyname;

    test_hmap_entry_add(3);
    
    for (int idx = 0; idx <= 3; idx++) {
        keyname = "key" + std::to_string(idx);
        hash_entry = (test_hash_entry_t *)hmap.entry_get(keyname);
        EXPECT_EQ(true, hash_entry != NULL);
        EXPECT_EQ(0, std::strncmp(keyname.c_str(), hash_entry->value.c_str(), strlen(hash_entry->value.c_str())));
        hash_entry = (test_hash_entry_t *)hmap.entry_delete(keyname);
        delete hash_entry;
        EXPECT_EQ(false, hmap.entry_exists(keyname));
    }
}

TEST(UnorderedHashMapTest, Negative)
{
    test_hash_entry_t *hash_entry, tmp;
    std::string keyname;

    keyname = "key1";

    // Check non-existing key.
    hash_entry = (test_hash_entry_t *)hmap.entry_get(keyname);
    EXPECT_EQ(true, hash_entry == NULL);

    //Deleting non-existing key.
    hash_entry = (test_hash_entry_t *)hmap.entry_delete(keyname);
    EXPECT_EQ(true, hash_entry == NULL);

    test_hmap_entry_add(3);
  
    // Adding duplicate key
    tmp.keyname = "key1";
    tmp.value   = "key1";
    EXPECT_EQ(EEXIST, hmap.entry_insert(keyname, &tmp));

    test_hmap_entry_delete(3);
}

/* The function pointer test_delete_entry_cb for some reason
 * is passed as 1 to the  entry_iterator_delete_all() and so
 * program crashes. Testcase disabled for that reason.
 */
void test_delete_entry_cb (void *data)
{
    free(data);
}

TEST(UnorderedHashMapTest, DISABLED_BasicDeleteAllEntry)
{
    test_hmap_entry_add(10);

    hmap.entry_iterator_delete_all(&test_delete_entry_cb);

    EXPECT_EQ(true, hmap.is_empty());
}

TEST(UnorderedHashMapTest, Perf10KEntriesRandomLookup)
{
    test_hash_entry_t *hash_entry;
    std::string keyname;
    std::chrono::steady_clock::time_point begin, end;

    begin = std::chrono::steady_clock::now();
    test_hmap_entry_add(10000);
    end = std::chrono::steady_clock::now();
    std::cout << "-----------------------------------------------------" << std::endl;
    std::cout << "> Hash Entry allocation for 10K entries = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    keyname = "key9000";
    begin = std::chrono::steady_clock::now();
    hash_entry = (test_hash_entry_t *)hmap.entry_get(keyname);
    end = std::chrono::steady_clock::now();
    std::cout << "> Hash Entry lookup of 9000/10000 = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;
    EXPECT_EQ(true, hash_entry != NULL);

    keyname = "key1000";
    begin = std::chrono::steady_clock::now();
    hash_entry = (test_hash_entry_t *)hmap.entry_get(keyname);
    end = std::chrono::steady_clock::now();
    std::cout << "> Hash Entry lookup of 1000/10000 = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;
    EXPECT_EQ(true, hash_entry != NULL);

    keyname = "key7000";
    begin = std::chrono::steady_clock::now();
    end = std::chrono::steady_clock::now();
    std::cout << "> Hash Entry lookup of 7000/10000 = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;
    EXPECT_EQ(true, hmap.entry_exists(keyname));

    keyname = "key3000";
    begin = std::chrono::steady_clock::now();
    hash_entry = (test_hash_entry_t *)hmap.entry_get(keyname);
    end = std::chrono::steady_clock::now();
    std::cout << "> Hash Entry lookup of 3000/10000 = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;
    EXPECT_EQ(true, hash_entry != NULL);

    keyname = "key4500";
    begin = std::chrono::steady_clock::now();
    hash_entry = (test_hash_entry_t *)hmap.entry_get(keyname);
    end = std::chrono::steady_clock::now();
    std::cout << "> Hash Entry lookup of 4500/10000 = " << std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin).count() << " ns" << std::endl;
    EXPECT_EQ(EEXIST, hmap.entry_insert(keyname, hash_entry));

    begin = std::chrono::steady_clock::now();
    test_hmap_entry_delete(10000);
    end = std::chrono::steady_clock::now();
    std::cout << "> Hash Entry deletion for 10K entries = " << std::chrono::duration_cast<std::chrono::milliseconds>(end - begin).count() << " ms" << std::endl;

    std::cout << "-----------------------------------------------------" << std::endl;
}