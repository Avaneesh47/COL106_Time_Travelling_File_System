#ifndef FILE_HPP
#define FILE_HPP

#include <string>
#include <vector>
#include <ctime>

// Version (TreeNode) structure
struct TreeNode{
    public:
        int version_id;
        std::string content;
        std::string message;
        time_t created_timestamp;
        time_t snapshot_timestamp;
        TreeNode* parent;
        std::vector<TreeNode*> children;
        TreeNode();
        ~TreeNode();
};

// File structure
class File{
    public:
        TreeNode* root = new TreeNode();
        TreeNode* active_version = root;
        std::vector<TreeNode*> version_map;
        int total_versions;
        time_t modified_timestamp;
        File();
        ~File();
};

#endif