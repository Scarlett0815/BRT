#include <iostream>
#include <cstdio>

using namespace std;

struct Node{
    int parent;
    int child[2];
    //left dir = 0, right dir = 1
    int dir;
    int key;
    // 0 equals black, 1 equals red
    int color;
};

int root = 0;
struct Node node[51];
int node_index = 0;

// normal insertion
void NormalInsertion(){
    int pre_node = 0;
    int temp_node = root;
    //left direction = 0, right direction = 1
    int direction = 0;
    while (temp_node != 0){
        if (node[temp_node].key < node[node_index].key){
            pre_node = temp_node;
            temp_node = node[temp_node].child[1];
            direction = 1;
        }
        else{
            pre_node = temp_node;
            temp_node = node[temp_node].child[0];
            direction = 0;
        }
    }
    if (direction){
        node[pre_node].child[1] = node_index;
        node[node_index].child[0] = node[node_index].child[1] = 0;
        node[node_index].parent = pre_node;
        node[node_index].dir = 1;
    }
    else{
        node[pre_node].child[0] = node_index;
        node[node_index].child[0] = node[node_index].child[1] = 0;
        node[node_index].parent = pre_node;
        node[node_index].dir = 0;
    }
    return;
}

void Rotation(int temp_node){
    // the node reaches root
    if (temp_node == root){
        node[root].color = 0;
        return;
    }

    // no need for rotation
    if (node[node[temp_node].parent].color == 0)
        return;
    // consecutive red node occur
    // case 1: uncle is red
    if (node[node[node[node[temp_node].parent].parent].child[1 - node[node[temp_node].parent].dir]].color == 1){
        //cout << "case1\n";
        node[node[node[node[temp_node].parent].parent].child[1 - node[node[temp_node].parent].dir]].color = 0;
        node[node[temp_node].parent].color = 0;
        node[node[node[temp_node].parent].parent].color = 1;
        //cout << node[node[node[node[temp_node].parent].parent].parent].color << endl;
        Rotation(node[node[temp_node].parent].parent);
        //cout << node[root].color << endl;
        return;
    }

    // case 2: uncle is black
    if (node[node[node[node[temp_node].parent].parent].child[1 - node[node[temp_node].parent].dir]].color == 0){
        //B
        int pre_parent = node[temp_node].parent;
        //C
        int pre_pre_parent = node[node[temp_node].parent].parent;
        // case a: A < B < C
        if (node[temp_node].dir == 0 && node[pre_parent].dir == 0){
            node[pre_pre_parent].child[0] = node[pre_parent].child[1];
            node[pre_parent].dir = node[pre_pre_parent].dir;
            node[pre_parent].parent = node[pre_pre_parent].parent;
            node[node[pre_pre_parent].parent].child[node[pre_pre_parent].dir] = pre_parent;
            node[pre_parent].child[1] = pre_pre_parent;
            node[pre_pre_parent].dir = 1;
            node[pre_pre_parent].parent = pre_parent;
            node[pre_parent].color = 0;
            node[pre_pre_parent].color = 1;
            if (pre_pre_parent == root) root = pre_parent;
            return;
        }
        //case b: A > B > C
        if (node[temp_node].dir == 1 && node[pre_parent].dir == 1){
            node[pre_pre_parent].child[1] = node[pre_parent].child[0];
            node[pre_parent].dir = node[pre_pre_parent].dir;
            node[pre_parent].parent = node[pre_pre_parent].parent;
            node[node[pre_pre_parent].parent].child[node[pre_pre_parent].dir] = pre_parent;
            node[pre_parent].child[0] = pre_pre_parent;
            node[pre_pre_parent].dir = 0;
            node[pre_pre_parent].parent = pre_parent;
            node[pre_parent].color = 0;
            node[pre_pre_parent].color = 1;
            if (pre_pre_parent == root) root = pre_parent;
            return;
        }
        //case c: C > A > B
        if (node[temp_node].dir == 1 && node[pre_parent].dir == 0){
            node[pre_pre_parent].child[0] = node[temp_node].child[1];
            node[pre_parent].child[1] = node[temp_node].child[0];
            node[temp_node].dir = node[pre_pre_parent].dir;
            node[temp_node].parent = node[pre_pre_parent].parent;
            node[node[pre_pre_parent].parent].child[node[pre_pre_parent].dir] = temp_node;
            node[temp_node].child[1] = pre_pre_parent;
            node[temp_node].child[0] = pre_parent;
            node[pre_parent].parent = temp_node;
            node[pre_parent].dir = 0;
            node[pre_pre_parent].parent = temp_node;
            node[pre_pre_parent].dir = 1;
            node[temp_node].color = 0;
            node[pre_pre_parent].color = 1;
            if (pre_pre_parent == root) root = temp_node;
            return;
        }
        //case d: C < A < B
        if (node[temp_node].dir == 0 && node[pre_parent].dir == 1){
            node[pre_pre_parent].child[1] = node[temp_node].child[0];
            node[pre_parent].child[0] = node[temp_node].child[1];
            node[temp_node].dir = node[pre_pre_parent].dir;
            node[temp_node].parent = node[pre_pre_parent].parent;
            node[node[pre_pre_parent].parent].child[node[pre_pre_parent].dir] = temp_node;
            node[temp_node].child[0] = pre_pre_parent;
            node[temp_node].child[1] = pre_parent;
            node[pre_parent].parent = temp_node;
            node[pre_parent].dir = 1;
            node[pre_pre_parent].parent = temp_node;
            node[pre_pre_parent].dir = 0;
            node[temp_node].color = 0;
            node[pre_pre_parent].color = 1;
            if (pre_pre_parent == root) root = temp_node;
            return;
        }
    }
}

//tree create
void CreateTree(){
    char ch;
    node[0].parent = 0;
    node[0].child[0] = 0;
    node[0].child[1] = 0;
    node[0].dir = 0;
    node[0].color = 0;
    cout << "please input the elements of the tree" << endl;
    while((ch = getchar()) != '\n'){
        ungetc(ch, stdin);
        cin >> node[1 + node_index ++].key;
        // initial the root
        if (node_index == 1){
            node[1].parent = 0;
            node[1].child[0] = 0;
            node[1].child[1] = 0;
            node[1].dir = 0;
            node[1].color = 0;
            root = 1;
        }
        else{
            // the color of the insert node is red
            node[node_index].color = 1;
            NormalInsertion();
            Rotation(node_index);
        }
        getchar();
    }
    return;
}

void Print(int print_point, int depth){
    if (print_point == 0){
        return;
    }
    else{
        for (int i = 0;i < depth;i ++){
            cout << ' ';
        }
        cout << node[print_point].key << endl;
        Print(node[print_point].child[0], depth + 1);
        Print(node[print_point].child[1], depth + 1);
        return;
    }
    return;
}

int main(){
    CreateTree();
    Print(root, 0);
}