# Overly Complicated Audio Engine (OCAE)

Simply, an audio engine designed tocompute sounds using basic generators (sound sources) and modifiers (filters) combined in a graph structure.

---
## Building

### Windows

To create a project solution, download and open CMake (version 3.8 or newer). set the root directory of this repository as the source code location, then set repository root/build as the build location for the binaries.
Then click Configure, choose win64 for building, and when that's done, click Generate. You'll find the project solution in the build folder.
Be sure to set the OCAE project as the startup project within Visual Studio!

### Linux (and maybe others)

Coming soon

---
## Note:

The project will build the executibles and copy the necessary shared libs to repository root/bin for easy access of the binaries.
