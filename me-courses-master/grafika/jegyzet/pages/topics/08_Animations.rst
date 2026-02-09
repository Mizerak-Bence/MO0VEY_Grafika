Animációk
=========

Az animáció nagyvonalakban annyit jelent, hogy bizonyos értékeket az idő függvényében változtatunk.

* Jelölje :math:`t \in \mathbb{R}` az időt!
* Változtathatjuk a modellek helyzetét, színét, a textúraleképzést például.

:math:`\rhd` Soroljuk fel, hogy például mi az amit még tudunk animálni!

Függvény megadása
-----------------

Jelölje :math:`\textbf{x}(t)` az idő függvényében változtatott értéket a :math:`t` időpillanatban. Hogy ha ezt formula formájában fel tudjuk írni, azzal gyakorlatilag meg is oldottuk az animálás problémáját.

.. admonition:: Példa

    Tegyük fel, hogy egy pontot szeretnénk fel-le mozgatni folyamatosan a :math:`z \in [5, 10]` intervallumon úgy, hogy 2 másodperc alatt tegyen meg egy teljes periódust. Ezt például színusz függvénnyel oldhatjuk meg:

    .. math::

        z(t) = 2.5 \cdot \sin\left(\dfrac{t}{2} \cdot 2\pi\right) + 7.5.

.. admonition:: Példa

    Jelenítsünk meg egy modellt, és animáljuk az anyagjellemző szórt fény összetevőjét! Ehhez az egyes színkomponensekhez használjuk az alábbi összefüggést!

    .. math::

        c(t) = \dfrac{\sin(\alpha + \beta t) + 1}{2}.

    Az egyes színkomponensekhez használjunk különféle :math:`\alpha` és :math:`\beta` paramétereket (így összesen 6 paramétert)!

    * Vizsgáljuk meg a különféle paraméterek hatását!
    * Ábrázoljuk a 3 függvényt!

Kulcsképkocka animáció
----------------------

Az animáció készítésének egy további módja, hogy ha bizonyos időpontokban ismerjük az animált értéket.

:math:`\rhd` Soroljuk fel, hogy milyen esetekben tudunk kulcsképkocka animációt használni?

Lineáris interpoláció
---------------------

A közbülső időpontokhoz tartozó értékeket a szomszédos időpontok értékei alapján lineáris interpolációval is meghatározhatjuk.

.. note::

    Nem szükségszerű, hogy csak a szomszédosakat vegyük figyelembe. Általánosan bármilyen interpolációs vagy approximációs módszert is használhatnánk.

Tegyük fel, hogy a :math:`t \in [t_i, t_{i+1}]` időpontban lévő értéket szeretnénk meghatározni.

* Megtehetjük, hogy ekkor :math:`\textbf{x}(t) = \textbf{x}(t_i)` értékkel számolunk. Ez viszont nem fog folytonos mozgást eredményezni (legfeljebb akkor, hogy ha nagyon nagy felbontással vettük fel az ismert pontokat).
* Lineáris interpolációt használva az alábbi képlettel számolhatunk:

.. math::

    \textbf{x}(t) = \textbf{x}(t_i) + \dfrac{t - t_i}{t_{i+1} - t_i} \cdot (\textbf{x}(t_{i+1}) - \textbf{x}(t_i)).

.. note::

    A lineáris interpolációval mozgatott pont mozgása ugyan folytonos, de szögletes lehet. Ezen különféle paraméteres görbék, magasabb rendű interpolációs módszerek használatával lehet segíteni.

Fizikai animáció
----------------

.. warning::

    A következőkben javaslatok szerepelnek a fizikai jelenségek modellezéséhez.
    Az alkalmazott számítási módok egyszerűsítések, helyenként heurisztikák.
    Nem szükségszerűen tükrözik a valós fizikai jelenségeket.

A következőkben a :math:`t` érték a keretidőt, vagyis a képkockák kirajzolása között (pontosabban az előző *update* óta) eltelt időt adja meg másodpercben.

Egyenes vonalú egyenletes mozgás
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Tegyük fel, hogy ismerjük a pontunk koordinátáit a :math:`t = 0` időpillanatban, továbbá tudjuk a sebességét. Feltételezzük továbbá, hogy egyenes vonalú, egyenletes mozgást végez. Ekkor a :math:`t` időpillanatban a pont a következőképpen számolható:

.. math::

    \textbf{x}(t) = \textbf{x}(0) + \textbf{v} \cdot t.

:math:`\rhd` Tekintsük át a `pong` példa ide vonatkozó részét!

Forgatás
~~~~~~~~

Az egyenes vonalú egyenletes mozgáshoz hasonlóan kezelhető a forgatás. Ekkor a sebesség szögsebesség lesz, és a pozíció helyett az elforgatás szögével számolhatunk.

