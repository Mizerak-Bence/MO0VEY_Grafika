Gyakran ismételt kérdések
=========================

Miért régi OpenGL szabványt kell használni?
-------------------------------------------

A tárgy célja nem a lehető legmodernebb technológiák elsajátítása, hanem az alapfogalmak, alapvető megjelenítési módoknak az ismertetése.

* A tér leképzése, transzformációk, színterek, poligonhálóval való közelítés, textúrázás ... fogalom szintjén nem változtak. (A használati módjuk rendszerenként viszont eltérő, és várhatóan a jövőben is változni fog.)
* A régi OpenGL szabvány használata egyszerűbb, azoknak is csak egy igen kis részére van szükség. Nem kell attól tartani, hogy túl sok dolgot feleslegesen tanulna meg közben az ember.


Miért C-ben készülnek a programok?
----------------------------------

A programozási nyelv megválasztásánál több szempontot egyidejűleg kellett figyelembe venni.

* Lehetőleg olyan nyelv legyen, amelyiken szoktak grafikus alkalmazásokat készíteni.
* Az elkészült programok legyenek átvihetőek.
* Álljon rendelkezésre minél több eszköz és dokumentáció a fejlesztéshez.
* Elvárható legyen a hallgatótól, hogy ismeri a programozási nyelvet. (A Programozás alapjai tárgyat elvileg mindenkinek teljesítenie kellett már, amelynél ugyancsak C programozás nyelv került felhasználásra.)

Egyelőre a C bizonyult olyan nyelvnek, amelyik ezeket teljesíteni tudja.


Lehet-e C++ -t használni?
-------------------------

C++ nyelvről általánosságban manapság már nem nagyon lehet beszélni. Kb. 3 évente jelenik meg új szabvány, amelybe kerülnek új elemek, és nem javasolják néhány régebbi használatát.

* A hallgatóság részéről az egyik érv a C++ mellett az szokott lenni, hogy ahhoz találnak anyagot. Szoktam nézegetni OpenGL-es tutorial-okat és fórumokat. Sajnos ezek nem minden esetben ütik meg a minőségi elvárásokat.
* Nagyon ritka, hogy valaki azért nem tud C-ben programozni, mert C++ -ban tud.

Annak alapvetően örülök, hogy ha valaki C++ -ban szeretne dolgozni. Azt javaslom, hogy rövid időn belül készítse el a feladatát C-ben, majd áttérhetünk a C++ nyelvű fejlesztésre. Igyekszem neki segíteni abban is.


Miért nem lehet objektum orientáltan programozni?
-------------------------------------------------

Tulajdonképpen abban kell. A programoknak objektum orientált szemlélet szerint célszerű készülniük. A C nyelv használata nem azt jelenti, hogy a paradigmát ne lehetne alkalmazni.

* A programban ábrázolt adatokat (más megközelítésben állapotteret vagy modellt) struktúrákba célszerű rendezni.
* Az ehhez tartozó műveleti részt függvények írják le, melyek első paramétereként, cím szerint kapják az objektum adatait.
* A moduláris felépítés érdekében a logikailag összetartozó struktúrákat és műveleteiket külön forrás (``.c``) és fejléc (``.h``) állományokba célszerű tenni.
* Egy megfelelően összerakott programban szépen látszanak az MVC elvek. Az adatokat tartalmazó részek, az események kezelése és a hozzájuk tartozó módosító (itt tipikusan *update*) műveletek illetve a megjelenítés (*render* függvények) el kell, hogy különüljenek.


Milyen fejlesztőkörnyezetet lehet használni?
--------------------------------------------

A fejlesztőkörnyezetre vonatkozóan nincs megkötés, sem IDE sem fordító vonatkozásában.

* A *Notepad++* és a *GCC* csak javasolt.
* Mivel átvihető szoftver készül, ezért a programnak le kell tudnia fordulnia GCC fordítóval is.
* A programok felépítése adott struktúrát követ. Ez egy GNU Makefile segítségével egyszerűen használható.

