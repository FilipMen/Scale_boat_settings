# -*- coding: utf-8 -*-

# Form implementation generated from reading ui file 'ui.ui'
#
# Created by: PyQt5 UI code generator 5.15.6
#
# WARNING: Any manual changes made to this file will be lost when pyuic5 isp
# run again.  Do not edit this file unless you know what you are doing.

from hamcrest import none
from PyQt5 import QtCore, QtGui, QtWidgets
import time
import string
#import pynmea2
import pandas as pd
import os
from PyQt5 import QtWebEngineWidgets
import json
from  PyQt5.QtWebEngineWidgets import *
from PyQt5.QtCore import *
import numpy as np
from decimal import Decimal
from pubnub.pnconfiguration import PNConfiguration
from pubnub.pubnub import PubNub
from pubnub.exceptions import PubNubException
from PyQt5.QtWidgets import *
import pyqtgraph as pg
from utils import TimeAxisItem, timestamp, timestamp1
from qtwidgets import Toggle
import serial
import serial.tools.list_ports
import keyboard
import csv
from os.path import exists
from datetime import datetime
import pytz
from ahrs.filters.complementary import Complementary
from ahrs.common.orientation import acc2q
from ahrs.common.orientation import ecompass
from magnetic_field_calculator import MagneticFieldCalculator
import math as m
from scipy.spatial.transform import Rotation as R





magnetometer = MagneticFieldCalculator()

result = magnetometer.calculate(
    latitude=-6.198363, ##GPS readings
    longitude=-75.579292,
)


field_value = result['field-value']
declination = field_value['inclination']['value']

BaudRates = ['2400','4800','9600','19200','57600','115200']

pnChannel = "raspi-tracker"

coor = np.genfromtxt("coordsResuMP.txt", delimiter = " ", skip_header = 1)
pnconfig = PNConfiguration()
pnconfig.publish_key = "pub-c-538b35ba-c872-43c7-8d00-6e6b98ce8d18"
pnconfig.subscribe_key = "sub-c-700df5b3-5efa-4d2a-89d6-f51d59e758a2"
pnconfig.uuid = "boat"
pnconfig.ssl = False

pubnub = PubNub(pnconfig)
pubnub.subscribe().channels(pnChannel).execute()

