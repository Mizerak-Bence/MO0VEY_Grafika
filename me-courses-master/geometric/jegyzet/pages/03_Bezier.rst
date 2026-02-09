************
Bezier görbe
************

A de Casteljau-algoritmus
=========================

A de Casteljau-algoritmus elemi lépésének vizsgálatához tekintsük a :math:`\textbf{b}_0`, :math:`\textbf{b}_1` és :math:`\textbf{b}_2` pontokat! Válasszunk egy tetszőleges :math:`t \in [0, 1]` valós értéket!

* Osszuk fel a :math:`\textbf{b}_0` és :math:`\textbf{b}_1` pontok közötti szakaszt :math:`t : (1 - t)` arányban! Jelöljük az így kapott pontot :math:`\textbf{b}_0^1(t)` formában!
* Hasonlóképpen osszuk fel a :math:`\textbf{b}_1` és :math:`\textbf{b}_2` pontok közötti szakaszt! Jelöljük ezt :math:`\textbf{b}_1^1(t)`-vel!
* Osszuk fel a :math:`\textbf{b}_0^1(t)` és :math:`\textbf{b}_1^1(t)` közötti szakaszt, és jelöljük :math:`\textbf{b}_0^2(t)`-vel!

Ezzel az eljárással egy görbét tudunk leírni, melyhez a segédpontokat a

.. math::

  \begin{align}
  \textbf{b}_0^1(t) &= (1 - t) \textbf{b}_0 + t \textbf{b}_1, \\
  \textbf{b}_1^1(t) &= (1 - t) \textbf{b}_1 + t \textbf{b}_2 \\
  \end{align}

formában számíthatjuk ki, magának a görbének a pontjait pedig a

.. math::

  \textbf{b}_0^2(t) = (1 - t)\textbf{b}_0^1(t) + t \textbf{b}_1^1(t)

alakban, vagy közvetlenül az eredeti pontokból a

.. math::

  \textbf{b}_0^2(t) = (1 - t)^2 \textbf{b}_0 + 2t (1 - t)\textbf{b}_1 + t^2 \textbf{b}_2

formában.

.. todo:: Érdemes egy ábrát készíteni hozzá!

:math:`\rhd` Vizsgáljuk meg, hogy milyen pontokat kapunk, hogy ha a :math:`t` a :math:`[0, 1]` intervallumon kívülre esik!

Vegyük észre, hogy az előbbiekben bemutatott felosztási módszert

* tetszőleges számú pontra,
* tetszőleges dimenziós térben

tudjuk alkalmazni! Ez a rekurzív eljárást nevezzük de Casteljau algoritmusnak.

:math:`\rhd` Ábrázoljuk a görbe egy pontjának a meghatározását 4 pont esetén (egy szabadon választott :math:`t` paraméterrel)!

:math:`\rhd` Ábrázoljuk a pontok származtatási (számítási) viszonyait az előző esethez!

.. note::

  * Paul de Faget de Casteljau, Citroën
  * https://en.wikipedia.org/wiki/Paul_de_Casteljau


A Bernstein polinom
===================

Az :math:`i`-edik :math:`n`-edfokú Bernstein polinomot az alábbi formában definiáljuk:

.. math::

  B_i^n(t) = \binom{n}{i} t^i (1 - t)^{n - i}, \quad i = 0, 1, \ldots, n.

Definíció szerint továbbá

.. math::

  B_0^0(t) = 1, \quad B_i^n(t) = 0, \text{ha } i \notin [0, n].

:math:`\rhd` Ábrázoljuk az :math:`n`-edfokú Bernstein polinomokat (a :math:`t \in [0, 1]` intervallum felett)!

A Bernstein polinom tulajdonságai:

* :math:`B_i^n(t) \geq 0`, ha :math:`t \in [0, 1]`,
* :math:`B_i^n(t) = (1 - t)B_i^{n-1}(t) + t B_{i-1}^{n-1}(t), \forall t \in [0, 1]` (rekurzív tulajdonság),
* egységfelbontást alkotnak/normalizáltak:

.. math::

  \sum_{i=0}^n B_i^n(t) = (t + (1 - t))^n = 1, \quad \forall t \in [0, 1],

* a deriváltjaik alacsonyabb fokú Bernstein polinomokkal felírhatók:

