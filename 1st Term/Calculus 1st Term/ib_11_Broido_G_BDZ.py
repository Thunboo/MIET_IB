import matplotlib.pyplot as plt
import numpy as np
import sympy as sp

plt.subplot(2,4,1)
x = np.linspace(-2,2,100)
y1, = plt.plot(x, x**2, 'b-', label='$y = x^2$')
x = np.linspace(0,2,50)
y2, = plt.plot(x, x**(1/2), 'r:', label='$y = x^{0.5}$')
plt.legend(handles = [y1, y2])
plt.title('1')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,2)
x = np.linspace(-2,2,100)
y1, = plt.plot(x, np.cbrt(x), 'b-', label='$y = x^{(1/3)}$')
y2, = plt.plot(x, x**3, 'r:', label='$y = x^3$')
plt.legend(handles = [y1, y2])
plt.title('2')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,3)
from math import e
x = np.linspace(-2,2,100)
y1, = plt.plot(x, np.exp(x), 'b-', label='$y = e^x$')
y2, = plt.plot(x, np.log(x), 'r:', label='$y = ln(x)$')
plt.legend(handles = [y1, y2])
plt.title('3')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,4)
x = np.linspace(0.00001, 16, 250)
log_of_x = np.emath.logn(1/2, x)
y1, = plt.plot(x, log_of_x, label='$y = log{_{(1/2)}}x$')
x = np.linspace(-4,15,400)
y2, = plt.plot(x, (1/2)**x, label='$y = (1/2)^x$')
plt.legend(handles = [y1,y2])
plt.title('4')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,5)
x = np.linspace( -(np.pi)/2, (np.pi)/2, 100)
y1, = plt.plot(x, np.sin(x), 'b-', label = '$y=sin(x)$')
y2, = plt.plot(x, np.arcsin(x), 'r:', label = '$y=arcsin(x)$')
y_sym=plt.plot(x, x, 'm-', '$y=x$')

plt.legend(handles = [y1, y2])
plt.title('5')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,6)
x = np.linspace( -(np.pi)/2.5, (np.pi)/2.5, 100)
y1, = plt.plot(x, np.tan(x), 'b-', label = '$y=tg(x)$')
y2, = plt.plot(x, np.arctan(x), 'r:', label = '$y=arctg(x)$')
plt.legend(handles = [y1, y2])
plt.title('6')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,7)
x = np.linspace(-np.pi, np.pi, 1000)
y1, = plt.plot(x, np.cos(x), 'r:', label='y=cos(x)')
y2, = plt.plot(x, np.arccos(x), 'b-', label='y=arccos(x)')
plt.legend(handles = [y1, y2])
plt.title('7')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.subplot(2,4,8)
x = np.linspace( 0.00001, (np.pi), 100)
y1, = plt.plot(x, 1 / np.tan(x), 'b-', label = '$y=ctg(x)$')
y2, = plt.plot(x, np.pi/2 - np.arctan(x), 'r:', label = '$y=arcctg(x)$')
plt.legend(handles = [y1, y2])
plt.ylim(-5,5)
plt.title('8')
plt.axhline(y=0, color='k')
plt.axvline(x=0, color='k')
plt.grid(True)
plt.xlabel('x')
plt.ylabel('y')

plt.show()
