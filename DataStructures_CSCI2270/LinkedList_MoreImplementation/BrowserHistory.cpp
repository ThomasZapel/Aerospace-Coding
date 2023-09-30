
#include "BrowserHistory.hpp"

BrowserHistory::BrowserHistory() {
}

BrowserHistory::~BrowserHistory() {
}

/*
 * Purpose: Has to detect if a defect is present in the linkedlist pointed by head
 * @param none
 * @return integer length of defect if one exists. If defect not present return -1
 */
int BrowserHistory::findDefectLength() {
    BrowserHistory::buildBrowserHistory();
    WebPage *fast = new WebPage;
    WebPage *slow = new WebPage;

    fast = head;
    slow = head;
    fast = fast->next->next;
    slow = slow->next;


    while(fast != slow && fast != 0) {
        fast = fast->next;
        if(fast == 0) {
            return -1;
        } else {
            fast = fast->next;
            slow = slow->next;
        }

    }
    
    if(fast == slow) {
        slow = slow->next;
        int count = 0;
        while(slow->id != fast->id) {
            slow = slow->next;
            count++;
            if(slow->id == fast->id) {
                return count;
            }
        }
        return count;
    }
    
    if(fast == 0) {
        return -1;
    }
    return 0;
}

/*
 * Purpose: Has to remove all the WebPage nodes from [start, end] inclusive.
 * Has to print appropriate messages on cout like below if the linkedlist is empty
 * or if the values of start/ end are improper
 * follow the same order for couts in the writeup - check empty list first, then check wrong start/end values
 * @param integers start and end (1 based indexing not 0 based)
 * @return none
 */
void BrowserHistory::removeWebPages(int start, int end) {

    WebPage *curr = new WebPage;
    curr = head;
    int length = 0;
    while(curr != 0 ) {
        curr = curr->next;
        length++;
    }

    if(head == 0) {
        cout << "Browsing history is Empty" << endl;
    } else if(start < 1 || end > length || start > end) {
        cout << "Invalid start or end values" << endl;
        return;
    } else {
        if(start == 1) {
            curr = head;
            int count = 1;
            while(start <= count && end >= count) {
                WebPage *prev = curr;
                curr = curr->next;
                delete prev;
                count++;
            }
            head = curr;
            return;
        }
        WebPage *before = new WebPage;
        curr = head->next;
        before = head;
        int count = 2;
        while(curr != 0) {
            while(start <= count && end >= count) {
                WebPage *prev = curr;
                curr = curr->next;
                delete prev;    
                count++;
            }
            if(count > end) {
                before->next = curr;
                return;
            }
            before = curr;
            curr = curr->next;
            count++;
        }
    }
}


/*
 * Purpose: Interweave the webpages alternatively into a new linkedlist 
 * starting with the first webpage in the list one
 * Assign the head of the new interweaved list to the head of this BrowserHistory
 * DO NOT create new nodes and copy the data, just use the same nodes from one and two and change pointers
 * If one of them runs out of length append the remaining of the other one at end
 * @param two linkedlist heads one and two
 * @return none
 */
void BrowserHistory::mergeTwoHistories(WebPage *headOne, WebPage *headTwo) {

    if(headOne == 0 || headTwo == 0) {
        if(headOne == 0) {
            head = headTwo;
            return;
        }
        if(headTwo == 0) {
            head = headOne;
            return;
        }
    }
    
    head = headOne;
    WebPage *tmp = head;
    WebPage *curr1 = headOne;
    WebPage *curr2 = headTwo;


    while(tmp != 0) {
        if(curr1 == 0) {
            while(tmp != 0) {
                tmp->next = curr2;
                if(curr2 == 0) {
                    return;
                }
                curr2 = curr2->next;
                tmp = tmp->next;
            }
        }
        curr1 = curr1->next;
        tmp->next = curr2;
        if(curr2 == 0) {
            while(tmp != 0) {
                tmp->next = curr1;
                if(curr1 == 0) {
                    return;
                }
                curr1 = curr1->next;
                tmp = tmp->next;
            }
        }
        curr2 = curr2->next;
        tmp = tmp->next;
        tmp->next = curr1;
        tmp = tmp->next;
    }
}



