from ._Acrobot import AcrobotCPP

import gym
import ctypes
import numpy as np
from gym import spaces
from numpy import sin, cos, pi


class Acrobot(gym.Env):
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 10
    }

    def __init__(self):
        self.env = AcrobotCPP()
        self.viewer = None
        self.dt = self.env.dt
        self.LINK_LENGTH_1 = self.LINK_LENGTH_2 = self.env.link_length
        self.LINK_MASS_1 = self.LINK_MASS_2 = self.env.link_mass
        self.LINK_COM_POS_1 = self.LINK_COM_POS_2 = self.env.link_com_pos
        self.LINK_MOI = self.env.link_moi
        self.MAX_VEL_1 = self.env.max_vel_1
        self.MAX_VEL_2 = self.env.max_vel_2
        self.AVAIL_TORQUE = [-1., 0., +1]
        self.torque_noise_max = 0.

        high = np.array([1.0, 1.0, 1.0, 1.0, self.MAX_VEL_1, self.MAX_VEL_2], dtype=np.float32)
        low = -high
        self.observation_space = spaces.Box(low=low, high=high, dtype=np.float32)
        self.action_space = spaces.Discrete(3)
        self.state = None

    def seed(self, seed=None):
        if seed is None:
            return [self.env.get_seed()]
        else:
            if not isinstance(seed, ctypes.c_uint32):
                seed = ctypes.c_uint32(seed).value
            self.env.set_seed(seed)
            return [seed]

    def step(self, action):
        if not isinstance(action, ctypes.c_int8):
            action = ctypes.c_int8(action).value
        state, reward, done = self.env.step(action)
        self.state = np.array(state)
        return self.state, reward, done, {}

    def reset(self):
        self.state = np.array(self.env.reset())
        return self.state

    def render(self, mode='human'):
        from gym.envs.classic_control import rendering

        s = self.state

        if self.viewer is None:
            self.viewer = rendering.Viewer(500,500)
            bound = self.LINK_LENGTH_1 + self.LINK_LENGTH_2 + 0.2  # 2.2 for default
            self.viewer.set_bounds(-bound,bound,-bound,bound)

        if s is None: return None

        p1 = [-self.LINK_LENGTH_1 *
              cos(s[0]), self.LINK_LENGTH_1 * sin(s[0])]

        p2 = [p1[0] - self.LINK_LENGTH_2 * cos(s[0] + s[1]),
              p1[1] + self.LINK_LENGTH_2 * sin(s[0] + s[1])]

        xys = np.array([[0,0], p1, p2])[:,::-1]
        thetas = [s[0]- pi/2, s[0]+s[1]-pi/2]
        link_lengths = [self.LINK_LENGTH_1, self.LINK_LENGTH_2]

        self.viewer.draw_line((-2.2, 1), (2.2, 1))
        for ((x,y),th,llen) in zip(xys, thetas, link_lengths):
            l,r,t,b = 0, llen, .1, -.1
            jtransform = rendering.Transform(rotation=th, translation=(x,y))
            link = self.viewer.draw_polygon([(l,b), (l,t), (r,t), (r,b)])
            link.add_attr(jtransform)
            link.set_color(0,.8, .8)
            circ = self.viewer.draw_circle(.1)
            circ.set_color(.8, .8, 0)
            circ.add_attr(jtransform)

        return self.viewer.render(return_rgb_array = mode=='rgb_array')
