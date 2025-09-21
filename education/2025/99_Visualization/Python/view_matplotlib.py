import matplotlib
matplotlib.use("TkAgg")
import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np

fig, ax = plt.subplots()
ax.set_xlim(0, 2*np.pi)
ax.set_ylim(-1.5, 1.5)
line, = ax.plot([], [], 'r-', linewidth=2)

x = np.linspace(0, 2*np.pi, 100)
phase = 0

def update(frame):
    global phase
    y = np.sin(x + phase)
    line.set_data(x, y)
    phase += 0.1
    return line,

ani = animation.FuncAnimation(fig, update, interval=50, blit=True)
plt.title("Matplotlib Example: Sine Wave Animation")
plt.show()
