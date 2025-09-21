#include "../include/File.hpp"

using namespace std;

TreeNode::TreeNode(){
    version_id = 0;
    content = "";
    message = "";
    created_timestamp = time(nullptr);
    parent = nullptr;
};

TreeNode::~TreeNode(){
    for(TreeNode* child: children){
        delete child;
    }
    children.clear();
};

File::File(){
    root->message = "Root";
    root->snapshot_timestamp = time(nullptr);
    active_version = root;
    version_map.push_back(root);
    total_versions = 1;
};

File::~File(){
    delete root;
    version_map.clear();
};