.. math::

  \left( B_i^n(t) \right)' = n(B_{i-1}^{n-1}(t) - B_{i}^{n-1}(t)),

* :math:`\text{argmax}_t B_i^n(t) = \dfrac{i}{n}, \forall i \in [0, n]`.

.. note::

  * https://en.wikipedia.org/wiki/Bernstein_polynomial
  * https://www.youtube.com/watch?v=AL0vcsLlYp4


A Bézier görbe paraméteres alakja
=================================

A de Casteljau algoritmus a Bézier görbe pontjait eredményezi. Ennek paraméteres alakja a Bernstein polinomok segítségével felírva:

.. math::

  \textbf{b}(t) = \sum_{i=0}^n \textbf{b}_i B_i^n(t), \quad t \in [0, 1].

A görbe számításához használt pontokat kontrollpontoknak vagy Bézier-pontoknak hívjuk.

.. note::

  * Pierre Étienne Bézier, Renault
  * https://en.wikipedia.org/wiki/Pierre_B%C3%A9zier
  * https://www.youtube.com/watch?v=2HvH9cmHbG4
  * https://www.youtube.com/watch?v=A8CM297pq2Y


Kapcsolat a de Casteljau algoritmussal
======================================

A de Casteljau algoritmusnál használt pontokat Bernstein polinomokkal a következőképpen írhatjuk föl:

.. math::

  \textbf{b}_i^r(t) =
  \sum_{j=0}^r \textbf{b}_{j+i} B_j^r(t),

ahol

.. math::

  r \in [0, n], i \in [0, n - r], \forall t \in [0, 1].


A Bézier görbe tulajdonságai
============================

Zárt az affin transzformációkra.

* A kontrollpontok transzformációjával kapott görbe megegyezik a pontonként transzformált görbével.
* Ez praktikusan azt jelenti, hogy a görbe transzformálásához elegendő a kontrollpontokat transzformálni, majd abból kiszámítani a görbe pontjait.
* A tulajdonság az arányos osztások következménye.

:math:`\rhd` Hogyan definiálhatjuk a konvexitást?

:math:`\rhd` Mit nevezünk konvex buroknak?

A Bézier görbe pontjai mindig a kontrollpontjainak a konvex burkában van.

* Az állítás a de Casteljau algoritmus következménye.
* Ez egyúttal garancia arra vonatkozóan is, hogy így a görbe nem fog hirtelen kiugrásokat tartalmazni (mint amilyenek a Lagrange interpolációnál előfordulhatnak).

A Bézier-görbe a paramétertartomány affin transzformációjára nézve invariáns.

* Használhatunk tetszőleges :math:`t = (u - a) / (b - a), u \in [a, b]` paraméterezést. A görbe alakja nem fog változni.
* A pontok ugyan nem változnak meg, az érintővektorok (és így a bejárás sebessége) viszont igen.
* Szintén a de Casteljau algoritmus következménye.

A Bézier görbe az első és az utolsó kontrollpontján áthalad (azokban interpolál).

A kontrollpontok bejárási sorrendjét megfordítva is ugyanazt a görbét kapjuk.

Globálisan változtatható. Minden kontrollpont hatással van a teljes görbe alakjára.

* Mivel a :math:`t = i / n` paraméternél a :math:`B_i^n` polinom van a legnagyobb hatással a görbére, ezért lehet következtetni az alakváltozásra. Emiatt pszeudó-lokálisan változtatható görbének is szokták nevezni.

A görbe csak akkor lesz egyenes, hogy ha a kontrollpontok egy egyenesre esnek (más szóval kollineárisak).


A görbe deriváltja
==================

A Bézier görbe deriváltjára vonatkozó felírási módok például az alábbiak.

.. math::

  \begin{align}
  \dot{\textbf{b}}(t)
  &= n \sum_{i=0}^n \textbf{b}_i (B_{i-1}^{n-1}(t) - B_i^{n-1}(t)) \\
  &= n \sum_{i=1}^n \textbf{b}_i B_{i-1}^{n-1}(t) - n \sum_{i=0}^{n-1} \textbf{b}_i B_i^{n-1}(t)) \\
  &= n \sum_{i=0}^{n-1} \textbf{b}_{i+1} B_i^{n-1}(t) - n \sum_{i=0}^{n-1} \textbf{b}_i B_i^{n-1}(t) \\
  &= n \sum_{i=0}^{n-1}(\textbf{b}_{i+1} - \textbf{b}_i) B_i^{n-1}(t)
  \end{align}

