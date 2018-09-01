//
//  Heap.h
//  MyCopy
//
//  Created by Juli on 25.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//

#ifndef Heap_h
#define Heap_h

using namespace std;

class Heap{
    unsigned int size;
    vector<int> array;
    
public:
    Heap(const vector<int> &_array);
    void show();
};

#endif /* Heap_h */
