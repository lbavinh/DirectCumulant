#!/bin/bash

#source ~/bnl/vendor/root-5.34.36/root/bin/thisroot.sh
source ./env_script.sh

# Generate a random seed for the job
# # crypto quality random number - should also work in parallel since thread safe
trandom="$(od -vAn -N4 -tu4 < /dev/urandom | tr -d '[:space:]')"
echo  "./bin/toymc.app --seed $(($trandom+0)) --generate --harm 2 --nevents 100000 --ptmin 0.3 --ptmax 3.0 --etamin -2.4 --etamax 2.4 --multmin 10 --multmax 20 --isVnfluct 0 --output cntreeout"
./bin/toymc.app --seed $(($trandom+0)) --generate --harm 2 --nevents 100000 --ptmin 0.3 --ptmax 3.0 --etamin -2.4 --etamax 2.4 --multmin 200 --multmax 201 --isVnfluct 0 --output cntreeout_2
echo  "./bin/toymc.app --analyze --nevents 100000 --input cntreeout --output vnresults"
./bin/toymc.app --analyze --nevents 100000 --input cntreeout_2 --output vnresults_2 --seed 0
