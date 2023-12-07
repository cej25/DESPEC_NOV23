#!/bin/bash
##Read in list of files to run
LISTFILE="/lustre/gamma/DESPEC_NOV23_NEARLINE/Cluster_Submission/file_list_30nov.txt"
declare -a size
while IFS= read -r line
do
    size+=($line)
done < "$LISTFILE"

##Submit job

sbatch -p long -J despec_go4_bb7_trees -D /lustre/gamma/DESPEC_NOV23_NEARLINE/ -o logs/go4_%A_%a_trees.out.log -e logs/go4_%A_%a_trees.err.log \
  --time=7-00:00:00 --mem-per-cpu=4G \
  --array=0-${#size[@]}:2 -- /lustre/gamma/DESPEC_NOV23_NEARLINE/Cluster_Submission/go4_launcher_nearline_trees.sh

  unset size
