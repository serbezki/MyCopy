//
//  ThreadPool.cpp
//  MyCopy
//
//  Created by Juli on 30.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//

#include <sstream>
#include <unistd.h>
#include <copyfile.h>
#include "ThreadPool.h"

ThreadPool::ThreadPool(int size){
    // Pool must have at least 1 thread.
    if (size <= 0){
        numberOfThreads = 1;
    }
    else{
        numberOfThreads = size;
    }
}

ThreadPool::~ThreadPool(){
}

void ThreadPool::handle(const std::pair<std::string, std::string> &task){
//    std::stringstream ss;
//    ss << "Thread (" << std::this_thread::get_id() << ") will copy : " << task.first << " to " << task.second << std::endl;
//    printf("%s\n", ss.str().c_str());
//    int retvalue = copyfile(task.first.c_str(), task.second.c_str(), NULL, COPYFILE_DATA | COPYFILE_UNLINK);
//    if (retvalue == 0){
//        printf("Success.\n");
//    }
//    else{
//        printf("Error when copying.\n");
//    }
}

int ThreadPool::addTask(const std::pair<std::string, std::string> &task){
    taskQueue.push(task);
    return 0;
}

void ThreadPool::worker(){
    unsigned int taskCount = 0;
    
    while (true){
        std::pair<std::string, std::string> task = taskQueue.pop();
        if (task.first.empty() && task.second.empty()){
            printf("No task received, sleeping for 0.1 seconds\n");
            
            // 0.1 seconds.
            usleep(100000);
            
            continue;
        }
        
        if (task.first == "exit" && task.second == "exit"){
            std::stringstream ss;
            ss << "Exiting thread: " << std::this_thread::get_id() << ", copied: " << taskCount << " files.";
            printf("%s\n", ss.str().c_str());
            return;
        }
        
        handle(task);
        taskCount++;
    }
}

int ThreadPool::start(){
    std::cout << "Number of threads: " << numberOfThreads << std::endl;
    for (int i = 0; i < numberOfThreads; i++){
        threadPool.push_back(std::thread(&ThreadPool::worker, this));
    }
    
    return 0;
}

int ThreadPool::stop(){
    for (int i = 0; i < numberOfThreads; i++){
        addTask({"exit", "exit"});
    }
    
    for (int i = 0; i < numberOfThreads; i++){
        threadPool[i].join();
    }
    
    return 0;
}











