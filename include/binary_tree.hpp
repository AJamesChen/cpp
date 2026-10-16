#pragma once

#include <memory>
#include <utility>

// Unbalanced binary search tree. Equivalent keys update the existing value.
// Keys must provide a strict weak ordering through operator<.
template <typename K, typename D> class Tree {
  public:
    Tree() = default;
    ~Tree() { clear(); }

    Tree(const Tree&) = delete;
    Tree& operator=(const Tree&) = delete;
    Tree(Tree&&) noexcept = default;
    Tree& operator=(Tree&& other) noexcept {
        if (this != &other) {
            clear();
            root = std::move(other.root);
        }
        return *this;
    }

    void insert(const K& key, const D& data) {
        auto* current = &root;
        while (*current) {
            auto& node = **current;
            if (key < node.key) {
                current = &node.left;
            } else if (node.key < key) {
                current = &node.right;
            } else {
                node.data = data;
                return;
            }
        }
        *current = std::make_unique<Node>(key, data);
    }

    // Returned pointers remain valid until the owning node is destroyed.
    D* find(const K& key) { return const_cast<D*>(std::as_const(*this).find(key)); }

    const D* find(const K& key) const {
        const auto* current = root.get();
        while (current) {
            if (key < current->key) {
                current = current->left.get();
            } else if (current->key < key) {
                current = current->right.get();
            } else {
                return &current->data;
            }
        }
        return nullptr;
    }

  private:
    struct Node {
        K key;
        D data;
        std::unique_ptr<Node> left, right;

        Node(const K& key, const D& data) : key(key), data(data) {}
    };

    void clear() noexcept {
        while (root) {
            if (root->left) {
                // Rotate the left child up without allocating or recursing.
                auto left = std::move(root->left);
                root->left = std::move(left->right);
                left->right = std::move(root);
                root = std::move(left);
            } else {
                // Detach the remaining child before destroying this node.
                auto node = std::move(root);
                root = std::move(node->right);
            }
        }
    }

    std::unique_ptr<Node> root;
};
