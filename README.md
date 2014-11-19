openMP-Uebung01 
===============
Für dieses Projekt wird [openMP](http://openmp.org/wp/openmp-compilers/) benötigt. Vorteilhaft ist die Verwendung des Intel Compilers

Nach installation muss unter MacOS die Envirement Variable gesetzt werden.
```export DYLD_LIBRARY_PATH="/opt/intel/composer_xe_2015.0.077/compiler/lib:$DYLD_LIBRARY_PATH"```

Der korrekte Pfad kann sich auf jedem System unterscheiden. Somit selbst über das Terminal an diese Stelle hangeln.
Dieser Exportbefehl, ggf in die .bash_profile Datei schreiben und dann mit ```source .bash_profile``` bauen.

```icpc -openmp -o main main.cpp```

Theoretisch sollte gcc ebenfalls openMP unterstützen, findet aber auf meinem System die omp.h Datei nicht. Unter Ubuntu müsste es fehlerfrei bauen.

##### Weitere Infos unter MacOS
- [Stackoverflow Script](http://stackoverflow.com/questions/20321988/error-enabling-openmp-ld-library-not-found-for-lgomp-and-clang-errors/21789869#21789869) zum installieren von Clang unter MacOS 10.8 nicht 10.9 und 10.10 
- [Clang auf gitbub](http://clang-omp.github.io)
- [Clang llvm](http://clang.llvm.org/get_started.html)
- [Intel Compiler](https://software.intel.com/en-us/intel-education-offerings)
