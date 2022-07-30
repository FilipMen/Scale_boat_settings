import quaternion
from sympy import Quaternion
import numpy as np
from hamcrest import none
from scipy.spatial.transform import Rotation as R
from ahrs.common.orientation import acc2q
from sympy import Quaternion

def skew(vec):
    skw = np.array([[0,-vec[2],vec[1]],
                    [vec[2],0,-vec[0]],
                    [-vec[1],vec[0],0]])
    return skw

# class Kalman():
#     def __init__(self,acc_data,mag_data):
#         self.acc = acc_data
#         self.mag = mag_data
#         r3 = np.array([acc_data]).T
#         r1 = (1/np.linalg.norm())


# A = np.array([[1,2,3],[4,5,6],[7,8,9]])



acc_data = [0.2945874,0.6682104,9.22561523]

acc_data = (acc_data/np.linalg.norm(acc_data))



Q = acc2q(acc_data)


quart = Quaternion(Q[0],Q[1],Q[2],Q[3])

ac = Quaternion.rotate_point([0,0,-9.81],quart)

r = R.from_quat([Q[1],Q[2],Q[3],Q[0]])
ab = r.apply(acc_data)

print(skew(acc_data))
















