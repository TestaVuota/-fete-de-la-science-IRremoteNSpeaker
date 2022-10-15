import numpy as np
import matplotlib.pyplot as plt
from matplotlib.widgets import Slider, Button
import matplotlib.animation as animation

# The parametrized function to be plotted
def f(t, amplitude, frequency):
    return amplitude * np.sin(2 * np.pi * frequency * t)

t = np.linspace(0, 1, 1000)

# Define initial parameters
init_amplitude = 5
init_frequency = 3

# Create the figure and the line that we will manipulate
fig, axes = plt.subplots(nrows=1, ncols=2)
ax = axes[0]
ax1 = axes[1]

line, = ax.plot(t, f(t, init_amplitude, init_frequency), lw=2)
ax.plot(t, np.zeros_like(t))
ax.set_xlabel('Time [s]')
ax.set_title('Signal sinusoïdal')
ax.grid()

x1, x2 =  f(t, init_amplitude, init_frequency), .5
line1, = ax1.plot(t, init_amplitude * np.heaviside(x1, x2))
ax1.plot(t, np.zeros_like(t))
ax1.grid()
ax1.set_title('Signal carré')

# adjust the main plot to make room for the sliders
fig.subplots_adjust(left=0.25, bottom=0.25)

# Make a horizontal slider to control the frequency.
axfreq = fig.add_axes([0.25, 0.1, 0.65, 0.03])
freq_slider = Slider(
    ax=axfreq,
    label='Frequency [Hz]',
    valmin=0.1,
    valmax=30,
    valinit=init_frequency,
)

# Make a vertically oriented slider to control the amplitude
axamp = fig.add_axes([0.1, 0.25, 0.0225, 0.63])
amp_slider = Slider(
    ax=axamp,
    label="Amplitude",
    valmin=0,
    valmax=10,
    valinit=init_amplitude,
    orientation="vertical"
)

# The function to be called anytime a slider's value changes
def update(val):
    line.set_ydata(f(t, amp_slider.val, freq_slider.val))
    fig.canvas.draw_idle()


# register the update function with each slider
freq_slider.on_changed(update)
amp_slider.on_changed(update)

# Create a `matplotlib.widgets.Button` to reset the sliders to initial values.
resetax = fig.add_axes([0.8, 0.025, 0.1, 0.04])
button = Button(resetax, 'Reset', hovercolor='0.975')


def reset(event):
    freq_slider.reset()
    amp_slider.reset()
button.on_clicked(reset)

def animateSin(i):
    line.set_ydata(amp_slider.val * np.sin(2 * np.pi * freq_slider.val * (t + i / 50)))
    return line,
    
def animateHeaviside(i):
    line1.set_ydata(amp_slider.val * np.heaviside(np.sin(2 * np.pi * freq_slider.val * (t + i / 50)), .5))  # update the data.
    return line1,

aniSinus = animation.FuncAnimation(
    fig, animateSin, interval=20, blit=True, save_count=50)

aniHeaviside = animation.FuncAnimation(
    fig, animateHeaviside, interval=20, blit=True, save_count=50)

plt.show()