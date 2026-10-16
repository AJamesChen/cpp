#include "binary_tree.hpp"

#include <gtest/gtest.h>

#include <string>
#include <type_traits>
#include <utility>

static_assert(std::is_same_v<decltype(std::declval<Tree<int, int>&>().find(0)), int*>);
static_assert(std::is_same_v<decltype(std::declval<const Tree<int, int>&>().find(0)), const int*>);
static_assert(!std::is_copy_constructible_v<Tree<int, int>>);
static_assert(!std::is_copy_assignable_v<Tree<int, int>>);
static_assert(std::is_nothrow_move_constructible_v<Tree<int, int>>);
static_assert(std::is_nothrow_move_assignable_v<Tree<int, int>>);

TEST(BinaryTreeTest, EmptyTreeReturnsNull) {
    Tree<int, int> tree;
    EXPECT_EQ(tree.find(1), nullptr);
    EXPECT_EQ(std::as_const(tree).find(1), nullptr);
}

TEST(BinaryTreeTest, FindsRootAndNodesInBothSubtrees) {
    Tree<int, int> tree;
    for (int key : {5, 2, 8, 1, 3, 7, 9}) {
        tree.insert(key, key * 10);
    }
    for (int key : {5, 2, 8, 1, 3, 7, 9}) {
        ASSERT_NE(tree.find(key), nullptr);
        EXPECT_EQ(*tree.find(key), key * 10);
        ASSERT_NE(std::as_const(tree).find(key), nullptr);
        EXPECT_EQ(*std::as_const(tree).find(key), key * 10);
    }
    for (int key : {0, 4, 6, 10}) {
        EXPECT_EQ(tree.find(key), nullptr);
        EXPECT_EQ(std::as_const(tree).find(key), nullptr);
    }
}

TEST(BinaryTreeTest, DuplicateKeysUpdateValuesAndPreservePointers) {
    Tree<int, std::string> tree;
    for (int key : {5, 2, 8}) {
        tree.insert(key, "original");
    }
    for (int key : {5, 2, 8}) {
        auto* original = tree.find(key);
        ASSERT_NE(original, nullptr);
        tree.insert(key, "updated");
        EXPECT_EQ(tree.find(key), original);
        EXPECT_EQ(*original, "updated");
    }
}

TEST(BinaryTreeTest, FoundValuesCanBeModified) {
    Tree<std::string, int> tree;
    tree.insert("middle", 2);
    auto* value = tree.find("middle");
    ASSERT_NE(value, nullptr);
    *value = 42;
    tree.insert("first", 1);
    tree.insert("third", 3);
    EXPECT_EQ(tree.find("middle"), value);
    EXPECT_EQ(*std::as_const(tree).find("middle"), 42);
}

TEST(BinaryTreeTest, EquivalentKeysNeedOnlyLessThanComparison) {
    struct Key {
        int order;
        int identity;
        bool operator<(const Key& other) const { return order < other.order; }
    };
    Tree<Key, int> tree;
    tree.insert({1, 10}, 100);
    tree.insert({1, 20}, 200);
    ASSERT_NE(tree.find({1, 30}), nullptr);
    EXPECT_EQ(*tree.find({1, 30}), 200);
}

TEST(BinaryTreeTest, MoveConstructionTransfersOwnership) {
    Tree<int, int> source;
    source.insert(1, 10);
    auto* value = source.find(1);
    Tree<int, int> destination(std::move(source));
    EXPECT_EQ(destination.find(1), value);
    ASSERT_NE(destination.find(1), nullptr);
    EXPECT_EQ(*destination.find(1), 10);
    EXPECT_EQ(source.find(1), nullptr);
    source.insert(2, 20);
    ASSERT_NE(source.find(2), nullptr);
    EXPECT_EQ(*source.find(2), 20);
}

TEST(BinaryTreeTest, MoveAssignmentReplacesExistingContents) {
    Tree<int, int> source;
    source.insert(1, 10);
    Tree<int, int> destination;
    destination.insert(2, 20);
    auto* value = source.find(1);
    destination = std::move(source);
    EXPECT_EQ(destination.find(1), value);
    ASSERT_NE(destination.find(1), nullptr);
    EXPECT_EQ(*destination.find(1), 10);
    EXPECT_EQ(destination.find(2), nullptr);
    EXPECT_EQ(source.find(1), nullptr);
}

TEST(BinaryTreeTest, DeepTreesSupportLookupAndCleanupInBothDirections) {
    constexpr int count = 10000;
    for (int direction : {-1, 1}) {
        Tree<int, int> tree;
        for (int i = 0; i < count; ++i) {
            tree.insert(direction * i, i);
        }
        ASSERT_NE(tree.find(direction * (count - 1)), nullptr);
        EXPECT_EQ(*tree.find(direction * (count - 1)), count - 1);
        EXPECT_EQ(tree.find(direction * count), nullptr);
        // Move assignment must also clean up the old deep tree iteratively.
        tree = Tree<int, int>();
        EXPECT_EQ(tree.find(0), nullptr);
        for (int i = 0; i < count; ++i) {
            tree.insert(direction * i, i);
        }
        // Scope exit exercises destruction of a deep tree.
    }
}
