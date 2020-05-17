from ._Pendulum import PendulumCPP

import gym
import ctypes
import numpy as np
from os import path
from gym import spaces


class Pendulum(gym.Env):
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 30
    }

    def __init__(self, g=10.0):
        if not isinstance(g, float):
            g = float(g)
        self.env = PendulumCPP(g)
        self.viewer = None
        self.state = None

        high = np.array([1., 1., self.env.max_speed], dtype=np.float32)
        self.action_space = spaces.Box(
            low=-self.env.max_torque,
            high=self.env.max_torque,
            shape=(1,),
            dtype=np.float32
        )
        self.observation_space = spaces.Box(
            low=-high,
            high=high,
            dtype=np.float32
        )

    def seed(self, seed=None):
        if seed is None:
            return [self.env.get_seed()]
        else:
            if not isinstance(seed, ctypes.c_uint32):
                seed = ctypes.c_uint32(seed).value
            self.env.set_seed(seed)
            return [seed]

    def step(self, action: float):
        state, reward, done = self.env.step(action)
        self.state = np.array(state)
        return self.state, reward, done, {}

    def reset(self):
        self.state = np.array(self.env.reset())
        return self.state

    def render(self, mode='human'):
        if self.viewer is None:
            from gym.envs.classic_control import rendering
            self.viewer = rendering.Viewer(500, 500)
            self.viewer.set_bounds(-2.2, 2.2, -2.2, 2.2)
            rod = rendering.make_capsule(1, 2.)
            rod.set_color(.8, .3, .3)
            self.pole_transform = rendering.Transform()
            rod.add_attr(self.pole_transform)
            self.viewer.add_geom(rod)
            axle = rendering.make_circle(.05)
            axle.set_color(0, 0, 0)
            self.viewer.add_geom(axle)
            fname = path.join(path.dirname(__file__), "assets/clockwise.png")
            self.img = rendering.Image(fname, 1., 1.)
            self.imgtrans = rendering.Transform()
            self.img.add_attr(self.imgtrans)
        self.viewer.add_onetime(self.img)
        self.pole_transform.set_rotation(self.state[0] + np.pi / 2)
        if self.env.last_u != 0:
            self.imgtrans.scale = (-self.env.last_u / 2, np.abs(self.env.last_u) / 2)
        return self.viewer.render(return_rgb_array=mode == 'rgb_array')

    def close(self):
        if self.viewer:
            self.viewer.close()
            self.viewer = None
