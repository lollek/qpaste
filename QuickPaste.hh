#ifndef __QPASTE_H__
#define __QPASTE_H__

#include <map>
#include <string>

class QuickPaste {
  public:
    QuickPaste();

    int run();

  private:
    std::map<int, std::string> hash;

    int reloadConfig();
    int popupMenu();
    int pasteText(int num, bool reload);
    int setCopyText(int num);
};

#endif //__QPASTE_H__
