import numpy as np
import lime.lime_tabular
from LimeExplainer import LimeExplainer
import os



# Generates explanations for a set of input states
class TrajectoryExplainer:

    def __init__(self, training_states, sampled_states_file, q_values_file, agent_cmd):

        # Create LimeExplainer
        self.explainer = LimeExplainer(training_states, sampled_states_file, agent_cmd, q_values_file)


    # Retrieve explanations
    def explain(self, input_states, input_actions):

        explanations = []

        # Explain the input states
        for i in range(input_states.shape[0]):

            input_state = input_states[i]
            action = input_actions[i]

            # Get explanation from the Lime explainer
            explanation = self.explainer.explain(input_state, action)
            explanations.append(explanation)











