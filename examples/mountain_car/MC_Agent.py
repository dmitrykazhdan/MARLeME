
import numpy as np


class MC_Agent:

    def __init__(self, args_path, n_p_ranges, n_v_ranges):

        self.args = {}
        self.n_p_ranges = n_p_ranges
        self.n_v_ranges = n_v_ranges


        # Load argument values
        with open(args_path) as f:
            content = f.readlines()

            for line in content:
                line = line.strip()
                argID, argVal = line.split(" ")
                argID, argVal = int(argID), int(argVal)

                self.args[argID] = argVal


    def execute(self, state):

        p, v = state[0], state[1]

        step_p, step_v = 1.8/self.n_p_ranges, 0.14/self.n_v_ranges

        p_index = (p + 1.2) // step_p
        v_index = (v + 0.07) // step_v

        argOffset = 3 * self.n_v_ranges * p_index + 3*v_index
        argVals = np.array([self.args[argOffset + i] for i in range(3)])

        action = np.argmax(argVals)

        return action






