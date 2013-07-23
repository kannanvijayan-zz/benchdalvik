
import java.util.Date;

public class BinaryTrees
{
    static class TreeNode
    {
        public TreeNode left;
        public TreeNode right;
        public int item;

        TreeNode(TreeNode l, TreeNode r, int i)
        {
            left = l;
            right = r;
            item = i;
        }

        int itemCheck() {
            if (left == null)
                return item;
            return item + left.itemCheck() - right.itemCheck();
        }
    }

    static TreeNode bottomUpTree(int item, int depth) {
        if (depth > 0) {
            return new TreeNode(bottomUpTree(2*item-1, depth-1),
                                bottomUpTree(2*item, depth-1),
                                item);
        }
        return new TreeNode(null, null, item);
    }

    static volatile int ret = 0;
    static volatile int check = 0;

    static void runBinaryTrees() {
        for ( int n = 4; n <= 7; n += 1 ) {
            int minDepth = 4;
            int maxDepth = Math.max(minDepth + 2, n);
            int stretchDepth = maxDepth + 1;
            
            TreeNode tn = bottomUpTree(0,stretchDepth);
            check = tn.itemCheck();
            
            TreeNode longLivedTree = bottomUpTree(0,maxDepth);
            for (int depth=minDepth; depth<=maxDepth; depth+=2){
                int iterations = 1 << (maxDepth - depth + minDepth);

                for (int i=1; i<=iterations; i++){
                    TreeNode t1 = bottomUpTree(i,depth);
                    check += t1.itemCheck();
                    TreeNode t2 = bottomUpTree(i,depth);
                    check += t2.itemCheck();
                }
            }
            ret = longLivedTree.itemCheck();
        }
    }

    public static void main(String[] args) {
        Date d1 = new Date();
        for (int i = 0; i < 100; i++)
            runBinaryTrees();
        Date d2 = new Date();
        System.out.println("Java Time: " + ((d2.getTime() - d1.getTime()) / 1000.0) +
                           " (count=" + check + ")");
    }
}
