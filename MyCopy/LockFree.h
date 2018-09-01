//
//  LockFree.h
//  MyCopy
//
//  Created by Juli on 30.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//
//  Lock free queue implemented with atomic CAS operations.
//  Possible usages of the structure:
//  1) Delegating tasks in the order they arrived.
//  2) Multiple threads trying to process incoming work.
//  3) Simply any kind of service that deals with asynchronous requests (e.g. TCP server).

#ifndef LockFree_h
#define LockFree_h

#include <string>
#include <utility>
    
struct LinkNode{
    std::string srcFileName;
    std::string tgtFileName;
    LinkNode* next;
};

class LockFreeQueue{
    LinkNode *head;
    LinkNode *tail;
    bool empty;
    unsigned int length;
public:
    LockFreeQueue();
    ~LockFreeQueue();
    int push(const std::pair<std::string, std::string> &task);
    std::pair<std::string, std::string> pop();
    bool isEmpty();
};

#endif /* LockFree_h */
