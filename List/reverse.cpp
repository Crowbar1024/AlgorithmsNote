#include <myheader.h>

// 206 easy 翻转整个链表
// 没说需要维护原来的链表
ListNode* reverseList(ListNode* head) {
    if (head == nullptr) return nullptr;
    ListNode *p1 = head, *p2 = head->next;
    // head ....p1 p2 ...
    // p2(head) ... p1
    while (p2) {  // p1一直指向原来head的那个节点，p2已经为空，head是原来最后的节点
        p1->next = p2->next;
        p2->next = head;
        head = p2;
        p2 = p1->next;
    }
    return head;
}

// 24 medium 交换每两个相邻的节点(12->21 34->43)
ListNode* swapPairs(ListNode* head) {
    ListNode dummy(INT_MIN), *cur = &dummy;
    cur->next = head;
    while (cur->next && cur->next->next) {
        ListNode* p1 = cur->next;
        ListNode *p2 = p1->next;
        p1->next = p2->next;
        p2->next = p1;
        cur->next = p2;
        cur = p1;
    }
    return dummy.next;
}

// NC02 (1 n) (2 n-1) ...
// 将链表头尾重新排序，n表示原最后一个
// 要求空间复杂度O1，事件On
// 感觉medium，很快想到，翻转后半部分，然后接下来的操作就是拼接
// tip1 非常关键，比如1(p1)->2->3(p2) 在进行拼接时，3->2，但2->3，产生环
// 所以一个简单的思路就是，切断前后两个将要拼接的链表
void reorderList(ListNode *head) {
    if (head == nullptr || head->next == nullptr || head->next->next == nullptr) return;
    ListNode *p1 = head, *p2 = head;
    while (p2->next != nullptr && p2->next->next != nullptr) {
        p1 = p1->next;
        p2 = p2->next->next;
    }
    ListNode *newHead = p1->next;  // 需要翻转链表的头节点
    p1->next = nullptr;  // tip1
    p1 = newHead;
    p2 = newHead->next;
    while (p2 != nullptr) {
        p1->next = p2->next;
        p2->next = newHead;
        newHead = p2;
        p2 = p1->next;
    }
    p1 = head;
    p2 = newHead;
    while (p2 != nullptr) {
        ListNode *tmp1 = p1->next, *tmp2 = p2->next;
        p1->next = p2;
        p2->next = tmp1;
        p1 = tmp1;
        p2 = tmp2;
    }
}


// 234 easy 判断一个链表是否是回文串
// 我的做法有点复杂，先把后半段翻转，再进行回文的判断，最后回复原始的顺序
// 举个例子，翻转后。会变成1->2->3->4<-5（链表的下半部分head是4，4的next是null）
// 或者1->2->3<-4这种形式（链表的下半部分head是3，3的next是null）
// 所以前一个节点一直指向原链表的下半部分的head，不需要做调整
bool isPalindrome(ListNode* head) {
    if (!head || head->next == nullptr) return true;
    ListNode *fastPtr = head, *slowPtr = head, *cur = head;
    while (fastPtr->next && fastPtr->next->next) {  // 这个边界条件确定了slowPtr->next的位置恰好是链表的下半部分
        fastPtr = fastPtr->next->next;
        slowPtr = slowPtr->next;
    }
    slowPtr = slowPtr->next;
    ListNode *p1 = slowPtr, *p2 = slowPtr->next;
    while (p2) {  // 翻转链表的下半部分
        p1->next = p2->next;
        p2->next = slowPtr;
        slowPtr = p2;
        p2 = p1->next;
    }
    ListNode *record = slowPtr;  // 翻转后，slowPtr是新的下半部分链表的head，即原链表的尾巴
    while (slowPtr) {  // 判断是否回文
        if (slowPtr->val != cur->val) return false;
        slowPtr = slowPtr->next;
        cur = cur->next;
    }
    p1 = record, p2 = record->next;
    while (p2) {  // 还原链表
        p1->next = p2->next;
        p2->next = record;
        record = p2;
        p2 = p1->next;
    }
    return true;
}


// 92 medium 在[m,n]范围内翻转整个链表
// 这种题我一般默认确实存在这个范围，所以代码里面没有写检查
ListNode* reverseBetween(ListNode* head, int m, int n) {
    if (head == nullptr || head->next == nullptr) return head;
    ListNode dummy(INT_MIN), *pre = &dummy;
    pre->next = head;
    for (int i = 0; i < m-1; i++) pre = pre->next;
    ListNode *p1 = pre->next, *tmp = p1, *p2 = p1->next;
    for (int i = 0; i < n-m; i++) {
        p1->next = p2->next;
        p2->next = tmp;
        tmp = p2;
        p2 = p1->next;
    }
    pre->next = tmp;
    return dummy.next;
}