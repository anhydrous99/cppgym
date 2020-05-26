from .._BlackJack import BlackJackCPP

import gym
import ctypes
import numpy as np
from gym import spaces


class BlackJack(gym.Env):
    def __init__(self, natural=False):
        self.env = BlackJackCPP(natural)
        self.action_space = spaces.Discrete(2)
        self.observation_space = spaces.Tuple((
            spaces.Discrete(32),
            spaces.Discrete(11),
            spaces.Discrete(2)
        ))
        self.state = None
        self.natural = natural

    def seed(self, seed=None):
        if seed is None:
            return [self.env.get_seed()]
        else:
            if not isinstance(seed, ctypes.c_uint32):
                seed = ctypes.c_uint32(seed).value
            self.env.set_seed(seed)
            return [seed]

    def step(self, action):
        assert self.action_space.contains(action)
        state, reward, done = self.env.step(action)
        self.state = np.array(state)
        return self.state, reward, done, {}

    def render(self, mode='human'):
        return None

    def reset(self):
        self.state = np.array(self.env.reset())
        return self.state
