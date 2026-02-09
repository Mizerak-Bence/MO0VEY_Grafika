Koordinátarendszerek, transzformációk
=====================================

A számítógépi grafikában alapvetően az a cél, hogy különféle alakzatokat, különféle színekkel jelenítsünk meg. Mindkettőhöz szükségünk lesz koordinátarendszerekre, mivel ezek segítségével tudjuk számszerűsíteni azokat.

Koordinátarendszerek
--------------------

Vektor

* Rendezett :math:`n`-es. Esetünkben általában :math:`\mathbb{R}^n`.
* Az :math:`n` a tér dimenzióját adja meg.

.. admonition:: Példa

  A :math:`(1, 8, 0, -3, 7) \in \mathbb{R}^5` egy 5 dimenziós valós vektor.

:math:`\rhd` Milyen műveleteket végezhetünk el vektorokkal?

:math:`\rhd` Hogyan számíthatjuk ki egy vektor hosszát?

:math:`\rhd` Hogyan számíthatjuk ki a két vektor által bezárt szöget?

Vektortér

* https://en.wikipedia.org/wiki/Vector_space

Descartes koordinátarendszer
----------------------------

A tér pontjait, mint a tengelyekhez tartozó halmazok Descartes szorzatának elemeit kezeljük.

Háromdimenziós térbeli pont esetén a jelölések.

* :math:`(x, y, z) \in \mathbb{R}^3`
* :math:`\textbf{x} = (x_1, x_2, x_3) \in \mathbb{R}^3`
* Geometriában használatos jelölés még, hogy :math:`P \in \mathbb{R}^3`, koordinátánként pedig :math:`(P_x, P_y, P_z)`.

.. warning::

  A skalárok vektoroktól való megkülönböztetéséhez nyomtatott formában
  (mint itt a jegyzetben is) általában félkövér betűtípust használunk.
  (Például az :math:`s` az egy skalár, míg a :math:`\textbf{v}` az egy
  vektor.) Írásban ugyanilyen célból egy nyilat (vagy fél nyilat) szokás felé rajzolni,
  például :math:`\overrightarrow{v}`.

Jellemzően euklideszi térben gondolkozunk.

normál vektor
-------------

A görbére, felületre merőleges vektor.

* https://mathworld.wolfram.com/NormalVector.html
* https://en.wikipedia.org/wiki/Normal_(geometry)

Speciális esete az egység hosszúságú normál vektor.

Tegyük fel, hogy adott egy :math:`\textbf{n} = \begin{bmatrix} x \\ y
\end{bmatrix}`. Ebből az egység hosszúságú vektort a következő formában
kaphatjuk meg:

.. math::

  \textbf{u} = \dfrac{\textbf{n}}{|\textbf{n}|} = \dfrac{\textbf{n}}{\sqrt{x^2 +
  y^2}}.

Egyenes leírása
---------------

Meredekséggel felírt egyenlet: :math:`y = m \cdot x + b`

Az általános egyenlet (explicit alakja): :math:`Ax + By + C = 0, \quad A^2 + B^2 \neq 0`.

Megadható az :math:`Ax + By = D` alakban is.

Normálvektoros egyenlet: Tegyük fel, hogy ismert egy :math:`\textbf{p}_0 =
(x_0, y_0)` pont, továbbá tudjuk, hogy az egyenes normál vektor :math:`\textbf{n}`. Az egyenes normál vektoros alakja: :math:`\textbf{n} \cdot (\textbf{p} -
\textbf{p}_0) = 0`.

Irányvektoros egyenlet: Tegyük fel, hogy ismerjük az egyenes egy :math:`\textbf{p}_0` pontját, és a :math:`\textbf{v}` irányvektorát. Az egyenes pontjait egy :math:`t \in \mathbb{R}` paraméter függvényében a következőképpen kaphatjuk meg: :math:`\textbf{p}(t) = \textbf{p}_0 + t \cdot \textbf{v}`.

Az :math:`(x_1, y_1)` és az :math:`(x_2, y_2)` pontokon áthaladó egyenes megadásához használhatjuk a következő összefüggést:

.. math::

  (x - x_1)(y_2 - y_1) = (y - y_1)(x_2 - x_1).

Az irányvektort a következő formában számíthatjuk:

.. math::

  \textbf{v} = \begin{bmatrix} x_2 - x_1 \\ y_2 - y_1 \end{bmatrix}.

