tcl-opencc
=====

[OpenCC](https://github.com/BYVoid/OpenCC)  is an opensource project for 
conversion between Traditional Chinese and Simplified Chinese, supporting 
character-level conversion, phrase-level conversion, variant conversion 
and regional idioms among Mainland China, Taiwan and Hong kong.

tcl-opencc is Tcl bindings for OpenCC (libopencc).


License
=====

Apache License 2.0


Commands
=====

opencc HANDLE configure  
HANDLE convert utf8_string  
HANDLE close


UNIX BUILD
=====

I only test tcl-opencc under openSUSE LEAP 15.0.

Users need install OpenCC development files. Below is an example for openSUSE:

     sudo zypper in opencc-devel

Building under most UNIX systems is easy, just run the configure script and 
then run make. For more information about the build process, see the 
tcl/unix/README file in the Tcl src dist. The following minimal example will 
install the extension in the /opt/tcl directory.

    $ cd tcl-opencc
    $ ./configure --prefix=/opt/tcl
    $ make
    $ make install

If you need setup directory containing tcl configuration (tclConfig.sh), 
below is an example:

    $ cd tcl-opencc
    $ ./configure --with-tcl=/opt/activetcl/lib
    $ make
    $ make install


Examples
=====

Convert Traditional Chinese to Simplified Chinese:

    package require opencc
     
    opencc handle "t2s.json"
    set outstring [handle convert "請提供預設記憶體大小以及硬碟容量，以及需要的清單。"]
    puts $outstring
    handle close

Convert Simplified Chinese to Traditional Chinese:

    package require opencc
     
    opencc handle "s2t.json"
    puts [handle convert "新浪网新闻中心是新浪网最重要的频道之一。"]
    puts [handle convert "朝韩首脑再度会晤 半岛外交斡旋紧锣密鼓"]
    handle close


