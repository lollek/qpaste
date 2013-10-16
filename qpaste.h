#ifndef __QPASTE_H__
#define __QPASTE_H__

#include <stdlib.h>

typedef struct LisztT {
  char *one;
  char *two;
  char *three;
  char *four;
  char *five;
  char *six;
  char *seven;
  char *eight;
  char *nine;
  char *zero;
} LisztT;

/* Since getline is GNU only */
ssize_t GetLine(char **Lineptr, size_t *N, FILE *Stream);

/* Returns a new LisztRoot */
LisztT *LisztNewRoot();
/* Deletes a LisztRoot */
void LisztFreeRoot(LisztT *LisztRoot);
/* Add to a LisztRoot */
void LisztAdd(LisztT* LisztRoot, char *Line, size_t Size);

/* Hide the running process */
extern void Stealth();
/* Load config */
void FetchConfig(LisztT* LisztRoot);
/* Set clipboard text to NewText */
void SetCopyText(char *NewText);
/* Set boardboard text and then paste it */
void PasteText(char *NewText);
/* Wrapper for strlen */
inline size_t AuxStrLen(char *string);
/* Wrapper for strcat */
nline char *AuxStrCat(char *s1, const char *s2);
/* Show all loaded texts */
void PrintAllLists(LisztT* LisztRoot) {

/* Main */
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow);

#endif
