# MARLEME: A Multi-Agent Reinforcement Learning Model Extraction Library

This repository contains the implementation of the MARLEME library. MARLEME is a Multi-Agent Reinforcement Learning Model Extraction C++ library, designed to improve interpretability of MARL systems by extracting interpretable models from them. 

MARLEME is designed to be widely applicable and extendable, and is agnostic to the underlying MARL system implementation. Furthermore, MARLEME can be integrated with the well-known [Local Interpretable Model-Agnostic Explanations (LIME)](https://github.com/marcotcr/lime) approach, in order to explain individual agent actions, and mine useful heuristics that can be used to improve approximation quality of extracted models.


## Setup 

- MARLEME requires C++14 or later

- LIME-based components require LIME to be installed. Installation instructions can be found [here](https://github.com/marcotcr/lime#installation)



## Usage


### Model Extraction

Model extraction is achieved by:
- Creating a model extractor (an implementation of the _ModelExtractor_ class)
- Creating a trajectory data object (an implementation of the _TrajectoryData_ class)
- Calling the _extractModel_ method of the model extractor, in order to extract a model from the trajectory data

The example below assumes that _ModelExtractorImpl_, _TrajectoryDataImpl_, and _TeamModelImpl_ are task-specific implementations of the _ModelExtractor_, _TrajectoryData_, and _TeamModel_ classes, respectively.

```
// Create a model extractor
ModelExtractorImpl modelExtractor(...);

// Create a trajectory data handling object
TrajectoryDataImpl trajectoryData(...);

// Extract a model from the trajectory data
TeamModelImpl *teamModel = modelExtractor.extractModel(trajectoryData);

```



### Model Execution

In order to use a model, simply call the _processState_ or _processStates_ methods, as shown below:

```C++

// Create a set of vectors holding the model outputs
vector<vector<double>> modelOutputs;

// Compute model outputs from input states
teamModel.processStates(states, modelOutput);

```

```C++

// Create vector holding the model output
vector<double> modelOutput;

// Compute model output from input state
agentModel.processState(state, modelOutput);

```

The above examples assume that _teamModel_ is an instance of a class implementing the _TeamModel_ class, and _agentModel_ is an instance of a class implementing the _AgentModel_ class.


 


### Explanation Generation

LIME-based components rely on the _LimeTabularExplainer_ functionality, and discretization of continuous input features (further details can be found [here](https://marcotcr.github.io/lime/tutorials/Tutorial%20-%20continuous%20and%20categorical%20features.html)).
Furthermore, these components assume access to the Q-function of a Reinforcement Learning agent. 

The current _LimeExplainer_ implementation assumes that an agent's Q-function can be accessed by running an agent executable file which:
- Reads state information form a specified file
- Runs the agent policy
- Writes the Q-function values for these states into a specific output file

Thus, the LIME-based components require the following:
- Training data (consisting of a set of agent states), to be used for feature discretization
- Agent executable filename
- Agent input states filename
- Agent output q-values filename 


Generating a single explanation from an input (state, action) pair can be done using the _LimeExplainer_ as follows:

```python

training_states = ...       # Load agent training states
sampled_states_file = ...   # Specify the filepath to the agent state file
q_values_file = ...         # Specify the filepath to the agent Q-values file
agent_cmd = ...             # Specify the path to the agent executable

# Create the LIME explainer
explainer = LimeExplainer(training_states, sampled_states_file, agent_cmd, q_values_file)

input_state = ...           # Specify the input state to be explained
action =      ...           # Specify the action selected by the agent in that state


# Generate the explanation
explanation = explainer.explain(input_state, action)
```

Generating a set of explanations from a set of (state, action) pairs can be done using the _TrajectoryExplainer_ as follows:

```python


training_states = ...       # Load agent training states
sampled_states_file = ...   # Specify the filepath to the agent state file
q_values_file = ...         # Specify the filepath to the agent Q-values file
agent_cmd = ...             # Specify the path to the agent executable

# Create the LIME trajectory explainer
explainer = TrajectoryExplainer(training_states, sampled_states_file, q_values_file, agent_cmd)

input_states = ...           # Specify the set of input states to be explained
input_actions =  ...         # Specify the actions selected by the agent in these states


# Generate the explanations
exlpanations = explainer.explain(input_states, input_actions)
```



## Files/Directories

**Core**: this directory contains the core MARLEME components, focusing on interpretable model extraction and deployment. These components are primarily represented by abstract classes, which place certain restrictions on the kind of behaviour a given component is expected to have, whilst allowing the component to have multiple task-specific implementations.

**Lime**: this directory contains the extra MARLEME components, that make use of the LIME approach. These components allow generation of explanations of specific agent actions, and producing sets of these explanations.

Note: currently these components are implemented in Python.
Developing C++ interfacing code in order to wrap them into C++ components is the subject of future work. 

**Takeaway**: this directory contains implementations of MARLEME components, applied to the [RoboCup Takeaway task](https://pdfs.semanticscholar.org/8c42/21b88f2b62e8c59c34c0dc66e54616553db9.pdf?_ga=2.73270739.1524378997.1559055092-1619808647.1538334002). These components include an implementation of an interpretable model based on [Abstract Argumentation](https://en.wikipedia.org/wiki/Argumentation_framework), as well as its correpsonding model extraction algorithm.
