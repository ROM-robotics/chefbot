from Tkinter import *
import os

master = Tk()

master.title("First Page")
topFrame = Frame(master,bg="black")
master.configure(background="black")
master.geometry("600x200")

master.overrideredirect(True)
master.overrideredirect(False)
topFrame.pack()

def startLaunch():
   	os.system("bash start.sh")

b1 = Button(topFrame, text="START", command=startLaunch, padx=40, pady=40 ,bg='blue' ,bd='5',fg='white', font=('Times New Roman','30'))

b2 = Button(topFrame, text="EXIT", command=master.quit, padx=40, pady=40 ,bg='red' ,bd='5' ,fg='white', font=('Times New Roman','30'))


b1.grid(column=1,row=1)
b2.grid(column=2,row=1)

topFrame.grid_columnconfigure(2, minsize=300)

master.mainloop()