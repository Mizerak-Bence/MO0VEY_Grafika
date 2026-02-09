Alapvető grafikai algoritmusok
==============================

A következőkben az algoritmusoknál raszteres megjelenítőt feltételezünk. Ezeknél a képernyőn megjelenített adatok valamilyen képmátrixba, videómemóriába kerülnek.

* Ez egy kétdimenziós tömb.
* A tömbben lévő értékek mutatják, hogy milyen színű legyen az adott képpont.

A jellegzetes geometriai alakzataink folytonosak, a raszterizálás viszont diszkrét és véges.
A raszterzilásra tekinthetünk úgy, mint egy mintavételezési folyamatra.

A raszterizálásnál szempont az, hogy

* a megjelenítés minél gyorsabb tudjon lenni, és
* a kép minősége minél jobb legyen.

Ezt a kettőt általában nem lehet egyszerre javítani.

.. warning::

  A geometriai alakzataink a valóságban nem léteznek.

Gyakorlati szempontból problémát jelent, hogy különböző konvenciók vannak a koordináták megadásához.

* Geometriai jelölésrendszert feltételezve a vízszintes tengely az :math:`x`, a függőleges tengely az :math:`y`. Az :math:`x` érték balról-jobbra, az :math:`y` érték pedig lenntről felfelé szokott növekedni.
* Lineáris algebra és numerikus módszerek kapcsán a mátrixot sor és oszlop szerint szokás indexelni.
* A grafikus megjelenítő eszközöknél az origó a bal felső sarokban szokott lenni. Az :math:`x` érték balról-jobbra nő, az :math:`y` érték fenntről-lefelé.

Szoktunk beszélni világ, valós és képi koordinátarendszerről. Ezek között az átváltás általában skálázás, tükrözés és eltolás műveletekkel valósítható meg.

.. admonition:: Példa

  Tegyük fel, hogy a képernyőnk felbontása :math:`1600 \times 800`. Ezen szeretnénk megjeleníteni az :math:`\{(x, y) | -5 \leq x < 5, 0 \leq y < 5\}` halmaz pontjait. Feltételezzük, hogy az origó a képernyő aljának közepén van.

  * Írjuk fel azt a függvényt, amelyik a sík pontjait a képernyő képpontjaihoz rendeli!

  .. math::

    f(x, y) = (\text{Round}(160 \cdot x + 800), \text{Round}(160 \cdot (5 - y)))

  * Írjuk fel azt a függvényt, amelyik a képernyő képpontjait a sik pontjaihoz rendeli!

  .. math::

    f(x, y) = ((x - 800) / 160, (800 - y) / 160)

.. note::

  Az átalakításnál kerekítés helyett gyakran csak alsóegészrész vagy a törtrész levágása szerepel.

Rajzoló algoritmusok
--------------------

Az egyszerűbb elemektől a bonyolultabbak felé kerülnek bemutatásra az algoritmusok.

A képernyőt a következő struktúrával írjuk le:

.. code:: cpp

  typedef struct Screen {
    int w;
    int h;
    int data[WIDTH][HEIGHT];
  } Screen;

Pontok
~~~~~~

A matematikai értelemben vett pontoknak nincs kiterjedésük, így azok megjelenítésével nem érdemes foglalkozni. A gyakorlatban mégis előfordul, úgy mint

* egy képpont színének átállításával kapott pont,
* kis méretű négyzet, vagy
* kis méretű kör.

Egy pontot adott raszteres megjelenítőn a képmátrix megfelelő értékének az átállításával lehet megjeleníteni.

* A képpontonkénti elérés nem feltétlenül hatékony.
* A videómemóriához nincs mindig közvetlen hozzáférésünk.
* Bizonyos rendszerek a pontoknak is definiálnak vastagságot, így gyakorlatilag négyzetként vagy körlapként jelenítik meg azokat.

Egy képpont megadásához az alábbi struktúrát használhatjuk:

.. code:: cpp

  typedef struct Point {
    int x;
    int y;
  } Point;

:math:`\rhd` Hogyan tudunk egy képpontot címezni, hogy ha a képbufferünk egy egydimenziós tömb?

Vízszintes és függőleges vonalak
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Vízszintes vonal rajzolása:

