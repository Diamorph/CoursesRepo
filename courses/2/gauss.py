import numpy as np
import matplotlib.pyplot as plt
import math
import numpy as np
import matplotlib.pyplot as plt
from tkinter import *
from tkinter import messagebox



CONTROL_POINTS_33 = [5.269,5.561,6.462,6.787,9.220,9.421,9.747,9.783,
            9.808, 12.425, 12.604, 13.512, 14.224]

def func_33(x):
    return round(np.exp(x) + x * np.log10(x) + x,3)

def get_finite_diff(y):
    diff = []
    for i in range(1, len(y)):
        diff.append(round(y[i] - y[i - 1],3))
    return diff


def get_finite_diff_matrix(y):
    diffs = [y]
    next_diff = y

    for i in range(len(y) - 1):
        next_diff = get_finite_diff(next_diff)
        diffs.append(next_diff)
    return diffs




def gauss(x_list,y_list,x):
    pos_0 = int(len(y_list)/2)
    x_0 = x_list[pos_0]
    print("pos_middle",pos_0)
    h = x_list[1] - x_list[0]
    res = y_list[pos_0]             #y0
    print("first ", res)
    q = (x - x_0) / h
    print("q = ", round(q,3))

    finite_diffs = get_finite_diff_matrix(y_list)
    n = len(finite_diffs)
    print(finite_diffs[0])
    print(finite_diffs[1])
    pos_0 = int(len(finite_diffs[1])/2)
    first_iter = finite_diffs[1][pos_0] * q    #q*delta(y_0)
    res+=first_iter
    print("first =", first_iter)
    print("res 0 + 1 = ", res)
    for i in range(2,n):
        print(" iteration:", i)
        print(finite_diffs[i])
        pos_0 = int(len(finite_diffs[i])/2)
        print("pos:",pos_0)
        y_0 = finite_diffs[i][pos_0]
        print("delta y = ", y_0)
        if (i%2==0):
            tmp = (g_m(i, q + i/2) * y_0) / math.factorial(i)
        else:
            tmp = (g_m(i, q + i/2 + 0.5) * y_0) / math.factorial(i)

        res += tmp
        print("tmp = ", round(tmp,3))
    return  res


def g_m(m,q):
    res = 1
    for i in range(1,m+1):
        tmp = q-i
        res *= tmp
        print(i,tmp)
    print("g_m = ", res)
    return res


def start():
    res = {}
    for i in range(len(CONTROL_POINTS_33)):
        tmp = CONTROL_POINTS_33[i]
        print("Value =", tmp)
        x_start = int(tmp)
        x_end = x_start + 1
        h = 0.2
        x_list = np.arange(x_start, x_end,h).tolist()
        y_list = []
        for i in range(len(x_list)):
            y_list.append(func_33(x_list[i]))
        y = func_33(tmp)
        res[y] = round(gauss(x_list, y_list, tmp),3)
    print(res)
    messagebox.showinfo("Результат за завданням", res)

def plot():
    res = {}
    mas = []
    y_plot = []
    for i in range(len(CONTROL_POINTS_33)):
        y_plot.append(func_33(CONTROL_POINTS_33[i]))
    for i in range(len(CONTROL_POINTS_33)):
        tmp = CONTROL_POINTS_33[i]
        print("Value =", tmp)
        x_start = int(tmp)
        x_end = x_start + 1
        h = 0.2
        x_list = np.arange(x_start, x_end, h).tolist()
        y_list = []
        for i in range(len(x_list)):
            y_list.append(func_33(x_list[i]))
        y = func_33(tmp)
        res[y] = round(gauss(x_list, y_list, tmp), 3)
        mas.append(res[y])

    plt.figure()
    plt.plot(CONTROL_POINTS_33, y_plot, '-b', label='Задані точки')
    plt.plot(CONTROL_POINTS_33, mas, '*r', label='Перша інтерполяційна формула Гаусса')
    plt.xlabel('Значення х')
    plt.ylabel('Значення y')
    plt.title('Перша інтерполяційна формула Гаусса')
    plt.show()

def start_data():
    x_list = np.arange(x_start.get(), x_end.get(), h.get()).tolist()
    y_list = []
    for i in range(len(x_list)):
        y_list.append(func_33(x_list[i]))
    key = x.get()
    y = func_33(key)
    res = {}
    res[y] = round(gauss(x_list, y_list, key), 3)
    messagebox.showinfo("Результат за заданими данними", res)

root = Tk()
root.title("Перша інтерполяційна формула Гаусса")
root.geometry("400x300+300+250")
x_start  = DoubleVar()
x_end = DoubleVar()
h = DoubleVar()
x = DoubleVar()
x_start_label = Label(text="Початковий x:")
x_end_label = Label(text="Кінцевий x:")
h_label = Label(text="Введіть крок")
x_label = Label(text='Введіть х')

x_start_label.grid(row=0, column=0, sticky="w")
x_end_label.grid(row=1, column=0, sticky="w")
h_label.grid(row=2, column=0, sticky="w")
x_label.grid(row=3, column=0, sticky="w")

x_start_entry = Entry(textvariable=x_start)
x_end_entry = Entry(textvariable=x_end)
h_entry = Entry(textvariable=h)
x_entry = Entry(textvariable=x)

x_start_entry.grid(row=0, column=1, padx=5, pady=5)
x_end_entry.grid(row=1, column=1, padx=5, pady=5)
h_entry.grid(row=2, column=1, padx=5, pady=5)
x_entry.grid(row=3, column=1, padx=5, pady=5)

result_data = Button(text="Обрахувати", command=start_data)
result_data.grid(row=4, column=1, padx=5, pady=5, sticky="e")

result = Button(text="Завдання", command=start)
result.grid(row=5, column=1, padx=5, pady=5, sticky="e")

plot = Button(text="Графік", command=plot)
plot.grid(row=6, column=1, padx=5, pady=5, sticky="e")

root.mainloop()