Az irányvektorból a normálvektor nem egyértelmű. A :math:`\textbf{n} = \begin{bmatrix} v_y \\ -v_x \end{bmatrix}` vagy az :math:`\textbf{n} = \begin{bmatrix} -v_y \\ v_x \end{bmatrix}` formában is számítható.

.. admonition:: Példa

  Írjuk fel a :math:`(-3, 2)` és a :math:`(5, 4)` pontokon áthaladó egyenes egyenletét!

  .. math::

    (x + 3)(4 - 2) = (y - 2)(5 + 3) \Rightarrow x - 4y + 11 = 0.

  Az általános egyenletben szereplő paraméterek tehát: :math:`A = 1, B = -4, C = 11`.

  Az egyenes irányvektora: :math:`\textbf{v} = \begin{bmatrix}4 \\ 1\end{bmatrix}`.

  Az irányvektoros egyenlet (például): :math:`\textbf{p}(t) = \begin{bmatrix}-3 \\ 2\end{bmatrix} + t \cdot \begin{bmatrix}4 \\ 1\end{bmatrix}`.

  Az egyenes normálvektora: :math:`\textbf{n} = \begin{bmatrix}-1 \\ 4\end{bmatrix}`.

  A normálvektoros egyenlet: :math:`\begin{bmatrix}-1 \\ 4\end{bmatrix}\cdot\begin{bmatrix}x + 3\\y - 2\end{bmatrix} = 0`.


Sík leírása
-----------

A normálvektoros egyenlet magasabb dimenzióban is használható, így a :math:`\textbf{p} \in \mathbb{R}^3` ponton áthaladó, :math:`\textbf{n} \in \mathbb{R}^3` normálvektorú sík egyenlete: :math:`\textbf{n} \cdot (\textbf{p} -
\textbf{p}_0) = 0`.

Az :math:`(x_0, y_0, z_0)` ponton áthaladó sík egyenlete felírható az :math:`A(x - x_0) + B(y - y_0) + C(z - z_0) = 0` explicit egyenlettel. Ennek a normál vektora :math:`(A, B, C)` lesz.

.. admonition:: Példa

  Írjuk fel a :math:`(-3, 9, -7)` pontokon áthaladó, :math:`\textbf{n} = (2, 4, -6)` normálvektorú sík egyenletét!

  .. math::

    2(x + 3) + 4(y - 9) - 6(z + 7) = 0.

Homogén koordinátarendszer
--------------------------

* August Ferdinand Möbius, 1827.
* https://en.wikipedia.org/wiki/Homogeneous_coordinates

Tulajdonképpen a Déscartes koordinátákat egészítjük ki egy arányossági tényezővel, amit :math:`w` betűvel jelölünk.

Sík esetében: :math:`(x, y) \rightarrow (x, y, w)`, tér esetében :math:`(x, y, z) \rightarrow (x, y, z, w)`.

* A Déscartes koordinátarendszerbeli pontokat a homogén koordinátarendszerbeliek részhalmazának tekintjük.
* A homogén koordinátarendszerbeli leírás nem egyértelmű. Egy Déscartes koordinátarendszerbeli pontot végtelen sok homogén koordinátarendszerbeli ponttal meg tudunk adni.
* A végtelenül távoli pontok tulajdonképpen irányokat jelölnek. Ezeknél a :math:`w` értéke 0.

A következőkben a koordinátarendszerek közötti átírási módot láthatjuk. Három dimenziós esetekre vonatkoznak, de egyszerűen általánosítható a módszer alacsonyabb és magasabb dimenzióba is.

Déscartes :math:`\rightarrow` Homogén

:math:`(x, y, z) \rightarrow (x, y, z, 1)`

Homogén :math:`\rightarrow` Déscartes

:math:`(x, y, z, w) \rightarrow \left(\dfrac{x}{w}, \dfrac{y}{w}, \dfrac{z}{w}\right)`

* Az osztás nyilván csak akkor végezhető el, hogy ha :math:`w \neq 0`.
* A :math:`w = 0` esetben beszélünk végtelenül távoli pontról, melynek nincs Déscartes koordinátarendszerbeli megfelelője.

A homogén koordinátarendszer használata az alábbiak miatt előnyös.

* A pont és az egyenes reprezentációja megegyezik.
* Tudunk vele ábrázolni végtelenül távoli pontokat.
* A számítások egyszerűbben leírhatóak lesznek.

