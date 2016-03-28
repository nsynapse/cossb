# cossb
Component-based Open &amp; Simple Service Broker

Features
===============
1. IoT(Internet of Things) software framework for Robotic services.
2. Service components can be downloaded/installed/uninstalled/updated dynamically responding to what devices have services in same network environment. Thus, our goal is that any services can be changed dynamically with no user or supervisor intervention. (Except the initial setting up).
3. Fast by using C/C++. Lesser computational power might be required under the same condition. You can obtain more advantages for the device form-factor, budget and so on..
4. loose-coupled with other services by Service Broker. This gives advantages like a service re-configuration or re-combination)
5. Not only for High performance computing machine(like a PC), It is going for the cheap embedded hardware devices like Raspberry Pi, Odroid..


Getting Started
===============

COSSB Usage
-------

COSSB application should be launched with administrative permission.

1. Run with manifest.xml

```
$ sudo cossb --run <your manifest.xml>
```


2. Show Version

```
$ sudo cossb --version
```

3. Help

```
$ sudo cossb --help
```

Supports
===============

* TCP Server using epoll (Linux only available)

Examples
===============
* Simple Hello World component
* UART component
* Simple Message Out component
* Simple Message Print component
* I2C component for Intel Edison
* GPIO component for Intel Edison



License
===============
You can freely use, modify, redistribute this source code under the 3-clause BSD License.
Some parts of the components and core libraries use open source code under the other license(LGPL, MIT..).
