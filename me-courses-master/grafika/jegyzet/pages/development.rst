A Fejlesztőkörnyezet beüzemelése
================================

A fejlesztőeszközök
-------------------

Windows esetében a fejlesztéshez szükséges dolgok a `c_sdk_220203.zip <https://web.uni-miskolc.hu/~matip/_downloads/c_sdk_220203.zip>`_ formájában letölthetőek. (A következőkben röviden *C SDK*.)
Telepíteni nem szükséges, mindössze ki kell tömöríteni egy tetszőleges helyre. A csomag tartalmazza

* a GNU C/C++ fordítóját,
* a szükséges OpenGL és SDL2 fejléceket és binárisokat,
* a Notepad++ szövegszerkesztőt.

GNU/Linux és más UNIX-szerű operációs rendszereken a ``gcc``, ``make`` programokra és az SDL2 vagy SDL3 függvénykönyvtár telepítésére van szükség.

Nem kötelező Notepad++-t használni. Áttekintésképpen az alábbiakban szerepel néhány szerkesztő és fejlesztőkörnyezet.

* Notepad++: https://notepad-plus-plus.org/
* Visual Studio Code: https://code.visualstudio.com/
* Eclipse CDT: https://projects.eclipse.org/projects/tools.cdt
* Qt Creator: https://www.qt.io/product/development-tools
* CLion: https://www.jetbrains.com/clion
* Code::Blocks: `https://www.codeblocks.org/ <https://www.codeblocks.org/>`_
* NetBeans: https://netbeans.apache.org/front/main/index.html
* Sublime Text: https://www.sublimetext.com/


A C SDK
-------

A C SDK-t elegendő letölteni, és kitömöríteni. Külön telepítés nem szükséges hozzá.

* Hogy ha nincs a géphez rendszergazdai jogosultság, akkor a ``shell.bat`` állományt érdemes használni. Ez csak egy környezeti változót állít be ahhoz, hogy a ``gcc`` és ``make`` parancsok elérhetőek legyenek.
* Hogy ha van a géphez rendszergazdai jogosultság, akkor érdemes rendszer szintjén beállítani, hogy a fordító útvonala (ami ``MinGW/bin``-re végződik) a ``PATH`` változóban szerepeljen.

.. note::

   Nem kötelező konkrétan ezt használni. A részeiből a naprakész változatok külön is telepíthetőek, beállíthatóak.

.. warning::

   Gyakori hiba, hogy a gépre már korábban lett telepítve C fordító, és emiatt a fordításnál hiba keletkezik amiatt, hogy a fordító nem találja az SDL2 fejléceket. Ennek a megoldásához a környezeti változókat érdemes átnézni. Parancssorból ez a

   .. code::

        echo %PATH%

   parancs kiadásával oldható meg.


Kódpéldák
---------

Az előadásokhoz és gyakorlatokhoz tartozó anyagok a `www.gitlab.com/imre-piller/me-courses <https://www.gitlab.com/imre-piller/me-courses>`_ címről érhetők el. 

* A repository-t időszakosan ``pull`` paranccsal érdemes frissíteni.
* Ebbe a repository-ba a Hallgatóknak nem kell feltölteni semmit.
* Az észrevételeket, javaslatokat természetesen szívesen veszem, és szükség esetén korrigálom.


Jegyzékek szervezése
--------------------

A fejlesztés kapcsán érdemes az alábbi 3 dolgot logikailag elkülöníteni:

* *C SDK*: a fejlesztőkörnyezethez tartozó fájlok (a fordító, és az ahhoz kapcsolódó fájlok értendők bele),
* *me-courses*: a példakódokat tartalmazó git repositority,
* *saját repository*: értve ez alatt a Hallgató saját git repository-ját.

Előírás arra vonatkozóan nincs, hogy ezek a fájlrendszerben hol legyenek, de érdemes szem előtt tartani a következőket.

* Sem a *C SDK*-t, sem pedig az *me-courses* repository tartalmát nem kellene feltölteni a saját repository-ba.
* Az *me-courses*-ban lévő példákból ki lehet indulni, egy-egy részt át lehet másolni, de nincs értelme a saját repository részeként feltölteni azt.

Egy praktikus fájlelrendezés lehet például az alábbi:

.. code::

    c_sdk/
        MinGW/
        me-courses/
        grafika/
        shell.bat


Ebben a `grafika` a Hallgató saját jegyzékét jelölné.


Példa programok fordítása és futtatása
--------------------------------------

* A példa programokról célszerű másolatot készíteni a saját repository-ba (azon belül is a ``gyakorlatok``, vagy angolul ``demos`` nevű jegyzékbe).
* El kell indítani a ``shell.bat`` fájlt.
* Be kell lépni a parancssorban a megfelelő mappába.
* Ki kell adni egy ``make`` parancsot.
* Le kell ellenőrízni, hogy létrejött-e a futtatható állomány.
* Meg kell próbálni elindítani. Dupla kattintás esetén hiányzó DLL-el kapcsolatos hibaüzenetet kaphatunk. Ezt vissza lehet keresni a ``MinGW/bin`` jegyzékben. Parancssorból futtatva a problémának nem szabad fennállnia.


