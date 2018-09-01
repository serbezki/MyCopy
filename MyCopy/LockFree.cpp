//
//  LockFree.cpp
//  MyCopy
//
//  Created by Juli on 30.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//

#include "LockFree.h"
    
LockFreeQueue::LockFreeQueue() : head(NULL), tail(NULL), empty(true), length(0){
    head = new LinkNode;
    head->next = NULL;
    tail = head;
}

LockFreeQueue::~LockFreeQueue(){
    LinkNode *p = head;
    
    if (p){
        LinkNode *q = p->next;
        delete p;
        p = q;
    }
}

int LockFreeQueue::push(const std::pair<std::string, std::string> &task){
    LinkNode *q = new LinkNode;
    q->srcFileName = task.first;
    q->tgtFileName = task.second;
    printf("Taskfirst: %s\n", task.first.c_str());
    q->next = NULL;
    
    LinkNode *p = tail;
    LinkNode *oldP = p;
    
    // Adding the node to the end. If we can't, we try again.
    do{
        while (p->next != NULL){
            p = p->next;
        }
    } while (__sync_bool_compare_and_swap(&(p->next), NULL, q) != true);
    
    // Set tail node to be the newly added node.
    __sync_bool_compare_and_swap(&tail, oldP, q);
    return 0;
}

std::pair<std::string, std::string> LockFreeQueue::pop(){
    LinkNode *p;
    
    do{
        p = head;
        if (p->next == NULL){
            return {"", ""};
        }
    } while (__sync_bool_compare_and_swap(&head, p, p->next) != true);
    
    
    
    return {p->next->srcFileName, p->next->tgtFileName};
}

bool LockFreeQueue::isEmpty(){
    return empty;
}
