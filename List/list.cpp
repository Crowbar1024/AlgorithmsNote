#include <myheader.h>


// 160 easy 两个单链表，有个交点，找到这个交点
// 假设表1前半部分a，表2前半部分b，公共部分c（因为一个节点只有一个next，所以会有一个公共部分）
// 让指针p1走完表1后走表2，p2走完表2后走1
// a-c-b = b-c-a
// 所以至多会在第2次经过交点时碰头
ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
    if (headA == nullptr || headB == nullptr) return nullptr;
    ListNode *p1 = headA, *p2 = headB;
    while (p1 != p2) {
        p1 = p1->next;     // BUG1：为图方便用了三元赋值法，p1 = nullptr ? headB : p1->next 显然需要注意顺序，如果走完后都是空指针，那么就会直接返回空指针
        p2 = p2->next;
        if (p1 == p2) return p1;
        if (p1 == nullptr) p1 = headB;
        if (p2 == nullptr) p2 = headA;
    }
    return p1;
}


// 234 easy 判断一个链表是否是回文串
// 判断回文的递归解
// 用check把p递归到末尾，然后一层层往栈顶上走
// 本来是把第一个参数设置为外部的一个变量，但这样写更cool
// 因为递归调用了n次，所以空间复杂度是On
bool isPalindrome(ListNode* head) {
    return check(head, head);
}
bool check(ListNode*& head, ListNode* p) {
    if(!p) return true;
    bool isPal = check(head, p->next);
    if(!isPal || head->val != p->val) return false;
    head = head->next;  // 因为传进来的head是指针的引用，这是自上而下的更新
    return isPal;
}







// 328 medium 按照序号的奇偶顺序重新排列整个链表，奇前偶后。要求空间复杂度O(1)
// in-place操作，调整原链表的顺序就行了
ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr) return nullptr;
    ListNode *oddcur = head, *evencur = head->next, *record = evencur;
    while (evencur && evencur->next) {
        oddcur->next = oddcur->next->next;
        evencur->next = evencur->next->next;
        oddcur = oddcur->next;
        evencur = evencur->next;
    }
    oddcur->next = record;
    return head;
}




// 328 medium 按照序号的奇偶顺序重新排列整个链表，奇前偶后。要求空间复杂度O(1)
// in-place操作，调整原链表的顺序就行了
ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr) return nullptr;
    ListNode *oddcur = head, *evencur = head->next, *record = evencur;
    while (evencur && evencur->next) {
        oddcur->next = oddcur->next->next;
        evencur->next = evencur->next->next;
        oddcur = oddcur->next;
        evencur = evencur->next;
    }
    oddcur->next = record;
    return head;
}
