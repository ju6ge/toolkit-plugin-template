Toolkit Plugin Template
=======================

Just a simple template of a plugin for rbdl-toolikit build outside of the rbdl-toolikit src tree

Usage
====

```shell
mkdir build 
cd build
cmake -DCUSTOM_QT_PATH=<QT_Lib_PATH> -DCMAKE_BUILD_TYPE=Release -DTOOLKIT_BUILD_PATH=<Toolkit_Build_DIR> -DTOOLKIT_SOURCE_PATH=<Toolkit_Source_DIR> ..
make
sudo make install
```
