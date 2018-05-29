import numpy as np
import matplotlib.pyplot as plt
from tkinter import *
from tkinter import messagebox


VAL_X_20 = [
    -9.319,
    -9.166,
    -8.594,
    -8.536,
    -8.288,
    -7.784,
    -7.146,
    -6.384,
    -6.165,
    -5.506,
    -5.205,
    -2.021,
    -1.865,
    -1.011,
    -0.607,
    0.762,
    2.043,
    2.611,
    3.861,
    5.094,
    5.490,
    6.766,
    7.501,
    9.674,
    9.922,
    11.210,
    12.740,
    13.061,
    13.191,
    13.232,
    15.142,
    15.229,
    15.357,
    15.594,
    16.579,
]

VAL_Y_20 = [
    -206.546,
    -215.645,
    -236.654,
    -237.463,
    -238.011,
    -225.579,
    -190.626,
    -140.269,
    -127.277,
    -98.611,
    -88.650,
    -45.542,
    -41.825,
    -20.935,
    -11.589,
    18.470,
    49.288,
    61.210,
    74.742,
    86.898,
    97.992,
    168.031,
    215.333,
    185.939,
    167.380,
    119.081,
    302.542,
    362.367,
    386.040,
    393.205,
    448.805,
    434.680,
    411.636,
    363.198,
    146.413,
]




CONTROL_POINTS_20 = [-7.665, -7.274, -6.581, -6.494, -6.288, -3.923, -1.416,
                     -1.393, -1.166, -0.551, 2.536, 3.765, 6.893, 10.139, 14.964]




def func_33(x):
    return np.exp(x) + x*np.log10(x) + x


def lagrange(x_list,y_list,x):
    res = 0
    for i in range(len(x_list)):
        print("Iteration: ", i)
        tmp = y_list[i]
        for j in range(len(x_list)):
            if i != j :
                tmp *= (x - x_list[j])/(x_list[i] - x_list[j])
                print(j,round(tmp,3))
        res += tmp
    return res

# for i in range (len(CONTROL_POINTS_20)):
#     print(round(lagrange(VAL_X_20,VAL_Y_20,CONTROL_POINTS_20[i]),3))


def start():
    res = {}
    for i in range (len(CONTROL_POINTS_20)):
        res[CONTROL_POINTS_20[i]] = round(lagrange(VAL_X_20,VAL_Y_20,CONTROL_POINTS_20[i]),3)
    messagebox.showinfo("Результат за завданням", res)

def plot():
    res = {}
    mas = []
    for i in range(len(CONTROL_POINTS_20)):
        res[CONTROL_POINTS_20[i]] = round(lagrange(VAL_X_20, VAL_Y_20, CONTROL_POINTS_20[i]), 3)
        mas.append(res[CONTROL_POINTS_20[i]])
    plt.figure()
    plt.plot(VAL_X_20, VAL_Y_20, '-b', label='Задані точки')
    plt.plot(CONTROL_POINTS_20, mas, '*r', label='Інтерполяційний многочлен Лагранжа')
    plt.xlabel('Значення х')
    plt.ylabel('Значення y')
    plt.title('Інтерполяційний многочлен Лагранжа')
    plt.show()

def start_data():
    x_list = np.arange(x_start.get(),x_end.get(),h.get()).tolist()
    y_list = []
    for i in range(len(x_list)):
        y_list.append(func_33(x_list[i]))
    res = {}
    key = x.get()
    res[key] = round(lagrange(x_list,y_list,key),3)
    res['Підстановка у функцію'] = round(func_33(key),3)
    messagebox.showinfo("Результат за заданими данними", res)


root = Tk()
root.title("Інтерполяційний многочлен Лагранжа")
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