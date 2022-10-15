#%%
from scipy import signal
import numpy as np
import matplotlib.pyplot as plt

# SRC : https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.square.html
t = np.linspace(0, 1, 500, endpoint=False)

plt.plot(t, signal.square(2 * np.pi * 5 * t))
plt.ylim(-2, 2)
plt.figure()

sig = np.sin(2 * np.pi * t)
pwm = signal.square(2 * np.pi * 30 * t, duty=(sig + 1)/2)

plt.subplot(2, 1, 1)
plt.plot(t, sig)

plt.subplot(2, 1, 2)
plt.plot(t, pwm)
plt.ylim(-1.5, 1.5)

plt.show()
#%%
# SRC : https://docs.scipy.org/doc/scipy/reference/generated/scipy.signal.sweep_poly.html   

# f(t) = 0.025*t**3 - 0.36*t**2 + 1.25*t + 2
# over the interval 0 <= t <= 10.

from scipy.signal import sweep_poly
import numpy as np

p = np.poly1d([0.025, -0.36, 1.25, 2.0])
t = np.linspace(0, 10, 5001)
w = sweep_poly(t, p)

import matplotlib.pyplot as plt

plt.subplot(2, 1, 1)
plt.plot(t, w)
plt.title("Sweep Poly\nwith frequency " +
          "$f(t) = 0.025t^3 - 0.36t^2 + 1.25t + 2$")

plt.subplot(2, 1, 2)
plt.plot(t, p(t), 'r', label='f(t)')
plt.legend()
plt.xlabel('t')
plt.tight_layout()

plt.show()
#%%