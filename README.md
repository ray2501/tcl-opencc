tcl-opencc
=====

[OpenCC](https://github.com/BYVoid/OpenCC)  is an opensource project for 
conversion between Traditional Chinese and Simplified Chinese, supporting 
character-level conversion, phrase-level conversion, variant conversion 
and regional idioms among Mainland China, Taiwan and Hong kong.

tcl-opencc is Tcl bindings for OpenCC (libopencc).
OpenCC version requires >= 0.4.3, and >= 1.0.1 is better.


License
=====

Apache License 2.0


Commands
=====

opencc HANDLE configFileName  
HANDLE convert utf8_string  
HANDLE close

### Configurations

#### Default onfigurations

* `s2t.json` Simplified Chinese to Traditional Chinese
* `t2s.json` Traditional Chinese to Simplified Chinese
* `s2tw.json` Simplified Chinese to Traditional Chinese (Taiwan Standard)
* `tw2s.json` Traditional Chinese (Taiwan Standard) to Simplified Chinese
* `s2hk.json` Simplified Chinese to Traditional Chinese (Hong Kong Standard)
* `hk2s.json` Traditional Chinese (Hong Kong Standard) to Simplified Chinese
* `s2twp.json` Simplified Chinese to Traditional Chinese (Taiwan Standard) with Taiwanese idiom
* `tw2sp.json` Traditional Chinese (Taiwan Standard) to Simplified Chinese with Mainland Chinese idiom
* `t2tw.json` Traditional Chinese (OpenCC Standard) to Taiwan Standard
* `t2hk.json` Traditional Chinese (OpenCC Standard) to Hong Kong Standard


UNIX BUILD
=====

I only test tcl-opencc under openSUSE LEAP 15.0 and Ubuntu 14.04

Users need install OpenCC development files. Below is an example for openSUSE:

     sudo zypper in opencc-devel

Below is an example for Ubuntu 14.04:

     sudo apt-get install opencc libopencc-dev

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

If OpenCC version is `0.4.3`, the config file is ini file format, not json.
Below is an example:

    package require opencc
     
    opencc handle "zht2zhs.ini"
    set outstring [handle convert "請提供預設記憶體大小以及硬碟容量，以及需要的清單。"]
    puts $outstring
    handle close

And another example for OpenCC 0.4.3:

    package require opencc
     
    opencc handle "zhs2zht.ini"
    puts [handle convert "新浪网新闻中心是新浪网最重要的频道之一。"]
    puts [handle convert "朝韩首脑再度会晤 半岛外交斡旋紧锣密鼓"]
    handle close

