My metal jacketed DS203 finally arrived last week.  Its a great little device and the manufacturers (http:://www.minidso.com)should be very proud, not only of thier work, but also because they have been forward thinking enough to open source the hardware and software.  I hope they're making a good commercial return.

There seem to be a number of different ways to buy this scope and the contents of the package seems to vary a bit.  Mine is h/w 2.72, sys v1.60, app v1.10+ and came with two scope probes (each with x1 and x10 settings), a small hex allen key.  The probes have come out their bags but so have resisted the temptation to open up the case with the allen key.

The only hardware mods I've done are to stick small plastic feet over said hex bolts to reduce temptation and to stop the unit sliding and getting scratched.  The other mod is to order up some MCX connectors and mini-clips to make up leads for the wav out and C & D channels.  Still waiting for those.

The standard application is functional (once you figure out that you can also press the left-right and up-down jog dials) but its hard to use and fonts are very small.  Luckily there are number of open source apps around, not just replacement for the scope, but logic analysers, FFTs, usb analysers, I2C decoders and more.  Fortunately too, that the designers created room for four application slots so you can have more than one installed at a time.  If you haven't found them already, http://seeedstudio.com will point you in the right direction.

Gabonator's (http://www.valky.eu) firmware is meant to be a better UI but that undersells it significantly.  The UI is indeed far more scope like and very easy to use but I also I keep on uncovering more under the hood.  After a small accident where the standard software got erased when I tried installing something else in slot 2, I've now got gabonator's app as my default in slot 1.  In slot 3 I've got the logic analyser and slot 4 QuadPawn, both from http://essentialscrap.com.  I've not used these much yet.  I'm a bit wary of slot 2 right now..


Forked Repository
-----------------

There are a couple of things I found I wanted to do with http://github.com/Gabonator/DS203:

- a dedicated run/stop button on the circle button
8/2/14 Settings->Keys allows you to set up short cut so its easy to put 'Start/Stop Aquisition' on the circle button and move the 'Toolbox' to the triangle button.  The circle looks like record icon so wanted to have that one for the start/stop.  Unfortunately the circle button setting is not saved so when you restart the app its gone back to Toolbox.  First mod: serialise the circle button setting.  The diff is minute and should be non-contentious so will ask for it to be merged upstream (as soon as I figure out how to do that). The only downside is that the first time you power up it tried to read the old settings file and gives you an error.  After that.. all good.

- display the right ranges for 10x probes.
8/2/14 This one is a bit more involved as it affects not only the displayed channel resolution but also the measurements.  I've pushed a changeset but its not complete and there's a few classes I don't properly understand.

The code compiles out the box with Visual Studio Express 2013 for Windows Desktop.
Installing the hex files is exactly the same as upstream

This is my first foray into GitHub so hope I'm playing nice.  If not, please attribute it to ignorance or caution rather than malice.

Andy

