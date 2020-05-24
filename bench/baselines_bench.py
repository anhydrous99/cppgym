import gym
import cppgym

from stable_baselines.common.policies import MlpPolicy
from stable_baselines import PPO2

from tqdm import tqdm
from time import time
import numpy as np
import pandas as pd


def run_test(env):
    model = PPO2(MlpPolicy, env)
    t0 = time()
    model.learn(10000)
    t1 = time()

    reward_arr = []
    for i in range(100):
        episode_reward = 0
        obs = env.reset()
        while True:
            action, _state = model.predict(obs)
            obs, rewards, done, _ = env.step(action)
            episode_reward += rewards
            if done:
                break
        reward_arr.append(episode_reward)
    return t1 - t0, np.average(reward_arr)


def sts(env_name):
    print(env_name)
    gym_env = gym.envs.make(env_name)
    cpp_env = cppgym.make(env_name)

    t1_arr = []
    t2_arr = []
    rw1_avg = []
    rw2_avg = []

    for _ in tqdm(range(10)):
        t1, reward_avg_1 = run_test(gym_env)
        t1_arr.append(t1)
        rw1_avg.append(reward_avg_1)
        t2, reward_avg_2 = run_test(cpp_env)
        t2_arr.append(t2)
        rw2_avg.append(reward_avg_2)
    return {'gym time': np.average(t1_arr), 'cpp time': np.average(t2_arr), 'gym reward': np.average(rw1_avg), 'cpp reward': np.average(rw2_avg)}


data = {'CartPole-v0': sts('CartPole-v0'),
        'CartPole-v1': sts('CartPole-v1'),
        'MountainCar-v0': sts('MountainCar-v0'),
        'MountainCarContinuous-v0': sts('MountainCarContinuous-v0'),
        'Pendulum-v0': sts('Pendulum-v0'),
        'Acrobot-v1': sts('Acrobot-v1')}
df = pd.DataFrame(data)
df.to_csv('write.csv')