.. code:: cpp

  void draw_horizontal(Screen* screen, int y, int color) {
    for (int x = 0; x < screen->w; ++x) {
      screen->data[x][y] = color;
    }
  }

Függőleges vonal rajzolása:

.. code:: cpp

  void draw_vertical(Screen* screen, int x, int color) {
    for (int y = 0; y < screen->h; ++y) {
      screen->data[x][y] = color;
    }
  }

.. note::

  Az előzőekben feltételeztük, hogy az `x` és `y` értékek a képernyő megjelenítési tartományán belül vannak. Ezt a programokban általában ellenőrízni is kell!

:math:`\rhd` Hogyan tudjuk ezeket hatékonyan kirajzoltatni, hogy ha a képbufferünk egy egydimenziós tömb?

Téglalapok
~~~~~~~~~~

A téglalapoknak egy speciális esetéről lesz szó, amelyeknél

* az oldalak párhuzamosak a tengelyekkel, és
* a téglalap egész képpontokat fed csak le.

.. code:: cpp

  typedef struct Rect {
    int x;
    int y;
    int width;
    int height;
  } Rect;

Téglalap rajzolása `color` színnel:

.. code:: cpp

  void draw_rect(Screen* screen, Rect* rect, int color) {
    for (int y = rect->y; y < rect->y + rect->h; ++y) {
      for (int x = rect->x; x < rect->x + rect->w; ++x) {
        screen->data[x][y] = color;
      }
    }
  }

.. note::

  Az előzőekben több feltételezéssel éltünk.

  * A téglalap teljes egészében a megjeleníthető tartományba esik.
  * A téglalap értékei megfelelőek (nincs például negatív szélesség).

Szakaszok rajzolása, élsimítás
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A raszteres képernyő véges, ezért egyenesek helyett inkább csak szakaszok rajzolásáról beszélhetünk.

A szakasz rajzolásához a legegyszerűbb megoldás a DDA (*Digital Differential Analyzer*).

.. code:: cpp

  void draw_line_dda(Screen* screen, Point* a, Point* b, int color) {
    double x, y, dx, dy, step;
    dx = (b->x - a->x);
    dy = (b->y - a->y);
    step = (abs(dx) > abs(dy)) ? abs(dx) : abs(dy);
    dx /= step;
    dy /= step;
    x = a->x;
    y = a->y;
    for (int t = 0; t <= step; ++t) {
      screen->data[(int)x][(int)y];
      x += dx;
      y += dy;
    }
  }

A Bresenham algoritmus ennél egy hatékonyabb megoldást ad.

* Előnye, hogy egész aritmetikát használ.
* Az elterjedt architektúrákon hatékonyan implementálható.
* Hardver szintjén elérhető implementációk (pl.: firmware-ben).

.. note::

  A következő algoritmus feltételezi, hogy

  * a szakasz az első síknegyedben van, és
  * a rajta áthaladó egyenes :math:`y = m \cdot x + b` alakú egyenletében :math:`0 \leq m < 1`.

.. code:: cpp

  void draw_line_bresenham(Screen* screen, Point* a, Point* b, int color) {
    int x, y, dx, dy, diff;
    dx = b->x - a->x;
    dy = b->y - a->y;
    diff = 2 * dy - dx;
    for (x = a->x, y = a->y; x <= b->x; ++x) {
      screen->data[x][y] = color;
      if (diff > 0) {
        ++y;
        diff -= 2 * dx;
      }
      diff += 2 * dy;
    }
  }

.. admonition:: Példa

  Vizsgáljuk meg, hogy milyen pontokat rajzol ki az algoritmus a :math:`(4, 3)` és :math:`(12, 5)` pontokat összekötő szakaszon!

  .. code::

    dx = 8, dy = 2, diff = -4

  .. csv-table::
    :header-rows: 1

    x,y,diff
    4,3,-4
    5,3,0
    6,3,4
    7,4,-12
    8,4,-8
    9,4,-4
    10,4,0
    11,4,4
    12,5,-12

Élsimítás (*Anti Aliasing*)

* Úgy tekinthetjük, hogy a szakasz több képpontra esik, így a hozzá tartozó intenzitásokat az átfedés arányában érdemes beállítani.

