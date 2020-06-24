#!/usr/bin/env python
from jinja2 import Environment, FileSystemLoader
import argparse
import os
import shutil

def main():
	template_dir = os.path.dirname(os.path.abspath(__file__))

	parser = argparse.ArgumentParser(description="Script to generate new Plugins for RBDL-Toolkit")
	parser.add_argument('--name', dest='plugin_name', type=str, help="Plugin Name, use CamelCase (no need to add Plugin at the End 😉)")
	parser.add_argument('--dir', dest='plugin_dir', type=str, help="Path to where the Plugin Sources should be put. Will create Subfolder there", default=".")

	args = parser.parse_args()

	#exit if no Plugin name was given
	if args.plugin_name is None:
		print("No plugin name supplied, exiting!")
		return

	name = args.plugin_name

	#change dir to where to create plugin folder
	os.chdir(args.plugin_dir)
	os.mkdir(name+"Plugin")

	template_env = Environment(loader=FileSystemLoader(template_dir))
	dest = os.path.join(os.getcwd(), name+"Plugin")

	templates = [ "CMakeLists.txt", "TemplatePlugin.h", "TemplatePlugin.cc", "metadata.json" ]
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
			t = template_env.get_template(tfile)

			f.write(t.render(plugin_name=name))

if __name__ == "__main__":
	main()
