from Tkinter import *
import os

master = Tk()
master.title("First Page")
topFrame = Frame(master, bg='black', pady=30)
topFrame.pack()


def driverLaunch():
	print("OK!")
   	os.system("bash start.sh")

def exitLaunch():
	os.system("bash exit.sh")

def programLaunch():
	os.system("bash program.sh")


b1 = Button(topFrame, text="ON", command=driverLaunch, padx=50, pady=40 ,bg='green' ,bd='5',fg='white', font=('Times New Roman','40'))


b2 = Button(topFrame, text="Run", command=programLaunch, padx=50, pady=40 ,bg='blue' ,bd='5' ,fg='white', font=('Times New Roman','40'))


b3 = Button(topFrame, text="OFF", command=exitLaunch, padx=50, pady=40 ,bg='red' ,bd='5' ,fg='white', font=('Times New Roman','40'))


b1.grid(column=1, row = 1)
b2.grid(column=2, row = 1)
b3.grid(column=3, row = 1)

topFrame.grid_columnconfigure(2, minsize=300)

master.mainloop()