tetszőleges :math:`\forall t \in [0, 1]` esetén.

Hodográf
--------

Láthatjuk, hogy a Bézier görbe deriváltja (*hodográfja*) egy :math:`(n-1)`-edfokú Bézier-görbe.

* Az eredeti kontrollpontokból képezzük a :math:`\Delta \textbf{b}_i = \textbf{b}_{i+1} - \textbf{b}_i` vektorokat!
* Vegyük ezek :math:`n`-szeresét!
* Toljuk ezeket az origóba!
* A derivált az így kapott (:math:`n` számú kontrollponthoz tartozó :math:`(n-1)`-edfokú) Bézier görbe lesz.

A hodográf segítségével vizsgálhatjuk a görbe tulajdonságait.

* Hogy ha a hodográf átmegy az origón, akkor van olyan (elfajuló) pontja az eredeti görbének, amelynél az érintő nullvkektor.
* Hogy ha a hodográfnak van az origón átmenő érintője amely inflexiós pontja, akkor az eredeti görbének van nulla görbületű pontja.
* Hogy ha a hodográfnak van az origón átmenő érintője (amely nem szinguláris pont), akkor az eredeti görbének van inflexiós pontja.

Kapcsolat a de Casteljau algoritmussal
--------------------------------------

Vezessünk be a csúcspontok különbségére vonatkozóan egy külön jelölést!

.. math::

  \begin{align}
  &\Delta^0 \textbf{b}_i = \textbf{b}_i, \\
  &\Delta^1 \textbf{b}_i = \textbf{b}_{i+1} - \textbf{b}_i, \\
  &\Delta^2 \textbf{b}_i = \textbf{b}_{i+2} - 2 \textbf{b}_{i+1} + \textbf{b}_i, \\
  &\ldots \\
  &\Delta^r \textbf{b}_i = \sum_{k=0}^r \binom{r}{k} (-1)^{r-k} \textbf{b}_{i+k}.
  \end{align}

A de Casteljau algoritmusnál használt :math:`\textbf{b}_i^k` pontok segítségével a Bézier-görbe :math:`r`-edik deriváltja felírható, mint

.. math::

  \dfrac{\mathrm{d}^r}{\mathrm{d}t^r} \textbf{b}(t) =
  \dfrac{\mathrm{d}^r}{\mathrm{d}t^r} \textbf{b}_0^n(t) =
  \dfrac{n!}{(n-r)!} \Delta^r \textbf{b}_0^{n-r}(t), \quad
  \forall t \in [0, 1].

Ez alapján láthatjuk, hogy

* :math:`\textbf{b}_0^n` a görbének a pontja,
* :math:`(\textbf{b}_0^{n-1}, \textbf{b}_1^{n-1})` az értintőt határozza meg,
* :math:`(\textbf{b}_0^{n-2}, \textbf{b}_1^{n-2}, \textbf{b}_2^{n-2})` a simulósíkot határozza meg.


A görbe kettévágása
===================

Tekintsünk egy :math:`n`-edfokú Bézier-görbét: :math:`\textbf{b}^n(t), t \in [0, 1]`! Válasszunk egy tetszőleges :math:`c \in (0, 1)` értéket! A megoldandó probléma, hogy hogyan találhatunk olyan :math:`n`-edfokú, :math:`t \in [0, 1]` intervallumon értelmezett Bézier-görbét, amely :math:`\textbf{b}^n(t), t \in [0, c]` ívvel egyezik meg.

Jelöljük a keresett görbét :math:`\textbf{c}^n(u)` alakban! A paramétere legyen :math:`u = t / c` formában adott. Azon kontrollpontokat szeretnénk meghatározni, amelyekre teljesül majd, hogy

.. math::

  \textbf{b}^n(t) = \textbf{c}^n(u(t)) = \textbf{c}^n \left( \dfrac{t}{c} \right),
  \forall t \in [0, c].

A megoldást a de Casteljau algoritmus segítségével kaphatjuk meg. Szimmetria okok miatt egyidejűleg a kettévágással kapott mindkét görbét közel azonos módon határozhatjuk meg.

