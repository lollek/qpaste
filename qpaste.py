#! /usr/bin/env python3

import os
import tkinter

class Popup(tkinter.Listbox):

    def __init__(self, master=None):
        tkinter.Listbox.__init__(self, master)
        master.title("qpaste")
        self.data = None
        for num, text in enumerate(self.refresh_data(), 1):
            self.insert(num, text)
        self.bind("<Double-Button-1>", lambda e:
                  self.add_to_clipboard(self.refresh_data()[int(self.curselection()[0])]))
        self.pack()

    #@staticmethod
    def refresh_data(self):
        if self.data is None:
            current_index = 0
            self.data = []
            with open("paste.cfg", encoding="utf-8") as f:
                for line in f:
                    if line[:7] == "~split~":
                        current_index += 1
                        self.data.append("")
                    elif current_index:
                        self.data[current_index-1] += line
        return self.data

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
    #pop.add_command(label="tst", command=main)
    #win.withdraw()
    pop.mainloop()        

if __name__ == "__main__":
    main()