Gépes gyakorlattal kapcsolatos tudnivalók
-----------------------------------------

* A számítógépes termekben lévő számítógépeken a D meghajtóra lehet elhelyezni azokat a dolgokat, amelyekre egész félévben szükség lehet. (Az asztalon lévő dolgok időszakosan törlésre kerülhetnek.)
* Mindenkinek létre kellene hoznia egy saját névre szóló jegyzéket.


Git-tel kapcsolatos tudnivalók
------------------------------

* Az elkészített kódokat (beleértve a gyakorlatokat és a féléves feladatot is) egy *git* repozitóriumba kell elhelyezni.
* Ez lehet például `GitHub <https://github.com/>`_-on, `GitLab <https://about.gitlab.com/>`_-on vagy `BitBucket <https://bitbucket.org/>`_-on. (Mindenki használhatja azt, amelyik szimpatikusabb.)
* A repozitóriumot publikussá kell tenni, hogy egyszerűen elérhető legyen.

A Hallgató saját repozitóriumának közvetlenül, a ``clone`` parancs kiadásával letölthetőnek kellene lennie, mint például ahogy az *me-courses* is:

.. code::

   git clone https://www.gitlab.com/imre-piller/me-courses


Kliens program
~~~~~~~~~~~~~~

A ``git`` használatához valamilyen kliens program szükséges.

* Az egyik egyszerű megoldás a parancssoros git kliens.
* Grafikus alkalmazást is lehet használni, hogy ha valakinek az szimpatikusabb.
* A szövegszerkesztőkbe, IDE-kbe integráltan, jellemzően bővítmény formájában rendelkezésre állnak ilyenek.

Alapvető parancsok
~~~~~~~~~~~~~~~~~~

.. code::

  git init
  git clone
  git status
  git add
  git rm
  git commit
  git log
  git push
  git pull

.. note::

  Gyakorlás céljából érdemes a parancsokat egy lokálisan létrehozott repozitóriumon próbálgatni.

.. warning::

   Attól függetlenül, hogy valaki milyen klienst használ, a git működésével, használatával tisztában kell lennie!


A repozitórium felépítése
-------------------------

A Hallgató saját repozitóriumának a felépítése alapvetően az alábbi formában kellene, hogy kinézzen:

Magyar nyelvű változat:

.. code::

  /feladat
  /gyakorlatok
  README.md

* A ``feladat`` jegyzékbe kerül majd a féléves feladat.
* A ``gyakorlatok`` jegyzékbe kell a gyakorlatokon megoldott kódokat feltölteni.
* A ``README.md`` állományba kerül majd a repository bemutatása, benne részletezve a féléves feladat specifikációját.

Angol nyelvű változat:

.. code:: shell

    /app
    /demos
    README.md

A jegyzékek és fájlok nevének következeteseknek kell lenniük!

.. note::

   Kisebb, indokolható eltérések megengedettek, például

   * külön jegyzék az esetleges fejlesztéshez kapcsolódó dokumentációnak,
   * jegyzék a képeknek, amelyek a ``README.md``-ben vannak,
   * jegyzékek olyan saját fejlesztésű eszközöknek (például ``tools`` vagy ``utils``), amelyek sem a féléves feladathoz, sem pedig a gyakorlatokhoz nem köthetők közvetlenül,
   * ``.gitignore`` fájl,
   * licensz fájl.

.. warning::

   A repository-ba az alábbiakat semmiképpen sem kellene feltölteni:

   * a fejlesztőkörnyezetet,
   * a lefordított binárisokat,
   * a fordítás során létrejövő segéd és átmeneti fájlokat.


Asset-ek kezelése
-----------------

Az alkalmazásokhoz (a grafikusokhoz különösképpen) szoktak tartozni különböző adatfájlok. Ilyenek például a képek, 3D-s modellek adatait tartalmazó fájlok. Ezek a program futásához szükségesek ugyan, a forráskódnak viszont nem képezik a részét, a fordításhoz nem szükségesek.

Jellemzően ezen fájlok nagyobb méretűek. Érdemes őket külön kezelni. Ez aktuálisan egy példán keresztül bemutatva a következő formában történne.

.. code::

  /assets/models/house.obj
  /assets/models/tree.obj
  /assets/textures/house.png
  /assets/texture/tree.png
  /assets/config.csv

* A textúrák és a modellek külön jegyzékekbe kerülnek.
* Az ``assets`` jegyzéket és tartalmát ZIP formátumban tömörítve kell feltölteni egy tárhelyre.
* A tárhelynek az elérhetőségét a `README.md` fájlban meg kell adni. Az ott szereplő leírás alapján össze kell tudni rakni a futtatható változatot.