Két ponton áthaladó egyenes
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Tegyük fel, hogy adottak az :math:`\textbf{e}_1 = (x_1, y_1, w_1)` és az :math:`\textbf{e}_2 = (x_2, y_2, w_2)` pontok! Az ezeken áthaladó egyenes vektorát a következő formában kapjuk:

.. math::

  \begin{vmatrix}
  \textbf{i} & \textbf{j} & \textbf{k} \\
  x_1 & y_1 & w_1 \\
  x_2 & y_2 & w_2 \\
  \end{vmatrix}.

Az egyenes koordinátái a determináns kifejtésével kapott együtthatók lesznek.

.. admonition:: Példa

  Számítsuk ki az :math:`(5, 8)` és a :math:`(7, 12)` pontokon áthaladó egyenest!

  .. math::

      \begin{vmatrix}
      \textbf{i} & \textbf{j} & \textbf{k} \\
      5 & 8 & 1 \\
      7 & 12 & 1 \\
      \end{vmatrix} =
      \begin{vmatrix}
      8 & 1 \\
      12 & 1 \\
      \end{vmatrix} \textbf{i} -
      \begin{vmatrix}
      5 & 1 \\
      7 & 1 \\
      \end{vmatrix} \textbf{j} +
      \begin{vmatrix}
      5 & 8 \\
      7 & 12 \\
      \end{vmatrix} \textbf{k} =
      (-4)\textbf{i} + (2)\textbf{j} + (4)\textbf{k}.

  Az egyenes tehát a :math:`(-4, 2, 4)` vektorral adható meg.

Két egyenes metszéspontja
~~~~~~~~~~~~~~~~~~~~~~~~~

A számítási mód az előzőhöz hasonlóan történik.

* A pontok helyett az egyeneseket írjuk be.
* Az egyenes helyett egy pont lesz a végeredmény.

Két pont távolsága
~~~~~~~~~~~~~~~~~~

Euklideszi térben az :math:`\textbf{a} \in \mathbb{R}^n` és a :math:`\textbf{b} \in \mathbb{R}^n` pontok távolságát a következő formában számíthatjuk:

.. math::

  d = \sqrt{\sum_{i=1}^n (a_i - b_i)^2}.

Megfogalmazhatjuk úgy is, hogy ez a pontokat leíró vektorok különbségének euklideszi normája, vagyis :math:`d = |\textbf{a} - \textbf{b}|_2`.

Pont-egyenes távolsága
~~~~~~~~~~~~~~~~~~~~~~

Tegyük fel, hogy az egyenes normálvektoros egyenletét ismerjük, továbbá feltételezzük, hogy :math:`|\textbf{n}| = 1` (vagyis a normálvektor egységnyi hosszúságú). A pont egyenestől való előjeles távolságát a :math:`d = \textbf{n}(\textbf{p} - \textbf{p}_0)` számítással határozhatjuk meg.

Pont-sík távolsága
~~~~~~~~~~~~~~~~~~

A normálvektoros egyenlet segítségével a pont síktól való távolságát a pont-egyenes távolság számításával analóg módon végezhetjük.

Merőleges vetítés
~~~~~~~~~~~~~~~~~

Tegyük fel, hogy adott egy egyenes, és egy rajta kívül eső pont. Meg szeretnénk határozni, hogy az egyenes melyik pontja van a külső ponthoz legközelebb.

Meg tudjuk határozni a külső ponton áthaladó, az eredeti egyenesre merőleges egyenes egyenletét, így a problémát visszavezethetjük két egyenes metszéspontjának számítására.

.. admonition:: Példa

  Tegyük fel, hogy adott egy egyenes, amely áthalad a :math:`(-6, 0)` és a :math:`(0, 3)` pontokon! Határozzuk meg az :math:`(5, 1)` pont merőleges vetületét!

  * A pontokon áthaladó egyenes felírható a :math:`(3, -6, 18)` vektorral.
  * Az egyenes :math:`\textbf{v} = (6, 3)` irányvektora egyúttal a merőleges egyenes normálvektora lesz.
  * A merőleges egyenes felírható a :math:`(6, 3, -33)` vektorral.
  * A metszéspont a :math:`(144, 207, 45)` homogén koordinátákkal adható meg, vagy például a :math:`(3.2, 4.6, 1)` formában.

  A vetületi pont a :math:`(3.2, 4.6)` Déscartes koordinátákkal felírva.