class Ui_MainWindow(object):
    def setupUi(self, MainWindow):
        MainWindow.setObjectName("MainWindow")
        MainWindow.resize(893, 712)
        self.centralwidget = QtWidgets.QWidget(MainWindow)
        self.centralwidget.setObjectName("centralwidget")
        self.gridLayout_2 = QtWidgets.QGridLayout(self.centralwidget)
        self.gridLayout_2.setObjectName("gridLayout_2")
        self.groupBox = QtWidgets.QGroupBox(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBox.sizePolicy().hasHeightForWidth())
        self.groupBox.setSizePolicy(sizePolicy)
        self.groupBox.setMinimumSize(QtCore.QSize(0, 0))
        self.groupBox.setMaximumSize(QtCore.QSize(1920, 1920))
        self.groupBox.setObjectName("groupBox")
        self.gridLayout_3 = QtWidgets.QGridLayout(self.groupBox)
        self.gridLayout_3.setObjectName("gridLayout_3")
        self.line = QtWidgets.QFrame(self.groupBox)
        self.line.setFrameShape(QtWidgets.QFrame.HLine)
        self.line.setFrameShadow(QtWidgets.QFrame.Sunken)
        self.line.setObjectName("line")
        self.gridLayout_3.addWidget(self.line, 2, 0, 1, 5)
        self.radioControl = Toggle(self.groupBox)
        self.radioControl.setObjectName("radioControl")
        self.gridLayout_3.addWidget(self.radioControl, 1, 2, 1, 2)
        self.label_17 = QtWidgets.QLabel(self.groupBox)
        self.label_17.setObjectName("label_17")
        self.gridLayout_3.addWidget(self.label_17, 1, 0, 1, 2)
        self.label_16 = QtWidgets.QLabel(self.groupBox)
        self.label_16.setObjectName("label_16")
        self.gridLayout_3.addWidget(self.label_16, 0, 0, 1, 2)
        self.enableBoat = Toggle(self.groupBox)
        self.enableBoat.setObjectName("enableBoat")
        self.gridLayout_3.addWidget(self.enableBoat, 0, 2, 1, 2)
        self.widget_2 = QtWidgets.QWidget(self.groupBox)
        self.widget_2.setObjectName("widget_2")
        self.gridLayout_8 = QtWidgets.QGridLayout(self.widget_2)
        self.gridLayout_8.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_8.setObjectName("gridLayout_8")
        self.verticalSlider = QtWidgets.QSlider(self.widget_2)
        self.verticalSlider.setMinimumSize(QtCore.QSize(50, 0))
        self.verticalSlider.setOrientation(QtCore.Qt.Vertical)
        self.verticalSlider.setTickPosition(QtWidgets.QSlider.TicksBothSides)
        self.verticalSlider.setMaximum(180)
        self.verticalSlider.setTickInterval(10)
        self.verticalSlider.setObjectName("verticalSlider")
        self.gridLayout_8.addWidget(self.verticalSlider, 1, 1, 1, 1)
        self.PWM1 = QtWidgets.QLineEdit(self.widget_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.PWM1.sizePolicy().hasHeightForWidth())
        self.PWM1.setSizePolicy(sizePolicy)
        self.PWM1.setMinimumSize(QtCore.QSize(50, 0))
        self.PWM1.setMaximumSize(QtCore.QSize(50, 16777215))
        self.PWM1.setReadOnly(True)
        self.PWM1.setObjectName("PWM1")
        self.gridLayout_8.addWidget(self.PWM1, 3, 1, 1, 1)
        self.label_7 = QtWidgets.QLabel(self.widget_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_7.sizePolicy().hasHeightForWidth())
        self.label_7.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setBold(True)
        self.label_7.setFont(font)
        self.label_7.setObjectName("label_7")
        self.gridLayout_8.addWidget(self.label_7, 0, 1, 1, 1)
        spacerItem = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_8.addItem(spacerItem, 3, 0, 1, 1)
        spacerItem1 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_8.addItem(spacerItem1, 3, 2, 1, 1)
        self.gridLayout_3.addWidget(self.widget_2, 3, 0, 2, 4)
        self.widget = QtWidgets.QWidget(self.groupBox)
        self.widget.setLayoutDirection(QtCore.Qt.LeftToRight)
        self.widget.setObjectName("widget")
        self.gridLayout_7 = QtWidgets.QGridLayout(self.widget)
        self.gridLayout_7.setContentsMargins(0, 0, 0, 0)
        self.gridLayout_7.setObjectName("gridLayout_7")
        spacerItem2 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_7.addItem(spacerItem2, 3, 0, 1, 1)
        self.rudder = QtWidgets.QLineEdit(self.widget)
        self.rudder.setMaximumSize(QtCore.QSize(50, 21))
        self.rudder.setAlignment(QtCore.Qt.AlignCenter)
        self.rudder.setReadOnly(True)
        self.rudder.setObjectName("rudder")
        self.gridLayout_7.addWidget(self.rudder, 3, 1, 1, 1)
        spacerItem3 = QtWidgets.QSpacerItem(40, 20, QtWidgets.QSizePolicy.Expanding, QtWidgets.QSizePolicy.Minimum)
        self.gridLayout_7.addItem(spacerItem3, 3, 2, 1, 1)
        self.horizontalSlider = QtWidgets.QSlider(self.widget)
        self.horizontalSlider.setMaximum(180)
        self.horizontalSlider.setSliderPosition(128)
        self.horizontalSlider.setOrientation(QtCore.Qt.Horizontal)
        self.horizontalSlider.setObjectName("horizontalSlider")
        self.gridLayout_7.addWidget(self.horizontalSlider, 1, 0, 1, 3)
        self.label_14 = QtWidgets.QLabel(self.widget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_14.sizePolicy().hasHeightForWidth())
        self.label_14.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setBold(True)
        self.label_14.setFont(font)
        self.label_14.setAlignment(QtCore.Qt.AlignCenter)
        self.label_14.setObjectName("label_14")
        self.gridLayout_7.addWidget(self.label_14, 0, 0, 1, 3)
        self.gridLayout_3.addWidget(self.widget, 5, 0, 1, 4)
        self.gridLayout_2.addWidget(self.groupBox, 2, 0, 1, 1)
        self.tabWidget = QtWidgets.QTabWidget(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Preferred)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.tabWidget.sizePolicy().hasHeightForWidth())
        self.tabWidget.setSizePolicy(sizePolicy)
        self.tabWidget.setMaximumSize(QtCore.QSize(16777215, 320))
        self.tabWidget.setObjectName("tabWidget")
        self.tab_2 = QtWidgets.QWidget()
        self.tab_2.setObjectName("tab_2")
        self.gridLayout_5 = QtWidgets.QGridLayout(self.tab_2)
        self.gridLayout_5.setObjectName("gridLayout_5")
        self.Roll = timePlot1(self.tab_2)
        self.Roll.setObjectName("Roll")
        self.gridLayout_5.addWidget(self.Roll, 0, 0, 1, 1)
        self.Pitch = timePlot1(self.tab_2)
        self.Pitch.setObjectName("Pitch")
        self.gridLayout_5.addWidget(self.Pitch, 0, 1, 1, 1)
        self.Yaw = timePlot1(self.tab_2)
        self.Yaw.setObjectName("Yaw")
        self.gridLayout_5.addWidget(self.Yaw, 0, 2, 1, 1)
        self.tabWidget.addTab(self.tab_2, "")
        self.tab = QtWidgets.QWidget()
        self.tab.setObjectName("tab")
        self.gridLayout_4 = QtWidgets.QGridLayout(self.tab)
        self.gridLayout_4.setObjectName("gridLayout_4")
        self.AccX = timePlot(self.tab)
        self.AccX.setObjectName("AccX")
        self.gridLayout_4.addWidget(self.AccX, 0, 0, 1, 1)
        self.AccY = timePlot(self.tab)
        self.AccY.setObjectName("AccY")
        self.gridLayout_4.addWidget(self.AccY, 0, 1, 1, 1)
        self.tabWidget.addTab(self.tab, "")
        self.gridLayout_2.addWidget(self.tabWidget, 0, 1, 1, 1)
        self.groupBox_3 = QtWidgets.QGroupBox(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Preferred, QtWidgets.QSizePolicy.Expanding)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBox_3.sizePolicy().hasHeightForWidth())
        self.groupBox_3.setSizePolicy(sizePolicy)
        self.groupBox_3.setObjectName("groupBox_3")
        self.gridLayout_6 = QtWidgets.QGridLayout(self.groupBox_3)
        self.gridLayout_6.setObjectName("gridLayout_6")
        self.webEngineView = QtWebEngineWidgets.QWebEngineView(self.groupBox_3)
        self.webEngineView.setUrl(QtCore.QUrl("about:blank"))
        self.webEngineView.setObjectName("webEngineView")
        self.gridLayout_6.addWidget(self.webEngineView, 0, 0, 1, 1)
        self.gridLayout_2.addWidget(self.groupBox_3, 2, 1, 1, 1)
        self.groupBox_2 = QtWidgets.QGroupBox(self.centralwidget)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.groupBox_2.sizePolicy().hasHeightForWidth())
        self.groupBox_2.setSizePolicy(sizePolicy)
        self.groupBox_2.setObjectName("groupBox_2")
        self.gridLayout = QtWidgets.QGridLayout(self.groupBox_2)
        self.gridLayout.setObjectName("gridLayout")
        self.accy1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.accy1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.accy1.setFont(font)
        self.accy1.setReadOnly(True)
        self.accy1.setObjectName("accy1")
        self.gridLayout.addWidget(self.accy1, 4, 1, 1, 1)
        self.vel1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.vel1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.vel1.setFont(font)
        self.vel1.setReadOnly(True)
        self.vel1.setObjectName("vel1")
        self.gridLayout.addWidget(self.vel1, 6, 1, 1, 1)
        self.label_13 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_13.sizePolicy().hasHeightForWidth())
        self.label_13.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_13.setFont(font)
        self.label_13.setObjectName("label_13")
        self.gridLayout.addWidget(self.label_13, 9, 0, 1, 1)
        self.curr1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.curr1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.curr1.setFont(font)
        self.curr1.setReadOnly(True)
        self.curr1.setObjectName("curr1")
        self.gridLayout.addWidget(self.curr1, 7, 1, 1, 1)
        self.label_11 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_11.sizePolicy().hasHeightForWidth())
        self.label_11.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_11.setFont(font)
        self.label_11.setObjectName("label_11")
        self.gridLayout.addWidget(self.label_11, 6, 0, 1, 1)
        self.pitch1 = QtWidgets.QLineEdit(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.pitch1.sizePolicy().hasHeightForWidth())
        self.pitch1.setSizePolicy(sizePolicy)
        self.pitch1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.pitch1.setFont(font)
        self.pitch1.setReadOnly(True)
        self.pitch1.setObjectName("pitch1")
        self.gridLayout.addWidget(self.pitch1, 0, 1, 1, 1)
        self.label_9 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_9.sizePolicy().hasHeightForWidth())
        self.label_9.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_9.setFont(font)
        self.label_9.setObjectName("label_9")
        self.gridLayout.addWidget(self.label_9, 2, 0, 1, 1)
        self.vol1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.vol1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.vol1.setFont(font)
        self.vol1.setReadOnly(True)
        self.vol1.setObjectName("vol1")
        self.gridLayout.addWidget(self.vol1, 9, 1, 1, 1)
        self.label = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label.sizePolicy().hasHeightForWidth())
        self.label.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label.setFont(font)
        self.label.setObjectName("label")
        self.gridLayout.addWidget(self.label, 0, 0, 1, 1)
        self.label_12 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_12.sizePolicy().hasHeightForWidth())
        self.label_12.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_12.setFont(font)
        self.label_12.setObjectName("label_12")
        self.gridLayout.addWidget(self.label_12, 7, 0, 1, 1)
        self.label_15 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_15.sizePolicy().hasHeightForWidth())
        self.label_15.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_15.setFont(font)
        self.label_15.setObjectName("label_15")
        self.gridLayout.addWidget(self.label_15, 4, 0, 1, 1)
        self.yaw1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.yaw1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.yaw1.setFont(font)
        self.yaw1.setReadOnly(True)
        self.yaw1.setObjectName("yaw1")
        self.gridLayout.addWidget(self.yaw1, 2, 1, 1, 1)
        self.label_10 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_10.sizePolicy().hasHeightForWidth())
        self.label_10.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_10.setFont(font)
        self.label_10.setObjectName("label_10")
        self.gridLayout.addWidget(self.label_10, 3, 0, 1, 1)
        self.roll1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.roll1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.roll1.setFont(font)
        self.roll1.setReadOnly(True)
        self.roll1.setObjectName("roll1")
        self.gridLayout.addWidget(self.roll1, 1, 1, 1, 1)
        self.accx1 = QtWidgets.QLineEdit(self.groupBox_2)
        self.accx1.setMaximumSize(QtCore.QSize(100, 16777215))
        font = QtGui.QFont()
        font.setPointSize(9)
        self.accx1.setFont(font)
        self.accx1.setReadOnly(True)
        self.accx1.setObjectName("accx1")
        self.gridLayout.addWidget(self.accx1, 3, 1, 1, 1)
        self.label_2 = QtWidgets.QLabel(self.groupBox_2)
        sizePolicy = QtWidgets.QSizePolicy(QtWidgets.QSizePolicy.Fixed, QtWidgets.QSizePolicy.Fixed)
        sizePolicy.setHorizontalStretch(0)
        sizePolicy.setVerticalStretch(0)
        sizePolicy.setHeightForWidth(self.label_2.sizePolicy().hasHeightForWidth())
        self.label_2.setSizePolicy(sizePolicy)
        font = QtGui.QFont()
        font.setPointSize(9)
        self.label_2.setFont(font)
        self.label_2.setObjectName("label_2")
        self.gridLayout.addWidget(self.label_2, 1, 0, 1, 1)
        self.gridLayout_2.addWidget(self.groupBox_2, 0, 0, 1, 1)
        MainWindow.setCentralWidget(self.centralwidget)
        self.menubar = QtWidgets.QMenuBar(MainWindow)
        self.menubar.setGeometry(QtCore.QRect(0, 0, 893, 22))
        self.menubar.setObjectName("menubar")
        MainWindow.setMenuBar(self.menubar)
        self.statusbar = QtWidgets.QStatusBar(MainWindow)
        self.statusbar.setObjectName("statusbar")
        MainWindow.setStatusBar(self.statusbar)

        self.retranslateUi(MainWindow)
        self.tabWidget.setCurrentIndex(0)
        QtCore.QMetaObject.connectSlotsByName(MainWindow)

    def retranslateUi(self, MainWindow):
        _translate = QtCore.QCoreApplication.translate
        MainWindow.setWindowTitle(_translate("MainWindow", "MainWindow"))
        self.groupBox.setTitle(_translate("MainWindow", "Control"))
        self.radioControl.setText(_translate("MainWindow", "Enable"))
        self.label_17.setText(_translate("MainWindow", "Radio control:"))
        self.label_16.setText(_translate("MainWindow", "Enable boat:"))
        self.enableBoat.setText(_translate("MainWindow", "Enable"))
        self.label_7.setText(_translate("MainWindow", "Motor power"))
        self.label_14.setText(_translate("MainWindow", "Rudder angle"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab_2), _translate("MainWindow", "Tab 2"))
        self.tabWidget.setTabText(self.tabWidget.indexOf(self.tab), _translate("MainWindow", "Tab 1"))
        self.groupBox_3.setTitle(_translate("MainWindow", "Geolocalization"))
        self.groupBox_2.setTitle(_translate("MainWindow", "Variables"))
        self.label_13.setText(_translate("MainWindow", "Voltage:"))
        self.label_11.setText(_translate("MainWindow", "Velocity:"))
        self.label_9.setText(_translate("MainWindow", "Yaw:"))
        self.label.setText(_translate("MainWindow", "Pitch:"))
        self.label_12.setText(_translate("MainWindow", "Current:"))
        self.label_15.setText(_translate("MainWindow", "AccY:"))
        self.label_10.setText(_translate("MainWindow", "AccX:"))
        self.label_2.setText(_translate("MainWindow", "Roll:"))
        #-------------------------- QT designer -------------------------------#
        path = os.getcwd()
        path = path.replace("\\", "/")
        path = path.replace(" ", "%20")
        print(f"file:///{path}/Map.html")
        self.webEngineView.load(QUrl(f"file:///{path}/Map.html"))
        self.PWM1.setText(str(self.verticalSlider.value()))
        self.setRuderValue()
        self.verticalSlider.valueChanged.connect(self.setMotor1Value)
        self.horizontalSlider.valueChanged.connect(self.setRuderValue)

    def setMotor1Value(self):
        self.PWM1.setText(str(round(self.verticalSlider.value()*100/180)))

    def setRuderValue(self):
        self.rudder.setText(str(round(-90+self.horizontalSlider.value())))






