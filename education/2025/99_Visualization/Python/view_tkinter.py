import tkinter as tk
from tkinter import messagebox

def say_hello():
    messagebox.showinfo("Greeting", "Hello, Tkinter!")

root = tk.Tk()
root.title("Tkinter Example")
root.geometry("300x200")
root.configure(bg="#222222")

label = tk.Label(root, text="Click the button:", fg="cyan", bg="#222222", font=("Arial", 14))
label.pack(pady=20)

button = tk.Button(root, text="Say Hello", command=say_hello, bg="orange", fg="white", font=("Arial", 12))
button.pack(pady=10)

root.mainloop()
