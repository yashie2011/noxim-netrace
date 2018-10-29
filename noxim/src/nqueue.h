/*
 * nqueue.h
 *
 **/
 //
// Copyright (c) 2013 Juan Palacios juan.palacios.puyana@gmail.com
// Subject to the BSD 2-Clause License
// - see < http://opensource.org/licenses/BSD-2-Clause>
//

#ifndef NQUEUE_H_
#define NQUEUE_H_

#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>

using namespace std;

template <typename T>
class Queue
{
 public:

  T pop()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    auto item = queue_.front();
    queue_.pop();
    mlock.unlock();
    return item;
  }
  T front()
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    if (queue_.empty())
    {
      return NULL;
    }
    auto item = queue_.front();
    mlock.unlock();
    return item;
  }

  void pop(T item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    while (queue_.empty())
    {
      cond_.wait(mlock);
    }
    item = queue_.front();
    mlock.unlock();
    queue_.pop();
  }

  void push(const T item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(item);
    mlock.unlock();
    cond_.notify_one();
  }

  void push(T** item)
  {
    std::unique_lock<std::mutex> mlock(mutex_);
    queue_.push(std::move(item));
    mlock.unlock();
    cond_.notify_one();
  }

  bool is_empty()
  {
	  if(queue_.empty())
		  return true;
	  else
		  return false;
  }
  unsigned int get_size()
  {
  	return queue_.size();
  }

 private:
  std::queue<T> queue_;
  std::mutex mutex_;
  std::condition_variable cond_;
};


#endif /* NQUEUE_H_ */
