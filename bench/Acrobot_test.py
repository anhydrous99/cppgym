from stable_baselines.common.callbacks import EvalCallback, StopTrainingOnRewardThreshold
from stable_baselines.common.policies import MlpPolicy
from stable_baselines import PPO2

import numpy as np
import cppgym
import gym

env = cppgym.make('Acrobot-v1')
#env = gym.make('Acrobot-v1')
model = PPO2(MlpPolicy, env, verbose=1)
model.learn(total_timesteps=100000)

reward_arr = []
for i in range(1000):
    episode_reward = 0
    obs = env.reset()
    while True:
        action, _state = model.predict(obs)
        obs, rewards, done, _ = env.step(action)
        env.render()
        episode_reward += rewards
        if done:
            break
    reward_arr.append(episode_reward)
print(np.average(reward_arr))