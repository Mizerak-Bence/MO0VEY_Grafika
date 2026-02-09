*********
Felületek
*********

Leírási módok
=============

* Explicit: :math:`z = f(x, y)`
* Implicit: :math:`F(x, y, z) = 0`
* Paraméteres: :math:`\textbf{s}: \mathbb{R}^2 \rightarrow \mathbb{R}^3`

:math:`\rhd` Vizsgáljuk meg a félgömb leírási módjait mindhárom esetben!

:math:`\rhd` Vizsgáljuk meg, hogy milyen esetekben és módon térhetünk át egyik leírási módról a másikra!

Explicit felületek
------------------

Az interpolációs görbékhez hasonlóan adódik a lehetőség, hogy keressünk olyan kétváltozós függvényeket, amelyek az adott (interpolációs) pontokon átmennek.

A felületek előállítására vonatkozóan példaként tekintsünk egy nagyon egyszerű módszert!

Tegyük fel, hogy adottak az :math:`(x_0, y_0, z_0), (x_1, y_1, z_1), \ldots, (x_n, y_n, z_n)` pontok a térben! Feltételezzük, hogy nincs olyan közöttük, hogy azonos :math:`x` értékhez különböző :math:`z` érték tartozna, hasonlóképpen :math:`y` esetében is!

Oldjuk meg az interpolációs problémát a :math:`(x_0, z_0), (x_1, z_1), \ldots, (x_n, z_n)` pontokra! Jelölje ezt az interpolációs függvényt :math:`f_x(x, z)`! Ezzel :math:`y`-tól függetlenül kaphatunk egy (vonal)felületet.

Hasonlóképpen oldjuk meg az interpolációt a :math:`(y_0, z_0), (y_1, z_1), \ldots, (y_n, z_n)` pontokra, amely :math:`x`-től függetlenül ad egy felületet.

Mindkét felület áthalad az interpolációs pontokon az adott tengelyek irányából, az átlagukként kapott felület pedig teljesíteni fogja az interpolációs probléma kritériumait.

.. note::

   Már a külön irányok figyelembevételével előállított felületek is teljesítik az interpoláció feltételeit.

Paraméteres felületek
---------------------

Tekintsünk egy :math:`G \subseteq \mathbb{R}^2` tartományt. Az

.. math::

   \textbf{s}(u, v) = \begin{bmatrix}
   r_x(u, v) \\
   r_y(u, v) \\
   r_z(u, v) \\
   \end{bmatrix}, (u, v) \in G
 
kétparaméteres vektorfüggvény által meghatározott ponthalmazt (differenciálgeometriai értelemben) felületnek nevezünk, hogy ha:

* :math:`\textbf{s}(u, v)` kölcsönösen egyértelmű, mindkét irányba folytonos,
* a :math:`G` tartomány minden pontjában folytonosan differenciálható,
* a :math:`\dfrac{\partial}{\partial u}\textbf{s}(u, v)` és :math:`\dfrac{\partial}{\partial v}\textbf{s}(u, v)` vektorok lineárisan függetlenek bármilyen :math:`(u, v) \in G` esetén.

Jellemzők
=========

A görbékhez hasonlóan a felületekhez is meghatározhatunk a felület adott pontjához rendelhető jellemzőket. Ezeket részletezik a következő szakaszok.

Érintősík
---------

Tekintsük az :math:`\textbf{s}(u, v)` felület egy tetszőleges pontját! Az ezen a ponton áthaladó felületi görbék érintői a közös pontban egy síkban vannak. Ezt nevezzük érintősíknak.

Tekintsük az :math:`u` és :math:`v` paraméterekhez tartozó paramétervonalakat! Az ezekhez tartozó érintőket az alábbi formában számolhatjuk ki:

.. math::

   \textbf{s}_u (u, v) = \dfrac{\partial}{\partial u}\textbf{s}(u, v),
   \quad
   \textbf{s}_v (u, v) = \dfrac{\partial}{\partial v}\textbf{s}(u, v).

Válasszunk ki a felületen egy :math:`\textbf{r}(t) = \textbf{s}(u(t), v(t))` görbét! Mivel

