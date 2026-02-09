Szövegek megjelenítése
======================

.. TODO: A Lisa-t, mint érdekes esetet említeni!

A szövegek megjelenítése esetében is van lehetőség vektorgrafikus és raszteres megjelenítésben gondolkozni.

* Vektorgrafikus megjelenítés esetén ki tudjuk rajzoltatni a betűket OpenGL segítségével, mint szakaszokat, poligonokat vagy akár, mint 3 dimenziós modelleket.
* Raszteres megjelenítés kapcsán főként textúrák megjelenítéséről van szó.

A szövegek megjelenítésénél számos problémát meg kell oldanunk, mint például az alábbiakat.

* Milyen karakterkészletet használjunk/támogasson az alkalmazás?
* Hogyan tároljuk le a betűk alakját?
* Hogyan kezeljük a különböző méretű betűket?
* Hova kerül az egyes betűk igazítási pontja?
* Hogyan oldjuk meg az átméretezést, hogy kisebb és nagyobb felbontáson is tetszetős legyen a megjelenítés?
* Az élsimítást, *subpixel* renderelést hogyan oldjuk meg?
* Több soros szövegeknél hogyan tördeljük a sorokat? (Egyenletes sorkitöltés? Elválasztás?)
* Hogyan használjunk színeket, félkövér és dőlt betűket?

Karakterkódolás
---------------

* ASCII
* Unicode, UTF-8

Fontok
------

A betűk alakjának kialakításával, megfelelő elrendezésükkel, térközök meghatározásával, a megfelelő betűtípusok kialakításával a tipográfia tudománya foglalkozik.

* https://en.wikipedia.org/wiki/Typography

:math:`\rhd` Honnan ered a *lower case* és az *upper case* kifejezés?

* TTF: *True Type Font*
* https://en.wikipedia.org/wiki/TrueType
* https://en.wikipedia.org/wiki/FreeType

Raszterizálás
-------------

* Ebben a lépésben rajzolhatjuk ki a megjelenítendő betűket textúrákra, amelyeket aztán különféle alakzatokon jeleníthetünk meg.
* Számításigényes művelet, ezért érdemes gyorsítótárazni (*font cache*).

Kerning
-------

* A betűk közötti térközök kiszámításának problémája, módszere.
* https://en.wikipedia.org/wiki/Kerning

Szövegkirajzolás SDL2 segítségével
----------------------------------

* Az :code:`SDL2_ttf` függvénykönyvtárat használhatjuk hozzá.
* https://wiki.libsdl.org/SDL2_ttf/FrontPage

:math:`\rhd` Tekintsük át a :code:`examples/text` példát!

GUI felületek kialakítása
-------------------------

* Vezérlők, widget-ek

:math:`\rhd` Milyen widget-eket ismerünk/szoktunk használni?

Számos elterjedt widget toolkit, GUI library van.

* HTML5
* Windows API
* Qt: https://doc.qt.io/qt-6/qtwidgets-index.html
* GTK: https://www.gtk.org/
* Dear ImGui: https://github.com/ocornut/imgui

.. https://github.com/capnramses/antons_opengl_tutorials_book/tree/master/27_font_atlas

