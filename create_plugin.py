#!/usr/bin/env python
from jinja2 import Environment, FileSystemLoader, Template
import argparse
import os
import shutil


def main():
	template_dir = os.path.dirname(os.path.realpath(os.path.abspath(__file__)))

	parser = argparse.ArgumentParser(description="Script to generate new Plugins for RBDL-Toolkit")
	parser.add_argument('--name', dest='plugin_name', type=str, help="Plugin Name, use CamelCase (no need to add Plugin at the End 😉)")
	parser.add_argument('--dir', dest='plugin_dir', type=str, help="Path to where the Plugin Sources should be put. Will create Subfolder there", default=".")
	parser.add_argument('--extension', dest='add_extension', action="store_true", help="Also adds the Model Extension template")
	parser.add_argument('--all', dest='all', action="store_true", help="Build plugin with all option except for intree and core")
	parser.add_argument('--3d', dest='qt3d', action="store_true", help="Adds 3D includes")
	parser.add_argument('--settings', dest='settings', action="store_true", help="Adds structure for readings/writings settings")
	parser.add_argument('--cmd', dest='cmd', action="store_true", help="Adds structure for command line settings")
	parser.add_argument('--filereader', dest='filereader', action="store_true", help="Adds structure for filereading")
	parser.add_argument('--core', dest='core', action="store_true", help="Create Core plugin instead of Optional Plugin")
	parser.add_argument('--intree', dest='intree', action="store_true", help="Plugin will be build in rbdl-toolkit src tree")
	parser.add_argument('--reload', dest='reload', action="store_true", help="Add Structure for easy reloading of data")

	args = parser.parse_args()

	#exit if no Plugin name was given
	if args.plugin_name is None:
		print("No plugin name supplied, exiting!")
		return

	name = args.plugin_name
	intree = args.intree
	core = args.core

	if not args.all:
		add_extension = args.add_extension
		qt3d = args.qt3d
		filereader = args.filereader
		cmd = args.cmd
		settings = args.settings
		reload = args.reload
	else:
		add_extension = True
		qt3d = True
		filereader = True
		cmd = True
		settings = True
		reload = True

	#change dir to where to create plugin folder
	os.chdir(args.plugin_dir)
	os.mkdir(name+"Plugin")

	template_env = Environment(loader=FileSystemLoader(template_dir))
	dest = os.path.join(os.getcwd(), name+"Plugin")

	templates = [ "CMakeLists.txt", "TemplatePlugin.h", "TemplatePlugin.cc", "metadata.json", "README.md"]
	if add_extension:
		templates += ["TemplateModelExtension.h", "TemplateModelExtension.cc"]
	files = [ ".gitignore" ]
	dirs = [ ]

	#only copy cmake dir and gitignore if building out of tree
	if not intree:
		for d in dirs:
			src = os.path.join(template_dir, d)
			shutil.copytree(src, os.path.join(dest, d))

		for f in files:
			shutil.copyfile(os.path.join(template_dir, f), os.path.join(dest, f))

	for tfile in templates:
		if tfile.find("Template") != -1:
			filename = tfile.replace("Template", name)
		else:
			filename = tfile
		with open(os.path.join(dest, filename),"w") as f:
			if filename == "README.md":
				#sometimes python formatting is 🙈
				text = """{{ plugin_name }}Plugin
=======================

## Build and Install

With these commands you can build this plugin outside of the rbdl-toolkit src tree, but you will also need to have a rbdl-toolkit build dir.

```shell
mkdir build
cd build
cmake -DCUSTOM_QT_PATH=<QT_Lib_PATH> -DCMAKE_BUILD_TYPE=Release -DTOOLKIT_BUILD_PATH=<Toolkit_Build_DIR> -DTOOLKIT_SOURCE_PATH=<Toolkit_Source_DIR> ..
make
sudo make install
```

### Build for use with AppImage

To build this plugin for use with the rbdl-toolkit.AppImage use the toolkit-buildplugin.AppImage which can be found in the rbdl-toolkit release.
"""
				t = Template(text)
			else:
				t = template_env.get_template(tfile)
			f.write(t.render(plugin_name=name, add_extension=add_extension, qt3d=qt3d, filereader=filereader, cmd=cmd, settings=settings, core=core, intree=intree, reload=reload))

if __name__ == "__main__":
	main()
