# MO0VEY

Ez a repó a Számítógépi grafika féléves beadandójához tartozik.

Az ötlet egy kisebb, bejárható sci-fi kalibrációs tér: a játékos egy karaktert irányít egy zárt technikai környezetben, ahol különböző tárgyakat lehet mozgatni, körbejárni, megfigyelni, és közben a fő fényforrást is át lehet állítani. A cél nem egy általános „néhány modell egy üres térben” jellegű demo, hanem egy rövid, egységes hangulatú jelenet, aminek van témája és vizuális iránya.

## Mit szeretnénk belőle
A végső változat egy olyan bemutatható jelenet lenne, ahol:
- be lehet járni a teret billentyűzettel és egérrel,
- külső fájlból betöltött modellek jelennek meg textúrával,
- a fontosabb objektumok mozgathatók vagy animáltak,
- a fények tényleg látványosan befolyásolják a jelenetet,
- az egész nem széteső technikai próba, hanem egy összerakott kis környezet.

Most az alapok már megvannak: modellbetöltés, textúrák, kamera, mozgatható objektumok, állítható fény és F1-es segítség. A következő lépés az, hogy a jelenet kapjon valódi környezetet, határokat, hangulatot és tisztább belső szerkezetet.

## Ami még tervben van
- egy tényleges szoba vagy kamra felépítése a mostani üres alap helyett,
- ütközés vagy mozgási korlátok, hogy ne lehessen mindenen átmenni,
- köd vagy más hangulati effekt,
- átláthatóbb modulokra bontás a jelenlegi általánosabb kódszerkezet helyett.

## Miért ilyen kevés fájl van a repóban
Ide szándékosan csak az kerül fel, ami a projekthez tényleg kell: a forráskód, a szükséges headerek, a használt assetek, a Makefile és a leírások. A fordítás során előálló fájlok, a fölösleges kísérleti assetek és a külső környezethez tartozó dolgok nem részei a beadandónak.

A `c_sdk_220203` mappa ettől még fontos, csak nem repótartalom. A tantárgyhoz ezt a környezetet kaptuk, erre épül a fordítás és a futtatás, tehát lokálisan szükséges, de maga a projekt nem ettől a mappától „lesz” beadandó.

## Fordítás Windows alatt
1. A `c_sdk_220203` mappa legyen a repó mellett.
2. Ha a textúratöltés a `libpng16-16.dll` hiányára panaszkodik, a DLL-t a `c_sdk_220203/MinGW/bin/` mappába kell bemásolni.
3. A projekt a `Beadando` mappából fordítható például ezzel:

```bat
..\c_sdk_220203\MinGW\bin\mingw32-make.exe
```

A részletesebb, technikai jellegű projektleírás a `Beadando/README.md` fájlban van.