* https://en.wikipedia.org/wiki/Digital_differential_analyzer_(graphics_algorithm)
* https://en.wikipedia.org/wiki/Bresenham%27s_line_algorithm
* https://en.wikipedia.org/wiki/Xiaolin_Wu%27s_line_algorithm

Háromszög kitöltés
~~~~~~~~~~~~~~~~~~

* *Triangle Rasterization*
* Arra törekszünk, hogy éppen csak annyi képpontot jelenítsünk meg, amennyire szükség van.
* A kitöltött háromszöget megjeleníthetjük úgy, mint közvetlenül egymás alá rajzolt vízszintes szakaszokat. (Megoldható lenne függőlegesekkel is.)

:math:`\rhd` Vizsgáljuk meg, hogy mennyi speciális és problémás eset fordulhat elő!

* http://www.sunshine2k.de/coding/java/TriangleRasterization/TriangleRasterization.html

Kör, ellipszis rajzolása
~~~~~~~~~~~~~~~~~~~~~~~~

A kört és általánosan az ellipszist is sokszögként közelíthetjük, mint zárt görbét. A probléma így visszavezethető a szakasz rajzolásra.

.. code:: cpp

  typedef struct Circle {
    int x;
    int y;
    int radius;
  } Circle;

  void draw_circle(Screen* screen, Circle* circle, int color) {
    double x_0, y_0, x, y;
    double phi, delta;
    phi = 0;
    delta = 0.01;
    x_0 = circle->radius * cos(phi) + circle->x;
    y_0 = circle->radius * sin(phi) + circle->y;
    while (phi < 2 * M_PI) {
      Point p_0;
      Point p;
      phi += delta;
      x = circle->radius * cos(phi) + circle->x;
      y = circle->radius * sin(phi) + circle->y;
      p_0->x = x_0;
      p_0->y = y_0;
      p->x = x;
      p->y = y;
      draw_line(screen, &p_0, &p, color);
      x_0 = x;
      y_0 = y;
    }
  }

:math:`\rhd` Hogyan érdemes megválasztani a `delta` változó értékét?

:math:`\rhd` Hogyan lehet az algoritmust ellipszis rajzolásához általánosítani?

* A Bresenham algoritmus körvonal rajzolására is alkalmas. (Szintén 8 esetet kell megkülönböztetni.)
* A háromszögekhez hasonlóan egymás alá rajzolt szakaszokként jeleníthetjük meg a kitöltött alakzatot.
* Az élsimítás problémája itt is felvetődik.
* A függvénykönyvtárak esetében kör és ellipszis helyett gyakran csak ív (körív, elliptikus ív) rajzolása szerepel, amelyhez szögtartományt is meg lehet adni.

Képelemek vágása
~~~~~~~~~~~~~~~~

* A megjelenítéshez használt felületünk (vagy úgy általában térrészünk) véges. Ezt nevezzük *viewport*-nak.
* Gyakori eset, hogy az eredményben csak az alakzatok bizonyos része látszik.
* Az alakzatok megjelenítendő részének meghatározása külön számításokat igényel.

Szakaszmetsző eljárások

* Danny Cohen, Ivan Sutherland: *Cohen-Sutherland algoritmus*, 1967
* You-Dong Liang, Brian A. Barsky: *Liang-Barsky algoritmus*

Az algoritmus működése:

* A teret a *viewport* oldalaival 9 részre vágjuk.
* Bevezetünk egy bináris kódolást, amely azt mutatja, hogy a *viewport*-tól milyen irányba vagyunk, például *top-bottom-left-right* sorrendben.
* A megjelenítendő térrészhez a `0000` kód fog tartozni.
* A szakasz végpontjaihoz megállapítjuk a kódokat.
* Elvégzünk egy bitenkénti vagy műveletet. Hogy ha `0000`-t kapunk, akkor a teljes szakasz megjelenítendő
* egyébként elvégzünk egy bitenkénti és (*AND*) műveletet. Hogy ha NEM `0000`-át kapunk, akkor a szakasz nem látszik.
* Ha `0000`-át kaptunk az *AND* műveletre, akkor elvégezzük a metszést az *OR* művelet szerinti bitekhez tartozó oldalakra.

:math:`\rhd` Mennyi eset van összesen a végpontok térrészbe esésére vonatkozóan? Vizsgáljunk meg ezek közül néhányat!