.. math::

   \dfrac{\mathrm{d}}{\mathrm{d}t}\textbf{r}(t) =
   \dfrac{\mathrm{d}}{\mathrm{d}t}\textbf{s}(u(t), v(t)) =
   \dfrac{\partial}{\partial u}\textbf{s}(u, v)\dfrac{\mathrm{d}}{\mathrm{d}t}u(t) +
   \dfrac{\partial}{\partial v}\textbf{s}(u, v)\dfrac{\mathrm{d}}{\mathrm{d}t}v(t)

alakban kifejezhető, ezért bármilyen pontbeli érintőegyenes az :math:`\textbf{s}_u` és :math:`\textbf{s}_v` vektorok lineáris kombinációjaként felírható, vagyis az azok által kifeszített síkban van.

Normálvektor
------------

Az érintősíkra merőleges vektort normálvektornak nevezzük, és az

.. math::

    \textbf{s}_u(u, v) \times \textbf{s}_v(u, v)

formában számolhatjuk. Ennek egységnyi hosszúságú változata a felület *normálegységvektora*:

.. math::

   \textbf{n}(u, v) = \dfrac
   {\textbf{s}_u(u, v) \times \textbf{s}_v(u, v)}
   {\lVert \textbf{s}_u(u, v) \times \textbf{s}_v(u, v) \rVert}.

:math:`\rhd` Hogyan tudjuk felírni az érintősík (normálvektoros) egyenletét?

Twist-vektor
------------

Az :math:`\textbf{s}` felület :math:`\textbf{s}(u, v)` pontjához tartozó

.. math::

   \dfrac{\partial^2}{\partial v \partial u}\textbf{s}(u, v)

vegyes másodrendű parciális deriváltját (mint vektort) a felület *twist-vektorának* nevezzük.

Vonalfelületek
==============

Vonalfelületnek nevezzük az olyan felületet, amely bármely pontján illeszkedik a felületre egy egyenes. Ezeket az egyeneseket alkotóknak nevezzük.

Egy lehetséges felírási módjuk például:

.. math::

   \textbf{s}(u, v) = \textbf{r}(u) + v \textbf{e}(u), \quad
   u \in [u_0, u_1], v \in [v_0, v_1],

ahol

* :math:`\textbf{r}`: tetszőleges térgörbe,
* :math:`\textbf{e}`: egy :math:`\mathbb{R} \rightarrow \mathbb{R}^3` vektor értékű függvény, amely az alkotók irányát adja.

Két, azonos paraméterezésű görbe, azonos pontjaihoz tartozó pontjainak konvex kombinációival (más szóval a pontokat összekötő szakaszokkal) szintén felületet kapunk:

.. math::

   \textbf{s}(u, v) = (1 - v)\textbf{r}_1(u) + v\textbf{r}_2(u),
   \quad v \in [0, 1], u \in [u_0, u_1].

(Ezt tekinthetjük/nevezhetjük a két görbe lineáris interpolációjának.)

Mozgó görbe által súrolt felület
================================

Tekintsünk egy tetszőleges :math:`\textbf{r}(u), u \in [u_0, u_1]` térgörbét!

* Feltételezzük, hogy homogén koordinátarendszerben vagyunk, vagyis a térbeli transzformációk megadásához :math:`4 \times 4`-es mátrixok szükségesek!
* Definiáljunk egyet a :math:`v \in [v_0, v_1]` paraméter függvényében az :math:`M(v) \in \mathbb{R}^{4 \times 4}` formában! (Feltételezzük továbbá, hogy a mátrix értékei a :math:`v` paraméter függvényében folytonosan változnak.)

Ezek segítségével definiálni tudunk felületeket a

.. math::

   \textbf{s}(u, v) = \textbf{M}(v) \cdot \textbf{r}(u),
   \quad u \in [u_0, u_1], v \in [v_0, v_1]

alakban.


Tenzori szorzatként előállított felületek
=========================================

* A térgörbék megadásához használhatunk (a görbe típusának megfelelően) interpolációs vagy kontrollpontokat.
* Megtehetjük, hogy ezeket egy másik paraméter segítségével szintén görbék mentén mozgatjuk. A kontrollpontokhoz tartozó görbéket *pályagörbéknek* hívjuk.
* A pályagörbe szintén lehet kontrollpontokkal megadott görbe.

