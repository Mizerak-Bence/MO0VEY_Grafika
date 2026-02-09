*****************
Racionális görbék
*****************

* Egységes leírási módra való törekvés
* NURBS - Non-Uniform Rational B-Spline

Racionális Bézier görbe
=======================

A racionális Bézier görbe az eddig vizsgált Bézier görbe egy lehetséges általánosítása.

Definíció
---------

Legyenek adottak

* a :math:`\{\textbf{b}_i\}_{i=0}^n` kontrollpontok, és
* a :math:`\{w_i\}_{i=0}^n` nemnegatív súlyértékek (:math:`\sum_{i=0}^n w_i \neq 0`).

Az :math:`n`-edfokú racionális Bézier-görbét az alábbi formában definiáljuk:

.. math::

  \textbf{b}(t) =
  \sum_{i=0}^n \dfrac{w_i B_i^n(t)}{\sum_{j=0}^n w_j B_j^n(t)}
  \textbf{b}_i, \quad t \in [0, 1].

A görbe tulajdonságai
---------------------

Amennyiben csak nemnegatív súlyokat engedünk meg, akkor a racionális Bézier görbe a kontrollpontok konvex burkán belül marad.

.. admonition:: Bizonyítás

  Vizsgáljuk meg a görbe felírásában az alapfüggvényeket:

  .. math::

    \dfrac{w_i B_i^n(t)}{\sum_{j=0}^n w_j B_j^n(t)}, \quad
    t \in [0, 1], i = 0, 1, \ldots, n.

  * Látható, hogy a kifejezés nemnegatív.
  * Az :math:`i \in [0, n]` indexek feletti összegzésükkor látható, hogy a nevező azonos, a számláló pedig meg fog egyezni a nevezővel, így összegben 1-et fog eredményezni.

  Így tehát garantált, hogy konvex kombinációról van szó, vagyis a görbe pontjai a kontrollpontok konvex burkán belül fognak maradni. :math:`\square`

További tulajdonságok:

* Hogy ha a kontrollpontok sorrendjét (a pontokhoz tartozó súlyokat megtartva) fordított sorrendben vesszük, akkor is ugyanazt a racionális Bézier görbét kapjuk.
* A görbe globálisan változtatható.
* A végpontokban interpolál.
* A végpontokban a görbe érintője egybeesik a végpont és az a melletti kontrollponton áthaladó egyenessel.
* A görbét bármely sík (2 dimenzióban egyenes) legfeljebb annyi pontban metszi, mint a kontrollpoligonját. (*Hullámzáscsökkentő tulajdonság*)
* A görbe a paraméterének affin transzformációjára nézve invariáns.
* A görbe a kontrollpontjainak projektív transzformációjára nézve zárt. 

Kúpszeletek leírása
-------------------

Egy kúpnak a metszete az alábbi alakzatot eredményezheti:

* parabola,
* ellipszis,
* hiperbola.

A másodfokú Bézier-görbe parabolaívet ad, így ezt már ismertnek tekinthetjük.

Tekintsük a :math:`w_0 = 1, w_2 = 1` esetet! A :math:`w_1` megválasztásától függően kaphatjuk az említett 3 görbe típus valamelyikét.
Végeredményben azt kapjuk, hogy

* :math:`0 < w_1 < 1` esetén ellipszis,
* :math:`w_1 = 1` esetén parabola,
* :math:`w_1 > 1` esetén hiperbola

amit kapunk.

Racionális de Casteljau-algoritmus
----------------------------------

A de Casteljau algoritmust kisebb módosítással használhatjuk racionális Bézier-görbék pontjainak a kiszámítására is. A közbülső pontok meghatározásához a súlyokat :math:`t` paraméter függvényében kell tudnunk változtatni. Ez az :math:`r`-edik lépésre nézve konkrétan az alábbit jelenti:

.. math::

   w_i^r(t) = (1 - t)w_i^{r-1}(t) + t w_{i+1}^{r-1}(t).

Ezeket a súlyokat aztán a közbülső pontok kiszámításához a

.. math::

   \textbf{b}_i^r(t) =
   (1-t)\dfrac{w_i^{r-1}(t)}{w_i^r(t)}{w_i^r(t)}\textbf{b}_i^{r-1} +
   t\dfrac{w_{i+1}^{r-1}(t)}{w_i^r(t)}\textbf{b}_{i+1}^{r-1}(t),

ahol

.. math::

   r = 1, \ldots, n, i = 0, 1, \ldots, n - r,

továbbá az :math:`r = 0` lépésben

.. math::

   w_i^0 = w_i, \textbf{b}_i^0 = \textbf{b}_i, \quad i = 0, 1, \ldots, n.

A görbe pontját a :math:`\textbf{b}(t) = \textbf{b}_0^n(t)` alakban kapjuk (ahol :math:`t \in [0, 1]`).

.. note::

   Ez az algoritmus is alkalmas a görbe kettévágására.

Racionális B-spline görbe
=========================

Ezt nevezik NURBS (*Non-Uniform Rational B-Spline*) görbének. Valójában inkább *nem feltétlenül uniform* görbék halmazáról van szó, mivel a súlyokat megválaszthatjuk azonosnak is.

Definíció
---------

Jelölje

* :math:`N_i^k` az :math:`i`-edik :math:`(k-1)`-edfokú normalizált B-spline alapfüggvényt!
* Legyenek adottak a :math:`\{\textbf{d}_i\}_{i=0}^n` kontrollpontok (vagy más néven *de Boor pontok*),
* az :math:`\{u_i\}_{i=0}^{n+k}` csomóértékek, és
* a :math:`\{w_i\}_{i=0}^n` nemnegatív súlyok (amelyek nem azonosan nulla értékűek).

