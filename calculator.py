import tkinter as tk

class Calculator:
    def __init__(self, master):
        self.master = master
        master.title("Calculator")

        self.display = tk.Entry(master, width=45, bd=8, font=('arial', 20, 'bold'), justify='right')
        self.display.grid(row=0, column=0, columnspan=4)
        self.display.insert(0, '0')

        # define buttons and their functionality
        self.button_1 = tk.Button(master, text='1', width=6, height=2, command=lambda: self.display.insert(tk.END, '1'))
        self.button_2 = tk.Button(master, text='2', width=6, height=2, command=lambda: self.display.insert(tk.END, '2'))
        self.button_3 = tk.Button(master, text='3', width=6, height=2, command=lambda: self.display.insert(tk.END, '3'))
        self.button_4 = tk.Button(master, text='4', width=6, height=2, command=lambda: self.display.insert(tk.END, '4'))
        self.button_5 = tk.Button(master, text='5', width=6, height=2, command=lambda: self.display.insert(tk.END, '5'))
        self.button_6 = tk.Button(master, text='6', width=6, height=2, command=lambda: self.display.insert(tk.END, '6'))
        self.button_7 = tk.Button(master, text='7', width=6, height=2, command=lambda: self.display.insert(tk.END, '7'))
        self.button_8 = tk.Button(master, text='8', width=6, height=2, command=lambda: self.display.insert(tk.END, '8'))
        self.button_9 = tk.Button(master, text='9', width=6, height=2, command=lambda: self.display.insert(tk.END, '9'))
        self.button_0 = tk.Button(master, text='0', width=6, height=2, command=lambda: self.display.insert(tk.END, '0'))

        self.button_add = tk.Button(master, text='+', width=6, height=2, command=lambda: self.display.insert(tk.END, '+'))
        self.button_subtract = tk.Button(master, text='-', width=6, height=2, command=lambda: self.display.insert(tk.END, '-'))
        self.button_multiply = tk.Button(master, text='*', width=6, height=2, command=lambda: self.display.insert(tk.END, '*'))
        self.button_divide = tk.Button(master, text='/', width=6, height=2, command=lambda: self.display.insert(tk.END, '/'))

        self.button_equal = tk.Button(master, text='=', width=6, height=2, command=self.calculate)
        self.button_clear = tk.Button(master, text='C', width=6, height=2, command=self.clear)

        # position the buttons on the grid
        self.button_1.grid(row=1, column=0)
        self.button_2.grid(row=1, column=1)
        self.button_3.grid(row=1, column=2)

        self.button_4.grid(row=2, column=0)
        self.button_5.grid(row=2, column=1)
        self.button_6.grid(row=2, column=2)

        self.button_7.grid(row=3, column=0)
        self.button_8.grid(row=3, column=1)
        self.button_9.grid(row=3, column=2)

        self.button_0.grid(row=4, column=0)
        self.button_clear.grid(row=4, column=1)
        self.button_equal.grid(row=4, column=2)

        self.button_add.grid(row=1, column=3)
        self.button_subtract.grid(row=2, column=3)
        self.button_multiply.grid(row=3, column=3)
        self.button_divide.grid(row=4, column=3)

    def calculate(self):
        try:
            expression = self.display.get()
            result = eval(expression)
            self.display.delete(0, tk.END)
            self.display.insert(tk.END, str(result))
        except:
            self.display.delete(0, tk.END)
            self.display.insert(tk.END, 'Error')

    def clear(self):
        self.display.delete(0, tk.END)
        self.display.insert(tk.END, '0')


root = tk.Tk()
calculator = Calculator(root)
root.mainloop()