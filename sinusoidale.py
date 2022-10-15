import numpy as np
from scipy.signal import sawtooth,square
import matplotlib.pyplot as plt
import matplotlib.animation as animation

fig, axes = plt.subplots(nrows=2, ncols=2)
ax0 = axes[0 ,0]
ax1 = axes[1, 0]
ax2 = axes[0, 1]
ax3 = axes[1, 1]
# ax4 = axes[0, 2]
# ax5 = axes[1, 2]

# sig = np.sin(2 * np.pi * x)
# pwm = square(2 * np.pi * 30 * x, duty=(sig + 1)/2)  

x = np.arange(-2*np.pi, 2*np.pi, 0.01)
freq = np.linspace(0,50,1001)[1:]

kappa = 2*np.pi*freq[0]
x1, x2 =  np.sin(x*kappa), .5
abscisse = np.zeros_like(x)
abscisse[int(int(len(abscisse)/2)+1)] = 1

line, = ax0.plot(x, x1)
ax0.plot(x, abscisse)
ax0.grid()
ax0.set_title('Signal sinusoïdale')
ax0.axes.xaxis.set_visible(False)

line1, = ax1.plot(x, np.heaviside(x1, x2))
ax1.plot(x, abscisse)
ax1.grid()
ax1.set_title('Signal carré')

line2, = ax2.plot(x, np.sign(x1))
ax2.plot(x, abscisse)
ax2.grid()
ax2.set_title('Signal sign')
ax2.axes.xaxis.set_visible(False)

line3, = ax3.plot(x, sawtooth(x1))
ax3.plot(x, abscisse)
ax3.grid()
ax3.set_title('Signal sawtooth')

#====================================================================================#
# Amplitude Shift Keying - ASK


# Phase shift keying - PSK

#====================================================================================#

def animateSin(i):
    line.set_ydata(np.sin((x + i / 50)*kappa))  # update the data.
    return line,

def animateHeaviside(i):
    line1.set_ydata(np.heaviside(np.sin((x + i / 50)*kappa), .5))  # update the data.
    return line1,

def animateSign(i):
    line2.set_ydata(np.sign(np.sin((x + i / 50)*kappa)))  # update the data.
    return line2,

def animateSawtooth(i):
    line3.set_ydata(sawtooth((x + i / 50)*kappa))  # update the data.
    return line3,


aniSinus = animation.FuncAnimation(
    fig, animateSin, interval=20, blit=True, save_count=50)

aniHeaviside = animation.FuncAnimation(
    fig, animateHeaviside, interval=20, blit=True, save_count=50)

aniSign = animation.FuncAnimation(
    fig, animateSign, interval=20, blit=True, save_count=50)

aniSawtooth = animation.FuncAnimation(
    fig, animateSawtooth, interval=20, blit=True, save_count=50)


#====================================================================================#

# To save the animation, use e.g.
#
# ani.save("movie.mp4")
#
# or
#
# writer = animation.FFMpegWriter(
#     fps=15, metadata=dict(artist='Me'), bitrate=1800)
# ani.save("movie.mp4", writer=writer)

plt.show()