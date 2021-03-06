﻿using System;
using System.Collections.Generic;
using System.Diagnostics;
using System.Linq;
using System.Runtime.InteropServices;
using System.Text;
using System.Threading.Tasks;
using System.Windows.Forms;

namespace QPaste
{
    class KeyboardHook
    {
        private static IntPtr HookID = IntPtr.Zero;
        private static LowLevelKeyboardProc HookProcessPtr = HookCallback;
        public static Action FunPaste;
        public static Action FunCopy;
        private delegate IntPtr LowLevelKeyboardProc(int nCode, IntPtr wParam, IntPtr lParam);


        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr SetWindowsHookEx(int idHook, LowLevelKeyboardProc lpfn, IntPtr hMod, uint dwThreadId);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        [return: MarshalAs(UnmanagedType.Bool)]
        private static extern bool UnhookWindowsHookEx(IntPtr hhk);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr CallNextHookEx(IntPtr hhk, int nCode, IntPtr wParam, IntPtr lParam);

        [DllImport("kernel32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern IntPtr GetModuleHandle(string lpModuleName);

        [DllImport("user32.dll", CharSet = CharSet.Auto, SetLastError = true)]
        private static extern void keybd_event(byte bVk, byte bScan, uint dwFlags, UIntPtr dwExtraInfo);

        public static void Activate()
        {
            using (ProcessModule curModule = Process.GetCurrentProcess().MainModule)
            {
                const int WH_KEYBOARD_LL = 13;
                HookID = SetWindowsHookEx(WH_KEYBOARD_LL, HookProcessPtr, GetModuleHandle(curModule.ModuleName), 0);
            }
        }

        public static void Deactivate()
        {
            if (HookID == IntPtr.Zero)
                return;

            UnhookWindowsHookEx(HookID);
            HookID = IntPtr.Zero;
        }

        public static void SendPaste()
        {
            const int KEYEVENTF_EXTENDEDKEY = 0x0001;
            const int KEYEVENTF_KEYUP = 0x0002;
            const int VK_LCONTROL = 0xA2;
            const int V = 0x56;

            // Hold Control down and press C
            keybd_event(VK_LCONTROL, 0, KEYEVENTF_EXTENDEDKEY, UIntPtr.Zero);
            keybd_event(V, 0, KEYEVENTF_EXTENDEDKEY, UIntPtr.Zero);
            keybd_event(V, 0, KEYEVENTF_KEYUP, UIntPtr.Zero);
            keybd_event(VK_LCONTROL, 0, KEYEVENTF_KEYUP, UIntPtr.Zero);
        }

        private static IntPtr HookCallback(int nCode, IntPtr wParam, IntPtr lParam)
        {
            const int WM_KEYDOWN = 0x0100;
            if (nCode >= 0 && wParam == (IntPtr)WM_KEYDOWN && Control.ModifierKeys == (Keys.Control | Keys.Alt))
            {    
                Action action = null;
                switch((Keys)Marshal.ReadInt32(lParam))
                {
                    case Keys.C: action = FunPaste; break;
                    case Keys.X: action = FunCopy; break;
                }
                if (action != null)
                {
                    Deactivate();
                    action();
                    Activate();
                }
            }
            return CallNextHookEx(HookID, nCode, wParam, lParam);
        }
    }
}