Transzformációk
---------------

A transzformációkat különféleképpen osztályozhatjuk, például, hogy:

* milyen elemeken végezhetők el, (például pont transzformációk),
* milyen dimenziós térben végezhetők el, (például sík és térbeli transzformációk),
* megtartják-e a távolságokat, arányokat, (például hasonlósági transzformációk).

Lineáris transzformációk esetében a transzformációt egy transzformációs mátrixszal is leírhatjuk. Homogén koordinátarendszerben, sík esetén ez egy :math:`M \in \mathbb{R}^{3 \times 3}` mátrix. Tegyük fel, hogy adott egy :math:`\textbf{p} \in \mathbb{R}^3` pont. A :math:`\textbf{p}'` transzformált pont a következő formában számítható:

.. math::

  \textbf{p}' = M \cdot \textbf{p}.

.. warning::

  A transzformációs mátrixszal való szorzás elvileg balról és jobbról is elvégezhető, viszont más transzformációt jelent. A használati módja szakirodalmanként eltérhet.

A következőkben a síkbeli ponttranszformációkat vizsgáljuk.

Egybevágósági transzformációk
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A legegyszerűbb esete az, amely a pontokat helyben hagyja. Ekkor a transzformációs mátrixszunk egy egységmátrix (identikus mátrix) lesz, vagyis:

.. math::

  M = \begin{bmatrix}
  1 & 0 & 0 \\
  0 & 1 & 0 \\
  0 & 0 & 1 \\
  \end{bmatrix}.

Tegyük fel, hogy a sík pontjait egy :math:`\textbf{d} \in \mathbb{R}^2` vektorral el szeretnénk tolni. (Ezt a műveletet szokás transzlációnak is nevezni.) Az ehhez tartozó transzformációs mátrix:

.. math::

  M = \begin{bmatrix}
  1 & 0 & d_x \\
  0 & 1 & d_y \\
  0 & 0 & 1 \\
  \end{bmatrix}.

A sík pontjainak az origó körüli elforgatásához meg kell adnunk egy szöget, amelyet például jelölhetünk :math:`\varphi` betűvel. Az elforgatás transzformációs mátrixsza:

.. math::

  M = \begin{bmatrix}
  \cos \varphi & -\sin \varphi & 0 \\
  \sin \varphi & \cos \varphi & 0 \\
  0 & 0 & 1 \\
  \end{bmatrix}.

Attól függően, hogy melyik színuszos elemhez teszünk negatív előjelet óramutató járásával ellentétes vagy megegyező irányú elforgatást kapunk.

A tükrözést szintén egybevágósági transzformációnak tekintjük. Mivel a skálázás egy speciális eseteként kezelhető, ezért ott kerül majd részletezésre.

Hasonlósági transzformációk
~~~~~~~~~~~~~~~~~~~~~~~~~~~

Egy alakzatot arányosan :math:`\lambda`-szorosára a következő transzformációs mátrixszal nagyíthatunk (vagy kicsinyíthetünk):

.. math::

  M = \begin{bmatrix}
  \lambda & 0 & 0 \\
  0 & \lambda & 0 \\
  0 & 0 & 1 \\
  \end{bmatrix}.

Hogy ha a :math:`\lambda`

* kisebb, mint 1, akkor kicsinyítés,
* 1 esetén identikus transzformáció,
* nagyobb, mint 1 érték esetén nagyítás.

Affin transzformációk
~~~~~~~~~~~~~~~~~~~~~

Az affin transzformációk azok, amelyek megtartják a párhuzamosságot. (Párhuzamos egyeneseket párhuzamos egyenesekbe visznek át.)

Az egyik típusa a skálázás (scaling), amellyel adott tengely szerinti kicsinyítést vagy nagyítást érhetünk el. Jelölje :math:`s_x` és :math:`s_y` az :math:`x` és az :math:`y` tengely szerinti skálázás mértékét. Az ehhez tartozó transzformációs mátrix:

.. math::

  M = \begin{bmatrix}
  s_x & 0 & 0 \\
  0 & s_y & 0 \\
  0 & 0 & 1 \\
  \end{bmatrix}.

Az :math:`s_x` és az :math:`s_y` megválasztásától függően tükrözést, és tengelyre való merőleges vetítést is le tudunk vele írni.

