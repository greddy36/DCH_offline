#!/bin/bash

for input in masstree_*.root
do
    # Remove .root and replace tree_ with hist_
    base=$(basename "$input" .root)
    output="${base/masstree_/hist_}.root"

    echo "Processing $input -> $output"

    root -l -b -q "treeTohist.C(\"$input\", \"$output\")"
done
