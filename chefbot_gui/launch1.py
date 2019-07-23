from Tkinter import *
import os

master = Tk()
master.title("First Page")
topFrame = Frame(master, bg='black', pady=350)

master.overrideredirect(True)
master.overrideredirect(False)
master.attributes('-fullscreen',True)

topFrame.pack()


def driverLaunch():
	print("OK!")
   	os.system("bash start.sh")

def exitLaunch():
	os.system("bash exit.sh")

def programLaunch():
	os.system("bash program.sh")


b1 = Button(topFrame, text="ON", command=driverLaunch, padx=40, pady=40 ,bg='blue' ,bd='5',fg='white', font=('Times New Roman','40'))

b2 = Button(topFrame, text="Go To", command=programLaunch, padx=40, pady=40 ,bg='green' ,bd='5' ,fg='white', font=('Times New Roman','40'))

b3 = Button(topFrame, text="OFF", command=exitLaunch, padx=40, pady=40 ,bg='red' ,bd='5' ,fg='white', font=('Times New Roman','40'))

b4 = Button(topFrame, text="JOYSTICK", padx=40, pady=40 ,bg='green' ,bd='5' ,fg='white', font=('Times New Roman','40'))

b5 = Button(topFrame, text="FaceDetection", padx=40, pady=40 ,bg='green' ,bd='5' ,fg='white', font=('Times New Roman','40'))




b1.grid(column=1, row = 1)
b2.grid(column=3, row = 1)
b3.grid(column=5, row = 1)
b4.grid(column=2, row = 2)
b5.grid(column=4, row = 2)

topFrame.grid_columnconfigure(10, minsize=500)

master.mainloop()