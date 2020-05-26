import cppgym
import gym
import time
import numpy as np
gym.logger.set_level(40)


def env_test(env, episodes):
    final = []
    t0 = time.time()
    min_rew = float('inf')
    for episode in range(episodes):
        state = env.reset()
        done = False
        total = 0
        while not done:
            action = env.action_space.sample()
            next_state, reward, done, _ = env.step(action)
            total += reward
            min_rew = min_rew if min_rew < reward else reward
            if done:
                break
        final.append(total)
    t1 = time.time()
    return np.average(final), t1 - t0


def main():
    n_episodes = 1000
    print('CartPole-v0')
    gym_env = gym.envs.make('CartPole-v0')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('CartPole-v0')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('CartPole-v1')
    gym_env = gym.envs.make('CartPole-v1')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('CartPole-v1')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('MountainCar-v0')
    gym_env = gym.envs.make('MountainCar-v0')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('MountainCar-v0')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('MountainCarContinuous-v0')
    gym_env = gym.envs.make('MountainCarContinuous-v0')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('MountainCarContinuous-v0')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('Pendulum-v0')
    gym_env = gym.envs.make('Pendulum-v0')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('Pendulum-v0')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('Acrobot-v1')
    gym_env = gym.envs.make('Acrobot-v1')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('Acrobot-v1')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('Blackjack-v0')
    gym_env = gym.envs.make('Blackjack-v0')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('Blackjack-v0')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')

    print('HotterColder-v0')
    gym_env = gym.envs.make('HotterColder-v0')
    score, time = env_test(gym_env, n_episodes)
    print(f'gym: score - {score} - time - {time * 1000} ms')
    cpp_env = cppgym.make('HotterColder-v0')
    score, time = env_test(cpp_env, n_episodes)
    print(f'cpp: score - {score} - time - {time * 1000} ms')


if __name__ == "__main__":
    main()
