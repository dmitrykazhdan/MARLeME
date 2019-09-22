from MC_Agent import MC_Agent
import numpy as np


# Path to agent trajectories
state_filename = "..."
action_filename = "..."

state_file = open(state_filename)
action_file = open(action_filename)


# Create mountain car agent
ordering_path = "..."
agent = Optimised_Agent(ordering_path)

state_lines = state_file.readlines()
action_lines = action_file.readlines()

correct = 0
incorrect = 0

# Compute 0-1 loss
for (state, action) in zip(state_lines, action_lines):

    state = np.array([float(i) for i in state.split(" ")])
    action = int(action)

    agent_action = agent.execute(state)

    if agent_action == action:
        correct += 1
    else:
        incorrect += 1

mismatch = (correct) / (correct + incorrect) * 100.0

print("0-1 loss: ", mismatch)