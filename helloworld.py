# -*- coding: utf-8 -*-
"""
Created on Wed Jan  5 00:05:00 2022

@author: bdutt
"""

import pandas as pd
import numpy as np

ts = pd.Series(np.random.randn(1000), index = pd.date_range("1/1/2000", periods=1000))
ts = ts.cumsum()
ts.plot()