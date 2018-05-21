//
//  MemTree.cpp
//  buddy_system
//
//  Created by 以明 on 2018/5/19.
//  Copyright © 2018年 以明. All rights reserved.
//

#include "MemTree.h"

MemTree::MemTree()
{
    cout << "Unit : byte; Input is refined as the exponential of 2" << endl
        << "Type in the maximum size of memory you wanna allocate: ";
    cin >> max_size;
    head = new Node(max_size);
    //head->size = max_size;
}

void MemTree::request()
{
    string name;
    int s;
    bool settled(false);
    cout << "Type in the name of the process: " << endl;
    getline(cin, name);
    cout << "Type in the size of memory you wanna allocate: ";
    cin >> s;
    request_help(s, name, settled, head);
}

void MemTree::request_help(int s, string name, bool& settled, Node* cur)
{
    if (!cur) {
        return;
    }
    // this process has already been allocated
    if (settled) {
        return;
    }
    // this block of memory has already been allocated
    if (cur->allocated) {
        return;
    }
    if (s > cur->size) {
        cout << "Boundary error!!!!" << endl;
    }
    else if (cur->isLeaf() && s > cur->size / 2 && s <= cur->size) {
        cur->allocated = true;
        cur->alloc_size = s;
        settled = true;
        cur->name = name;
    }
    else {
        if (!cur->left) {
            cur->left = new Node(cur->size / 2);
            //cur->left->size = cur->size / 2;
        }
        if (!cur->right) {
            cur->right = new Node(cur->size / 2);
            //cur->right->size = cur->size / 2;
        }
        // first left, then right
        request_help(s, name, settled, cur->left);
        request_help(s, name, settled, cur->right);
    }
}

void MemTree::release()
{
    string name;
    cout << "Type in the name of the process you wanna release: " << endl;
    getline(cin, name);
    release_help(name, head);
    //delete_node(name, head);
    //reorganize(head);
}

void MemTree::release_help(string name, Node* cur)
{
    if (!cur) {
        return;
    }
    release_help(name, cur->left);
    release_help(name, cur->right);
    if (!cur->isLeaf()) {
        // find the node at left leaf
        if (cur->left && cur->left->name == name) {
            delete cur->left;
            cur->left = nullptr;
            // if the right leaf is not allocated, then release it too
            if (cur->right && cur->right->isLeaf() && !cur->right->allocated) {
                delete cur->right;
                cur->right = nullptr;
            }
        }
        // find the node at right leaf
        else if (cur->right && cur->right->name == name) {
            delete cur->right;
            cur->right = nullptr;
            // if the left leaf is not allocated, then release it too
            if (cur->left && cur->left->isLeaf() && !cur->left->allocated) {
                delete cur->left;
                cur->left = nullptr;
            }
        }
        // reorganizing : unallocated right leaf
        else if (!cur->left && cur->right && cur->right->isLeaf() && !cur->right->allocated) {
            delete cur->right;
            cur->right = nullptr;
        }
        // reorganizing : unallocated left leaf
        else if (!cur->right && cur->left && cur->left->isLeaf() && !cur->left->allocated) {
            delete cur->left;
            cur->left = nullptr;
        }
        // reorganizing : unallocated left leaf and right leaf
        else if (cur->left && cur->left->isLeaf() && !cur->left->allocated && cur->right && cur->right->isLeaf() && !cur->right->allocated) {
            delete cur->left;
            cur->left = nullptr;
            delete cur->right;
            cur->right = nullptr;
        }
    }
}

void MemTree::display()
{
    display_help(head);
}

void MemTree::display_help(Node* p)
{
    if (!p) {
        return;
    }
    if (p->isLeaf()) {
        if (p->allocated) {
            cout << p->name << " : " << p->alloc_size << " in " << p->size << endl;
        }
        else {
            cout << "Unallocated : " << p->size << endl;
        }
    }
    display_help(p->left);
    display_help(p->right);
}
