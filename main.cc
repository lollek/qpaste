#ifdef _WIN32
#include <windows.h>
#include <winuser.h>
#endif

#include "QuickPaste.hh"

#ifdef _WIN32
int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
                   LPSTR lpCmdLine, int nCmdShow) {
  /* Hide self */
  AllocConsole(); 
  ShowWindow(FindWindowA("ConsoleWindowClass", NULL), 0);
#else
int main(void) {
#endif

  /* Start Parser/Paste app */
  QuickPaste app;
  return app.run();
}
