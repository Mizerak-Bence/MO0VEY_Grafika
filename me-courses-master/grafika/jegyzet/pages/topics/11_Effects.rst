Speciális megjelenítési módszerek, hatások
==========================================

A sugárkövetés a fény modellezésével a valósághű megjelenítés számos problémáját megoldja. Hasonlóképpen, fizikai szimulációs rendszert is készíthetünk a virtuális terünkhöz. A probléma ezekkel, hogy nagyon számításigényesek, ezért általában valamilyen helyettesítő megoldást használunk. A következőkben néhány jellegzetes effektusnak a modellezési lehetőségeit tekintjük át.

.. TODO: Hivatkozni a különböző megoldásokra a játékokban!

Égbolt modellezése
------------------

* Skybox
* Skydome

:math:`\rhd` Hogyan kerülhető el az, hogy az égbolt közepén összegyűrődjön a textúra?

:math:`\rhd` A félgömbös modell esetében egy felületi ponthoz hogyan számítható ki a normálvektor?

Domborzat modellezése
---------------------

A domborzat modellezéséhez egy gyakori megközelítés, hogy ismerjük a felület bizonyos pontjait (jellemzően négyzetrácson), majd a közbülső pontokat azok alapján határozzuk meg.

* Tulajdonképpen a :math:`z = f(x, y)` formában írjuk le a felületet.

:math:`\rhd` Hogyan érdemes tárolni, szerkeszteni a magasságértékeket?

:math:`\rhd` Hogyan becsülhető egy tetszőleges :math:`(x, y)` pontban a :math:`z` értéke?

:math:`\rhd` Hogyan becsülhetők a normálvektorok?

Árnyékok
--------

Az OpenGL (általunk aktuálisan használt változata) az árnyékokat nem kezeli.

Folt
~~~~

Az alakzatunk alá megjeleníthetünk egy (például kör alakú) foltot, ami az objektummal együtt mozog.

* Előnye, hogy egyszerűen megoldható, és mégis ad hozzá valamennyit a megjelenítés minőségéhez.
* Hátránya, hogy főként csak sík felületeken, egy irányba vetítve működik, és nem túl valószerű.

Leképzett modell
~~~~~~~~~~~~~~~~

A megjelenített alakzatunkat skálázással síkba lapíthatjuk. Sötét színnel megjelenítve árnyék hatását keltheti.

* Előnye, hogy az árnyék alakja igazodik a megjelenített alakzathoz. Az implementációja aránylag egyszerű.
* Hátránya, hogy szintén csak leszűkített esetben működik. A számítási ideje gyakorlatilag megegyezik a modell megjelenítési idejével.

:math:`\rhd` Nézzük meg a :code:`shadow` példát!

Előrenderelt textúra
~~~~~~~~~~~~~~~~~~~~

* Előnye, hogy jó minőségű árnyékokat tudunk így kapni, amely megjelenítése nem rontja a futási időt.
* Hátránya, hogy az árnyékok statikusak. A kivitelezése jellemzően sugárkövetéses módszerekkel történhet. Az árnyékok előrenderelése sok ideig tarthat. Az előrenderelt textúrákat tárolni kell.

:math:`\rhd` Milyen megoldandó problémák merülnek fel az előrenderelés során?

Sugárkövetés
~~~~~~~~~~~~

* Előnye, hogy az árnyékok valószerűek tudnak lenni.
* Hátránya, hogy számításigényes.

Tükrök
------

Az árnyékhoz hasonlóan a modell ismételt kirajzolásával oldható meg aránylag egyszerűen.

* Félig átlátszó felületeket érdemes hozzá használni.
* A fény pozícióját is tükrözni kell.
* A mélységbuffer kezelésére külön figyelni kell.

:math:`\rhd` Nézzük meg a :code:`mirror` példát!

Kollekciók kezelése
-------------------

Az alkalmazásokban gyakran szükség lehet arra, hogy egy elemből tetszőleges sokat letároljunk. Ezt valamilyen dinamikus tároló használatával célszerű megoldani. Erre a C programozási nyelv közvetlenül nem ad megoldást.

Maximalizált méretű tömb
~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: cpp

  #define MAX_ARRAY_SIZE

  typedef struct Array {
    Item items[MAX_ARRAY_SIZE];
    int n_items;
  } Array;

* Beszúrás esetén az :code:`n_items` értékét növelni kell.
* Figyelni kell, hogy ne lépjük túl a :code:`MAX_ARRAY_SIZE` értéket.
* Az elem törlésénél az :code:`n_items` értékét csökkenteni kell, és az elemek mozgatására is szükség lehet.

Dinamikusan átméretezhető tömb
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

.. code:: cpp

  typedef struct Array {
    Item* items;
    int n_items;
  } Array;

  create_array(Array* array, int size);
  append_to_array(Array* array, const Item* item);
  remove_from_array(Array* array, int index);
  destroy_array(Array* array);

