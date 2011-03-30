#!/bin/sh

output=$1
shift 1
input=$*

montage $input -tile x1 -geometry +0+0 -background none $output
