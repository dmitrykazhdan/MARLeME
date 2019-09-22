import numpy as np
import matplotlib.pyplot as plt
from MC_Agent import MC_Agent
from RL_Agent import RL_Agent


def plot_policy(policy):

    poses = np.linspace(-1.2, 0.6, 256)
    vels = np.linspace(-0.07, 0.07, 256)
    positions, velocities = np.meshgrid(poses, vels)

    @np.vectorize
    def execute(position, velocity):
        return policy.execute((position, velocity))

    action_values = execute(positions, velocities)

    fig, ax = plt.subplots()
    c = ax.pcolormesh(positions, velocities, action_values)
    ax.set_xlabel('position')
    ax.set_ylabel('velocity')
    cbar = fig.colorbar(c, ax=ax, boundaries=[-.5, .5, 1.5, 2.5], ticks=[0, 1, 2])
    cbar.ax.set_yticklabels(['push_left', 'no_push', 'push_right'])
    plt.show()




plot_extracted_agent = False

if plot_extracted_agent:
    ordering_path = "..."
    agent = MC_Agent(ordering_path)
else:
    agent = RL_Agent()


plot_policy(agent)
