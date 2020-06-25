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
	parser.add_argument('--extention', dest='add_extention', action="store_true", help="Also adds the Model Extention template")

	args = parser.parse_args()

	#exit if no Plugin name was given
	if args.plugin_name is None:
		print("No plugin name supplied, exiting!")
		return

	name = args.plugin_name
	add_extention = args.add_extention

	#change dir to where to create plugin folder
	os.chdir(args.plugin_dir)
	os.mkdir(name+"Plugin")

	template_env = Environment(loader=FileSystemLoader(template_dir))
	dest = os.path.join(os.getcwd(), name+"Plugin")

	templates = [ "CMakeLists.txt", "TemplatePlugin.h", "TemplatePlugin.cc", "metadata.json", "README.md"]
	if add_extention:
		templates += ["TemplateModelExtention.h", "TemplateModelExtention.cc"]
	files = [ ".gitignore" ]
	dirs = [ "cmake" ]

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

# Build and Install

With these commands you can build this plugin outside of the rbdl-toolkit src tree, but you will also need to have a rbdl-toolkit build dir.

```shell
mkdir build
cd build
cmake -DCUSTOM_QT_PATH=<QT_Lib_PATH> -DCMAKE_BUILD_TYPE=Release -DTOOLKIT_BUILD_PATH=<Toolkit_Build_DIR> -DTOOLKIT_SOURCE_PATH=<Toolkit_Source_DIR> ..
make
sudo make install
```
"""
				t = Template(text)
			else:
				t = template_env.get_template(tfile)
			f.write(t.render(plugin_name=name, add_extention=add_extention))

if __name__ == "__main__":
	main()
