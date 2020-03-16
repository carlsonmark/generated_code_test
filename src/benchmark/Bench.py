# Comparing numpy against C++

import numpy as np
import timeit


def apod_sine_bell(data,rows,cols):
    radScale = np.pi / (rows - 1)
    for row in range(rows):
        scalingFactor = np.sin(row * radScale)
        data[row,:] *= scalingFactor
    return


def apod_sine_bell_noloop(data,rows,cols):
    radScale = np.pi / (rows - 1)
    factors = np.sin(np.arange(rows).reshape(-1,1) * radScale)
    data *= factors
    return


def setup_data():
    s = '''\
import numpy as np
data = np.ones((1024,1024)) * 0.11 + np.ones((1024,1024)) * 0.11j 
    '''
    return s


def run_benchmarks(number=100):
    cmd = 'apod_sine_bell(data,1024,1024)'
    print(cmd, '{:9.0f} ns'.format(1e9*timeit.timeit(cmd, setup='from __main__ import apod_sine_bell; ' + setup_data(), number=number)/number),
          'per iteration')
    cmd = 'apod_sine_bell_noloop(data,1024,1024)'
    print(cmd, '{:9.0f} ns'.format(1e9*timeit.timeit(cmd, setup='from __main__ import apod_sine_bell_noloop; ' + setup_data(), number=number)/number),
          'per iteration')
    return


if __name__ == '__main__':
    run_benchmarks()
    # d=np.ones((5,5)) * 0.11 + np.ones((5,5)) * 0.11j
    # apod_sine_bell(d,5,5)
    # print(d)
    d=np.ones((5,5)) * 0.11 + np.ones((5,5)) * 0.11j
    apod_sine_bell_noloop(d,5,5)
    print(d)
