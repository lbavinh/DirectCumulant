# MpdMiniEvent

The MpdMiniEvent set of classes (library) allows to store and work with *filename.miniDst.root* files or with list of such files.

************************************************************

Maintainer:   Grigory Nigmatkulov

Institution:  National Research Nuclear University MEPhI

Date:         May 01, 2020

E-mail:       nigmatkulov@gmail.com ; ganigmatkulov@mephi.ru ; pavel.batyuk@jinr.ru

************************************************************

Brief description of how to compile and run the analysis over miniDst on your laptop and/or HybriLit.

## Installation

a) System has to have ROOT preinstalled (should work with versions 5 and 6).

b) There is a Makefile stored in the **_MpdMiniEvent_** directory. In order to compile the codes one needs to run:

```
make
```

c) Since it is the most commonly used, the **g++** compiler is used for the
compilation. However, one can also switch it to **clang++** (has been successfully tested)

d) After the compilation is finished the shared library *libMpdMiniDst.so* will be
created.

e) If you have some errors during the compilation please contact the miniDst
maintainer (and/or miniDst mailing list).

## Processing miniDst

There are three ROOT macroses with example of how to perform a simple analysis using miniDst. They are stored in the **MpdMiniEvent/macros** directory and called: *MiniDstAnalyzer.C*, *RunAnalyzer.C*, and *SimpleMiniDstAnalyzer.C*.

Lets assume that one has and input file(s) *InputFile* with a *name.miniDst.root* or a list of miniDst files, called *name.lis(t)*, and MpdMiniEvent compiled (i.e. the *libMpdMiniDst.so* library exists).

There are 2 possible processing scenarios of using MpdMiniEvent library and classes depending on the ROOT version:

### ROOT 5:

One should run ROOT from the terminal:

```
[myterm]> root RunAnalyzer.C\(\"InputFile\"\)
```

Or run this macros from the interactive session:
```
[myterm]> root
root [0].x RunAnalyzer.C("InputFile")
```

Any of aforementioned ways load *libMpdMiniDst.so*, compile and run *RunAnalyzer.C*. After the processing the remove dictionary and library created by ACLiC.

### ROOT 6:

Since ROOT 6 does not have CINT there is some extra flexibility on how to analyze the data. The first one is listed above. The second option is to run the *MiniDstAnalyzer.C* macro directly.

Either from the terminal:

```
root MiniDstAnalyzer.C\(\"InputFile"\)
```

Or from the root session:

```
[myterm]> root
root [0].x MiniDstAnalyzer.C("InputFile")
```

### Simple Processing

The other possibility is not to use **MpdMiniEvent** classes, but read *filename.miniDst.root* files as regular ROOT TTree. The macros *SimpleMiniDstAnalyzer.C* shows an example of doing it.

## Troubleshooting

For any questions or with any suggestions please contact the package maintainer: 
nigmatkulov@gmail.com
ganigmatkulov@mephi.ru
