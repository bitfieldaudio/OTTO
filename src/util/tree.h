#pragma once

#include <functional>
#include <vector>
#include <memory>

namespace top1 {

class TreeNode {
public:
  virtual void visit(std::function<void(TreeNode&)> visitor) {
    visitor(*this);
  };
};

class NamedTreeNode : public TreeNode {
  std::string name;
  TreeNode node;
};

template<class T> cC
class TreeLeaf : TreeNode {
  T value;
};

class TreeBranch : public TreeNode {

  std::vector<std::shared_ptr<TreeNode>> children;

public:

  void visit(std::function<void(TreeNode&)> visitor) override {
    for (auto &child : children) {
      child->visit(visitor);
    }
  }

  virtual bool hasChildren() const {
    return !children.empty();
  }

  virtual void addChild(std::shared_ptr<TreeNode> child) {
    children.push_back(child);
  }

  TreeNode &operator[](uint i) {
    return children[i];
  }

  TreeNode &operator+=(TreeNode child) {
    addChild(child);
    return *this;
  }
};
}
Sofie
