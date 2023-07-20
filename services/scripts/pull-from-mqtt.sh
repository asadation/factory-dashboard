#!/bin/bash 

mosquitto_sub -h 34.74.80.63 -t Factory/factory1/sensor/humidity | tee ~/data/factory1/humidity_per
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/sensor/temperature | tee ~/data/factory1/temperature_cel
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/machines/number | tee ~/data/factory1/machines
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/machines/running | tee ~/data/factory1/running_machines
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/units/produced | tee ~/data/factory1/units_prod
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/units/defected | tee ~/data/factory1/units_def
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/energy/machine1 | tee ~/data/factory1/energy_mach_1
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/energy/machine2 | tee ~/data/factory1/energy_mach_2
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/energy/machine3 | tee ~/data/factory1/energy_mach_3
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/energy/machine4 | tee ~/data/factory1/energy_mach_4
mosquitto_sub -h 34.74.80.63 -t Factory/factory1/energy/machine5 | tee ~/data/factory1/energy_mach_5