* Hogy ha :math:`s_x = 1` és :math:`s_y = 0`, akkor az :math:`x` tengelyre vetítünk.
* Hogy ha :math:`s_x = 0` és :math:`s_y = 1`, akkor az :math:`y` tengelyre vetítünk.

Szintén affin transzformáció a nyírás (shear). Vizsgáljuk azt az esetet, amely az :math:`x` tengely pontjait helyben hagyja. Ekkor tulajdonképpen egy olyan eltolásról van szó, amely a transzformált pont :math:`y` koordinátájával arányos. Jelölje az arányossági tényezőt :math:`\tau`! Az ehhez tartozó transzformációs mátrix:

.. math::

  M = \begin{bmatrix}
  1 & 0 & 0 \\
  \tau & 1 & 0 \\
  0 & 0 & 1 \\
  \end{bmatrix}.

Hasonlóképpen felírható a másik tengely szerinti nyírás is.

Összetett transzformációk
~~~~~~~~~~~~~~~~~~~~~~~~~

Több transzformációt egymás után, lépésenként végre tudunk hajtani. Például, hogy ha van 3 transzformációnk a hozzájuk tartozó :math:`M_1`, :math:`M_2` és :math:`M_3` transzformációs mátrixszokkal, akkor a transzformált pontok a következőképpen adódnak:

