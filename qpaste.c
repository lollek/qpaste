#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <windows.h> 
#include <winuser.h> 

#include "qpaste.h"

#define GETLINEBUFSIZE 256

ssize_t GetLine(char **Lineptr, size_t *N, FILE *Stream) {
  char Buffer[GETLINEBUFSIZE];
  char *EOFChecker = fgets(Buffer, GETLINEBUFSIZE, Stream);
  *N = strlen(Buffer) + 1; // Remove the +1?
  *Lineptr = (char *)realloc(*Lineptr, *N); // Add +1 for \0
  strncpy(*Lineptr, Buffer, *N);

  if (EOFChecker == NULL)
    return -1;
  return 0;
}

LisztT *LisztNewRoot() {
  LisztT *LisztRoot = (LisztT *)malloc(sizeof(LisztT));
  LisztRoot->one = NULL;
  LisztRoot->two = NULL;
  LisztRoot->three = NULL;
  LisztRoot->four = NULL;
  LisztRoot->five = NULL;
  LisztRoot->six = NULL;
  LisztRoot->seven = NULL;
  LisztRoot->eight = NULL;
  LisztRoot->nine = NULL;
  LisztRoot->zero = NULL;
  return LisztRoot;
}

void LisztFreeRoot(LisztT *LisztRoot) {
  free(LisztRoot->one);
  free(LisztRoot->two);
  free(LisztRoot->three);
  free(LisztRoot->four);
  free(LisztRoot->five);
  free(LisztRoot->six);
  free(LisztRoot->seven);
  free(LisztRoot->eight);
  free(LisztRoot->nine);
  free(LisztRoot->zero);
  free(LisztRoot);
}

void LisztAdd(LisztT* LisztRoot, char *Line, size_t Size) {
  char **ToEdit;
  switch (Line[0]) {
    case '1': ToEdit = &LisztRoot->one; break;
    case '2': ToEdit = &LisztRoot->two; break;
    case '3': ToEdit = &LisztRoot->three; break;
    case '4': ToEdit = &LisztRoot->four; break;
    case '5': ToEdit = &LisztRoot->five; break;
    case '6': ToEdit = &LisztRoot->six; break;
    case '7': ToEdit = &LisztRoot->seven; break;
    case '8': ToEdit = &LisztRoot->eight; break;
    case '9': ToEdit = &LisztRoot->nine; break;
    case '0': ToEdit = &LisztRoot->zero; break;
  }
  if (*ToEdit == NULL) {
    *ToEdit = (char *)malloc(Size + 1);
    strncpy(*ToEdit, Line, Size + 1);
  }
}

void Stealth() { 
  //HWND Stealth; 
  AllocConsole(); 
  ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
  //Stealth = FindWindowA("ConsoleWindowClass", NULL); 
  //ShowWindow(Stealth, 0); 
} 

void FetchConfig(LisztT* LisztRoot) {
  char *Line = NULL;
  FILE *File = NULL;
  size_t Size;

  if ((File = fopen("qpaste.cfg", "r")) == NULL) {
    MessageBox(NULL, "Couldn't open qpaste.cfg, exiting :(", "Note", MB_OK);
    exit(1);
  }

  while (GetLine(&Line, &Size, File) != -1) {
    if (Size > 4 && '1' <= Line[0] && Line[0] <= '9' && 
        Line[1] == '.' && Line[2] == ' ')
      LisztAdd(LisztRoot, Line, Size);
  }
  free(Line);
  fclose(File);
}

void SetCopyText(char *NewText) {
	size_t Size = strlen(NewText);
	char *CCopy;
	HGLOBAL HCopy;
	OpenClipboard(NULL);
	EmptyClipboard();
	HCopy = GlobalAlloc(GMEM_MOVEABLE, Size+1);
	CCopy = GlobalLock(HCopy);
	memcpy(CCopy, NewText, Size);
	CCopy[Size] = '\0';
	GlobalUnlock(HCopy);
	SetClipboardData(CF_TEXT, HCopy);
}

void PasteText(char *NewText) {
  // Might need to include <winable.h>
  // http://msdn.microsoft.com/en-us/library/windows/desktop/ms646310(v=vs.85).aspx
  INPUT KeysToSend[2];
  SetCopyText(NewText);

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

  //SendInput(2, KeyToSend, sizeof(INPUT));
}

inline size_t AuxStrLen(char *string) {
  return string == NULL ? 0 : strlen(string) + 1;
}
inline char *AuxStrCat(char *s1, const char *s2) {
  return s1 == NULL ? NULL : strcat(s1, s2);
}

void PrintAllLists(LisztT* LisztRoot) {
  size_t TextSize = (AuxStrLen(LisztRoot->one) +
                     AuxStrLen(LisztRoot->two) +
                     AuxStrLen(LisztRoot->three) +
                     AuxStrLen(LisztRoot->four) +
                     AuxStrLen(LisztRoot->five) +
                     AuxStrLen(LisztRoot->six) +
                     AuxStrLen(LisztRoot->seven) +
                     AuxStrLen(LisztRoot->eight) +
                     AuxStrLen(LisztRoot->nine) +
                     AuxStrLen(LisztRoot->zero));
  char *string = (char *)malloc(TextSize);
  strcpy(string, "\0");
  if (AuxStrCat(string, LisztRoot->one) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->two) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->three) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->four) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->five) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->six) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->seven) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->eight) == NULL)
    strcat(string, "\n");
  if (AuxStrCat(string, LisztRoot->nine) == NULL)
    strcat(string, "\n");
  AuxStrCat(string, LisztRoot->zero) == NULL

  MessageBox(NULL, string, "Note", MB_OK);
  free(string);
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, 
                    LPSTR lpCmdLine, int nCmdShow) {
  Stealth(); 
  LisztT *LisztRoot = LisztNewRoot(); //Make this an array of char pointers instead
  FetchConfig(LisztRoot);
  while (1) {
    if(GetAsyncKeyState(VK_LMENU)) {
      if (GetAsyncKeyState('C')) 
        PrintAllLists(LisztRoot);
      else if (GetAsyncKeyState('1') && LisztRoot->one != NULL)
        PasteText(LisztRoot->one + 3);
      else if (GetAsyncKeyState('2') && LisztRoot->two != NULL)
        PasteText(LisztRoot->two + 3);
      else if (GetAsyncKeyState('3') && LisztRoot->three != NULL)
        PasteText(LisztRoot->three + 3);
      else if (GetAsyncKeyState('4') && LisztRoot->four != NULL)
        PasteText(LisztRoot->four + 3);
      else if (GetAsyncKeyState('5') && LisztRoot->five != NULL)
        PasteText(LisztRoot->five + 3);
      else if (GetAsyncKeyState('6') && LisztRoot->six != NULL)
        PasteText(LisztRoot->six + 3);
      else if (GetAsyncKeyState('7') && LisztRoot->seven != NULL)
        PasteText(LisztRoot->seven + 3);
      else if (GetAsyncKeyState('8') && LisztRoot->eight != NULL)
        PasteText(LisztRoot->eight + 3);
      else if (GetAsyncKeyState('9') && LisztRoot->nine != NULL)
        PasteText(LisztRoot->nine + 3);
      else if (GetAsyncKeyState('0') && LisztRoot->zero != NULL)
        PasteText(LisztRoot->zero + 3);
    }
    Sleep(100);
  }
  LisztFreeRoot(LisztRoot);
  return 0;
}


