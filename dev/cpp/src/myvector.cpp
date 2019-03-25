/*
 * https://github.com/gibsjose/cpp-cheat-sheet/blob/master/Data%20Structures%20and%20Algorithms.md
 *
 * Contiguous memory allocation, similar to array and accessed using index
 *
 * Note:
 * =====
 * Erase on iterator will invalidate the iterator, check the trick to avoid crashes.
 *  
 * Use:
 * ====
 * > when more items needed to be only inserted.
 * > If items can be accessed by index.
 *
 * Don't use:
 * =========
 * > More number of items.
 * > More deletes.
 *
 * Following operations covered.
 *  [1] Insertion
 *  [2] Deletion, delete all.
 *  [3] Check if entry exist.
 *  [4] Iteration.
 *  [5] Get the size.
 *  [6] Check if the vector is empty.
 */

#include <vector>
#include <string>
#include <iostream>

std::vector<std::string> myvector;

/* Insertion operations.
 * O(n)
 */
void
vector_item_front_insert (std::string &item)
{
    myvector.push_front(item);
}

/* Insertion operations.
 * O(1)
 */
void
vector_item_back_insert (std::string &item)
{
    myvector.push_back(item);
}

/* Insertion operations.
 * O(n)
 */
void
vector_item_insert (std::string &item, int idx)
{
    myvector.insert(myvector.begin(), idx, item);
}

/* Insertion operations.
 * O(1)
 */
void
vector_item_front_remove (std::string &item)
{
    myvector.pop_front();
}

/* Insertion operations.
 * O(1)
 */
void
vector_item_back_remove (std::string &item)
{
    myvector.pop_back();
}

/* Remove operations.
 * O(n)
 */
void
vector_item_remove (std::string &item)
{
    for (auto it = myvector.begin(); it != myvector.end();) {
        if (*it == item) {
            // Free if its a ptr and then erase;
            // it = myvector.erase(it);
        } else {
            it++;
        }
    }
}

bool
isOdd (int &num)
{
    return num % 2 == 0;
}

bool
deleteAll (void *ptr)
{
    free(ptr);
    return true;
}

/* Remove all.
 * O(n)
 */
void
vector_item_erase (void)
{
    myvector.clear();
    myvector.erase(myvector.begin(), myvector.end());
    myvector.erase(myvector.begin());
    std::remove_if(myvector.begin(), myvector.end(), isOdd);
    std::remove_if(myvector.begin(), myvector.end(), deleteAll);
}

/* Check if entry exist / Iteration
 */
bool
vector_item_exists (std::string &item)
{
    bool exists = false;

    for (auto const &val : myvector) {
        if (val.compare(item) == 0) {
            exists = true;
            break;
        }
    }

    return exists;
}

/* 
 * Get the size.
 */
size_type
vector_get_size (void)
{
    return myvector.size();
}

/*
 * Check if the list is empty.
 */
bool
vector_is_empty (void)
{
    return myvector.empty();
}
