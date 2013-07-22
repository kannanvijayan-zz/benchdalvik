
#include <sys/time.h>
#include <stddef.h>
#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <algorithm>

double DoubleTime() {
    struct timeval tv;
    gettimeofday(&tv, NULL);
    return (double)tv.tv_sec + (((double)tv.tv_usec) / 1000000);
}

struct TreeNode {
    TreeNode *left;
    TreeNode *right;
    int item;

    inline TreeNode(TreeNode *l, TreeNode *r, int i)
      : left(l), right(r), item(i)
    {}

    ~TreeNode() {
        if (left)
            delete left;
        if (right)
            delete right;
    }

    inline int itemCheck() {
        if (!left)
            return item;
        return item + left->itemCheck() - right->itemCheck();
    }
};

TreeNode *bottomUpTree(int item, int depth) {
    if (depth > 0) {
        return new TreeNode(bottomUpTree(2*item-1, depth-1),
                            bottomUpTree(2*item, depth-1),
                            item);
    }
    return new TreeNode(NULL, NULL, item);
}


static volatile int32_t ret = 0;
static volatile int32_t check = 0;

void runBinaryTrees() {
    for ( int n = 4; n <= 7; n += 1 ) {
        int minDepth = 4;
        int maxDepth = std::max(minDepth + 2, n);
        int stretchDepth = maxDepth + 1;
        
        TreeNode *tn = bottomUpTree(0,stretchDepth);
        check = tn->itemCheck();
        delete tn;
        
        TreeNode *longLivedTree = bottomUpTree(0,maxDepth);
        for (int depth=minDepth; depth<=maxDepth; depth+=2){
            int iterations = 1 << (maxDepth - depth + minDepth);

            check = 0;
            for (int i=1; i<=iterations; i++){
                TreeNode *t1 = bottomUpTree(i,depth);
                check += t1->itemCheck();
                delete t1;
                TreeNode *t2 = bottomUpTree(i,depth);
                check += t2->itemCheck();
                delete t2;
            }
        }
        ret = longLivedTree->itemCheck();
        delete longLivedTree;
    }
}


int main() {
    double d1 = DoubleTime();
    for (int i = 0; i < 1000; i++) {
        runBinaryTrees();
    }
    double d2 = DoubleTime();
    fprintf(stderr, "CXX Time: %lf  (count=%d)\n", (d2 - d1), check);
    return 0;
}
