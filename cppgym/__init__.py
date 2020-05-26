# __init__.py

from .ClassicControl.CartPole import CartPole

from .ClassicControl.MountainCar import MountainCar

from .ClassicControl.MountainCarContinuous import MountainCarContinuous

from .ClassicControl.Pendulum import Pendulum

from .ClassicControl.Acrobot import Acrobot

from .ToyText.BlackJack import BlackJack

from .ToyText.HotterColder import HotterColder


def make(env: str):
    from gym.wrappers.time_limit import TimeLimit
    if env == 'CartPole-v0':
        return TimeLimit(CartPole(), max_episode_steps=200)
    elif env == 'CartPole-v1':
        return TimeLimit(CartPole(), max_episode_steps=500)
    elif env == 'MountainCar-v0':
        return TimeLimit(MountainCar(), max_episode_steps=200)
    elif env == 'MountainCarContinuous-v0':
        return TimeLimit(MountainCarContinuous(), max_episode_steps=999)
    elif env == 'Pendulum-v0':
        return TimeLimit(Pendulum(), max_episode_steps=200)
    elif env == 'Acrobot-v1':
        return TimeLimit(Acrobot(), max_episode_steps=500)
    elif env == 'Blackjack-v0':
        return BlackJack()
    elif env == 'HotterColder-v0':
        return TimeLimit(HotterColder(), max_episode_steps=200)
