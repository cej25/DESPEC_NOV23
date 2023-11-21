#!/bin/bash

##Setup environment
#source /cvmfs/eel.gsi.de/centos7-x86_64/bin/go4login
source /cvmfs/eel.gsi.de/debian10-x86_64/bin/go4login
export ROOT_INCLUDE_PATH=/lustre/gamma/DESPEC_NOV23_NEARLINE
echo "DESPEC Kronos Started at `date`"

##Read in list of files to run. Format names seperated by space,tab,newline
LISTFILE="/lustre/gamma/DESPEC_NOV23_NEARLINE/Cluster_Submission/file_list_17nov.txt"

##Count number of files
NFILES=$(cat ${LISTFILE} | wc -l)
echo "Analysing" $NFILES "Files"

##Read names from list file
declare -a array
while IFS= read -r line
do
    array+=($line)
done < "$LISTFILE"

echo "Array is $SLURM_ARRAY_TASK_ID"
part=(  "${array[@]:$SLURM_ARRAY_TASK_ID:2}" ) # :5 number of files to put together -> Has to be the same in the 2 .sh scripts

echo "Running Go4!"
go4analysis -file ${part[*]} -enable-asf 1800 -asf /lustre/gamma/DESPEC_NOV23_NEARLINE/Cluster_Submission/Nearline_Histograms/implanttest1_${SLURM_ARRAY_TASK_ID}.root