Jelöljük a de Casteljau algoritmusban szereplő közbülső pontokat általánosan :math:`\textbf{b}_i^j` formában (ahol :math:`(i + j) \in [0, n]`).

A :math:`[0, c]` intervallumhoz tartozó görbe kontrollpontjai:

.. math::

  \textbf{b}_0^0, \textbf{b}_0^1(c), \textbf{b}_0^2(c), \ldots, \textbf{b}_0^{n-1}(c), \textbf{b}_0^n(c),

vagy röviden :math:`\textbf{c}_i = \textbf{b}_0^i(c)`.

A :math:`[c, 1]` intervallumhoz tartozó görbe kontrollpontjai:

.. math::

  \textbf{b}_n^0, \textbf{b}_{n-1}^1(c), \textbf{b}_{n-2}^2(c), \ldots, \textbf{b}_1^{n-1}(c), \textbf{b}_0^n(c),

vagy röviden :math:`\textbf{c}_i = \textbf{b}_{n-i}^i(c)`.

:math:`\rhd` Ábrázoljuk egy negyedfokú görbén az összefüggést!

.. note::

  Mivel a kettévágás során számított kontrollpontok az eredeti görbe kontrollpontjainak a konvex burkában vannak, ezért

  * a két új görbe konvex burka az eredeti konvex burok valódi része lesz, és
  * az eljárás egyúttal mutatja a Bézier-görbe hullámzáscsökkentő tulajdonságát.


Hullámzáscsökkentés
===================

A Bézier görbét egy sík legfeljebb annyi pontban metszi, mint a kontrollpoligonját.

.. note::

  Az egyenest az állításban, mint a sík egy alacsonyabb dimenziós esetét tekintjük.

Az állítás a de Casteljau algoritmussal bizonyítható, mivel a kontrollpoligon tulajdonképpen a görbéhez konvergál, így nem jelenhet meg új metszéspont.


Bézier-spline
=============

A polinomok fokszámának alacsonyan tartása, és a lokális vezérelhetőség a Bézier-görbék használata kapcsán is fontos szempont lehet. A problémát ez esetben is az alacsonyabb fokszámú polinomos görbék egymáshoz illesztésével oldhatjuk meg.

A Bézier-spline-ok használatához az azokat felépítő Bézier-görbék kapcsolódási módjait kell megvizsgálnunk. Az egyszerűség kedvéért tekintsünk csak két görbét:

* :math:`\textbf{a}(u), u \in [u_0, u_1]`, és
* :math:`\textbf{b}(u), u \in [u_1, u_2]`.

Ezek kontrollpontjai rendre :math:`\{\textbf{a}_i\}_{i=0}^n` és :math:`\{\textbf{b}_i\}_{i=0}^n`.

A kapcsolódás mértékének a leírásához egyaránt használjuk a :math:`C^k` és :math:`G^k` jelöléseket, ahol :math:`k \in \mathbb{N}_0`.

* :math:`C^k` esetében azt várjuk el, hogy a :math:`k`-adik deriváltak teljes mértékben megegyezzenek.
* :math:`G^k` esetében elegendő, hogy ha a :math:`k`-adik deriváltak iránya megegyezik.

:math:`C^1` kapcsolódás esetében például az érintővektoroknak meg kell egyezniük, míg :math:`G^1` kapcsolódás esetében elegendő, hogy ha az érintőegyenesek megegyeznek.

Nulladrendű kapcsolódás
-----------------------

:math:`C^0` kapcsolódás esetén annyit szeretnénk csak elérni, hogy az

.. math::

  \textbf{a}(u_1) = \textbf{b}(u_1)

teljesüljön. Ehhez elegendő, hogy :math:`\textbf{a}_n = \textbf{b}_0` teljesüljön.

Elsőrendben folytonos kapcsolódás
---------------------------------

A :math:`G^1` kapcsolódáshoz az

.. math::

  \textbf{a}_{n-1}, \textbf{a}_n = \textbf{b}_0, \textbf{b}_1

kontrollpontoknak egy egyenesre kell esniük.

A :math:`C^1` kapcsolódáshoz a kollinearitáson kívül még teljesülnie kell az alábbi aránynak:

