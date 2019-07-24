from Tkinter import *
import os

master = Tk()

master.title("Choose to run program")
topFrame = Frame(master,bg="black")
master.configure(background="black")

w, h = master.winfo_screenwidth(), master.winfo_screenheight()
master.overrideredirect(1)
master.geometry("%dx%d+0+0" % (w, h))

master.overrideredirect(True)
master.overrideredirect(False)
topFrame.pack()


def slamLaunch():
   	os.system("bash slam.sh")

def exitLaunch():
	os.system("bash exit.sh")

def programLaunch():
	os.system("bash program.sh")
	
def joystickLaunch():
	os.system("bash joystick.sh")

def faceLaunch():
	os.system("bash facedetect.sh")


b1 = Button(topFrame, text="SLAM", command=slamLaunch, padx=40, pady=40 ,bg='blue' ,bd='5',fg='white', font=('Times New Roman','40'), width=8, height=2)

b2 = Button(topFrame, text="REBOOT", command=exitLaunch, padx=40, pady=40 ,bg='red' ,bd='5' ,fg='white', font=('Times New Roman','40'), width=8)

b3 = Button(topFrame, text="Go To", command=programLaunch, padx=40, pady=40 ,bg='blue' ,bd='5' ,fg='white', font=('Times New Roman','40'), width=8)

b4 = Button(topFrame, text="JoyStick", command=joystickLaunch, padx=40, pady=40 ,bg='blue' ,bd='5' ,fg='white', font=('Times New Roman','40'), width=8)

b5 = Button(topFrame, text="Face\nDetection", command=faceLaunch, padx=40, pady=40 ,bg='blue' ,bd='5' ,fg='white', font=('Times New Roman','40'), width=8)

b1.grid(column=1, row = 1)
b5.grid(column=3, row = 1)
b3.grid(column=1, row = 2)
b4.grid(column=3, row = 2)
b2.grid(column=2, row = 3)

topFrame.grid_rowconfigure(2, minsize=250)
topFrame.grid_rowconfigure(1, minsize=250)
topFrame.grid_columnconfigure(2, minsize=100)


master.mainloop()
