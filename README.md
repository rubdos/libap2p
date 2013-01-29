    Copyright (C)  
    2012 - 2013 - Ruben De Smet  
    This program is free software; you can redistribute it and/or  
    modify it under the terms of the GNU General Public License  
    as published by the Free Software Foundation; either version 3  
    of the License, or (at your option) any later version.  

    This program is distributed in the hope that it will be useful,  
    but WITHOUT ANY WARRANTY; without even the implied warranty of  
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the  
    GNU General Public License for more details.  

    You should have received a copy of the GNU General Public License  
    along with this program; if not, see <http://gnu.org/licenses/>  

# libap2p

## About

libap2p aims to become an advanced cross platform peer to peer library.  
API documentation can be found here:  
[HTML doxygen pages:](http://rubdos.github.com/libap2p/doxygen_html)  
[LaTeX doxygen:](http://rubdos.github.com/libap2p/doxygen_latex)  

CAUTION: not usable yet!  

## Requirements:

* cryptopp
* boost libraries (iostreams, filesystem, system, thread, signals)
* cmake
* make compatible
* g++ compiler or compatible (mingw...)

## Compiling:

1. $> mkdir build && cd build
2. $> cmake ..
3. $> make #(or make -j[threadcount])