.. math::

  \lVert \textbf{a}_n - \textbf{a}_{n-1} \rVert : \lVert \textbf{b}_1 - \textbf{b}_0 \rVert =
  (u_1 - u_0) : (u_2 - u_1).

Másodrendben folytonos kapcsolódás
----------------------------------

A :math:`G^2` kapcsolódáshoz az

.. math::

  \textbf{a}_{n-2}, \textbf{a}_{n-1}, \textbf{a}_n = \textbf{b}_0, \textbf{b}_1, \textbf{b}_2

kontrollpontoknak egy síkba kell esniük. (Ez a sík a kapcsolódási pontbeli simulósík.)

A :math:`C^1` kapcsolódáshoz nézzük meg, hogy milyen pontban metszik egymást a :math:`\textbf{a}_{n-2}\textbf{a}_{n-1}` és a :math:`\textbf{b}_{1}\textbf{b}_{2}` szakaszokhoz tartozó egyenesek! Jelöljük ezt :math:`\textbf{m}`-mel!

Ezekre teljesülnie kell, hogy

.. math::

  \dfrac{\lVert \textbf{m} - \textbf{a}_{n-1} \rVert}{\lVert \textbf{a}_{n-1} - \textbf{a}_{n-2} \rVert} =
  \dfrac{u_2 - u_1}{u_1 - u_0}, \quad
  \dfrac{\lVert \textbf{m} - \textbf{b}_{1} \rVert}{\lVert \textbf{b}_{1} - \textbf{b}_{2} \rVert} =
  \dfrac{u_1 - u_0}{u_2 - u_1}.

.. note::

  A kapcsolódás folytonosságának a vizsgálata természetesen magasabb rendű esetekre is vizsgálható.


Fokszámnövelés
==============

Praktikus lehet, hogy ha egy :math:`n`-edfokú Bézier-görbéhez meg tudjuk határozni azt az :math:`(n+1)`-edfokú Bézier-görbét, amely ugyanazt a görbét írja le.

Tekintsünk egy :math:`\textbf{b}_0, \textbf{b}_1, \textbf{b}_2, \ldots, \textbf{b}_n` kontrollpontokkal adott Bézier-görbét! Keressük azon :math:`\textbf{b}_0^1, \textbf{b}_1^1, \textbf{b}_2^1, \ldots, \textbf{b}_{n+1}^1` kontrollpontokat, amelyekre teljesül, hogy

.. math::

  \sum_{i=0}^n \textbf{b}_i B_i^n(t) =
  \sum_{i=0}^{n+1} \textbf{b}_i^1 B_i^{n+1}(t), \quad \forall t \in [0, 1].

Ezt megoldva azt kapjuk, hogy

.. math::

  \textbf{b}_i^1 =
  \left( \dfrac{i}{n + 1} \right) \textbf{b}_{i-1} +
  \left(1 - \dfrac{i}{n + 1} \right) \textbf{b}_{i}.

Ez megadható a

.. math::

  \textbf{b}_i^1 =
  \textbf{b}_{i} +
  \dfrac{i}{n + 1} (\textbf{b}_{i-1} - \textbf{b}_{i})

alakban is.

Szemléletesen tehát azt vesszük észre, hogy a fokszámnövelés során az új kontrollpoligont az eredeti kontrollpoligon sarkainak a levágásával kapjuk.

* Hogy ha a fokszámnövelést tetszőleges sokszor alkalmazzuk, akkor a kontrollpoligonunk a Bézier görbéhez fog tartani.
* Fokszámot csökkenteni általában nem tudunk (legfeljebb közelíti, alacsonyabb fokszámú görbét megadni).


Töröttvonalas közelítés
=======================

A töröttvonalas közelítésre megjelenítés vagy az ívhossz számítása érdekében lehet például szükségünk.

Használhatunk például egyenközű felosztást a

.. math::

  t_i = a + i \dfrac{b - a}{n}

választással. A pontosabb közelítés és a hatékonyság érdekében érdemes azonban a görbületet is figyelembe vennünk. Ehhez használhatjuk például a következő algoritmust.

