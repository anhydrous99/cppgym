# CppGym

This project is not intended as a replacement of [OpenAI's Gym](https://github.com/openai/gym/), but as an extension. 
This extension re-implements some of the more simple environments in the toolkit with a focus in performance. 
These performance improvements are done by relying on the Modern C++ language, C++17 to be exact, memoization
of some of the operations, as well as some mathematical shortcuts, at little to no degradation of accuracy.

## Performance

This benchmark is in the directory bench/benchmark.py, it simply runs each environment for 1000 steps measuring the time
for both the Gym and CppGym version. 

| Environment              | Gym (ms) | CppGym (ms) | x Improvement |
|--------------------------|----------|-------------|---------------|
| CartPole-v0              | 286.99   | 180.53      | 1.589         |
| CartPole-v1              | 291.99   | 184.00      | 1.586         |
| MountainCar-v0           | 7174.67  | 1585.03     | 4.526         |
| MountainCarContinuous-v0 | 40272.73 | 30235.95    | 1.332         |
| Pendulum-v0              | 16055.94 | 6068.91     | 2.646         |
| Acrobot-v1               | 61415.93 | 4649.20     | 13.21         |
| Blackjack-v0             | 51       | 12          | 4.25          |

### Accuracy

In the bench/baselines_bench file, to test whether a standard algorithm, like PPO, can be trained as the original
environments can. The program calculates the average reward and time for stable-baseline's PPO2 over 10 runs each 
for 100 evaluation episodes. 

| Environment              | Gym Time (s) | CppGym Time (s) | Gym Reward | CppGymReward | Improvement |
|--------------------------|--------------|-----------------|------------|--------------|-------------|
| CartPole-v0              | 13.475       | 13.168          | 145.68     | 156.209      | 2.3%        |  
| CartPole-v1              | 13.567       | 13.368          | 162.18     | 165.009      | 1.5%        |
| MountainCar-v0           | 13.95        | 13.31           | -200       | -200         | 4.8%        |
| MountainCarContinuous-v0 | 12.79        | 12.578          | -41.57     | -41.70       | 1.7%        |
| Pendulum-v0              | 13.08        | 12.24           | -1201.14   | -1245.2      | 6.8%        |
| Acrobot-v1               | 15.12        | 13.92           | -302.393   | -234.709     | 8.6%        |


## Installation

Depending on your operating system, (Mac OS, Windows, or Linux), you will need to have the respective compiler, 
(XCode, MSVC, or GCC). For Mac OS, I've tested with Mojave, with Windows MSVC v142 - v14.26, and GCC 9.3.0; I've tested
this with Python 3.7 and 3.8. Of course, this doesn't mean other versions won't work. 

This is assuming you have git, cmake, and python in your path.

```shell script
pip install git+https://github.com/anhydrous99/cppgym.git
```

### Some dependencies

* CMake 3.16>=
* Git
* GCC, MSVC, or XCode
* Numpy
* OpenAI's Gym

For the benchmarks,

* TQDM
* Pandas
* Stable-Baselines

The C++ part of the code's only reliance is the standard library upto the C++17 standard and PyBind11 which is a 
submodule within this git project and, therefore, acquired automatically. 

## How to & Sample

To use you simple import cppgym and run make as you would an OpenAI Gym's environment:
```python
import cppgym
env = cppgym.make('CartPole-v0')
```

Here is a random agent within the CartPole-v0 environment:
```python
import cppgym  # Import the cppgym module
import numpy as np
n_episodes = 100  # Number of episodes
env = cppgym.make('CartPole-v0')  # Create environment
reward_list = []
for _ in range(n_episodes):
    state = env.reset()  # Reset the environment (as OpenAI's gym)
    total_reward = 0.0
    while True:
        action = env.action_space.sample()  # Sample from the action space (as OpenAI's gym)
        next_state, reward, done, _ = env.step(action)  # Step the environment (as OpenAI's gym)
        env.render()  # Render the environment (as OpenAI's gym)
        total_reward += reward
        if done:
            break
    reward_list.append(total_reward)

env.close()
print(f'mean: {np.mean(reward_list)} std: {np.std(reward_list)}')
```