Legyenek adottak a

* :math:`\{\textbf{c}_i\}_{i=0}^n` kontrollpontok, és
* az ezekhez tartozó :math:`\{F_i(u): u \in [u_0, u_1]\}_{i=0}^n` bázisfüggvények!

Egy görbét ezek segítségével az

.. math::

   \textbf{r}(u) = \sum_{i=0}^n \textbf{c}_i F_i(u), \quad u \in [u_0, u_1]

alakban írhatunk föl.

A kontrollpontok "mozgatásához" hasonlóképpen adjunk meg egy bázisfüggvénnyel felírható térgörbét, amely így viszont már a :math:`\textbf{c}_i` kontrollpontot fogja meghatározni a :math:`v` paraméter függvényében. Az ehhez tartozó :math:`\{\textbf{a}_{i,j}\}_{j=0}^m` kontrollpontok szintén az :math:`i` függvényében írhatók fel. A kontrollpontok tehát a

.. math::

    \textbf{c}_i(v) =
    \sum_{j=0}^m \textbf{a}_{i,j}G_j(v), \quad v \in [v_0, v_1], i = 0, 1, \ldots, n

formában lesznek meghatározhatók.

Visszahelyettesítve az :math:`\textbf{r}(u)` görbe felírásába:

.. math::

   \begin{align}
   \textbf{s}(u, v) &=
   \sum_{i=0}^n \left(
   \sum_{j=0}^m \textbf{a}_{i,j}G_j(v)
   \right) F_i(u) \\
   &= \sum_{i=0}^n \sum_{j=0}^m \textbf{a}_{i,j} F_i(u) G_j(v),
   \end{align}

ahol :math:`u \in [u_0, u_1], v \in [v_0, v_1]`.

A felületek ezen előállítási módját nevezzük tenzori szorzatként való előállításnak.

* Az :math:`[a_ij]_{i=0,j=0}^{n,m}` pontokat kontrollpontoknak,
* az ezekből létrejövő hálót *kontrollhálónak* nevezzük.

.. todo:: Polygon mesh konverzió, triangulization

Kérdések
========

* Milyen módokon írhatunk le felületeket (matematikai megközelítésben)?
* Differenciálgeometriai értelemben hogyan definiálunk egy felületet?
* Írja le a paraméteres felületek gyakran használt pontbeli jellemzőit!
* Mit nevezünk vonalfelületeknek?
* Hogyan írhatunk fel mozgó görbe által súrolt felületeket?
* Mutassa be a tenzori szorzatként előállított felületek származtatási módját!

Számítási feladatok
===================

Adott egy felület paraméteres (vagy explicit) alakban. (Explicit esetén írja fel a paraméteres alakot!)

* Határozza meg a felület egy pontját az :math:`(u, v)` paraméterértéknél!
* Számítsa ki a pontbeli normálvektort!
* Írja fel a ponthoz tartozó érintőfelület egyenletét!
* Határozza meg a twist vektort!

Programozási feladatok
======================

Explicit felületek vizsgálata
-----------------------------

Tekintsük az :math:`f(x, y) = x^3+(x-2)^2+(y+1)^3-(y+2)^2` explicit alakban megadott függvényt!

* Ábrázoljuk a felületet az :math:`(x, y) \in [-5, 5]^2` tartomány felett (például ennek a segítségével: https://academo.org/demos/3d-surface-plotter)!
* Határozzuk meg a felület normálvektorát és érintőfelületét az :math:`(1, 2)` pontban!

Felületek tulajdonságainak vizsgálata
-------------------------------------

Készítsünk egy programot, amellyel paraméteres felületeket tudunk megjeleníteni egy rögzített tartomány felett!

* Törekedjünk arra, hogy fények használatával, színekkel a megjelenítés minél szemléletesebb legyen!
* Oldjuk meg, hogy egy adott :math:`(u, v)` paraméter esetén megjelenítésre kerüljön a felületi pont, a paramétervonalak, a felületi normálvektor! 

További feladatok
=================

* Vizsgáljuk meg, hogy hogyan általánosítható a Bézier görbe töröttvonalas közelítése Bézier görbékből létrehozott tenzori szorzat felületekre!