* Keressük meg a :math:`\textbf{b}_0` és a :math:`\textbf{b}_n` pontokon átmenő egyenestől a legtávolabb eső kontrollpontot. Ennek az indexét jelöljük :math:`j`-vel, a távolságát pedig :math:`m_j`-vel!
* Hogy ha :math:`m_j \leq \varepsilon` teljesül, akkor kész vagyunk. A görbe a :math:`\textbf{b}_0` és :math:`\textbf{b}_n` pontokat összekötő szakasszal helyettesíthető.
* Hogy ha nem teljesül, akkor osszuk fel a görbét a :math:`t = j / n` paraméternél! Rekurzívan folytassuk a kirajzolást az így kapott két görbére!

.. note::

  Zárt görbék esetében a görbét kettévágva (:math:`t = 0.5` paraméternél) már tudjuk alkalmazni az algoritmust.


Interpoláció
============

Megtehetjük, hogy úgy keressük egy Bézier-görbének a kontrollpontjait, hogy a kapott görbe bizonyos pontokon áthaladjon. Így tehát interpolációs problémák megoldására is használható közvetve az eredendően approximációs görbe.

Tekintsük az interpolációs alapfeladatot a :math:`\textbf{p}_0, \textbf{p}_1, \textbf{p}_2, \ldots, \textbf{p}_n` interpolációs pontokkal, és :math:`0 \leq u_0 < u_1 < \cdots < u_n \leq 1` paraméter értékekkel!

Keressük azokat a :math:`{\textbf{b}_i}_{i=0}^n` kontrollpontokat, amelyekre teljesül, hogy

.. math::

  \textbf{b}(u_i) = \textbf{p}_i, \quad i \in [0, n].

A Bernstein polinomos alakot felhasználva ebből adódik, hogy

.. math::

  \textbf{b}(u_i) = \sum_{j=0}^n B_j^n(u_i) \textbf{b}_j = \textbf{p}_i, \quad i \in [0, n].

Ezt mátrixos alakra hozva a következő (inhomogén lineáris) egyenletrendszert kapjuk:

.. math::

  \begin{bmatrix}
  B_0^n(u_0) & B_1^n(u_0) & \cdots & B_n^n(u_0) \\
  B_0^n(u_1) & B_1^n(u_1) & \cdots & B_n^n(u_1) \\
  B_0^n(u_2) & B_1^n(u_2) & \cdots & B_n^n(u_2) \\
  \vdots & \vdots & \ddots & \vdots \\
  B_0^n(u_n) & B_1^n(u_n) & \cdots & B_n^n(u_n) \\
  \end{bmatrix}
  \cdot
  \begin{bmatrix}
  \textbf{b}_0 \\
  \textbf{b}_1 \\
  \textbf{b}_2 \\
  \vdots \\
  \textbf{b}_n \\
  \end{bmatrix}
  =
  \begin{bmatrix}
  \textbf{p}_0 \\
  \textbf{p}_1 \\
  \textbf{p}_2 \\
  \vdots \\
  \textbf{p}_n \\
  \end{bmatrix}.

Feltételezve, hogy az :math:`u_i` értékek különbözőek, az egyenletrendszereket (koordinátánként megoldva) mindig lesz egyértelmű megoldásunk.


Kérdések, elméleti feladatok
============================

* Mi az a de Casteljau algoritmus? (Mutassa be ábrával, számításokkal szemléltetve!)
* Definiálja az :math:`n`-edfokú Bernstein polinomot! Milyen tulajdonságai vannak?
* Hogyan írható fel a Bézier görbe paraméteres alakja a Bernstein polinom segítségével?
* Milyen kapcsolat van a de Casteljau algoritmus és a Bernstein polinomok között?
* Ismertesse a Bézier görbe tulajdonságait!
* Mit nevezünk hodográfnak? Hogyan írható ez fel a Bézier görbe esetében?
* Milyen kapcsolat van a Bézier görbe deriváltja és a de Casteljau algoritmus között?
* Hogyan tudunk egy Bézier görbét a :math:`c \in \mathbb{R}` paraméterénél kettévágni?
* Hogyan tudunk Bézier görbékből Bézeier-spline-t készíteni? Milyen módon garantálhatóak a nullad-, első- és másodrendű folytonosságok?
* Hogyan tudjuk egy Bézier görbének növelni a fokszámát?
* Hogyan érdemes a Bézier görbére töröttvonalas közelítést adni? (Mutassa be az erre vonatkozó algoritmust!)
* Hogyan tudjuk Bézier görbe segítségével megoldani az interpolációs problémát!


