/*************************************************************/
/*                BrowserHistory Definition                  */
/*************************************************************/
/* TODO: Implement the member functions of BrowserHistory    */
/*     This class uses a linked-list of WebPage structs to   */
/*     represent the schedule of web pages                   */
/*************************************************************/

#include "browserHistory.hpp"
#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>

using namespace std;

/*
 * Purpose: Constructor for empty linked list
 * @param none
 * @return none
 */
BrowserHistory::BrowserHistory() {
    head = nullptr;
}

/*
 * Purpose: Check if list is empty
 * @return true if empty; else false
 */
bool BrowserHistory::isEmpty() {
    return (head == NULL);
}

/*
 * Purpose: prints the current list of pages 
 * in the given format.
 * [ID::1]-(URL::url1) -> ... -> NULL
 * @param none
 * @return none
 */
void BrowserHistory::displayHistory() {

    if(head == 0) {
        cout << "== CURRENT BROWSER HISTORY ==\nEmpty History\nNULL\n===" << endl;
    } else {
        WebPage *tmp = head;
        cout << "== CURRENT BROWSER HISTORY ==\n";
        while(tmp != 0) {
          cout  <<  "[ID:: "  <<  tmp->id  <<  "]-(URL::"  <<  tmp->url  <<  ") -> ";
          tmp = tmp->next;
        }
        cout  <<  "NULL\n===\n";
    }

    
}

/*
 * Purpose: Add a new webpage to the browser history LL
 *   between the previous and the page that follows it in the list.
 * @param previousPage, the show that comes before the new page
 * @param newPage, the webpage to be added. 
 * @return none
 */
void BrowserHistory::addWebPage(WebPage* previousPage, WebPage* newPage) {
    if(previousPage == 0) {
        // add to begining of list
        newPage->next = head; // might need this
        head = newPage;
        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (HEAD)\n";
    } else {
        // add between previous and the page that follows it (ie. prev->next)
        newPage->next = previousPage->next;
        previousPage->next = newPage;
        cout << "adding: " << "[" << newPage->id << "]-" << newPage->url << " (prev: " << "[" << previousPage->id << "])\n";
    }

}

/*
 * Purpose: populates the BrowserHistory with the predetermined pages
 * @param none
 * @return none
 */
void BrowserHistory::buildBrowserHistory() {
  WebPage *newPage = new WebPage;
  WebPage *previousPage = new WebPage;
  previousPage = nullptr;
  newPage->url = "https://www.colorado.edu/";
  newPage->id = 10;
  newPage->views = 0;
  BrowserHistory::addWebPage(previousPage,newPage);

  previousPage = newPage;
  WebPage *newPage2 = new WebPage;
  newPage2->url = "https://www.wikipedia.org/";
  newPage2->id = 11;
  newPage2->views = 0;
  BrowserHistory::addWebPage(previousPage,newPage2);

  previousPage = newPage2;
  WebPage *newPage3 = new WebPage;
  newPage3->url = "https://brilliant.org/";
  newPage3->id = 12;
  newPage3->views = 0;
  BrowserHistory::addWebPage(previousPage,newPage3);

  previousPage = newPage3;
  WebPage *newPage4 = new WebPage;
  newPage4->url = "https://www.khanacademy.org/";
  newPage4->id = 13;
  newPage4->views = 0;
  BrowserHistory::addWebPage(previousPage,newPage4);

  previousPage = newPage4;
  WebPage *newPage5 = new WebPage;
  newPage5->url = "https://www.numberphile.com/";
  newPage5->id = 14;
  newPage5->views = 0;
  BrowserHistory::addWebPage(previousPage,newPage5);
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by ID and return a pointer to that node.
 * @param int id - ID of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByID(int id) {
    WebPage *ptr = head;
    while (ptr != 0) {
      if(ptr->id == id) {
        return ptr;
      }
      ptr = ptr->next;
    }
    return nullptr;
}


/*
 * Purpose: Search the BrowserHistory for the specified 
 * web page by the URL and return a pointer to that node.
 * @param string url - url of the web page to look for in LL.
 * @return pointer to node of page, or NULL if not found
 *
 */
WebPage* BrowserHistory::searchPageByURL(std::string url) {
    WebPage *tmp = head;
    while (tmp != 0) {
      if(tmp->url == url) {
        return tmp;
      }
      tmp = tmp->next;
    }
    return nullptr;
}

/*
 * Purpose: Give an owner to a web page.
 * @param receiver - name of the show that is receiving the rating
 * @param rating - the rating that is being given to a show
 * @return none
 */
void BrowserHistory::addOwner(std::string url, string owner) {
    WebPage *tmp = head;
    while (tmp != 0) {
      if(tmp->url == url) {
        tmp->owner = owner;
        cout << "The owner (" << tmp->owner << ") has been added for the ID - "<< tmp->id << "\n";
      }
      tmp = tmp->next;
    }
    if(BrowserHistory::searchPageByURL(url) == 0) {
      cout << "Page not found\n";
    }
    
}

void BrowserHistory::updateViews(string url) {
    WebPage *ptr = head;
    while (ptr != 0) {
      if(ptr->url == url) {
        ptr->views++;
      }
      ptr = ptr->next;
    }
}
