二分不一定要求对象有序，只要满足某种规律就行


我发现了二分的对象也有一点问题 如果是[2^n,2^(n+1)-1]，即完全二叉树的某一层的序号 那么mid = (l+r)/2， 并且l=mid;r=mid-1，会永远也取不到某些点 可以修改mid的求法，比如+1/2 或者让上界取不到等等 这些都需要思考