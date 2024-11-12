import tkinter as tk
from tkinter import messagebox
from tkcalendar import DateEntry

#root 
root = tk.Tk()
root.title("Ticket Booking")
root.geometry("400x600")
root.resizable(False,False)

#Header 
header = tk.Label(root,text="Book Train Ticket",font=("Arial",18,"bold"),bg="light blue",fg="black",pady=10)
header.pack(pady=10,fill=tk.X)

#Frame for input 
form_frame = tk.Frame(root)
form_frame.pack(pady=10,padx=20)

#User inputs:
#  1) Name
name_label = tk.Label(form_frame,text="Enter Name",font=("Arial",12))
name_label.grid(row=0,column=0)
name_entry = tk.Entry(form_frame,font=("Arial",12))
name_entry.grid(row=0,column=1)

#  2) Age
Age_label = tk.Label(form_frame,text="Enter Age",font=("Arial",12))
Age_label.grid(row=1,column=0)
Age_entry = tk.Entry(form_frame,font=("Arial",12))
Age_entry.grid(row=1,column=1)

#  3) Gender
Gender_label = tk.Label(form_frame,text="Select Gender",font=("Arial",12))
Gender_label.grid(row=3,column=0)
gender_var = tk.StringVar(value="Male")
Gender_entry = tk.OptionMenu(form_frame,gender_var,"Male","Female","Other")
Gender_entry.grid(row=3,column=1)

#  4) Train
Train_label = tk.Label(form_frame,text="Select Train",font=("Arial",12))
Train_label.grid(row=4,column=0)
Train_var = tk.StringVar(value="Train")
Train_entry = tk.OptionMenu(form_frame,Train_var,"Train 1","Train 2","Train 3","Train 4")
Train_entry.grid(row=4,column=1)

#  5)Date
Date_label = tk.Label(form_frame,text="Select Date",font=("Arial",12))
Date_label.grid(row=5,column=0)
Date_var = tk.StringVar(value="Male")
Date_entry = DateEntry(form_frame,Date_pattern = "dd/mm/yyyy")
Date_entry.grid(row=5,column=1)

def book_ticket():
    name = name_entry.get()
    age = Age_entry.get()
    gender = gender_var.get()
    train = Train_var.get()
    date = Date_entry.get()

    if name and age:
        messagebox.showinfo("Confirmation",f"Name : {name}\nAge : {age}\nGender :{gender}\nTrain :{train}\nDate: {date}")

    else:
        messagebox.showwarning("No data","Enter Valid Data")

#Booking Ticket
button = tk.Button(root,text="Book Ticket",font=("Arial",18,"bold"),command=book_ticket,bg="green",fg="black")
button.pack(pady=20)

#Footer
footer = tk.Label(root,text="Thank you for visiting this site",font=("Arial",8,"italic"),bg="light blue",fg="black")
footer.pack(fill=tk.X,pady=25,side=tk.BOTTOM)

root.mainloop()
