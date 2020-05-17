import cppgym
import gym
import time
import numpy as np


def env_test(env, episodes):
    final = []
    t0 = time.time()
    for episode in range(episodes):
        state = env.reset()
        done = False
        total = 0
        while not done:
            action = env.action_space.sample()
            next_state, reward, done, _ = env.step(action)
            total += reward
            if done:
                break
        final.append(total)
    t1 = time.time()
    return np.average(final), t1 - t0


def main():
    n_episodes = 1000
    print('CartPole')
    cartpole_gym = gym.envs.make('CartPole-v1')
    score, time = env_test(cartpole_gym, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')

    cartpole_cpp = cppgym.CartPole()
    score, time = env_test(cartpole_cpp, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')


if __name__ == "__main__":
    main()
