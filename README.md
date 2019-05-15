# hdlConvertor
[![Travis-ci Build Status](https://travis-ci.org/Nic30/hdlConvertor.png?branch=master)](https://travis-ci.org/Nic30/hdlConvertor)
[![Win Build status](https://ci.appveyor.com/api/projects/status/e3cvi3ig5y4vni7e?svg=true)](https://ci.appveyor.com/project/nic30/hdlconvertor)
[![PyPI version](https://badge.fury.io/py/hdlConvertor.svg)](http://badge.fury.io/py/hdlConvertor)
[![Python version](https://img.shields.io/pypi/pyversions/hdlConvertor.svg)](https://img.shields.io/pypi/pyversions/hdlConvertor.svg)
[ROADMAP](https://drive.google.com/file/d/1zyegLIf7VaBRyb-ED5vgOMmHzW4SRZLp/view?usp=sharing)


The System Verilog and VHDL parser for Python/C++ written in C++. This library parses all HDL languages to a single AST so other libraries does not have to care about Verilog/VHDL differences. 

This project was extracted from [HWT](https://github.com/Nic30/hwt).
There is also Java version. But it seems that there is no use for it.


## Installation
```
# note that only last 2 are really required rest is downloaded automatically as dependency
sudo apt install build-essential uuid-dev cmake default-jre libantlr4-runtime-dev antlr4
sudo pip3 install -r requirements.txt

sudo pip3 install hdlConvertor
#or download repository and run
sudo python3 setup.py install
```
Or the same using python and pip for python 2.7.

Installer also supports other commands.
```
export PYTHONPATH=/tmp/python_install/lib/python2.7/site-packages/
python setup.py install --prefix /tmp/python_install/ -j 8 --build-type Debug -- -DANTLR_JAR_LOCATION=../../../antlr4/antlr-4.7.1-complete.jar -- VERBOSE=1

Other commands:
python setup.py --help-commands
```

## Usage
In the meantime when there is no wiki yet you can take look at src/hdlObjects.
There are classes for objects in HDL langues and there are also toJson() for them.
This function is used for conversion to Python objects.

In python all parsed stuff are just dictionaries and values (str, int).

Top class of hdlObjects is Context, wich is container of all other hdl objects.


Example of usage:
```python
import hdlConvertor
res = hdlConvertor.parse("yourfile.vhd", "vhdl")
for e in res['entities']:
    print(e['name'])

```

If you having the troubles please check the installation part of the scripts for travis-ci and appveyor, they are verified to be working.
Also if it is something which is not unique to your system, tell us so we can fix it.


### Supported languages:

* VHDL 2002 (based on grammar https://guest.iis.ee.ethz.ch/~zimmi/download/vhdl02_syntax.html, https://github.com/antlr/grammars-v4/blob/master/vhdl/vhdl.g4 )
* Verilog 2001 (based on grammar http://www.syncad.com/VeriLogger_bnf_Syntax_Verilog_2001.htm, https://github.com/antlr/grammars-v4/blob/master/verilog/Verilog2001.g4)
* System Verilog 2012 (without preprocessor) (based on grammar http://insights.sigasi.com/tech/systemverilog.ebnf.html) (This does not work as expected due missing preprocessor but it will be added and it can be executed manually.)


### Similar projects:

* [pyVHDLParser](https://github.com/Paebbels/pyVHDLParser) - python vhdl parser with 2008 support
* [hdlparse](https://github.com/kevinpt/hdlparse/) - vhdl/verilog parser in python 
* [v2sc](https://github.com/denisgav/v2sc) - vhdl to systemc
* [verilog-parser](https://github.com/ben-marshall/verilog-parser) - verilog parser, c 
* [systemc-clang](https://github.com/anikau31/systemc-clang) - SystemC Parser using the Clang Front-end
* [verilog-parser](https://github.com/ben-marshall/verilog-parser) - A Flex/Bison Parser for the IEEE 1364-2001 Verilog Standard.
* [rust_hdl](https://github.com/kraigher/rust_hdl) - rust vhdl 2008 parser
* [slang](https://github.com/MikePopoloski/slang) - Parser and compiler library for SystemVerilog.
* [HDL_ANTLR4](https://github.com/denisgav/HDL_ANTLR4) - C# projects that use ANTLR4 library to analyse VHDL and Verilog code 


### License

License in top folder applies to this project only.
In this repository there are also grammars (.g4 files - BSD 3, GPL-3, GPL).
