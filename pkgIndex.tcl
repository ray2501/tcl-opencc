# -*- tcl -*-
# Tcl package index file, version 1.1
#
if {[package vsatisfies [package provide Tcl] 9.0-]} {
    package ifneeded opencc 0.4 \
	    [list load [file join $dir libtcl9opencc0.4.so] [string totitle opencc]]
} else {
    package ifneeded opencc 0.4 \
	    [list load [file join $dir libopencc0.4.so] [string totitle opencc]]
}
