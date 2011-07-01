#ifndef GFORT_TREE_H_
#define GFORT_TREE_H_

#include <vector>

namespace GFort 
{

/// Tree Node class
template <class T>
class TreeNode : std::vector<TreeNode>
{
public:
    /// Constructor.
    TreeNode()                  { parent_ = NULL; }

    /// Gets the parent of the node
    T* Parent()                  { return parent; }

    /// Returns true if it is tree root
    bool IsRoot()               { return parent == NULL; }

    /// Sets the parent
    void SetParent(T* parent)   { parent_ = parent; }

    void AddChild(TreeNode* child)
    {
        child->SetParent(dynamic_cast<T*>(this));
		children_.push_back(child);
    }

private:
    // Stores the pointer of parent
    T*  parent_;
};

} // namespace

#endif // GFORT_TREE_H_
