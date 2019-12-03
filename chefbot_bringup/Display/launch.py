from Tkinter import *
import os

master = Tk()
master.title("First Page")
topFrame = Frame(master, bg='black')
topFrame.pack()


def driverLaunch():
	print("OK!")
   	os.system("bash start.sh")

def exitLaunch():
	os.system("bash exit.sh")

def programLaunch():
	os.system("bash program.sh")


b1 = Button(topFrame, text="ON", command=driverLaunch, padx=10)


b2 = Button(topFrame, text="Run", command=programLaunch, padx=10)


b3 = Button(topFrame, text="OFF", command=exitLaunch, padx=10)


b1.grid(column=2, row = 1)
b2.grid(column=4, row = 1)
b3.grid(column=6, row = 1)

topFrame.grid_columnconfigure(4, minsize=100)

master.mainloop()