#!/bin/bash

while true
do
        humidity_per=`tail ~/data/factory1/humidity_per -n 1`
        temperature_cel=`tail ~/data/factory1/temperature_cel -n 1`
        machines=`tail ~/data/factory1/machines -n 1`
        running_machines=`tail ~/data/factory1/running_machines -n 1`
        units_prod=`tail ~/data/factory1/units_prod -n 1`
        units_def=`tail ~/data/factory1/units_def -n 1`
        energy_mach_1=`tail ~/data/factory1/energy_mach_1 -n 1`
        energy_mach_2=`tail ~/data/factory1/energy_mach_2 -n 1`
        energy_mach_3=`tail ~/data/factory1/energy_mach_3 -n 1`
        energy_mach_4=`tail ~/data/factory1/energy_mach_4 -n 1`
        energy_mach_5=`tail ~/data/factory1/energy_mach_5 -n 1`

        PAYLOAD=$( jq -c -n \
        --arg energy_mach_1 $energy_mach_1 \
        --arg energy_mach_2 $energy_mach_2 \
        --arg energy_mach_3 $energy_mach_3 \
        --arg energy_mach_4 $energy_mach_4 \
        --arg energy_mach_5 $energy_mach_5 \
        --arg humidity_per $humidity_per \
        --arg machines $machines \
        --arg running_machines $running_machines \
        --arg temperature_cel $temperature_cel \
        --arg units_def $units_def \
        --arg units_prod $units_prod \
        '{"humidity_per":$humidity_per,"temperature_cel":$temperature_cel,"machines":$machines,"running_machines":$running_machines,"units_prod":$units_prod,"units_def":$units_def,"energy_mach_1":$energy_mach_1,"energy_mach_2":$energy_mach_2,"energy_mach_3":$energy_mach_3,"energy_mach_4":$energy_mach_4,"energy_mach_5":$energy_mach_5}' )

        firebase database:update /messages/factory1/-N_Z6wrta_BZWaqE_M1c --data $PAYLOAD --project fy-project-335c2 --force
	sleep 30

done
