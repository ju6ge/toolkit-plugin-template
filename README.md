Toolkit Plugin Template
=======================

A plugin template which is desinged to be used with the python script to generate new plugin source trees that can be build out of tree of rbdl-toolkit.

## Dependencies
- jinja2

## Usage

To create a simple basic plugin run the following command:

```shell
./create_plugin.py --name CameCaseName --dir <path where src tree will be created>
```

To also create a model extention alongside the plugin run:

```shell
./create_plugin.py --name CameCaseName --dir <path where src tree will be created> --extention
```

To see all options run:
```shell
./create_plugin.py --help
```

## Toolkit Plugin Documentation 

There is an [article](https://github.com/ORB-HD/rbdl-toolkit/wiki/Writing-a-toolkit-plugin) in the toolkit wiki on the most important parts of most plugins.
