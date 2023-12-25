# QA (Quick Access)

A terminal alternative with support for plugins and more features to be added

## Commands

  - hello: just says hello
  - echo [string]: outputs the arguments
  - exit: exits QA
  - name: outputs name and version
  - version: outputs versin
  - hash <string>: allows you to hash a string with QA's hash function
  - help <string>: show the help message
  - set <string> <int>: changes a global variables value

## Global Variables
  - DEBUG (int): toggle debug messages
  - TRANSPARENCY (int): toggles wether of not host os should run the commands QA couldn't

## Default plugins

  - my_plugin: doesn't do much just a test
  - yes: implementation of the linux yes command


# How to structure plugins

right now, no package manager is implemented. To create a plugin add the name of compiled executable without the extension to *plugin_list.txt* (be sure to leave last line blank)
every argument from QA will be passed on to the plugin, it should return 0 if it ran successfully and 1 otherwise.