class timePlot(QWidget):
    def __init__(self, parent=None, yname='Reading / mV'):
        QWidget.__init__(self, parent)
        self.plot = pg.PlotWidget(
            title="Example plot",
            labels={'left': yname},
            axisItems={'bottom': TimeAxisItem(orientation='bottom')}
        )
        self.plot.setYRange(0, 5000)
        self.plot.setXRange(timestamp(), timestamp() + 20)
        self.plot.showGrid(x=True, y=True)

        self.layout = QGridLayout(self)
        self.layout.addWidget(self.plot, 0, 0)

        self.plotCurve = self.plot.plot()
        self.plotCurve1 = self.plot.plot()

        self.plotData = {'x': [], 'y': [], 'z': []}

    def updatePlot(self, newValue, newValue1):
        self.plotData['y'].append(newValue)
        self.plotData['z'].append(newValue1)
        self.plotData['x'].append(timestamp1())
        self.plot.setYRange(min(self.plotData['y'][-150:] + self.plotData['z'][-150:]),
                            max(self.plotData['y'][-150:] + self.plotData['z'][-150:]))
        self.plot.setXRange(timestamp() - 15, timestamp() + 5)
        self.plotCurve.setData(self.plotData['x'], self.plotData['y'], pen=pg.mkPen(color=(255, 0, 0)))
        self.plotCurve1.setData(self.plotData['x'], self.plotData['z'], pen=pg.mkPen(color=(0, 255, 0)))


