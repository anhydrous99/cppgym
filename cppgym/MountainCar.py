from ._MountainCar import MountainCarCPP

import gym
import math
import ctypes
import numpy as np
from gym import spaces


class MountainCar(gym.Env):
    metadata = {
        'render.modes': ['human', 'rgb_array'],
        'video.frames_per_second': 30
    }

    def __init__(self, goal_velocity=0):
        if not isinstance(goal_velocity, float):
            goal_velocity = float(goal_velocity)
        self.env = MountainCarCPP(goal_velocity)

        self.low = np.array([self.env.min_position, -self.env.max_speed], dtype=np.float32)
        self.high = np.array([self.env.max_position, self.env.max_speed], dtype=np.float32)

        self.viewer = None

        self.action_space = spaces.Discrete(3)
        self.observation_space = spaces.Box(self.low, self.high, dtype=np.float32)

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

    @staticmethod
    def _height(xs):
        return np.sin(3 * xs) * .45 + .55
    
    def render(self, mode='human'):
        screen_width = 600
        screen_height = 400

        world_width = self.env.max_position - self.env.min_position
        scale = screen_width / world_width
        carwidth = 40
        carheight = 20

        if self.viewer is None:
            from gym.envs.classic_control import rendering
            self.viewer = rendering.Viewer(screen_width, screen_height)
            xs = np.linspace(self.env.min_position, self.env.max_position, 100)
            xys = self._height(xs)

            self.track = rendering.make_polyline(xys)
            self.track.set_linewidth(4)
            self.viewer.add_geom(self.track)

            clearance = 10

            l,r,t,b = -carwidth/2, carwidth/2, carheight, 0
            car = rendering.FilledPolygon([(l, b), (l, t), (r, t), (r, b)])
            car.add_attr(rendering.Transform(translation=(0, clearance)))
            self.cartrans = rendering.Transform()
            car.add_attr(self.cartrans)
            self.viewer.add_geom(car)
            frontwheel = rendering.make_circle(carheight / 2.5)
            frontwheel.set_color(.5, .5, .5)
            frontwheel.add_attr(rendering.Transform(translation=(carwidth / 4, clearance)))
            frontwheel.add_attr(self.cartrans)
            self.viewer.add_geom(frontwheel)
            backwheel = rendering.make_circle(carheight / 2.5)
            backwheel.add_attr(rendering.Transform(translation=(-carwidth / 4, clearance)))
            backwheel.add_attr(self.cartrans)
            backwheel.set_color(.5, .5, .5)
            self.viewer.add_geom(backwheel)
            flagx = (self.env.goal_position - self.env.min_position) * scale
            flagy1 = self._height(self.env.goal_position) * scale
            flagy2 = flagy1 + 50
            flagpole = rendering.Line((flagx, flagy1), (flagx, flagy2))
            self.viewer.add_geom(flagpole)
            flag = rendering.FilledPolygon([(flagx, flagy2), (flagx, flagy2 - 10), (flagx + 25, flagy2 - 5)])
            flag.set_color(.8, .8, 0)
            self.viewer.add_geom(flag)

        pos = self.state[0]
        self.cartrans.set_translation((pos - self.env.min_position) * scale, self._height(pos) * scale)
        self.cartrans.set_rotation(math.cos(3 * pos))

        return self.viewer.render(return_rgb_array= mode=='rgb_array')

    def get_keys_to_action(self):
        return {(): 1, (276,): 0, (275,): 2, (275, 276): 1}  # control with left and right arrow keys 

    def close(self):
        if self.viewer:
            self.viewer.close()
            self.viewer = None
