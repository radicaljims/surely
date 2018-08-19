## SDL + OpenGL, via cmake

1. Install pre-reqs: `./install_prereqs.sh`
2. Setup cmake and build: `./setup.sh`
    * If you want an XCode project, run `./xcode_setup.sh` instead
    * To rebuild after changes: `./rebuild.sh`
3. Run: `./build/target/ogl.app/Contents/MacOS/ogl`

Tuned for OSX, probably need some tweaks for Windows (GLEW?) and Linux.
