#!/usr/bin/env python3

from Tkinter import *
import os

def send():
	os.system("bash go.sh")

master = Tk()
master.title("Run Robot")

topFrame = Frame(master,bg="gray")
topFrame.pack()


Label(topFrame, text="X:",font=('Times New Roman','30'),bg="gray",fg="white").grid(row=1,column=0)
Label(topFrame, text="Y:",font=('Times New Roman','30'),bg="gray",fg="white").grid(row=2,column=0)

e1 = Entry(topFrame, width=25)
e2 = Entry(topFrame, width=25)

e1.grid(row=1, column=1)
e2.grid(row=2, column=1)

b1=Button(topFrame, text='Go', command=send, font=('Times New Roman','20'),bd='5').grid(row=3, column=2,pady=4)
b2=Button(topFrame, text='Quit', command=master.quit, font=('Times New Roman','20'),bd='5').grid(row=3, column=3, pady=4)

topFrame.grid_columnconfigure(2, minsize=100)
topFrame.grid_columnconfigure(0, minsize=100)


mainloop()