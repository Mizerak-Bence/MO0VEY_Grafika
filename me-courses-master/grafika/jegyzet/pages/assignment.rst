Féléves feladat
===============

Minimális elvárások az elkészített programmal szemben
-----------------------------------------------------

* **Kamerakezelés**: A virtuális teret az egér és/vagy billentyűzet segítségével be kell tudni járni.
* **Objektumok**: Térbeli objektumok legyenek. Ezeket, mint modelleket külön fájlból lehessen betölteni.
* **Animáció, mozgatás**: A program legyen interaktív. A modelleket, fényeket billentyűzettel, egérrel lehessen mozgatni; legyenek animált részek.
* **Textúrák**: A modelleknek legyen textúrája.
* **Fények**: A programban a fényeket a ``+`` és ``-`` billentyűk segítségével lehessen állítani (vagy egyéb kézenfekvő módon a program leírása alapján).
* **Használati útmutató**: Az ``F1`` gomb megnyomására (vagy egyéb kézenfekvő módon) jelenjen megy egy leírás a programról, annak használatáról, kezelési módjáról.

Az elkészített programnak jól strukturáltnak, következetesnek kell lennie.
Törekedni kell arra, hogy a modellek, a kezelés kidolgozott, a megjelenítés esztétikus legyen.
Ezek a minimális elvárások a programmal szemben.
Amennyiben ezek teljesülnek, úgy a feladat már elégséges.


Többlet funkciók
----------------

A jobb jegyért például az alábbi dolgokat lehet a programban megvalósítani.

* **Bonyolultabb animációk**: Például karakterek animálása, görbék mentén mozgatás.
* **Fizika**: Például ingák, rugózás, szövet, víz.
* **Részecskerendszerek**: Például Tűz, füst, eső, hóesés.
* **AI**: Táblás játékok esetén kézenfekvő, egyéb játékoknál ellenfelek vezérlése például.
* **Köd**: Köd hatás megvalósítása, dinamikus változtatása.
* **Átlátszóság**: Átlátszó részeket tartalmazó textúrák alkalmazása, félig áttetsző részek a megjelenített objektumokon.
* **Árnyék**: Árnyékszerű hatások létrehozása.
* **Ütközésvizsgálat**: Bounding-box implementáció valamilyen formája.
* **Stencil buffer használata**: Nem téglalap alakú képterületek megvalósításához.
* **Felhasználói felület**: A paraméterek állításához külön felületi elemek.
* **Objektumok kijelölése egérrel**: A megjelenített objektumok kijelölése.
* **Térkép kezelése**: Például magasságmező betöltése képfájlból úgy, hogy adott modellek helyét is meg lehessen adni rajta.
* **Procedurális geometria, textúrák**: Modellek létrehozása valamilyen algoritmus segítségével.
* **LOD**: *Level of Details* a hatékonyabb megjelenítéshez.
* **Bump mapping, displacement mapping**: Képek használata a felületi érdesség tárolásához, megjelenítéséhez.
* **Environment mapping**: Környezetről készített kép használata textúraként, az ahhoz tartozó transzformációk megvalósítása.
* **Sztereoszkópia**: Például renderelés valamilyen 3D-s megjelenítő eszközhöz.

Minden így elkészített plusz funkció 1-gyel növeli az érdemjegyet (5-ben maximálva).
Mindenkinek javaslom, hogy legalább 3 plusz dolgot építsen be a programjába.


Programmal és beküldésével kapcsolatos észrevételek
---------------------------------------------------

* A program forráskódjának ``make`` paranccsal lefordítható formában kell szerepelnie a repository-ban.
* A programhoz tartozó adatokat egy ``assets`` nevű jegyzékbe kell elhelyezni.
* Az ``assets`` jegyzéket tömörítve valahová fel kellene tenni (például: saját weboldal, DropBox, OneDrive), nem pedig csatolmányként küldeni. Ennek a linkjét a ``README.md`` fájlban kell feltüntetni.
* A project mérete kitömörítést követően a 200 MByte-ot lehetőleg ne haladja meg.
* A textúrákhoz PNG vagy JPEG formátumú fájlokat érdemes használni.
* A ``main`` függvényt tartalmazó fájl neve ``main.c`` legyen.
* A forráskódban az elnevezéseknek angolul kell szerepelni.
* Minimális számú globális változót kell használni.
* A fejléc állományokba dokumentált formában kerüljön az interfészek leírása. A forrásállományba ideális esetben nem szükségesek megjegyzések.
* A kódban a repeptitív, adattárolásra emlékeztető kódrészeket külön adatszerkezetbe, adatfájlba kell kiszervezni (például CSV fájlokba).
* Törekedni kell arra, hogy a program figyelmeztetések (*warning*) nélkül forduljon.
* Ha a forráskódhoz tartozik valamilyen külső forrásból származó kódrész, akkor azt a megfelelő licensz feltüntetése mellett lehet használni!


Gyakori hibák
-------------

* Nem került kiválasztásra a feladat. Először egy részletes, konkrétumokat tartalmazó, szöveges leírásnak kell készülnie a féléves feladathoz, ami hogy ha az egyeztetéseket követően rendben van, akkor kellene egyáltalán hozzákezdeni a feladat elkészítéséhez.
* A kiválasztandó feladat mögött nincs koncepció. Néhány, a semmi, vagy egy textúrázott kocka közepén mozgó, forgó objektum önmagában még nem egy túl átgondolt, kiforrott témára utal.
* A program és a repozitórium szerkezete nem megfelelő.
* Nem a modellbetöltő statikus függvénykönyvtár került felhasználásra.
* Túlságosan sok a globális változó.
* A program szerkezete, a forráskódhoz tartozó állományok nem tükrözik, hogy konkrétan miről szólna a választott feladat. (A programoknak OOP szemlélettel kellene készülniük.)
* A program ablakát nem lehet átméretezni az arányok megtartása mellett.
* A program azt az ``Actions`` struktúrát tartalmazza, amire vonatkozóan már rendszeresen említésre került, hogy az nem jó megoldás.
* A programban az objektumokon indokolatlan helyeken át lehet menni.
* Az animáció nem idő függvényében, hanem a kirajzolás számának megfelelően változik.
* A betöltött modellek, textúrák esetében az útvonalak nem átvihetőek. (A *backslash* és a kis-nagybetű különbségek szoktak ilyen problémát okozni.)
* A program túlságosan sok repetitív részt tartalmaz. Azokat modellek betöltésével, ``for`` ciklus használatával lehet tipikusan orvosolni.
* Nem látszanak a programban a fényhatások.
* Nem megfelelő a programban a fények átállítása. Úgy néz ki, mint hogy ha csak a monitor fényerejét állítgatná a felhasználó.
* Nem került bemutatásra a program. Hogy ha minden előzmény, korábbi bemutatás nélkül érkezik be egy feladat, az olyan formában még nem fogadható el. (A feladat elkészítésének az a célja, hogy az illető bizonyítsa, hogy a grafikus programozásban gyakorlatot szerzett, az annak kapcsán felmerülő kérdéseket érdemben meg tudja válaszolni.)

