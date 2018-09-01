//
//  ThreadPool.h
//  MyCopy
//
//  Created by Juli on 30.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//
//  A library intended to make multi-threaded operations easier.
//  Can be customized to distribute work across multiple processes
//  or match small tasks to individual threads. Worker processes do
//  not return data in the default implementation, but that can
//  easily be done with minor changes.

#ifndef ThreadPool_h
#define ThreadPool_h

#include <iostream>
#include <thread>
#include <queue>
#include <string>
#include <utility>
#include <vector>
#include "LockFree.h"

class ThreadPool{
    int numberOfThreads;
    
    // Data to be proccesed is added to a LockFreeQueue.
    LockFreeQueue taskQueue;
    std::vector<std::thread> threadPool;
    
    void worker();
    
public:
    ThreadPool(int size);
    virtual ~ThreadPool();
    
    // Extra methods for additional functionality.
    virtual void init() {};
    virtual void finish() {};
    
    void handle(const std::pair<std::string, std::string> &task);
    
    // Insert data into the processing queue (string for now).
    int addTask(const std::pair<std::string, std::string> &task);

    int start();
    int stop();
};

#endif /* ThreadPool_h */
