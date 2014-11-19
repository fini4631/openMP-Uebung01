openMP-Uebung01
===============
Für dieses Projekt wird openMP benötigt. Vorteilhaft ist die Verwendung des Intel Compilers

Nach installation muss unter MacOS die Envirement Variable gesetzt werden.
```export DYLD_LIBRARY_PATH="/opt/intel/composer_xe_2015.0.077/compiler/lib:$DYLD_LIBRARY_PATH"```

Der korrekte Pfad kann sich auf jedem System unterscheiden. Somit selbst über das Terminal an diese Stelle hangeln.
Dieser Exportbefehl, ggf in die .bash_profile Datei schreiben und dann mit ```source .bash_profile``` bauen.

```icpc -openmp -o main main.cpp```

Theoretisch sollte gcc ebenfalls openMP unterstützen, findet aber auf meinem System die omp.h Datei nicht. Unter Ubuntu müsste es fehlerfrei bauen.
