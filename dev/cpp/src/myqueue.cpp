/*
 * https://github.com/gibsjose/cpp-cheat-sheet/blob/master/Data%20Structures%20and%20Algorithms.md
 *
 * container adapter [i.e] Its just a wrapper on another container underneath like deque.
 * [e.g] stack and queue uses deque container underneath
 *
 * Use:
 * ====
 * > For FIFO.
 * > [e.g] use for online ordering etc...
 *
 *
 * Following operations covered.
 *  [1] push
 *  [2] pop.
 *  [3] front.
 *  [4] back.
 *  [5] Flush queue
 *  [6] Get the size.
 *  [7] Check if the queue is empty.
 */

#include <queue>
#include <string>
#include <mutex>

std::queue<std::string> myqueue;
std::mutex myqueue_mutex;

/* Push the element to the queue
 */
void
queue_item_push (void *item)
{
    myqueue_mutex.lock();
    myqueue.push(item);
    myqueue_mutex.unlock();
}

/* Pop the next element in the queue
*/
void
queue_item_pop (void)
{
    myqueue_mutex.lock();
    myqueue.pop();
    myqueue_mutex.unlock();
}

/* Get the element from the front of queue
 */
void *
queue_item_front (void)
{
    void *data = NULL;

    myqueue_mutex.lock();
    data = myqueue.front(item);
    myqueue_mutex.unlock();

    return data;
}

/* Get the element from the back of queue
 */
void *
queue_item_back (void)
{
    void *data = NULL;

    myqueue_mutex.lock();
    data = myqueue.back();
    myqueue_mutex.unlock();

    return data;
}

int queue_flush (void)
{
    void *data = NULL;

    myqueue_mutex.lock();
    while(!myqueue.empty()) {
        data = myqueue.front();
        /* Free data here */
        myqueue.pop();
    }
    myqueue_mutex.unlock();
}

int
queue_get_size (void)
{
    int size = false;

    myqueue_mutex.lock();
    size = myqueue.size();
    myqueue_mutex.unlock();

    return size;
}

bool
queue_is_empty (void)
{
    bool is_empty = false;

    myqueue_mutex.lock();
    is_empty = myqueue.empty();
    myqueue_mutex.unlock();

    return is_empty;
}