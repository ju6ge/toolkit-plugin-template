#include "{{ plugin_name }}Plugin.h"
#include <iostream>

{{ plugin_name }}Plugin::{{ plugin_name }}Plugin() {
	parentApp = NULL;
}

{{ plugin_name }}Plugin::~{{ plugin_name }}Plugin() {
}

void {{ plugin_name }}Plugin::init(ToolkitApp* app) {
	//save reference to parent ToolkitApp 
	parentApp = app;

	std::cout << "{{ plugin_name }}Plugin loaded" << std::endl;
}

