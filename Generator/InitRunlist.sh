#!/bin/bash
if [ "$#" -eq 1 ] && [ "${1}" -ge 1 ] && [ "${1}" -le 3 ]; then
	if [ "${1}" -eq 1 ]; then
		generator="pure"
	elif [ "${1}" -eq 2 ]; then
		generator="nonflow"
	elif [ "${1}" -eq 3 ]; then
		generator="acceptance"
	fi
else
	echo "Usage:  InitRunlist.sh _ Generator type"
	echo "Generator type 1 - pure flow"
	echo "Generator type 2 - with nonflow"
	echo "Generator type 3 - with acceptance effect"
	exit
fi
ls /weekly/$USER/lbavinh/Generator/OUT/${generator}/v2hadron_*.root > /weekly/$USER/lbavinh/Generator/OUT/${generator}/runlist.list