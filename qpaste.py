#! /usr/bin/env python3

import os

def complain(string):
    print(string)

def update_all():
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
                
def add_to_clipboard(string_to_add):
    assert type(string_to_add) is str
    os.system("echo {} | clip".format(string_to_add.strip()))

def main():
    if os.name != "nt":
        return complain(
            "Your OS is not recognized as Windows.\n" +
            "Running this on any other Operating System wont really work")

    lst = update_all()
    num = input("Type number 1-{} to add it to clipboard: ".format(len(lst)))
    if num.isdigit() and 1 <= int(num) <= len(lst):
    add_to_clipboard(lst[int(num)-1])
    
        

if __name__ == "__main__":
    main()
