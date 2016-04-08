#### Question 9

You will be implementing the following methods in the `BinaryTree` class:

- `int sumNodes() const;`

Write a function `sumNodes()` that returns the sum of all the nodes in a binary
tree.

```
    9
   / \
  3   2
 / \   \
4   1   6
```

`sumNodes()` on the above tree should produce:

```
9 + 3 + 2 + 4 + 1 + 6 = 25
```

If the tree is empty, `sumNodes()` should return 0.

**Write your solution in `binarytree_q9.cpp`.**


- - -

#### Question 10

You will be implementing the following methods in the `BinaryTree` class:

- `vector<vector<int>> findPaths(int goal) const;`

Given a binary tree and an integer `goal`, write a function `findPaths(int
goal)` that returns a list of all root-to-leaf paths (starting at the root and ending in a leaf) in the tree where
the nodes' elements on the path sum to `goal`.

For example, if the binary tree is:

```
        _10_
       /    \
     11      9
    /  \    / \
   8    4  6   5
  /
 7
```

and `goal = 25`, your code should return:

`[[10, 11, 4],  [10, 9, 6]]`

Please make sure you return a vector of vectors of ints (i.e.
`vector<vector<int>>`) where the `int`s are the values of the nodes' elements
in the paths.

You may assume that the binary tree is composed of only non-negative integers.

**Write your solution in `binarytree_q10.cpp`.**
