import numpy as np
import matplotlib.pyplot as plt
import math

def func_33(x):
    return np.exp(x) + x*np.log10(x) + x

start = 4.5
end = 25
step = 0.5

x = np.arange(start, end, step)
y = func_33(x)

order = 11 # order of polynom
A = np.fliplr(np.vander(x, order))
print("A ", A)
coefs, _, _, _ = np.linalg.lstsq(A, y)
print("coefs ", coefs)

cnt = 10 # number of points to plot
interp_x = np.linspace(start, end, cnt)
print("Interp_x", interp_x)

print(interp_x)
interp_y = np.zeros(cnt)

for ind, ix in enumerate(interp_x):
    print(ind,ix)
    interp_y[ind] = np.sum(coefs * ix ** np.arange(0, order))

print("interp_y",interp_y)

plt.figure()
plt.plot(interp_x, interp_y, '-b', label='Лінія інтерполяції')
plt.plot(x, y, '*r', label='Значення у функції')
plt.xlabel('Значення х')
plt.ylabel('Значення y')
plt.title('Інтерполяція Вандермонда')
plt.show()