class Graphic_interface(QtWidgets.QMainWindow):
    def __init__(self, parent=None):
        QtWidgets.QWidget.__init__(self, parent=None)
        self.serialPort = serial.Serial()
        # ***** Tool bar declaration ********
        toolBar = QToolBar("Tool bar")
        toolButton = QToolButton()
        toolButton.setText("Select COM: ")
        toolButton.setCheckable(False)
        toolBar.addWidget(toolButton)
        self.addToolBar(toolBar)

        # ******** Text "Select COM" declaration ********
        toolButton.setText("Select COM: ")
        toolButton.setCheckable(False)
        toolBar.addWidget(toolButton)

        # ******** ComboBox for selecting the COM port ***
        self.combo = QComboBox(self)
        Coms = GetComPorts()
        for element in Coms:
            self.combo.addItem(element)
        toolBar.addWidget(self.combo)

        # ******** Text "Select BaudRate" declaration ****
        toolButton = QToolButton()
        toolButton.setText(" Select BaudRate: ")
        toolButton.setCheckable(False)
        toolBar.addWidget(toolButton)

        # ******** ComboBox for selecting the BaudRate ****
        self.combo1 = QComboBox(self)
        for element in BaudRates:
            self.combo1.addItem(element)
        toolBar.addWidget(self.combo1)

        # ******** Open Button *****************************
        self.openCOM = QPushButton()
        self.openCOM.setText("Open")
        self.openCOM.clicked.connect(self.uSerial)
        toolBar.addWidget(self.openCOM)


        # ***** Tool bar declaration ********
        toolBar2 = QToolBar("Tool bar")
        toolButton1 = QToolButton()
        # ******** Text "CSV name" declaration ********
        toolButton1.setText("File name: ")
        toolButton1.setCheckable(False)
        toolBar2.addWidget(toolButton1)

        self.lineEdit1 = QLineEdit()
        self.lineEdit1.setText('Data')
        toolBar2.addWidget(self.lineEdit1)

        self.OpenBrowser = QPushButton()
        self.OpenBrowser.setText("Open")
        toolBar2.addWidget(self.OpenBrowser)

        self.Record = Toggle()
        toolBar2.addWidget(self.Record)
        self.addToolBar(toolBar2)

        self.MainWindow = Ui_MainWindow()
        self.MainWindow.setupUi(self)

        self.path = ""
        self.mode = 10
        self.MainWindow.enableBoat.stateChanged.connect(self.setMode)
        self.MainWindow.radioControl.stateChanged.connect(self.setMode)
        self.Record.stateChanged.connect(self.InitRecord)

    def setMode(self):
        if self.MainWindow.enableBoat.isChecked():
            if self.MainWindow.radioControl.isChecked():
                self.mode = 20
            else:
                self.mode = 30
        else:
            self.mode = 10

    def UpdateSerial(self, COMport, BaudRate):
        try:
            if self.serialPort.isOpen():
                self.serialPort.close()
            self.serialPort = serial.Serial(COMport, BaudRate)
        except Exception as e:
            print(e)

    def uSerial(self):
        self.UpdateSerial(self.combo.currentText(), int(self.combo1.currentText()))

    def resizeEvent(self, event):
        super().resizeEvent(event)

    def keyReleaseEvent(self, event):
        if event.key() == QtCore.Qt.Key_W:
            if self.MainWindow.verticalSlider.value() < 180:
                self.MainWindow.verticalSlider.setValue(self.MainWindow.verticalSlider.value()+1)
        if event.key() == QtCore.Qt.Key_S:
            if self.MainWindow.verticalSlider.value() > 0:
                self.MainWindow.verticalSlider.setValue(self.MainWindow.verticalSlider.value() - 1)

        return super().keyReleaseEvent(event)

    def closeEvent(self, event):
        self.serialPort.close()
        print('El programa ha terminado!')

    def event(self, e):
        if not isinstance(e, (
            QtCore.QEvent,
            QtGui.QKeyEvent,
            QtGui.QCloseEvent,
        )):
            print("unknown event: %r %r", e.type(), e)
        return super().event(e)

    def InitRecord(self):
        if self.Record.isChecked():
            file_name = "Data/" + self.lineEdit1.text()
            file_name = "Data/Boat_data" if file_name == "" else file_name
            self.path = file_name + ".csv"
            cont = 1
            while exists(self.path):
                self.path = file_name + "({})".format(cont) + ".csv"
                cont += 1
            with open(self.path, 'a', newline='') as f:
                csvData = []
                csvData.append('TimeStamp')
                csvData.append('Roll')
                csvData.append("Pitch")
                csvData.append("Yaw")
                csvData.append("AccX")
                csvData.append("AccY")
                csvData.append("Current")
                csvData.append("Voltage")
                csvData.append('pwm1')
                csvData.append('pwm2')
                csvData.append('Motor Angle')
                csvData.append('Latitude')
                csvData.append('Longitude')
                data_writer = csv.writer(f)
                data_writer.writerow(csvData)

