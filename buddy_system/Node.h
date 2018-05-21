//
//  Node.h
//  buddy_system
//
//  Created by 以明 on 2018/5/19.
//  Copyright © 2018年 以明. All rights reserved.
//

#ifndef Node_h
#define Node_h
#include <iostream>
#include <cmath>
#include <string>

using namespace std;

class MemTree;

class Node {
    friend class MemTree;
    private:
        // !!!!!! must initialize left and right pointer as nullptr !!!!!
        Node(int x = 0) : size(x),left(nullptr), right(nullptr), alloc_size(0), allocated(false) {}
        ~Node();
        bool isLeaf();
        int size;
        int alloc_size;
        bool allocated;
        string name;
        Node* left;
        Node* right;
};

#endif /* Node_h */
