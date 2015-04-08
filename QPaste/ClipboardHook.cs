using System;
using System.Collections.Generic;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows;
using System.Windows.Interop;

namespace QPaste
{
    class ClipboardHook
    {
        private const int WM_DRAWCLIPBOARD = 0x0308;
        private const int WM_CHANGECBCHAIN = 0x030D;

        private static HwndSource HwndSource;
        private static WindowInteropHelper InteropHelper;
        private static IntPtr NextEvent;
        public static Action<String> OnNewData = null;

        [DllImport("user32.dll", CharSet = CharSet.Auto)]
        private static extern int SendMessage(IntPtr hwnd, int wMsg, IntPtr wParam, IntPtr lParam);

        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        private static extern IntPtr SetClipboardViewer(IntPtr hWnd);

        [DllImport("User32.dll", CharSet = CharSet.Auto)]
        private static extern bool ChangeClipboardChain(IntPtr hWndRemove, IntPtr hWndNewNext);

        public static void Activate(Window masterWindow)
        {
            InteropHelper = new WindowInteropHelper(masterWindow);
            HwndSource = HwndSource.FromHwnd(InteropHelper.Handle);
            if (HwndSource != null)
                HwndSource.AddHook(MainWindowProc);

            NextEvent = SetClipboardViewer(HwndSource.Handle);
        }

        public static void Deactivate()
        {
            ChangeClipboardChain(HwndSource.Handle, NextEvent);
        }

        private static IntPtr MainWindowProc(IntPtr hwnd, int msg, IntPtr wParam, IntPtr lParam, ref bool handled)
        {
            switch (msg)
            {
                case WM_DRAWCLIPBOARD:
                    if (Clipboard.ContainsText(TextDataFormat.Text) && OnNewData != null)
                    {
                        String s = Clipboard.GetText(TextDataFormat.Text);
                        if (!String.IsNullOrEmpty(s))
                            OnNewData(Clipboard.GetText(TextDataFormat.Text));
                    }
                    SendMessage(NextEvent, msg, wParam, lParam);
                    break;

                case WM_CHANGECBCHAIN:
                    if (wParam == NextEvent)
                        NextEvent = lParam;
                    else
                        SendMessage(NextEvent, msg, wParam, lParam);
                    break;
            }

            return IntPtr.Zero;
        }
    }
}


