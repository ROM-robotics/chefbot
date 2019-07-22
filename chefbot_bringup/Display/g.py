from tkinter import *

root = Tk() #makes a blank popup, under the variable name 'root'

topFrame = Frame(root,bg="darkblue")
topFrame.pack()


def tableOne():
    text.insert(INSERT,"Table One\n")
    print("Reach Table One.")

def tableTwo():
    text.insert(INSERT,"Table Two\n")
    print("Reach Table Two.")

def tableThree():
    text.insert(INSERT,"Table Three\n")
    print("Reach Table Three.")

def tableFour():
    text.insert(INSERT,"Table Four\n")
    print("Reach Table Four.")

def tableFive():
    text.insert(INSERT,"Table Five\n")
    print("Reach Table Five.")

def tableSix():
    text.insert(INSERT,"Table Six\n")
    print("Reach Table Six.")

def tableSeven():
    text.insert(INSERT,"Table Seven\n")
    print("Reach Table Seven.")

def tableEight():
    text.insert(INSERT,"Table Eight\n")
    print("Reach Table Eight.")

def tableNine():
    text.insert(INSERT,"Table Nine\n")
    print("Reach Table Nine.")

def tableTen():
    text.insert(INSERT,"Table Ten\n")
    print("Reach Table Ten.")



def goHome():
    text.insert(INSERT,"Home\n")
    print("Reach HOME.")

button1 = Button(topFrame, text='Table 1', fg='brown' ,command = tableOne ,pady=10 ,bg='sky blue')
button2 = Button(topFrame, text='Table 2', fg='brown' , command = tableTwo ,pady=10 ,bg='sky blue')
button3 = Button(topFrame, text='Table 3', fg='brown' ,command = tableThree  ,pady=10 ,bg='sky blue')
button4 = Button(topFrame, text='Table 4', fg='brown' , command = tableFour ,pady=10 ,bg='sky blue')
button5 = Button(topFrame, text='Table 5', fg='brown' ,command = tableFive ,pady=10 ,bg='sky blue')
button6 = Button(topFrame, text='Table 6', fg='brown' , command = tableSix ,pady=10 ,bg='sky blue')
button7 = Button(topFrame, text='Table 7', fg='brown' ,command = tableSeven  ,pady=10 ,bg='sky blue')
button8 = Button(topFrame, text='Table 8', fg='brown' , command = tableEight ,pady=10 ,bg='sky blue')
button9 = Button(topFrame, text='Table 9', fg='brown' ,command = tableNine ,pady=10 ,bg='sky blue')
button10 = Button(topFrame, text='Table 10', fg='brown' , command = tableTen ,pady=10 ,bg='sky blue')


button1.grid(column=1, row = 2)
button2.grid(column=1, row = 4)
button3.grid(column=1, row = 6)
button4.grid(column=2, row = 1)
button5.grid(column=2, row = 3)
button6.grid(column=2, row = 5)
button7.grid(column=2, row = 7)
button8.grid(column=3, row = 2)
button9.grid(column=3, row = 4)
button10.grid(column=3, row = 6)


topFrame.grid_columnconfigure(2, minsize=200)


text = Text(root, height=10, width=50,bg="darkblue",foreground="white")
text.pack()

root.mainloop()
 