Jelölje :math:`\varphi(t)` az elforgatás szögét az idő függvényében, :math:`\textbf{r}` pedig a forgatás sebességét. Tegyük fel, hogy ismerjük a szöget a :math:`t = 0` időpillanatban. Ezek alapján a számítás:

.. math::

    \varphi(t) = \varphi(0) + \textbf{r} \cdot t.

Szabadesés
~~~~~~~~~~

Feltételezzük, hogy a pontunkra gravitációs erő hat, és így szabadon esik. Jelölje a gravitációs erőt a :math:`\textbf{g}` vektor. A pont aktuális sebességét jelölje :math:`\textbf{v}`.

A gyorsulást jelölje :math:`\textbf{a}`. Ennek mértékegysége :math:`\dfrac{m}{s^2}`, tehát azt mutatja meg, hogy egy másodperc alatt mennyit változik a sebesség.

Egyszerűen úgy tudjuk figyelembe venni, hogy ha a pont sebességét ennek függvényében változtatjuk:

.. math::

    \textbf{v}^{(i+1)} = \textbf{v}^{(i)} + \textbf{a} \cdot t.

A gyorsulást a testre ható erőből kaphatjuk. Ezt jelölje :math:`\textbf{F}` (*force*). Ennek mértékegysége :math:`kg \cdot \dfrac{m}{s^2}`. A következőképpen számíthatjuk:

.. math::

    \textbf{a} = \dfrac{\textbf{F}}{m},

ahol az :math:`m` a test tömegét jelöli (*mass*). A testre ható erők eredőjét azok összegéből kaphatjuk meg. (Hogy ha a testre csak a gravitációs erő hat, és a test tömegét egységnyinek tekintjük, akkor :math:`\textbf{a} = \textbf{g}`.)

Ütközés, pattanás, visszaverődés
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

Feltételezzük, hogy a pontunk egy adott síkon nem tud keresztül menni, arról visszapattan. Tegyük fel, hogy ez a sík a :math:`z = 0` sík. Tegyük fel továbbá, hogy a pont aktuális pozíciója és a :math:`t` időponttal későbbi pozíciója közötti szakasz metszi ezt a síkot. A metszéspontot jelölje :math:`\textbf{x}_c`, a mozgó pont aktuális időpontjához tartozó erőt pedig :math:`\textbf{F}_c`.

* Ideális visszaverődést feltételezve az ütközés pillanatához tartozó erőt úgy kapjuk, hogy ha az :math:`\textbf{F}_c` erő :math:`z` komponensét negáljuk.
* Hogy ha nem ideális visszaverődéssel szeretnénk számolni, akkor az erőt valamilyen :math:`[0, 1)` közötti értékkel szorozhatjuk.
* A pont helyzetét a :math:`\textbf{x}_c` pozícióra kellene állítani. Ez problémát jelenthet, hogy ha az újabb ütközésvizsgálatkor a pont "beleragad" a felületbe. Ezen úgy segíthetünk, hogy ha a pontot egy kis értékkel arrébb toljuk a felülettől (például a felületi normális mentén).

Surlódás, fékezés
~~~~~~~~~~~~~~~~~

Modellezni szeretnénk, ahogy egy test sebessége a surlódás következtében folyamatosan csökken.
Feltételezzük a következőket.

* A számításokat :math:`t = 0` időpillanattól kezdjük.
* A test sebessége az idő függvénye, kezdetben :math:`v(0) = v_0`.
* A sebesség csökkenését az eltelt idővel tekintjük arányosnak. (*Lehetne a sebességgel is.*)
* A test sebessége egységnyi idő alatt mindig konstansszorosára változik. Jelöljük ezt :math:`\lambda`-val (:math:`\lambda \in [0, 1]`)!

Ezek alapján a test aktuális sebességét a következőképpen számíthatjuk ki:

.. math::

    v(t) = v_0 \cdot \lambda^t.

Számítsuk ki a :math:`t` időpillanatig megtett út hosszát! Ehhez az alábbi határozott integrál kiszámítására van szükség:

.. math::

    \int_{0}^{t} \! v(x) \cdot x \, \mathrm{d}x =
    \int_{0}^{t} \! v_0 \cdot \lambda^x \cdot x \, \mathrm{d}x =
    v_0 \cdot \left[ \dfrac{1}{\text{ln}\lambda} \cdot x \cdot \lambda^x - \dfrac{1}{\text{ln}^2 \lambda} \cdot \lambda^x\right]_{0}^{t}.

Behelyettesítve azt kapjuk, hogy

.. math::

    s(t) = v_0 \cdot \left(
    \dfrac{\lambda^t}{\text{ln}\lambda} \cdot t -
    \dfrac{\lambda^t}{\text{ln}^2 \lambda} +
    \dfrac{1}{\text{ln}^2 \lambda}
    \right).