* A tömb mérete a beszúrásokat, törléseket végrehajtva változhat.

:math:`\rhd` Milyen heurisztikákat használhatunk az allokált (:code:`items`) tömb méretének meghatározásához?

Láncolt lista
~~~~~~~~~~~~~

.. code:: cpp

  typedef struct Node {
    const Item* item
    struct Node* next;
  } Node;

  typedef struct List {
    Node* head;
  } List;

  create_list(List* list);
  append_to_list(List* list, const Item* item);
  remove_from_list(List* list, int index);
  destroy_list(List* list);

:math:`\rhd` Milyen további kollekció típusok szoktak még előfordulni?

:math:`\rhd` Hogyan lehet ezeket implementálni C-ben?

Nyomvonal modellezése
---------------------

Tegyük fel, hogy meg szeretnénk jeleníteni a virtuális terünkben, hogy merrefelé jártunk.

:math:`\rhd` Nézzük meg a :code:`footprints` példát!

Részecskerendszerek
-------------------

Egyszerűbb esetben tekinthetünk egy részecskére úgy, mint egy pontra, amelynek van sebessége

.. code:: cpp

  typedef struct Particle {
    vec3 position;
    vec3 velocity;
  } Particle;

A következőkben néhány példát láthatunk részecskerendszerek segítségével megvalósított effektekre.

Eső, hóesés modellezése
-----------------------

* A részecskéket adott magasságból indíthatjuk, úgy hogy azok szabadon essenek.
* Az esés során különféle módosítókat is alkalmazhatunk (például, hogy a hópelyhek szálingózzanak).

Robbanás
--------

Egy adott pontból véletlenszerűen választott sebességekkel tudjuk például modellezni.

:math:`\rhd` Nézzük meg a :code:`explosion` példát!

Tűz, füst
---------

Változatos lehetőségek vannak a modellezési módjára.

Animált textúra
~~~~~~~~~~~~~~~

* Képsorozatként megjeleníthetjük egy alakzat textúráján.
* Általában félig átlátszó textúrákat szoktak hozzá használni.
* Gyakran egymással szöget bezáró sík felületekként jelenítik meg (például merőleges, vagy 60 fokos szögben).

Modellek sorozata
~~~~~~~~~~~~~~~~~

* A tűz alakját meg lehet próbálni modellezni, majd időközönként váltogatni.
* Ez gyakorlatilag a képsorozat térbeli változata.

Változó színű részecskék
~~~~~~~~~~~~~~~~~~~~~~~~

Egy további lehetőség például, hogy a részecskék színét időben változtatjuk, például a fehér, sárga, piros és fekete színátmenetekkel.

* Tegyük fel, hogy egy láng élettartama 3 másodperc!
* Hasson a részecskékre egy erőhatás, amelyik :math:`z = 1` irányba mozgatja a részecskét!
* Amint egy részecske *kihűlt*, indítsuk újra az origóból!

.. code:: cpp

  #define N_FLAMES

  typedef struct Flame {
    vec3 position;
    vec3 velocity;
    double lifetime
  } Flame;

  typedef struct Fire {
    Flame flames[N_FLAMES];
  } Fire;

:math:`\rhd` Nézzük meg a :code:`fire` példát!

:math:`\rhd` Hogyan tudnánk megoldani azt, hogy a láng teteje összefelé tartson?

:math:`\rhd` Milyen fényhatásokat lehet érdemes beállítani a tűz közepéhez?

Cella alapú hőáramlás szimuláció
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

A tűz megjelenítéséhez készíthetünk egyszerű áramlási, hőterjedési modellt.

* Meg kell határozni egy rögzített, raszteres felbontást. Ez praktikusan egy négyzetrács pontjait jelenti, amelyhez az intenzitásokat egy mátrixban tárolunk.
* Definiálhatunk egy szabályrendszert, ami alapján az aktuális intenzitások alapján kiszámítjuk a következő iterációhoz tartozó intenzitásokat.
* Hogy ha a rácsfelosztás miatt az eredmény túlságosan szögletes lenne, akkor alkalmazhatunk valamilyen interpolációt. (Textúrázás esetében ezt az OpenGL megoldja helyettünk.)

:math:`\rhd` Nézzük meg a :code:`fire.html` példát!

Víz, folyadékok
---------------

Állóvíz modellezése
~~~~~~~~~~~~~~~~~~~

* Egy félig átlátszó textúra használatával megoldható.
* A textúrát mozgatva érdekesebbé tehető az összkép.

Hullámzás modellezése
~~~~~~~~~~~~~~~~~~~~~

A víz felszínét modellezhetjük, mint magasságmezőt.

Folyadék áramlása
~~~~~~~~~~~~~~~~~

Raszteres rácsfelbontást alkalmazva szimulálhatjuk, hogy azokban mennyi a folyadék mennyisége.

.. TODO: Keressünk (vagy rajzoljunk) egy négyzet alakú víz textúrát, amelyik egymáshoz periodikusan illeszthető.

