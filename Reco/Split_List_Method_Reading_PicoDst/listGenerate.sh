#!/bin/bash
echo "Did they add something new?"
ls /weekly/parfenov/mpd_winter2019/mpd_prod/7.7gev/picodst/ | wc -l
mkdir -p /weekly/$USER/lbavinh/Split_List_PicoDst/split/
echo "Creating list for each job"
split -l24 -d /weekly/$USER/lbavinh/Split_List_PicoDst/runlist_PicoDst.list /weekly/$USER/lbavinh/Split_List_PicoDst/split/runlist_PicoDst_
echo "Number of needed job array is"
ls /weekly/$USER/lbavinh/Split_List_PicoDst/split/ | wc -l
echo "Initializing runlist for SGE JOB"
ls /weekly/$USER/lbavinh/Split_List_PicoDst/split/runlist_PicoDst_* > /weekly/$USER/lbavinh/Split_List_PicoDst/split/runlist.list