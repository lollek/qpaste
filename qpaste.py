#! /usr/bin/env python3

import os
import tkinter

class Popup(tkinter.Listbox):

    def __init__(self, master=None):
        tkinter.Listbox.__init__(self, master)
        master.title("qpaste")
        for num, text in enumerate(self.refresh_data()):
            self.insert(num+1, text)
        self.pack()

    @staticmethod
    def refresh_data():
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
    def add_to_clipboard(string_to_add):
        #assert type(string_to_add) is str
        os.system("echo {} | clip".format(string_to_add.strip()))

def main():
    if os.name != "nt":
        return print(
            "Your OS is not recognized as Windows.\n" +
            "Running this on any other Operating System wont really work")
    stdscr = tkinter.Tk()
    pop = Popup(master=stdscr)
    #win.withdraw()
    pop.mainloop()        

if __name__ == "__main__":
    main()