class timePlot1(QWidget):
    def __init__(self, parent=None, yname='Reading / mV'):
        QWidget.__init__(self, parent)
        self.plot = pg.PlotWidget(
            title="Example plot",
            labels={'left': yname},
            axisItems={'bottom': TimeAxisItem(orientation='bottom')}
        )
        self.plot.setYRange(0, 5000)
        self.plot.setXRange(timestamp(), timestamp() + 20)
        self.plot.showGrid(x=True, y=True)

        self.layout = QGridLayout(self)
        self.layout.addWidget(self.plot, 0, 0)

        self.plotCurve = self.plot.plot()
        self.plotCurve1 = self.plot.plot()
        self.plotCurve2 = self.plot.plot()

        self.plotData = {'x': [], 'y': [], 'z': [], 'z1': []}

        

    def updatePlot(self, newValue, newValue1, newValue2):
        self.plotData['y'].append(newValue)
        self.plotData['z'].append(newValue1)
        self.plotData['z1'].append(newValue2)
        self.plotData['x'].append(timestamp1())
        self.plot.setYRange(min(self.plotData['y'][-150:] + self.plotData['z'][-150:] + self.plotData['z1'][-150:]),
                            max(self.plotData['y'][-150:] + self.plotData['z'][-150:] + self.plotData['z1'][-150:]))
        self.plot.setXRange(timestamp() - 15, timestamp() + 5)
        self.plotCurve.setData(self.plotData['x'], self.plotData['y'], pen=pg.mkPen(color=(255, 0, 0)))
        self.plotCurve1.setData(self.plotData['x'], self.plotData['z'], pen=pg.mkPen(color=(0, 0, 255)))
        self.plotCurve2.setData(self.plotData['x'], self.plotData['z1'], pen=pg.mkPen(color=(0, 255, 0)))

