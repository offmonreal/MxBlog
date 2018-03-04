#!/bin/bash
OLDIFS=$IFS
#IFS=$(echo -en "\n\b")
for i in `find ./source`
    do
		if test -f $i
		then
			#echo $i
			filename="${i##*/}"
			#echo $filename
			xxd -i $i "../MxBlog/source/resource/"$filename".h"
			#echo $i "../MxBlog/source/resource/"$filename".h"
		fi
    done
#IFS=$OLDIFS

 # xxd -i $i $i . ".h"
