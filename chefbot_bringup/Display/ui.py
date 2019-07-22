#!/usr/bin/env python3

from Tkinter import *
import os

def send():
	os.system("bash go.sh")

master = Tk()
master.title("Run Robot")

topFrame = Frame(master)
topFrame.pack()


Label(topFrame, text="X:").grid(row=1,column=0)
Label(topFrame, text="Y:").grid(row=2,column=0)

e1 = Entry(topFrame)
e2 = Entry(topFrame)

e1.grid(row=1, column=1)
e2.grid(row=2, column=1)

b1=Button(topFrame, text='Quit', command=master.quit).grid(row=3, column=5, pady=4)
b2=Button(topFrame, text='Go', command=send).grid(row=3, column=4,pady=4)

topFrame.grid_columnconfigure(0, minsize=100)

mainloop()