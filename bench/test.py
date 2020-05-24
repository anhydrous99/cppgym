# Sample code from the README.md

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