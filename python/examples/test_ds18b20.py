#!/usr/bin/env python 
#-*- coding: utf-8 -*-

import glob
import time


BASE_DIR = '/sys/bus/w1/devices/'

class DS18B20:
    """ Read the 1-Wire DS18B20 temperatures """
    def __init__( self ):
        self.device_folders = glob.glob( BASE_DIR + '28*')

    def read_temp_raw( self, device_folder ):
        f = open( '%s/w1_slave' % device_folder, 'r')
        lines = f.readlines()
        f.close()
        return lines

    def read_device_temp( self, device_folder ):
        """ extract the temperature from device file """
        lines = self.read_temp_raw( device_folder )
        # Wait until we got a valid measurement
        while lines[0].strip()[-3:] != 'YES':
            time.sleep(0.2)
            lines = self.read_temp_raw( device_folder )
        if 't=' in  lines[1]:
            vals = lines[1].strip().split('t=')
            temp_c = float(vals[1]) / 1000.0
            return ( vals[0].strip(), temp_c )
        else:
            return None

    @property
    def temp( self ): 
        """ Read temperature from one single DS18B20 sensor. """
        return self.read_device_temp( self.device_folders[0] )[1]

    def read_all( self ):
        """ Read all DS18B20 temperatures sensors and returns a
            list of (rom,temp) tuples """
        _r = []
        for device_folder in self.device_folders:
            _r.append( self.read_device_temp(device_folder) )
        return _r

sensors = DS18B20()
print( '--- Read onboard DS1820 temperature ---' )
for i in range(5):
    print( 'Iteration %i: %6.3f Celcius' % (i,sensors.temp) )
    time.sleep(1)

print( '--- Read all DS1820 sensors on the 1-Wire bus ---' )
for i in range( 5 ):
    print( 'Iteration: %i' % i )
    for reading in sensors.read_all():
        print( '    >>> ROM: %s, Temp: %6.3f Celsius' % reading )	
    time.sleep(1)
