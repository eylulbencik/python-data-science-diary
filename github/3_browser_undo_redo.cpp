#include <iostream>
#include <string>
using namespace std;

const int MAX_SIZE = 100;

struct BrowserHistory {
    string backStack[MAX_SIZE];
    int backTop;
    string forwardStack[MAX_SIZE];
    int forwardTop;
    string currentPage;
};

void initBrowser(BrowserHistory& browser) {
    browser.backTop = -1;
    browser.forwardTop = -1;
    browser.currentPage = "";
}

bool isBackEmpty(BrowserHistory& browser) {
    return browser.backTop == -1;
}

bool isForwardEmpty(BrowserHistory& browser) {
    return browser.forwardTop == -1;
}

void visitPage(BrowserHistory& browser, string url) {
    if (!browser.currentPage.empty()) {
        browser.backTop++;
        browser.backStack[browser.backTop] = browser.currentPage;
    }
    
    browser.currentPage = url;
    browser.forwardTop = -1;
    
    cout << "Visited: " << url << endl;
}

void goBack(BrowserHistory& browser) {
    if (isBackEmpty(browser)) {
        cout << "No pages in back history\n";
        return;
    }
    
    browser.forwardTop++;
    browser.forwardStack[browser.forwardTop] = browser.currentPage;
    
    browser.currentPage = browser.backStack[browser.backTop];
    browser.backTop--;
    
    cout << "Back to: " << browser.currentPage << endl;
}

void goForward(BrowserHistory& browser) {
    if (isForwardEmpty(browser)) {
        cout << "No pages in forward history\n";
        return;
    }
    
    browser.backTop++;
    browser.backStack[browser.backTop] = browser.currentPage;
    
    browser.currentPage = browser.forwardStack[browser.forwardTop];
    browser.forwardTop--;
    
    cout << "Forward to: " << browser.currentPage << endl;
}

void printCurrentPage(BrowserHistory& browser) {
    if (browser.currentPage.empty())
        cout << "No page loaded\n";
    else
        cout << "Current page: " << browser.currentPage << endl;
}

void printHistory(BrowserHistory& browser) {
    cout << "\n--- Browser History ---\n";
    
    cout << "Back stack: ";
    if (isBackEmpty(browser)) {
        cout << "empty";
    } else {
        for (int i = browser.backTop; i >= 0; i--) {
            cout << browser.backStack[i];
            if (i > 0) cout << " | ";
        }
    }
    cout << endl;
    
    printCurrentPage(browser);
    
    cout << "Forward stack: ";
    if (isForwardEmpty(browser)) {
        cout << "empty";
    } else {
        for (int i = browser.forwardTop; i >= 0; i--) {
            cout << browser.forwardStack[i];
            if (i > 0) cout << " | ";
        }
    }
    cout << endl;
}

int main() {
    BrowserHistory browser;
    initBrowser(browser);
    
    cout << "=== Browser Navigation with Undo/Redo ===\n\n";
    
    visitPage(browser, "google.com");
    visitPage(browser, "youtube.com");
    visitPage(browser, "github.com");
    printHistory(browser);
    
    cout << "\n--- Going Back ---\n";
    goBack(browser);
    goBack(browser);
    printHistory(browser);
    
    cout << "\n--- Going Forward ---\n";
    goForward(browser);
    printHistory(browser);
    
    cout << "\n--- Visit New Page (clears forward history) ---\n";
    visitPage(browser, "stackoverflow.com");
    printHistory(browser);
    
    cout << "\n--- Try Forward (should fail) ---\n";
    goForward(browser);
    
    return 0;
}
