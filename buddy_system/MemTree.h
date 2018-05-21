//
//  MemTree.h
//  buddy_system
//
//  Created by 以明 on 2018/5/19.
//  Copyright © 2018年 以明. All rights reserved.
//

#ifndef MemTree_h
#define MemTree_h
#include "Node.h"

class MemTree {
public:
    MemTree();
    void request();
    void release();
    void display();
private:
    void request_help(int s, string name, bool& settled, Node* cur);
    //void reorganize(Node* cur);
    //bool delete_node(string name, Node* cur);
    void release_help(string name, Node* cur);
    void display_help(Node* p);
    Node* head;
    int max_size;
};


#endif /* MemTree_h */