A programban a keretidő (:math:`\Delta t`) alapján kell meghatározni, hogy a csúszó/fékező test sebessége milyen. Ehhez tehát ki kell számolni, hogy

* mekkora a :math:`\Delta t`-hez tartozó elmozdulásvektor, és hogy
* mennyi lesz a sebessége a testnek a keretidő végén.
* A :math:`v_0` ilyen esetben már a keretidő elején lévő sebességet jelenti.

A :math:`\Delta t` értékét érdemes másodpercben meghatározni. A :math:`\lambda` ekkor azt fogja jelenteni, hogy másodpercenként hányszorosára fog változni a test sebessége. Például, hogy ha :math:`\lambda = 0.5`, akkor az azt jelenti, hogy a test sebessége másodpercenként a felére fog csökkenni.

A :math:`v(t) = v_0 \cdot \lambda^t` helyett használhatunk :math:`e` alapú exponenciális függvényt. Ekkor a :math:`\lambda` jelentése (mértékegysége) más lesz, de a :math:`\lambda` konstans ismeretében a számítások egyszerűsödnek.

Csontozás
---------

Az animált karaktereink (például emberek, állatok, járművek) általában egymástól függetlenül mozgatható kisebb részekből állnak.

* A karakter aktuális helyzetének megadásához ezeket fa struktúrába szervezhetjük.
* Az összekapcsolt elemeket (a kapcsolódási pontokat) *joint*-oknak szokták nevezni.
* Az animációhoz ezekből egy csontvázat (*skeleton*-t) hozunk létre. Tulajdonképpen ezt mozgatjuk, és ez alapján lehet kiszámolni a hozzá rendelt alakzatok, modell elemek helyzetét.

Egy *joint*-hoz jellemzően az alábbiak tartoznak:

* egy tetszőleges transzformációs mátrixot,
* a gyerekelemek (mint további *joint*-ok),
* a megjelenítendő modell.

Egy lehetséges :code:`Joint` struktúra például az alábbi.

.. code:: cpp

    typedef struct Joint {
        double translation[3];
        double rotation[3];
        double scale[3];
        Model* model;
        int texture_id;
        Joint* children;
        int n_children;
    } Joint;

:math:`\rhd` Milyen műveleteket érdemes megadni a :code:`Joint` struktúrához?

A karakterünk animálásához az alábbiakra hagyatkozhatunk.

* Feltételezzük, hogy a gyerekelemekre az összes korábbi transzformáció hat.
* A *skeleton* mélységi bejárásakor elegendő az aktuális transzformációs mátrixra alkalmazni az aktuális gyerekelem transzformációs mátrixát.
* Azért, hogy ne kelljen inverz transzformációs mátrixokat számolni, a bejárás során minden csomóponthoz érve lementhetjük az aktuális transzformációs mátrixot (:code:`glPushMatrix()`), a csomópontot elhagyva visszaállíthatjuk a transzformációs verem tetején lévőt (:code:`glPopMatrix()`).


Kérdések
--------

* A virtuális színterünkben mi az amit animálni tudunk? (Soroljon fel legalább 5-öt!)
* Mi a keretidő fogalma és mértékegysége?
* Hogyan tudjuk animáció készítése során megvalósítani az egyenes vonalú egyenletes mozgást?
* Mi a szögsebesség mértékegysége? (Adjon meg legalább két alternatívát!)
* Hogyan működik a kulcsképkocka animáció, és hozzá kapcsolódóan a lineáris interpoláció?
* Hogyan tudjuk megvalósítani az egyenletes sebességgel történő forgatást?
* Karakter animáció esetén mit nevezünk *joint*-nak és milyen adatok tartoznak hozzá?
* Hogyan használható a transzformációs verem a karakterek animálásához?


Számítási feladatok
-------------------

* Ismerünk egy értéket a :math:`t_5` és :math:`t_6` időpontokban. Lineáris interpolációval hogyan határozhatjuk meg ennek az értékét a :math:`t` időpontban, feltételezve, hogy :math:`t \in [t_5, t_6]`?
* Animálni szeretnénk, és ismerjük a :math:`\varphi_1 = 20^{\circ}, \varphi_2 = 80^{\circ}` és :math:`\varphi_4 = 50^{\circ}` szögeket, amelyek rendre az 1, 2 és 4 másodperchez tartoznak. Mennyi lesz a szög értéke 2.22 másodpercnél (lineáris interpolációt használva)?


Programozási feladatok
----------------------

* Animáljunk egy ingát (például színusz függvény segítségével), amelyik a :math:`[-40, 40]` szögtartományban mozog, és 3 másodperc alatt lendül ki az egyik végállásából a másikba!
* Animáljunk egy pattogó labdát! Vizsgáljuk meg az ideális, és a nem ideális ütközés esetét is!
* Próbáljuk meg animálni egy 4 lábú állat mozgását!