A :math:`k`-adrendű (vagy más szóval :math:`(k-1)`-edfokú) racionális B-spline görbét az alábbi módon definiáljuk:

.. math::

   \textbf{s}(u) =
   \sum_{i=0}^n \textbf{d}_i
   \dfrac{w_i N_i^k(u)}{\sum_{j=0}^n w_j N_j^k(u)},
   u \in [u_{k-1}, u_{n+1}], 1 < k \leq n + 1.


.. seealso::

   * https://en.wikipedia.org/wiki/B%C3%A9zier_curve

Tulajdonságai
-------------

A B-spline görbék számos tulajdonsága szerencsére a racionális B-spline görbék esetében is megmarad.

* Hogy ha a végpontokban a multiplicitás :math:`(k - 1)`, akkor a görbe a végpontokban interpolál.
* Az előbbi esetben teljesül az is, hogy az érintők a végpontokban a görbe végeinél lévő 2 kontrollpont által meghatározott egyenesek lesznek.
* A görbe lokálisan módosítható.
* Egy :math:`\textbf{s}(u)` görbe :math:`u \in [u_i, u_{i+1})` íve (ahol :math:`i = k - 1, k, \ldots, n`) a (:math:`k` darab :math:`\{\textbf{d}_j\}_{j=i-k+1}^i` kontrollpont konvex burkában van, a teljes görbe pedig ezen konvex burkok uniójában.
* Hullámzáscsökkentő tulajdonság: A görbét bármely sík (2 dimenzióban egyenes) legfeljebb annyi pontban metszi, mint a kontrollpoligonját.
* Hogy ha a végpontokban a csomóértékek multiplicitása :math:`(k - 1)`, és nincs különböző közbülső csomóérték, akkor Bézier-görbét kapunk.

Racionális de Boor-algoritmus
-----------------------------

A de Casteljau algoritmushoz hasonlóan a de Boor-algoritmusnak is van racionális görbékre vonatkozó változata.


Alkalmazási területek
=====================

Skálázható vektorgrafika
------------------------

* *Scalable Vector Graphics*
* https://en.wikipedia.org/wiki/SVG

Az alapvető elemei:

* https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Basic_Shapes
* https://www.w3.org/TR/SVG11/shapes.html

Path parancs
~~~~~~~~~~~~

* https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Paths

Elvégezhető műveletei:

* ``M``: Move To
* ``L``: Line To
* ``H``: Horizontal
* ``V``: Vertical
* ``Z``: Close Path

A kisbetűs változatok a relatívak az utolsó megadott ponthoz képest.

Curve parancs
~~~~~~~~~~~~~

* https://developer.mozilla.org/en-US/docs/Web/SVG/Tutorial/Paths#curve_commands

HTML5 Canvas
------------

* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/bezierCurveTo

:math:`\rhd` Vizsgáljuk meg, hogy más programozási nyelvek, függvénykönyvtárak esetében hogyan tudunk Bézier görbéket rajzolni!

PostScript
----------

* https://en.wikipedia.org/wiki/PostScript

TikZ
----

* https://en.wikipedia.org/wiki/PGF/TikZ
* https://tikz.net/

WaveFront OBJ formátum
----------------------

* https://paulbourke.net/dataformats/obj/

Vektorgrafikus szerkesztők
--------------------------

* Inkscape: https://inkscape.org/
* CorelDRAW: https://www.coreldraw.com/en/

.. note::

  A Bézier görbék nem vektorgrafikus szerkesztőkben is megjelennek, mint például a *path* eszköz a GIMP esetében.

Betűtípusok tervezése
---------------------

Font systems:

* https://en.wikipedia.org/wiki/PostScript
* https://en.wikipedia.org/wiki/Font_hinting
* https://en.wikipedia.org/wiki/OpenType
* https://fontforge.org/en-US/

Apple, font design:

* https://developer.apple.com/fonts/TrueType-Reference-Manual/RM01/Chap1.html
* https://developer.apple.com/fonts/TrueType-Reference-Manual/RM02/Chap2.html

.. http://chanae.walon.org/pub/ttf/ttf_glyphs.htm

.. todo:: Mutatni példát bázisfüggvény súlyozásos esetre, amely nem Bézier és nem B-Spline!

Kérdések
========

* Hogyan definiálható a racionális Bézier görbe?
* Mi az előnye a racionális Bézier görbének a Bézier görbéhez képest? Milyen tulajdonságokat örököl át?
* Hogyan írhatunk le kúpszeleteket racionális Bézier görbék segítségével?
* Hogyan definiálható a racionális B-spline görbe?
* Milyen tulajdonságai vannak a racionális B-spline görbéknek?

Programozási feladatok
======================

Racionális Bézier görbe
-----------------------

* Implementálja a görbét!
* Oldja meg, hogy a csomóértékeket és a súlyokat is interaktív módon lehessen változtatni!
* Adjon közelítést a görbe hosszára!

Racionális B-spline görbe
-------------------------

* Implementálja a görbét!
* Oldja meg, hogy a csomóértékeket és a súlyokat is interaktív módon lehessen változtatni!
* Adjon közelítést a görbe hosszára!

További feladatok
=================

* Vizsgálja meg, hogy milyen pontossággal lehet közelíteni a racionális Bézier görbéket Bézier görbékkel!
* Vizsgálja meg, hogy milyen pontossággal lehet közelíteni a racionális B-spline görbéket B-spline görbékkel!
* Legyen adott egy nagy elemszámú ponthalmaz, amelyre görbét szeretnénk illeszteni. (Feltételezzük, hogy a görbe nem tud minden ponton áthaladni majd.) Oldjuk meg a görbe illesztését, mint optimalizálási feladatot a megfelelő kontrollpontok, csomóértékek és súlyértékek megválasztásával!