def GetComPorts():
    comlist = serial.tools.list_ports.comports()
    connected = []
    for element in comlist:
        connected.append(element.device)
    return connected

from guiLoop import guiLoop # https://gist.github.com/niccokunzmann/8673951

@guiLoop
def Main_loop():
    tx_data = {
        "1": 0,
        "2": 0,
        "3": 0,
        "m": 0
    }
    clock_count = 0
    sample_time = 0.05
    yield_time = 0.01
    cLon1 = 0
    cLat1 = 0
    xVel_real = 0
    yVel_real = 0
    calibration = True
    
    while calibration:
        if ui.serialPort.isOpen():
            if clock_count >= sample_time/yield_time:
                clock_count = 0
                tx_data["1"] = 180 - ui.MainWindow.horizontalSlider.value()
                tx_data["2"] = keyboard.is_pressed('d') * ui.MainWindow.verticalSlider.value()
                tx_data["3"] = keyboard.is_pressed('a') * ui.MainWindow.verticalSlider.value()
                tx_data["m"] = ui.mode
                ui.serialPort.write((json.dumps(tx_data)+'\n').encode())
                #print(json.dumps(tx_data))
            else:
                clock_count += 1
            if ui.serialPort.in_waiting:
                rx = ui.serialPort.readline().decode("utf-8").rstrip('\r\n')
                try:
                    data = json.loads(rx)
                except:
                    print('fallo')
                    pass
                else:
                    ax = data["ax"]*(4*9.81/32768)
                    ay = data["ay"]*(4*9.81/32768)
                    az = data["az"]*(4*9.81/32768)

                    gx = data["gx"]*(1000/32768)*(np.pi/180)
                    gy = data["gy"]*(1000/32768)*(np.pi/180)
                    gz = data["gz"]*(1000/32768)*(np.pi/180)

                    mx = data["mx"]*(4800/(2**13))/1000
                    my = data["my"]*(4800/(2**13))/1000
                    mz = data["mz"]*(4800/(2**13))/1000

                    acc_0 = np.array([ax,ay,az])
                    acc_0 = 9.81*acc_0/np.linalg.norm(acc_0)
                    gyr_0 = np.array([gx,gy,gz])
                    mag_0 = np.array([mx,my,mz])

                    Qk1 = ecompass(acc_0, mag_0, frame='NED', representation='quaternion')
                    sensor = Complementary(frame='NED')
                    
                    calibration = False
        yield yield_time

    while True:
        if ui.serialPort.isOpen():
            if clock_count >= sample_time/yield_time:
                clock_count = 0
                tx_data["1"] = 180 - ui.MainWindow.horizontalSlider.value()
                tx_data["2"] = keyboard.is_pressed('d') * ui.MainWindow.verticalSlider.value()
                tx_data["3"] = keyboard.is_pressed('a') * ui.MainWindow.verticalSlider.value()
                tx_data["m"] = ui.mode
                ui.serialPort.write((json.dumps(tx_data)+'\n').encode())
                #print(json.dumps(tx_data))
            else:
                clock_count += 1

            if ui.serialPort.in_waiting:
                rx = ui.serialPort.readline().decode("utf-8").rstrip('\r\n')
                try:
                    data = json.loads(rx)
                except:
                    print("No Json format")
                else:
                    ''' 
                    IMU information, with this information is needed to calculate the Roll, Pitch and Yaw
                    '''
                    ax = data["ax"]*(4*9.81/32768)
                    ay = data["ay"]*(4*9.81/32768)
                    az = data["az"]*(4*9.81/32768)
                    gx = data["gx"]*(1000/32768)*(np.pi/180)
                    gy = data["gy"]*(1000/32768)*(np.pi/180)
                    gz = data["gz"]*(1000/32768)*(np.pi/180)
                    mx = data["mx"]*(4800/(2**13))/1000
                    my = data["my"]*(4800/(2**13))/1000
                    mz = data["mz"]*(4800/(2**13))/1000

                    #Estimate attitude

                    gyr_data = np.array([gx,gy,gz])
                    acc_data = np.array([ax,ay,az])
                    acc_data = 9.81*acc_0/np.linalg.norm(acc_data)
                    mag_data = np.array([mx,my,mz])
                    
                    Q = sensor.update(gyr=gyr_data-gyr_0,acc=acc_data,mag=mag_data,q = Qk1)
                    Qk1 = Q

                    r = R.from_quat([Q[1],Q[2],Q[3],Q[0]])

                    base_acc = r.apply(acc_data)

                    print(acc_data,base_acc)
                
                    ax_real = base_acc[0]
                    ay_real = base_acc[1]

                    xVel_real = xVel_real+ax_real*0.05
                    yVel_real = yVel_real+ay_real*0.05

                    roll = np.arctan2(2.0*(Q[0]*Q[1] + Q[2]*Q[3]), 1.0 - 2.0*(Q[1]**2 + Q[2]**2))*(180/m.pi)
                    pitch = np.arcsin(2.0*(Q[0]*Q[2] - Q[3]*Q[1]))*(180/m.pi)
                    yaw = np.arctan2(2.0*(Q[0]*Q[3] + Q[1]*Q[2]), 1.0 - 2.0*(Q[2]**2 + Q[3]**2))*(180/m.pi)

                    ui.MainWindow.Roll.updatePlot(roll, 0 ,0)
                    ui.MainWindow.Pitch.updatePlot(pitch, 0, 0)
                    ui.MainWindow.Yaw.updatePlot(yaw, 0, 0)
                    
                    bVol = data["bV"]/10.0
                    bCurr = data["bC"]*0.0625*0.0182-0.8094
                    ui.MainWindow.AccX.updatePlot(xVel_real,0)
                    cLat = data["lat"]/100000.0
                    cLon = data["lon"] / 100000.0
                    vel = data["vel"] /1000.0
                    ui.MainWindow.AccY.updatePlot(yVel_real, 0)
                    cLatS = str(cLat)
                    pos = cLatS.find('.')
                    cLatD = float(cLatS[0:pos-2]) + float(cLatS[pos-2:])/60.0
                    cLonS = str(cLon)
                    pos = cLonS.find('.')
                    cLonD = float(cLonS[0:pos - 2]) - float(cLonS[pos - 2:]) / 60.0
                    if (cLatD != cLat1 or cLonD != cLon1):
                        cLat1 = cLatD
                        cLon1 = cLonD
                        updateCoor(cLatD, cLonD)
                        print(f"{cLatD},{cLonD}")

                    if ui.Record.isChecked():
                        with open(ui.path, 'a',  newline='') as f:
                            csvData = []
                            csvData.append(datetime.now(pytz.timezone('America/Bogota')).strftime("%H:%M:%S.%f"))
                            csvData.append(roll)
                            csvData.append(pitch)
                            csvData.append(yaw)
                            csvData.append(xVel_real)
                            csvData.append(yVel_real)
                            csvData.append(bVol)
                            csvData.append(bCurr)
                            #csvData.append(pwm1)
                            #csvData.append(pwm2)
                            #csvData.append(mAngle)
                            csvData.append(cLatD)
                            csvData.append(cLonD)

                            data_writer = csv.writer(f)
                            data_writer.writerow(csvData)
                    ui.MainWindow.pitch1.setText(str(round(pitch, 3)))
                    ui.MainWindow.roll1.setText(str(round(roll, 3)))
                    ui.MainWindow.yaw1.setText(str(round(yaw, 3)))
                    ui.MainWindow.accx1.setText(str(round(ax_real, 3)))
                    ui.MainWindow.accy1.setText(str(round(ay_real, 3)))
                    #ui.MainWindow.vel1.setText(str(round(az, 3)))
                    ui.MainWindow.vol1.setText(str(round(bVol, 3)))
                    ui.MainWindow.curr1.setText(str(round(bCurr, 3)))
                
                #print(rx)
        yield yield_time


def updateCoor(lat, lng):
        try:
            envelope = pubnub.publish().channel(pnChannel).message({
                'lat': lat,
                'lng': lng
            }).sync()
            print("publish timetoken: %d" % envelope.result.timetoken)
        except PubNubException as e:
            print(e)

if __name__ == "__main__":
    import sys
    app = QtWidgets.QApplication(sys.argv)
    ui = Graphic_interface()
    Main_loop(ui)
    ui.show()
    sys.exit(app.exec_())
