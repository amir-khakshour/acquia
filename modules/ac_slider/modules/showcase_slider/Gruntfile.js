'use strict';

module.exports = function (grunt) {

  grunt.initConfig({
    watch: {
      options: {
        livereload: 35987
      },
      sass: {
        files: ['sass/{,**/}*.{scss,sass}'],
        tasks: ['compass:dev'],
        options: {
          livereload: false
        }
      },
      registry: {
        files: ['*.info', '{,**}/*.{php,inc}'],
        tasks: ['shell'],
        options: {
          livereload: false
        }
      },
      images: {
        files: ['images/**']
      },
      css: {
        files: ['css/{,**/}*.css']
      },
      js: {
        files: ['js/{,**/}*.js', '!js/{,**/}*.min.js'],
        tasks: ['jshint', 'uglify:dev']
      }
    },

    shell: {
      all: {
        command: 'drush cache-clear theme-registry'
      }
    },
    sprite:{
      all: {
        src: 'images/*.png',
        dest: 'sprite.png',
        padding: 20, // Exaggerated for visibility, normal usage is 1 or 2
        destCss: 'sass/sprites.scss',
        cssTemplate: 'sprite.yml',
      }
    },
    image_resize: {
      options: {
        width: 32,
        height: 32,
        overwrite: true
      },
      dist: {
        src: ['_images/*.png'],
        dest: 'images/'
      },
    },
    compass: {
      options: {
        config: 'config.rb',
        bundleExec: true,
        force: true,
        sassDir: 'sass',
        cssDir: 'css',
      },
      dev: {
        options: {
          environment: 'development'
        }
      },
      dist: {
        options: {
          environment: 'production'
        }
      }
    },

    jshint: {
      options: {
        jshintrc: '.jshintrc'
      },
      all: ['js/{,**/}*.js', '!js/{,**/}*.min.js']
    },

    uglify: {
      dev: {
        options: {
          mangle: false,
          compress: false,
          beautify: true
        },
        files: [{
          expand: true,
          flatten: true,
          cwd: 'js',
          dest: 'js',
          src: ['**/*.js', '!**/*.min.js'],
          rename: function(dest, src) {
            var folder = src.substring(0, src.lastIndexOf('/'));
            var filename = src.substring(src.lastIndexOf('/'), src.length);
            filename = filename.substring(0, filename.lastIndexOf('.'));
            return dest + '/' + folder + filename + '.min.js';
          }
        }]
      },
      dist: {
        options: {
          mangle: true,
          compress: true
        },
        files: [{
          expand: true,
          flatten: true,
          cwd: 'js',
          dest: 'js',
          src: ['**/*.js', '!**/*.min.js'],
          rename: function(dest, src) {
            var folder = src.substring(0, src.lastIndexOf('/'));
            var filename = src.substring(src.lastIndexOf('/'), src.length);
            filename = filename.substring(0, filename.lastIndexOf('.'));
            return dest + '/' + folder + filename + '.min.js';
          }
        }]
      }
    }
  });

  grunt.loadNpmTasks('grunt-contrib-watch');
  grunt.loadNpmTasks('grunt-contrib-compass');
  grunt.loadNpmTasks('grunt-contrib-jshint');
  grunt.loadNpmTasks('grunt-contrib-uglify');
  grunt.loadNpmTasks('grunt-shell');
  grunt.loadNpmTasks('grunt-image-resize');

  // Load in `grunt-spritesmith`
  grunt.loadNpmTasks('grunt-spritesmith');
  grunt.registerTask('build', [
    'uglify:dist',
    'compass:dist',
    'jshint'
  ]);

};
