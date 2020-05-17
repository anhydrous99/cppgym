# __init__.py

from ._CartPole import CartPoleCPP
from .CartPole import CartPole

from ._MountainCar import MountainCarCPP
from .MountainCar import MountainCar


def make(env: str):
    from gym.wrappers.time_limit import TimeLimit
    from gym.envs.registration import EnvSpec
    if env == 'CartPole-v0':
        return TimeLimit(CartPole(), max_episode_steps=200)
    elif env == 'CartPole-v1':
        return TimeLimit(CartPole(), max_episode_steps=500)
    elif env == 'MountainCar-v0':
        return TimeLimit(MountainCar(), max_episode_steps=200)
