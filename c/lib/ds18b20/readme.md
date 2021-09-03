# DS18B20 - 1-Wire DS18B20 reader via the Linux FileSystem

The `DS18B20` class defined in this library can be used to read the temperature.

When 1-Wire interface is activated with `raspi-config`, the DS18B20 temperature can be read from the `/sys/bus/w1/devices/28-00*/w1_slave` path.

# Credit and License

This library is based on the work of [TeraHz published here on GitHub](https://github.com/TeraHz/DS18B20).

This keeps the same LICENSE.
