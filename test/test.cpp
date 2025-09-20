#include <catch2/catch_test_macros.hpp>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <random>

#include "AVL.h"

using namespace std;



TEST_CASE("AVL Tree rebalances itself on insertions", "[avl][rotations]") {

    SECTION("Single Left Rotation (Right-Right imbalance)") {
        AVL tree;
        tree.insert(10);
        tree.insert(20);
        tree.insert(30);

        std::vector<int> result = tree.inorder();
        REQUIRE(result == std::vector<int>{10, 20, 30});
    }

    SECTION("Single Right Rotation (Left-Left imbalance)") {
        AVL tree;
        tree.insert(30);
        tree.insert(20);
        tree.insert(10);

        std::vector<int> result = tree.inorder();
        REQUIRE(result == std::vector<int>{10, 20, 30});
    }

    SECTION("Double Rotation: Left then Right (Left-Right imbalance)") {
        AVL tree;
        tree.insert(30);
        tree.insert(10);
        tree.insert(20);

        std::vector<int> result = tree.inorder();
        REQUIRE(result == std::vector<int>{10, 20, 30});
    }

    SECTION("Double Rotation: Right then Left (Right-Left imbalance)") {
        AVL tree;
        tree.insert(10);
        tree.insert(30);
        tree.insert(20);

        std::vector<int> result = tree.inorder();
        REQUIRE(result == std::vector<int>{10, 20, 30});
    }
}

TEST_CASE("Incorrect Operations on AVL", "[invalid]") {
	AVL tree;

	SECTION("Remove from empty tree") {
		REQUIRE_NOTHROW(tree.remove(123));
		REQUIRE(tree.inorder().empty());
	}

	SECTION("Insert duplicate") {
		tree.insert(10);
		tree.insert(10);
		REQUIRE(tree.inorder() == std::vector<int>{10});
	}

	SECTION("Remove non-existent value") {
		tree.insert(20);
		REQUIRE_NOTHROW(tree.remove(999));
		REQUIRE(tree.inorder() == std::vector<int>{20});
	}

	SECTION("Insert negative value") {
		tree.insert(-5);
		REQUIRE(tree.inorder() == std::vector<int>{-5});
	}

	SECTION("Insert very large value") {
		tree.insert(INT_MAX);
		auto result = tree.inorder();
		REQUIRE_FALSE(result.empty());   // makes sure it has at least one element
		REQUIRE(result.back() == INT_MAX);
	}
}

TEST_CASE("Insert and remove at random", "[avl][stress]") {
    AVL tree;

    // make numbers 1 through 100
    std::vector<int> nums(100);
    std::iota(nums.begin(), nums.end(), 1);

    // insert them all
    for (int n : nums) {
        tree.insert(n);
    }

    // tree should have 100 elements in order
    auto afterInsert = tree.inorder();
    REQUIRE(afterInsert.size() == 100);
    REQUIRE(afterInsert == nums);

    // shuffle the list and pick 10 to delete
    std::random_device rd;
    std::mt19937 rng(rd());
    std::shuffle(nums.begin(), nums.end(), rng);

    std::vector<int> picked(nums.begin(), nums.begin() + 10);

    // remove them
    for (int n : picked) {
        tree.remove(n);
    }

    // build expected result: numbers 1..100 except the 10 we removed
    std::vector<int> expected;
    for (int n = 1; n <= 100; ++n) {
        if (std::find(picked.begin(), picked.end(), n) == picked.end()) {
            expected.push_back(n);
        }
    }

    // tree should now have 90 elements, all sorted
    auto afterRemove = tree.inorder();
    REQUIRE(afterRemove.size() == 90);
    REQUIRE(afterRemove == expected);
}
