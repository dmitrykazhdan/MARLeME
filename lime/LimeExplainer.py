import numpy as np
import lime.lime_tabular
import os


class LimeExplainer:

    def __init__(self, training_states, sampled_states_file, agent_file, q_values_file):

        self.sampled_states_file = sampled_states_file
        self.agent_file = agent_file
        self.q_values_file = q_values_file

        # Create the LIME explainer
        self.explainer = lime.lime_tabular.LimeTabularExplainer(
            training_data=training_states,
            mode="regression",
            discretize_continuous=True,
            kernel_width=np.sqrt(training_states.shape[1]) * .65,
            discretizer='decile',
            sample_around_instance=True,
            verbose=False)


    def explain(self, input_state, action):

        self.action = action

        exp = self.explainer.explain_instance(input_state,
                                         self.predict_fn,
                                         num_features=5,
                                         num_samples=8000)

        explanation = exp.as_list()

        return explanation



    # Run given states through policy
    def predict_fn(self, states):

        # Save the states to the input agent file
        np.savetxt(self.sampled_states_file, states, fmt="%.4f")

        # Run the agent policy on all of the given states saved in the file
        os.system(self.agent_file)

        # Read out given output values from the agent output file
        with open(self.q_values_file) as f:
            content = f.readlines()

        values = np.array([[float(i) for i in line.strip().split(" ")] for line in content])

        # Get q-values for specific action
        values = values[:, self.action]

        return values



