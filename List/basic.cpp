#include <myheader.h>


// 203 easy 删除所有为val的元素
ListNode* removeElements(ListNode* head, int val) {
    if (head == nullptr) return nullptr;
    ListNode dummy(INT_MIN);
    ListNode* cur = &dummy;
    cur->next = head;
    while (cur->next) {
        if (cur->next->val == val) {
            ListNode *tmp = cur->next;
            cur->next = tmp->next;
            delete tmp;
        } else cur = cur->next;
    }
    return dummy.next;
}

// NC25 easy 升序链表，删除所有重复的，让所有元素只出现一次
ListNode* deleteDuplicates(ListNode* head) {
    ListNode dummy(INT_MIN), *tail = &dummy;
    tail->next = head;
    while (head && head->next) {
        while (head && head->next && head->val == head->next->val) {
            head = head->next;
        }
        tail->next = head;
        tail = tail->next;
        head = head->next;
    }
    return dummy.next;
}

// NC24 medium 升序链表，删除所有重复的，只保留所有只出现一次的
// 难点在于要删掉全部，所以需要一个pre节点去记录前一个
ListNode* deleteDuplicates(ListNode* head) {
    ListNode dummy(INT_MIN), *tail = &dummy;
    tail->next = head;
    ListNode* pre = tail;
    while (head && head->next) {
        if (head->val != head->next->val) {
            pre = head;
        } else {
            while (head && head->next && head->val == head->next->val) {
                head = head->next;
            }
            pre->next = head->next;
        }
        head = head->next;
    }
    return dummy.next;
}


// 21 easy 合并两个有序链表
ListNode* mergeTwoLists(ListNode* l1, ListNode* l2) {
    ListNode dummy(INT_MIN), *cur = &dummy;
    while (l1 && l2) {
        if (l1->val < l2->val) {
            cur->next = l1;
            l1 = l1->next;
        } else {
            cur->next = l2;
            l2 = l2->next;
        }
        cur = cur->next;
    }
    cur->next = l1 ? l1 : l2;
    return dummy.next;
}


// 2 easy 两个链表（反过来就是个数）相加并输出
// 2-4-3 + 5-6-4 = 7-0-8
ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    ListNode dummy(INT_MIN), *tail = &dummy;
    int carry = 0;
    while (l1 || l2 || carry) {
        int sum = (l1 ? l1->val : 0) + (l2 ? l2->val : 0) + carry;
        carry = sum / 10;
        tail->next = new ListNode(sum % 10);  // 返回的是链表，需要保存
        if (l1) l1 = l1->next;
        if (l2) l2 = l2->next;
        tail = tail->next;
    }
    return dummy.next;
}

// 19 medium 删除倒数第n个点
// x0x0x p1先不走，p2先到0，然后两个指针再往后走
ListNode* removeNthFromEnd(ListNode* head, int n) {
    ListNode dummy(INT_MIN), *p1 = &dummy, *p2 = &dummy;
    p1->next = p2->next = head;
    while(n--) p2 = p2->next;
    // 让p1跑到第二个0前一个位置
    while (p2->next) {
        p1 = p1->next;
        p2 = p2->next;
    }
    ListNode *tmp = p1->next;
    p1->next = tmp->next;
    delete tmp;
    return dummy.next;
}


// 61 medium 链表向右移动k个单位，尾巴回到头，类似数组向右移动，返回新的链表
ListNode* rotateRight(ListNode* head, int k) {
    if (!head) return nullptr;
    ListNode *cur = head, *newHead = nullptr;
    int len = 0;
    while (cur) {
        cur = cur->next;
        len++;
    }
    k = k % len;
    if (!k) return head;
    int cnt = 1;
    for (cur = head; cur; cur = cur->next, cnt++) {
        if (cnt == len - k) {  // 把第len-k个节点开始，最后一个节点的next接到head即可
            ListNode *tmp = cur;
            newHead = cur->next;
            while (tmp->next) {
                tmp = tmp->next;
            }
            cur->next = nullptr;
            tmp->next = head;
            break;
        }
    }
    return newHead;
}

// NC23 对一个链表，给了一个pivot中点，让链表的小于它的放左边，大于等于右边，对次序没有要求
// 容易失误之处在于两段链表其中之一是空
ListNode* separateList(ListNode *head, int x) {
    if (!head || !head->next) return head;
    // l是小于的链表遍历的节点，lh是l的head
    ListNode *l = nullptr, *r = nullptr, *cur = head;
    ListNode *lh = nullptr, *rh = nullptr;
    while (cur) {
        if (cur->val < x) {
            if (!l) {
                l = cur;
                lh = l;
            } else {
                l->next = cur;
                l = l->next;
            }
        } else {
            if (!r) {
                r = cur;
                rh = r;
            } else {
                r->next = cur;
                r = r->next;
            }
        }
        cur = cur->next;
    }
    
    if (!lh) {
        r->next = nullptr;
        return rh;
    }
    l->next = rh;
    if (rh) {
        r->next = nullptr;
    }
    return lh;
}