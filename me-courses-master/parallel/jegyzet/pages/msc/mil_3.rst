3. OpenMP
=========

Egy API többszálú alkalmazások írásához.

* Célja, hogy egyszerűsítse a programok írását C, C++ és Fortran nyelven. (2005-től, a 2.5-ös verziótól kezdve egységes az API minden nyelven.)
* Többségében fordító direktívákat használ.
* Figyelembe veszi a nyelv strukturális elemeit.
* Nyilvántartja, lekérdezhetővé teszi a szálak számát.
* A szálak azonosítóit 0-tól kezdve egészként adja meg. (Ezzel egyszerűsíti a problémák felosztását.)
* Kezeli a változók láthatóságát (*private*/*shared*).
* A szálak egymás között megosztott memórián keresztül tudnak kommunikálni.
* *Race condition*: a szálak ütemezése befolyásolja a program eredményeit.
* Az ütemezéstől független helyes futást szinkronizációval lehet garantálni.
* Van benne implicit és explicit barrier.
* Windows kompatibilis.
