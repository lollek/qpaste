#include <cstdlib>
#include <iostream>
#include <fstream>
#include <string>

#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#include <winable.h>
#endif

#include "QuickPaste.hh"

#define CONFIGNAME "QuickPaste.cfg"

using namespace std;

QuickPaste::QuickPaste() :
  hash()
{}

int QuickPaste::run() {
  /* Wait for keypress */
  for (;;) {
    if (GetAsyncKeyState(VK_LMENU)) {
      if (GetAsyncKeyState('C')) {
        popupMenu();
      } else {
        for (int i = 0; i < 10; ++i) {
          if (GetAsyncKeyState('0' + i)) {
            pasteText(i, false);
            break;
          }
        }
      }
    }
    Sleep(100);
  }
  return 0;
}

int QuickPaste::popupMenu() {
  if (reloadConfig() != 0) {
    return 1;
  }
  return 0;
}

int QuickPaste::pasteText(int num, bool reload) {
  if (reload) {
    if (reloadConfig() != 0) {
      return 1;
    }
  }
  if (setCopyText(num) != 0) {
    return 1;
  }

  INPUT KeyToSend[2];

  /* Control Key */
  KeyToSend[0].type = INPUT_KEYBOARD;
  KeyToSend[0].ki.wScan = 0;
  KeyToSend[0].ki.time = 0;
  KeyToSend[0].ki.dwExtraInfo = 0;
  KeyToSend[0].ki.wVk = VK_CONTROL;
  KeyToSend[0].ki.dwFlags = 0;

  /* V Key */
  KeyToSend[1].type = INPUT_KEYBOARD;
  KeyToSend[1].ki.wScan = 0;
  KeyToSend[1].ki.time = 0;
  KeyToSend[1].ki.dwExtraInfo = 0;
  KeyToSend[1].ki.wVk = 'V';
  KeyToSend[1].ki.dwFlags = 0;

  /* Send Keydown */
  SendInput(1, &KeyToSend[0], sizeof(INPUT));
  SendInput(1, &KeyToSend[1], sizeof(INPUT));

  /* Send Keyup */
  KeyToSend[0].ki.dwFlags = KEYEVENTF_KEYUP;
  KeyToSend[1].ki.dwFlags = KEYEVENTF_KEYUP;

  SendInput(1, &KeyToSend[1], sizeof(INPUT));
  SendInput(1, &KeyToSend[0], sizeof(INPUT));

  return 0;
}

int setCopyText(int num) {
  if (hash.find(num) == map<int, string>::end) {
    return 1;
  }
  size_t size = hash[num].size();
  char *ccopy;
  HGLOBAL hcopy;
  OpenClipboard(NULL);
  EmptyClipboard();
  hcopy = GlobalAlloc(GMEM_MOVEABLE, size + 1);
  ccopy = GlobalLock(hcopy);
  memcpy(ccopy, hash[num].c_str(), size);
  ccopy[size] = '\0';
  GlobalUnlock(hcopy);
  SetClipboardData(CF_TEXT, hcopy);
  return 0;
}

int QuickPaste::reloadConfig() {
 ifstream config(CONFIGNAME);
  if (!config) {
    cerr << "Error: Could not open " << CONFIGNAME << '\n';
    return 1;
  }

  string line;
  unsigned pos;

  getline(config, line);
  while (config) {
    if ((pos = line.find(";")) != string::npos) {
      int num = atoi(line.substr(0, pos).c_str());
      line = line.substr(pos + 1);
      if (0 <= num && num <= 9 && line.size()) {
        hash[num] = line;
      }
    }
    getline(config, line);
  }

  config.close();
  return 0;
}
