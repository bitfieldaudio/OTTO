/**
 * http://gruntjs.com/configuring-tasks
 */
module.exports = function(grunt) {
    var path = require('path');
    var DEMO_PATH = 'demo/dist';
    var DEMO_SAMPLE_PATH = 'demo/sample';

    grunt.initConfig({
        pkg: grunt.file.readJSON('package.json'),
        clean: ['demo/html'],
        run: {
            demo: {
                cmd: 'doxygen',
                args: ['Doxyfile']
            }
        },

        watch: {
            doxyfile: {
                files: [
                    'template/**/*.*', 'Doxyfile'
                ],
                tasks: ['clean','run:demo']
            }
        },

        "browserSync": {
            bsFiles: {
                src: './demo/html/**/*.*'
            },
            options: {
                watchTask: true,
                server: {
                    baseDir: "./demo/html/"
                }
            }
        }
    });

    // Load task libraries
    ['grunt-contrib-clean','grunt-contrib-watch', 'grunt-run', 'grunt-browser-sync'].forEach(function(taskName) {
        grunt.loadNpmTasks(taskName);
    });

    grunt.registerTask('demo', 'Create documentations for demo', ['run:demo']);

    // Definitions of tasks
    grunt.registerTask('default', 'Watch project files', ['demo', 'browserSync', 'watch']);

}