Számítási feladatok
===================

.. note::

  A számításokat 4 tizedesjegy pontossággal végezze!

Tegyük fel, hogy adottak a :math:`\textbf{p}_0 = (0, 0), \textbf{p}_1 = (2, 5), \textbf{p}_2 = (4, 3), \textbf{p}_3 = (5, -1)` kontrollpontok.

* Számítsa ki a Bézier-görbe pontját a :math:`t = 0.4` paraméterértéknél de Casteljau algoritmus segítségével!
* Határozza meg a Bézier-görbe pontját a :math:`t = 0.2` paraméternél a Bernstein polinomos paraméteres alak segítségével!
* Határozza meg a görbe érintőjét a :math:`t = 0.3` paraméternél!
* Írja fel a görbe érintőjének egyenletét és a ponthoz tartozó normálvektort a :math:`t = 0.4` pontban!
* Vágjuk ketté a görbét a :math:`t = 0.25` paraméternél! Határozzuk meg mindkét kapott görbének a kontrollpontjait!
* Számítsuk ki annak az 5-ödfokú görbének a kontrollpontjait, amely ugyanezt a görbét állítja elő!


Programozási feladatok
======================

A de Casteljau algoritmus
-------------------------

* Implementáljuk a de Casteljau algoritmust!
* Rajzoljuk be egy adott pont számítása esetén a segédvonalakat!
* Oldjuk meg, hogy a kijelölt ponthoz tartozó :math:`t` paramétert lehessen módosítani (például csúszkával vagy görgővel)!

Binomiális együtthatók számítása
--------------------------------

* Ábrázoljuk az :math:`n`-edfokú Bernstein polinomokat! (Rögzített :math:`n` esetén, vagy oldjuk meg, hogy a programban megadható legyen tetszőleges :math:`n` érték!)
* Vizsgáljuk meg a binomiális együttható faktoriálisokkal és rekurzív formulával történő számítási módját!
* Utóbbinál vizsgáljuk meg a gyorsítótárazás hatását!
* Készítsünk méréseket és ábrázoljuk a kapott eredményeket!

Görbe kettévágása
-----------------

* Készítsünk egy alkalmazást a görbe kettévágásának szemléltetésére!
* Színekkel különítsük el a kettévágással kapott görbék kontrollpontjait!
* Oldjuk meg, hogy a kettévágáshoz használt paramétert lehessen megadni/módosítani!

Fokszám növelése
----------------

Implementáljunk egy algoritmust, amellyel interaktív módon (a görbe kontrollpontjainak módosíthatóságát megtartva) tudjuk egy Bézier görbének növelni a fokszámát! 

Görbe megjelenítése
-------------------

Implementáljuk a Bézier-görbe megjelenítéséhez azt az algoritmust, amelyik igyekszik minimalizálni a szükséges szakaszok számát a töröttvonalas megjelenítésnél!

Bézier interpoláció
-------------------

Implementáljunk egy alkalmazást, amely :math:`(n+1)` pontra megoldja a Bézier interpolációs problémát!
Hasonlítsuk össze a Lagrange és a Bézier interpolációs görbéket azonos kontroll pontok esetében! 


További feladatok
=================

* Vizsgáljuk meg, hogy egy Bézier görbékkel határolt síkidomnak hogyan tudjuk kiszámítani/közelíteni a területét!
* Vizsgáljuk meg, hogy milyen lehetőségek vannak az Bézier approximáció és interpoláció egyidejű használatára vonatkozóan!
* Tegyük fel, hogy tetszőleges sok pontra szeretnénk egy :math:`n`-edrendű Bézier görbét illeszteni! Vizsgáljuk meg a szóbajöhető approximációs, optimalizálási módszereket!
* Hasonlítsa össze a konvergencia sebességét a Bézier görbe kettévágása és a fokszámnövelés viszonylatában!
* Implementáljunk egy alkalmazást, amely egy zárt Bézier görbén belül pattogó pontot jelenít meg!
* Hogyan tudunk kontrollpontokon áthaladó (interpoláló) :math:`G^1` folytonos görbét megadni úgy, hogy az csak egyenes szakaszokból és körívekből áll, ismerjük ezek arányát, és minimális a görbe hossza?

