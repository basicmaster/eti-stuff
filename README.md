# eti-stuff

"eti-stuff" is an attempt to understand the eti structure as defined in ETS 300 799.

[eti-frontend](#eti-frontend) and [eti-backend](#eti-backend) are based on [Qt-DAB](https://github.com/JvanKatwijk/qt-dab), with code included from [dabtools](https://github.com/Opendigitalradio/dabtools) to actually generate the eti frames.

[eti-cmdline](#eti-cmdline) is based on the dab-cmdline software and is - as the name suggests - the command line version.

The eti-frontend and eti-cmdline programs take a sample stream as input and create an eti file, while eti-backend is interpreting the eti file.

By piping the output from either eti-frontend of eti-cmdline into eti-backend, a more or less complete DAB receiver exists.

# Contents

The set consists (currently) of three programs (all under continuous development)

* [eti-frontend](#eti-frontend)
* [eti-backend](#eti-backend)
* [eti-cmdline](#eti-cmdline)

## eti-frontend

THE ETI-FRONTEND IS NO MORE SUPPORTED, JUST FORGET IT

which was a stripped Qt-DAB version that generates eti-frames as output.

The GUI is - obviously - based on Qt-DAB. There is an additional command line option `-O -`, that will cause the ETI files to be sent to stdout.

The "normal" way of working is to have an input device selected, select a channel, press the start button, and as soon as an ensemble is identified, and the GUI shows the names of the programs, to press the button "eti is waiting", after which it will send the eti frames to the selected output device.

## eti-backend

which is a stripped Qt-DAB version that takes eti-frames as input. A command line option (`-s`) can be used to specify an input file or stdinput. If none is specified, the program will show a widget for selecting an input file.
   
The GUI is simple, it will show the name of the ensemble and the names of programs. Selecting a program is as in the Qt-DAB software. 

It will start reading after pressing the start button.

## eti-cmdline

which is derived from the dab-cmdline program and shares the relevant command line parameters.

For more information please read the `README.md` in the subdirectory `eti-cmdline`.

### Syntax

If you want to emulate a full DAB receiver, then run

      eti-cmdline-xxx -C 11C -G 80 | eti-backend -s -
      
Or you can use dablin or dablin_gtk from https://github.com/Opendigitalradio/dablin by running
      
      eti-cmdline-xxx -C 11C -G 80 | dablin_gtk
      
where xxx refers to the input device being supported, one of (`rtlsdr`, `sdrplay`, `airspy`, `rawfiles`, `wavfiles`).
      

# Disclaimer

The software is under development and most likely contains errors.

eti-stuff is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU General Public License for more details.


# Copyright

Copyright Jan van Katwijk <J.vanKatwijk@gmail.com>.

This software is part of the Qt-DAB, Qt-DAB is free software; you can redistribute it and/or modify it under the terms of the GNU General Public License as published by the Free Software Foundation; either version 2 of the License, or (at your option) any later version, taking into account the licensing conditions of the parts of the software that are derived from wotk of others.

This software uses parts of dabtools. Excerpt from the README of dabtools reads

"dabtools is written by Dave Chapman <dave@dchapman.com>
   
Parts of the code in eti-backend are copied verbatim (or with trivial modifications) from David Crawley's OpenDAB and hence retain his copyright."

Obviously, the copyrights for the parts copied (or directly derived) from the dabtools remain with Dave Chapman.