* https://en.wikipedia.org/wiki/Line_clipping
* https://en.wikipedia.org/wiki/Cohen%E2%80%93Sutherland_algorithm
* https://www.geeksforgeeks.org/line-clipping-set-1-cohen-sutherland-algorithm/
* https://www.skytopia.com/project/articles/compsci/clipping.html

Poligonok vágása

* https://en.wikipedia.org/wiki/Sutherland%E2%80%93Hodgman_algorithm

Floodfill algoritmus
~~~~~~~~~~~~~~~~~~~~

Az előzőekben olyan algoritmusokat vizsgáltunk, amelyek a koordináták alapján, a matematikai alakzatokat közelítve oldották meg a megjelenítést.

Az adott színnel való kitöltés egy szintén gyakori algoritmus, amely inkább a gráfalgoritmusokhoz sorolható.

* https://en.wikipedia.org/wiki/Flood_fill

Szoftveres eszközök
-------------------

GUI toolkit-ek
~~~~~~~~~~~~~~

* Graphical User Interface
* *Widget*: *Window Gadget*
* https://en.wikipedia.org/wiki/List_of_widget_toolkits

Windows API

* Direct2D
* https://learn.microsoft.com/en-us/windows/win32/direct2d/the-direct2d-api
* https://en.wikipedia.org/wiki/Direct2D

GTK

* GTK: GIMP ToolKit, GIMP: GNU Image Manipulation Program, GNU: GNU's Not UNIX
* https://www.gtk.org/
* https://www.cairographics.org/tutorial/

KDE

* A Qt keretrendszerre épül.
* Mostmár elérhető hozzá deklaratív és procedurális grafika.
* https://doc.qt.io/qt-5/qpainter.html

Java Swing

* Az AWT keretrendszer utódjának tekinthető.
* https://docs.oracle.com/javase/8/docs/api/java/awt/Graphics.html

További függvénykönyvtárak
~~~~~~~~~~~~~~~~~~~~~~~~~~

DOS

* VGA, VESA videó módok
* Borland Graphics Interface, https://en.wikipedia.org/wiki/Borland_Graphics_Interface

HTML5 Canvas API

* https://en.wikipedia.org/wiki/Category:Graphics_libraries


OpenGL, DirectX, Vulkan

* 2D-s megjelenítésre is alkalmasak.
* Később kerülnek még részletezésre.

.. TODO: 2D rajzoló API-k összehasonlítása

Esemény- és programvezérelt programozás
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Az alkalmazásunk szempontjából eseményeknek tekinthetjük például az alábbiakat:

* billentyűzet esemény,
* egér esemény,
* időzítő esemény,
* hálózati kérésre adott válasz esemény.

Aszinkron eseményekről van szó.

* Az eseményvezérelt programozás azt jelenti, hogy a programban végrehajtandó műveleteket bizonyos eseményekhez rendeljük.
* Programvezérelt esetben a programkódunkban kell azt (szinkron módon) vizsgálni, hogy következett-e be esemény.

.. code:: cpp

  #include "app.h"

  /**
  * Main function
  */
  int main(int argc, char* argv[])
  {
      App app;

      create_app(&app, 800, 600);
      while (app.is_running) {
          handle_app_events(&app);
          update_app(&app);
          render_app(&app);
      }
      destroy_app(&app);

      return 0;
  }

:math:`\rhd` Hogy lehetne megoldani a visszatérési hibakód kezelését?

Keretidő

* A két, egymást követő képkocka kirajzolása között eltelt idő.
* Jelölhetjük például :math:`\Delta t`-vel.
* Ezt használjuk fel az alkalmazás állapotának a frissítéséhez.

.. note::

  Az *update* és a *render* műveletek nem minden esetben kell, hogy felváltva kövessék egymást.

MVC modell

* Modell-Nézet-Vezérlő, *Model-View-Controller*
* A programunk aktuális állapotát jelenítjük meg a *render* végrehajtása során. Egy leképzésről, függvény jellegű kapcsolatról van szó.
* Esetünkben az eseménykezelő függvény az ami a *Controller*.
* Az MVC-nek számos változata, és értelmezése van, például MVP, MVVM.
* https://en.wikipedia.org/wiki/Model%E2%80%93view%E2%80%93controller

