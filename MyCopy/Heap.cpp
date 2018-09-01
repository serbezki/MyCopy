//
//  Heap.cpp
//  MyCopy
//
//  Created by Juli on 26.08.18.
//  Copyright © 2018 Juli. All rights reserved.
//

#include <vector>
#include <iostream>
#include "Heap.h"

Heap::Heap(const vector<int> &_array){
    size = (int)_array.size();
    cout << "Size: " << size << endl;
    array = _array;
    
    // Produce a max heap.
    for (int i = size / 2; i >= 0; i--){
        // Root of subtree.
        int y = array[i];
        
        // 'c' is a child of 'y'.
        int c = 2 * i;
        
        while (c <= size){
            // heap[c] should be the larger sibling node.
            if (c < size && array[c] < array[c + 1]){
                c++;
            }
            
            // Should 'y' be in heap[c / 2]?
            if (y >= array[c]){
                // Yes.
                break;
            }
            
            // If not, then we move the child up.
            array[c / 2] = array[c];
            
            // Move down one level.
            c = c * 2;
        }
        
        array[c / 2] = y;
    }
}

void Heap::show(){
    for (int i = 0; i < size; i++){
        cout << array[i] << " ";
    }
    
    cout << endl;
}

