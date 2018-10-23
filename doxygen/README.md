# Navionics Doxygen Theme
Custom Navionics Theme for Doxygen Document engine


## Hot To use it:
* Move the directories `template` and `Doxyfile` in your preferred space
* Edit the `Doxyfile` and provide the:
  * INPUT directory, it's the code directory. **NOTE:** This directory need to contain a Markdown file named `README.md`used as homepage of documentation.
  * OUTPUT_DIRECTORY , it's the directory where you want the site
* Open the terminal and run the command `doxygen Doxifile`




## Hot To customize it:
It's a canonical [NPM project](https://www.npmjs.com/) driven by [Grunt](https://gruntjs.com/) tools. If you want develop new feature you need to have [NodeJS](https://nodejs.org/it/) installed in your system.

The html assets it's developed with [Bootstrap library](https://getbootstrap.com/).

### Directory Content

* `demo/`: The demo directory how to test the theme           
* `template/`: The template files and static assets
* `Doxyfile`: Doxygen config file
* `Gruntfile.js`: Grunt config file
* `package.json`: Npm config file
* `LICENSE`: License file      
* `README.md`: This file
