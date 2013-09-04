#! /usr/bin/env python3

import os
import tkinter

class Popup(tkinter.Frame):

    def __init__(self, master=None):
        tkinter.Frame.__init__(self, master)
        self.pack()
        self.show_yourself()
       
    def show_yourself(self):
        self.hi_there = tkinter.Button(self)
        self.hi_there["text"] = "Hello World\n(click me)"
        self.hi_there["command"] = self.say_hi
        self.hi_there.pack(side="top")

        self.QUIT = tkinter.Button(self, text="QUIT", fg="red",
                              command=root.destroy)
        self.QUIT.pack(side="bottom")
 
    @staticmethod
    def refresh_data(self):
        current_index = 0
        returnl = []
        with open("paste.cfg", encoding="utf-8") as f:
            for line in f:
                if line[:7] == "~split~":
                    current_index += 1
                    returnl.append("")
                elif current_index:
                    returnl[current_index-1] += line
        return returnl

    @staticmethod
    def add_to_clipboard(self, string_to_add):
        assert type(string_to_add) is str
        os.system("echo {} | clip".format(string_to_add.strip()))

def complain(string):
    print(string)

def main():
    if os.name != "nt":
        return complain(
            "Your OS is not recognized as Windows.\n" +
            "Running this on any other Operating System wont really work")
    stdscr = tkinter.Tk()
    stdscr.title("qpaste")
    pop = Popup(master=stdscr)
    #win.withdraw()
    pop.mainloop()
    """
    lst = update_all()
    num = input("Type number 1-{} to add it to clipboard: ".format(len(lst)))
    if num.isdigit() and 1 <= int(num) <= len(lst):
        add_to_clipboard(lst[int(num)-1])
    """
        

if __name__ == "__main__":
    main()