.. math::

  \textbf{p}' = M_1 \cdot \textbf{p},
  \textbf{p}'' = M_2 \cdot \textbf{p}',
  \textbf{p}''' = M_3 \cdot \textbf{p}''.

A teljes transzformáció felírható úgy, hogy :math:`\textbf{p}''' = M_3 \cdot M_2 \cdot M_1 \cdot \textbf{p}`

Általában ugyanazon transzformációkat több ponton is végre szeretnénk hajtani, és a mátrix szorzás asszociatív, ezért megtehetjük, hogy először kiszámítjuk az :math:`M = M_3 \cdot M_2 \cdot M_1` összetett transzformáció mátrixát, majd elegendő a transzformálandó pontokat ezzel szorozni.

.. note::

  A példa 3 transzformációra vonatkozik, de természetesen tetszőleges sok transzformációra általánosan működik a módszer.

Transzformációk inverze
~~~~~~~~~~~~~~~~~~~~~~~

Amennyiben a geometriai transzformációnknak van inverze, akkor azt az eredeti transzformáció mátrixának inverz mátrixsza fogja leírni. Az elemi transzformációk esetében ezek természetesen adódnak.

* Az identikus transzformációnak az identikus transzformáció az inverze.
* Egy :math:`(d_x, d_y)` vektorral való eltolásnak a :math:`(-d_x, -d_y)` vektorral való eltolás az inverze.
* Egy :math:`\varphi` szöggel történő elforgatásnak a :math:`-\varphi` szöggel való elforgatás az inverze.
* Egy :math:`(s_x, s_y)` paraméterekkel való skálázásnak az :math:`\left(\dfrac{1}{s_x}, \dfrac{1}{s_y}\right)` paraméterekkel való skálázás az inverze.
* Egy :math:`\tau` paraméterű nyírásnak az :math:`\dfrac{1}{\tau}` paraméterű nyírás az inverze.

Összetett transzformációk inverzének számításánál figyelni kell az elemi transzformációk sorrendjére.

Térbeli transzformációk
-----------------------

A térbeli transzformációk a síkbeli transzformációkhoz hasonlóan leírhatók mátrixszokkal.

Identikus transzformáció:

.. math::

  M = \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & 1 & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}.

Egy :math:`\textbf{d}` vektorral történő eltolás:

.. math::

  M = \begin{bmatrix}
  1 & 0 & 0 & d_x \\
  0 & 1 & 0 & d_y \\
  0 & 0 & 1 & d_z \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}.

Elforgatás az :math:`x` tengely körül :math:`\varphi_x` szöggel:

.. math::

  M = \begin{bmatrix}
  1 & 0 & 0 & 0 \\
  0 & cos \varphi_x & -\sin \varphi_x & 0 \\
  0 & \sin \varphi_x & \cos \varphi_x & 0 \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}.

Elforgatás az :math:`y` tengely körül :math:`\varphi_y` szöggel:

.. math::

  M = \begin{bmatrix}
  \cos \varphi_y & 0 & -\sin \varphi_y & 0 \\
  0 & 1 & 0 & 0 \\
  \sin \varphi_y & 0 & \cos \varphi_y & 0 \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}.

Elforgatás a :math:`z` tengely körül :math:`\varphi_z` szöggel:

.. math::

  M = \begin{bmatrix}
  \cos \varphi_z & -\sin \varphi_z & 0 & 0 \\
  \sin \varphi_z & \cos \varphi_z & 0 & 0 \\
  0 & 0 & 1 & 0 \\
  0 & 0 & 0 & 1 \\
  \end{bmatrix}.

.. warning::

  * A 3 tengely szerinti egyidejű elforgatások nem egyértelműek.
  * https://en.wikipedia.org/wiki/Gimbal_lock


Kérdések
--------

* Hogyan lehet átírni egy Descartes koordinátarendszerbeli pont koordinátáit homogén koordinátarendszerbe?
* Hogyan írható át egy homogén koordinátarendszerbeli pont Descartes koordinátarendszerbe?
* Hogyan írható fel egy adott :math:`\varphi` szög esetében az origó körüli elforgatás mátrixa?
* Hogyan néznek ki az eltolás, elforgatás és skálázás mátrixoknak az inverzei?
* Hogyan számíthatjuk ki két egyenes metszéspontját homogén koordinátarendszerben?
* Hogyan számíthatjuk ki két homogén koordinátarendszerbeli pont alapján a rajtuk áthaladó egyenest?
* Miből tudhatjuk, hogy egy homogén koordinátarendszerbeli pontnak nincs Descartes koordinátarendszerbeli megfelelője?
* Hogyan számíthatjuk ki egy összetett transzformáció transzformációs mátrixát az elemi transzformációs mátrixok ismeretében?
* Adjunk példát olyan esetre, amikor számít a transzformációk sorrendje!
* Adjunk példát olyan esetre, amikor nem számít a transzformációk sorrendje!
* Írjuk fel annak a térbeli transzformációnak a transzformációs mátrixát, amelyik a tér pontjait az X-Z síkra képzi le!
* Milyen előnyei miatt használunk homogén koordináta rendszert?

* Milyen fő lépéseken keresztül lesz a forrásfájlokból futtatható állomány?
* Mire szolgálnak a statikus függvénykönyvtárak (*static library*)?
* Miért és hogyan használjuk a ``make`` programot?
* Mi a különbség a statikus és a dinamikus linkelés között?
* Mit csinál az SDK-ban a ``shell.bat``?
* Célszerűen mi kerül a forrás és a fejléc (*header*) állományokba?


Számítási feladatok
-------------------

* Adjunk meg a :math:`(2, -1, 4)` Déscartes koordinátarendszerbeli pontnak olyan homogén koordinátarendszerbeli felírását, melyben a koordináták összege pontosan 60 értékre adódik!

* Írja fel annak a síkbeli transzformációnak a transzformációs mátrixát, amelyik a tér pontjait a :math:`(10, 20)` középponttal háromszorosára skálázza!

* Írja fel homogén koordinátákkal a :math:`(10, 4)` és a :math:`(3, -8)` pontokon áthaladó egyenest!

* Számítsa ki a :math:`(8, -3, -2)` és a :math:`(2, -5, 4)` vektorokkal megadott homogén koordinátarendszerbeli egyenesek metszéspontját!

* Tegyük fel, hogy a sík pontait az :math:`(5, 9)` vektorral eltoljuk, majd az origó körül 30 fokkal elforgatjuk. Írja fel az ehhez tartozó transzformáció mátrixszát! Határozza meg az inverz transzformáció mátrixszát is!


Programozási feladatok
----------------------

.. note::

  A ``circle`` példához hasonlóan készítendő el.

Téglatestek
~~~~~~~~~~~

* Készítsünk egy programot, amellyel téglatestek adatait lehet kezelni!
* Definiáljunk egy struktúrát (például ``Cuboid`` vagy ``Brick`` néven), amely tartalmazza a téglatest 3 élének a hosszát!
* Definiáljunk egy függvényt, amellyel ellenőrzött módon be lehet állítani egyszerre a 3 él hosszát (például ``set_size`` néven)!
* Definiáljunk egy függvényt, amelyik kiszámítja a téglatest térfogatát (például ``calc_volume``), és egy másikat amelyik a felszínét (például ``calc_surface``)!
* Definiáljunk egy függvényt, amelyik a téglalapot megvizsgálja, hogy van-e négyzet alakú lapja!

