//
//  main.cpp
//  MyCopy
//
//  Created by Juli on 25.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//

#include <vector>
#include <string>
#include <cstdlib>
#include <sstream>
#include <unistd.h>
#include <dirent.h>
#include "ThreadPool.h"

int main(int argc, const char * argv[]) {
    if (argc != 3){
        printf("Usage: MyCopy <source> <destination\n\n");
        printf("Example: MyCopy ~/SourceDir/ ~/TargetDir/\n");
        return 0;
    }
    
    std::string srcDir = argv[1];
    std::string tgtDir = argv[2];
    
    std::vector<std::string> srcFiles;
    
    DIR *dir;
    struct dirent *ent;
    if ((dir = opendir(srcDir.c_str())) != NULL){
        while ((ent = readdir(dir)) != NULL){
            srcFiles.push_back(ent->d_name);
        }
        closedir(dir);
    }
    else{
        perror("");
        return EXIT_FAILURE;
    }
    
    printf("Started copying...\n");
    ThreadPool pool(1);
    pool.start();
    for (int i = 2; i < srcFiles.size(); i++){
        //pool.addTask({srcDir + srcFiles[i], tgtDir + srcFiles[i]});
    }
    pool.stop();
    
    /*
    if (access(srcDir.c_str(), 00) != 0){
        printf("Source directory doesn't exist or path isn't valid!\n");
        return EXIT_FAILURE;
    }
    
    if (access(tgtDir.c_str(), 00) != 0){
        printf("Target directory doesn't exist, will attempt to create it.");
        std::string mkdirCmd = "mkdir -p " + tgtDir;
        const int dir = system(mkdirCmd.c_str());
        switch (dir){
            case -1:
                printf("Could not execute command to create target dir!");
                return 1;
                break;
            case 0:
                printf("Target directory successfully created!");
                break;
            case 1:
                printf("Permission denied when creating new directory");
        }
    }
    */
    
    return 0;
}
