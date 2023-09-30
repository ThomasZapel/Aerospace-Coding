#ifndef BROWSER_HISTORY_HPP
#define BROWSER_HISTORY_HPP

// Base class
#include "../library/BrowserHistoryBase.hpp"

class BrowserHistory : public BrowserHistoryBase
{
    public:
        BrowserHistory();
        ~BrowserHistory();
        int findDefectLength();
        void removeWebPages(int start, int end);
        void mergeTwoHistories(WebPage *headOne, WebPage * headTwo);
};

#endif