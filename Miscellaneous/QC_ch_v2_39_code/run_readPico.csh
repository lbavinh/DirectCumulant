#!/bin/tcsh

starver pro

set fileList = $1
set outFile  = `basename ${fileList}`.hist.root

root4star -q -b 'readPicoDst.C("'${fileList}'", "'${outFile}'")'
