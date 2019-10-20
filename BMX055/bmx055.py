#!/usr/bin/python3
# -*- coding: utf-8 -*-

import smbus
import time

ACC_ADDRESS = 0x19
ACC_REGISTER_ADDRESS = 0x02
GYRO_ADDRESS = 0x69
GYRO_REGISTER_ADDRESS = 0x02
MAG_ADDRESS = 0x13
MAG_REGISTER_ADDRESS = 0x42

def get_acc(i2c):
    x_lsb = i2c.read_byte_data(ACC_ADDRESS, ACC_REGISTER_ADDRESS)
    x_msb = i2c.read_byte_data(ACC_ADDRESS, ACC_REGISTER_ADDRESS+1)
    y_lsb = i2c.read_byte_data(ACC_ADDRESS, ACC_REGISTER_ADDRESS+2)
    y_msb = i2c.read_byte_data(ACC_ADDRESS, ACC_REGISTER_ADDRESS+3)
    z_lsb = i2c.read_byte_data(ACC_ADDRESS, ACC_REGISTER_ADDRESS+4)
    z_msb = i2c.read_byte_data(ACC_ADDRESS, ACC_REGISTER_ADDRESS+5)

    x_value = (x_msb * 16) + ((x_lsb & 0xF0) / 16)
    x_value = x_value if x_value < 2048 else x_value - 4096
    y_value = (y_msb * 16) + ((y_lsb & 0xF0) / 16)
    y_value = y_value if y_value < 2048 else y_value - 4096
    z_value = (z_msb * 16) + ((z_lsb & 0xF0) / 16)
    z_value = z_value if z_value < 2048 else z_value - 4096
    
    x_acc = x_value * 0.009604
    y_acc = y_value * 0.009604
    z_acc = z_value * 0.009604

    #x_acc = x_value * 0.00098
    #y_acc = y_value * 0.00098
    #z_acc = z_value * 0.00098


    return x_acc, y_acc, z_acc


def get_gyro(i2c):
    x_lsb = i2c.read_byte_data(GYRO_ADDRESS, GYRO_REGISTER_ADDRESS)
    x_msb = i2c.read_byte_data(GYRO_ADDRESS, GYRO_REGISTER_ADDRESS+1)
    y_lsb = i2c.read_byte_data(GYRO_ADDRESS, GYRO_REGISTER_ADDRESS+2)
    y_msb = i2c.read_byte_data(GYRO_ADDRESS, GYRO_REGISTER_ADDRESS+3)
    z_lsb = i2c.read_byte_data(GYRO_ADDRESS, GYRO_REGISTER_ADDRESS+4)
    z_msb = i2c.read_byte_data(GYRO_ADDRESS, GYRO_REGISTER_ADDRESS+5)

    x_value = (x_msb * 256) + x_lsb
    x_value = x_value if x_value < 32768 else x_value - 65536
    y_value = (y_msb * 256) + y_lsb
    y_value = y_value if y_value < 32768 else y_value - 65536
    z_value = (z_msb * 256) + z_lsb
    z_value = z_value if z_value < 32768 else z_value - 65536
    
    x_gyro = x_value * 0.0038
    y_gyro = y_value * 0.0038
    z_gyro = z_value * 0.0038

    return x_gyro, y_gyro, z_gyro
    

def get_mag(i2c):
    x_lsb = i2c.read_byte_data(MAG_ADDRESS, MAG_REGISTER_ADDRESS)
    x_msb = i2c.read_byte_data(MAG_ADDRESS, MAG_REGISTER_ADDRESS+1)
    y_lsb = i2c.read_byte_data(MAG_ADDRESS, MAG_REGISTER_ADDRESS+2)
    y_msb = i2c.read_byte_data(MAG_ADDRESS, MAG_REGISTER_ADDRESS+3)
    z_lsb = i2c.read_byte_data(MAG_ADDRESS, MAG_REGISTER_ADDRESS+4)
    z_msb = i2c.read_byte_data(MAG_ADDRESS, MAG_REGISTER_ADDRESS+5)

    x_value = (x_msb * 8) + ((x_lsb & 0xF8) / 8)
    x_value = x_value if x_value < 4096 else x_value - 8192
    y_value = (y_msb * 8) + ((y_lsb & 0xF8) / 8)
    y_value = y_value if y_value < 4096 else y_value - 8192
    z_value = (z_msb * 2) + ((z_lsb & 0xFE) / 2)
    z_value = z_value if z_value < 16384 else z_value - 32768

    x_mag = x_value
    y_mag = y_value
    z_mag = z_value
        
    return x_mag, y_mag, z_mag


def bmx055():
    # initialize
    i2c = smbus.SMBus(1)

    i2c.write_byte_data(ACC_ADDRESS, 0x0F, 0x03)  # +/- 2g

    i2c.write_byte_data(GYRO_ADDRESS, 0x0F, 0x04)  # +/- 125 degree/s

    i2c.write_byte_data(MAG_ADDRESS, 0x4B, 0x83)  # soft reset

    
    for i in range(10):
      x_acc, y_acc, z_acc = get_acc(i2c)
      x_gyro, y_gyro, z_gyro = get_gyro(i2c)
      x_mag, y_mag, z_mag = get_mag(i2c)

      print ("=====")
      print ("ACC [%f, %f, %f]" % (x_acc, y_acc, z_acc))
      print ("GYRO [%f, %f, %f]" % (x_gyro, y_gyro, z_gyro))
      print ("MAG [%f, %f, %f]" % (x_mag, y_mag, z_mag))

      time.sleep(1)

    i2c.close()
    

if __name__ == '__main__':
    bmx055()

