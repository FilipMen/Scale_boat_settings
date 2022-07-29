
from cgi import print_form
import math as m
from time import time
import numpy as np
from ahrs.filters import EKF
from ahrs.common.orientation import acc2q
from magnetic_field_calculator import MagneticFieldCalculator
import pandas as pd

sensorData = pd.read_csv('C:/Users/juanm/Documents/GitHub/Scale_boat_settings/GUI/Data/Data(4).csv')

print(sensorData.loc[1:5,'AccX':'AccZ'])

accData = sensorData.loc[:,'AccX':'AccZ'].to_numpy()*(4*9.81/32768)
GyrData = sensorData.loc[:,'GyrX':'GyrZ'].to_numpy()*(1000/32768)*(np.pi/180)
MagData = sensorData.loc[:,'MagX':'MagZ'].to_numpy()
Time = sensorData.loc[:,'TimeStamp']







magnetometer = MagneticFieldCalculator()

result = magnetometer.calculate(
    latitude=-80, ##GPS readings
    longitude=140,
)

field_value = result['field-value']
declination = field_value['inclination']['value']




sensor = EKF(magnetic_ref=declination,frequency=50)

Qk1 = np.array([1,0,0,0])

for i in range(1,10):

    acc_data = accData[i]
    gyr_data = GyrData[i]
    mag_data = MagData[i]

    Q = sensor.update(gyr=gyr_data, acc=acc_data, mag=mag_data,q = Qk1)
    Qk1 = Q
    roll = m.atan2(2*(Q[0]*Q[1]+Q[2]*Q[3]),1-2*(Q[1]**2+Q[2]**2))
    pitch = m.asin(2*(Q[0]*Q[2]-Q[1]*Q[3]))
    yaw = m.atan2(2*(Q[0]*Q[3]+Q[1]*Q[2]),1-2*(Q[2]**2+Q[3]**2))
    print("roll: %f pitch: %f yaw: %f" %(roll,pitch,yaw))






        



