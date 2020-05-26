from ._HotterColder import HotterColderCPP

import gym
import ctypes
import numpy as np
from gym import spaces


class HotterColder(gym.Env):
    def __init__(self):
        self.env = HotterColderCPP()
        self.action_space = spaces.Box(low=np.array([-self.env.bounds]), high=np.array([self.env.bounds]),
                                       dtype=np.float32)
        self.observation_space = spaces.Discrete(4)

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
        return self.env.step(action)

    def reset(self):
        return self.env.reset()
