import pyqtgraph as pg
import datetime
import time


def timestamp1():
    time_act = datetime.datetime.now().strftime('%d.%m.%Y %H:%M:%S,%f')[:-4]
    dt_obj = datetime.datetime.strptime(time_act,
                                        '%d.%m.%Y %H:%M:%S,%f')
    millisec = dt_obj.timestamp()
    return millisec


def timestamp():
    return int(time.mktime(datetime.datetime.now().timetuple()))

class TimeAxisItem(pg.AxisItem):
    def __init__(self, *args, **kwargs):
        super().__init__(*args, **kwargs)
        self.setLabel(text='Time', units=None)
        self.enableAutoSIPrefix(False)

    def tickStrings(self, values, scale, spacing):
        return [datetime.datetime.fromtimestamp(value).strftime('%H:%M:%S,%f')[:-4] for value in values]