.. note::

  Az alkalmazás kódját ezen logika szerint érdemes szervezni. Nem jó, hogy ha keverednek a megjelenítéssel, eseménykezeléssel és az állapottér módosításával kapcsolatos kódrészek.

Interaktív grafikus felületek kialakítása
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A programunkban be- és kimenet kezelésére egyaránt szükség van.

A különféle (hardveres vagy grafikus elemekhez kötött) vezérlők segítségével interakcióba tudunk lépni a virtuális terünk elemeivel.

SDL2
~~~~

* https://www.libsdl.org/
* https://wiki.libsdl.org/SDL2/Books
* https://tr0ll.net/libsdl/docs/sdldoc.pdf

Kérdések
--------

* Milyen problémák megoldásához használjuk az SDL2-őt?
* Mi a keretidő, és mire használjuk a programokban?
* Miért szerepeltetünk a függvények többségénél első paraméterként egy struktúra mutatót? Mi ennek a megfelelője más nyelvekben?
* Mikor kerül megjelenítésre a virtuális tér SDL2 esetében?
* Milyen események tartoznak az egér kezeléséhez?
* Milyen események tartoznak a billentyűzet kezeléséhez?


Számítási feladatok
-------------------

* Tegyük fel, hogy az :math:`(x, y) \in [-8, 8] \times [-6, 6]` pontokat szeretnénk megjeleníteni a képernyőn. A képernyő felbontása :math:`1024 \times 768`.

  * Írja fel azt a függvényt, amelyik a sík pontjaihoz a képernyő képpontjait rendeli!
  * Írja fel azt a függvényt, amelyik a képernyő képpontjaihoz a sík pontjait rendeli!
  * Írjuk fel az előző függvényeket transzformációs mátrixok alakjában!

* A síkban egy 10 egység sugarú körvonalat 2 egység szélességű vonallal jelenítünk meg. Mennyi az így kapott alakzat területe?


Programozási feladatok
----------------------

Szakaszok rajzolása
~~~~~~~~~~~~~~~~~~~

* Definiáljunk egy szakasz (``Line``) nevű struktúrát, amelyik tartalmazza a szakasz végpontjait és a kirajzoláshoz használt színt! (A szín lehet index vagy karakter szerint megadott, vagy RGB komponensekkel is. Utóbbi esetben célszerű definiálni egy külön ``Color`` struktúrát.)
* Nézzünk utána, hogy hogyan kezelhető SDL-ben az egéresemény! Kérdezzük le az egérkurzor pozícióját és írassuk ki a szabványos kimenetre!
* Készítsünk egy szakasz rajzoló programot, amellyel egérkattintással lehet megadni a szakaszok végpontjait! (Feltételezzük, hogy legfeljebb ``MAX_LINE_COUNT`` számú szakasz tárolható és jeleníthető meg egyszerre.)
* Készítsünk egy palettát, ahonnan kattintással kiválasztható az adott szakasz megjelenítéséhez használt színt!
* Készítsünk egy olyan változatot, melyben a szakaszok helyett beszínezett téglalapok vannak!


Kör közelítése
~~~~~~~~~~~~~~

* Az ``examples/circle`` példában szereplő ``Circle`` struktúrát egészítsük ki egy szín attribútummal!
* A szakasz kirajzolásához használt függvény segítségével készítsünk egy olyan programot, amely a körvonalat szakaszokkal közelíti!
* Vizsgáljuk meg azon eseteket, amikor a közelítést a felosztáshoz használt lépések számával, a lépések szögével illetve a kirajzolt szakaszok maximális hosszával adhatjuk meg!
* Készítsünk egy programot, amellyel különböző színű köröket lehet megjeleníteni!
* Oldjuk meg, hogy az egér segítségével új köröket is meg lehessen adni! (A számukat itt is maximalizálhatjuk, például egy ``MAX_CIRCLE_COUNT`` értékkel.)
* Az egéresemények kezelésével rajzoljunk be egy + vagy x jelet azon körökbe, amely felett van éppen a kurzor. (Egyidejűleg több felett is lehet.)
* Oldjuk meg, hogy a kirajzolt köröket az egér segítségével lehessen mozgatni!

