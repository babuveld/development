/*
 * Its a double linked list. Its slower compared to vectors.
 *
 * Use:
 * ====
 * > when more items needed to be inserted/removed in middle.
 * > If number of items will be more.
 *
 * Don't use:
 * =========
 * > For direct access.
 *
 * Following operations covered.
 *  [1] Insertion
 *  [2] Deletion, delete all.
 *  [3] Check if entry exist.
 *  [4] Iteration.
 *  [5] Get the size.
 *  [6] Check if the list is empty.
 */

#include <list>
#include <string>
#include <iostream>

std::list<std::string> mylist;

/* Insertion operations.
 * O(1)
 */
void
list_item_front_insert (std::string &item)
{
    mylist.push_front(item);
}

/* Insertion operations.
 * O(1)
 */
void
list_item_back_insert (std::string &item)
{
    mylist.push_back(item);
}

/* Insertion operations.
 * O(n)
 */
void
list_item_insert (std::string &item, int idx)
{
    mylist.insert(mylist.begin(), idx, item);
}

/* Insertion operations.
 * O(1)
 */
void
list_item_front_remove (std::string &item)
{
    mylist.pop_front(item);
}

/* Insertion operations.
 * O(1)
 */
void
list_item_back_remove (std::string &item)
{
    mylist.pop_back(item);
}

/* Remove operations.
 * O(n)
 */
void
list_item_remove (std::string &item)
{
    mylist.remove(item);
}

/* Remove all.
 * O(n)
 */
void
list_item_erase (void)
{
    mylist.clear();
    mylist.erase(mylist.begin(), mylist.end());
}

/* Remove operations.
 * O(n)
 */
void
list_item_erase (void)
{
    mylist.erase(mylist.begin());
}

/* Check if entry exist / Iteration
 */
bool
list_item_exists (std::string &item)
{
    bool exists = false;

    for (auto const &val : mylist) {
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
list_get_size (void)
{
    return mylist.size();
}

/*
 * Check if the list is empty.
 */
bool
list_get_size (void)
{
    return mylist.empty();
}
