#include <iostream>
#include <fstream>
#include <cstdlib>
#include <string>
#include "../code_1/browserHistory.hpp"

using namespace std;

void displayMenu();

int main(int argc, char* argv[]) {

    if(argc>1) 
    {
        freopen(argv[1],"r",stdin);
    }

    BrowserHistory list;

    displayMenu();
    int menuChoice;
    cin >> menuChoice;
    while(menuChoice < 6) {
        switch(menuChoice) {
            // BUILD HISTORY //
            case 1:
              list.buildBrowserHistory();
              list.displayHistory();
              break;
            // DISPLAY HISTORY //
            case 2:
               list.displayHistory();
               break;
            // ADD WEB PAGE //
            case 3:
            {
                WebPage *newPage = new WebPage;
                cout << "Enter the new web page's url:" << endl;
                cin >> newPage->url;

                cout << "Enter the new web page's id:" << endl;
                cin >> newPage->id;
                while(list.searchPageByID(newPage->id) != 0) {
                    cout << "This ID already exists. Try again." << endl;
                    cout << "Enter the new web page's id:" << endl;
                    cin >> newPage->id;
                }

                cout << "Enter the previous page's url (or First):" << endl;
                string previous;
                cin >> previous;
                WebPage *previousPage = new WebPage;
                if(previous == "First") {
                    previousPage = nullptr;
                } else if(list.searchPageByURL(previous) != 0) {
                        previousPage = list.searchPageByURL(previous);
                } else {
                    while(list.searchPageByURL(previous) == 0) {
                        cout << "INVALID(previous page url)... Please enter a VALID previous page url!\nEnter the previous page's url (or First):\n";
                        cin >> previous;
                        if(previous == "First") {
                            previousPage = nullptr;
                            break;
                        }
                    }
                }
      
                list.addWebPage(previousPage,newPage);
                list.updateViews(newPage->url);
                break;
            }
            // ADD OWNER //
            case 4:
            {
                string url,owner;
                cout << "Enter url of the web page to add the owner:" << endl;
                cin >> url;
                while(list.searchPageByURL(url) == 0) {
                    cout << "Page not found\n";
                    cout << "Enter url of the web page to add the owner:" << endl;
                    cin >> url;
                }

                cout << "Enter the owner:";
                cin.ignore();
                getline(cin,owner);
                list.addOwner(url,owner);

                break;
            }
            // VIEW COUNT FOR A WEB PAGE //
            case 5:
                string url;
                cout << "Enter url of the web page to check the view count: " << endl;
                cin >> url;
                WebPage *site = new WebPage;
                while(list.searchPageByURL(url) == 0) {
                    cout << "Page not found. Try again.\nEnter url of the web page to check the view count: \n";
                    cin >> url;
                }
                site = list.searchPageByURL(url);
                cout << "View count for URL - "<< site->url << " is " << site->views << endl;
                break;       
        }
        displayMenu();
        menuChoice = 0;
        cin >> menuChoice;
    }
    cout << "Quitting...Goodbye!\n";
    return 0;
}




/************************************************
           Definitions for main_1.cpp
************************************************/
void displayMenu()
{
    cout << "Select a numerical option:" << endl;
    cout << "+=====Main Menu=========+" << endl;
    cout << " 1. Build history " << endl;
    cout << " 2. Display history " << endl;
    cout << " 3. Add web page " << endl;
    cout << " 4. Add owner" << endl;
    cout << " 5. View count for a web page" << endl;
    cout << " 6. Quit " << endl;
    cout << "+-----------------------+" << endl;
    cout << "#> ";
}
