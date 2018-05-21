//
//  Node.cpp
//  buddy_system
//
//  Created by 以明 on 2018/5/19.
//  Copyright © 2018年 以明. All rights reserved.
//

#include "Node.h"

Node::~Node()
{
    //delete left;
    //delete right;
    cout << "Delete!!" << endl;
}

bool Node::isLeaf()
{
    return left == nullptr && right == nullptr;
}
