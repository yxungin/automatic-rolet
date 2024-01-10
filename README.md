Projekt: Automatické ovládání rolet s ESP8266 a krokovým motorem

Úvod
Tento projekt umožňuje automatické ovládání rolet pomocí ESP8266 Wi-Fi modulu a krokového motoru. ESP8266 je použit pro vytvoření webového serveru, který umožňuje uživatelům ovládat rolety pomocí webového rozhraní. Kód Arduino spolu s krokovým motorem A4988 zajišťuje fyzický pohyb rolet na základě příchozích příkazů přes Wi-Fi.

Součástky:
ESP8266 Wi-Fi modul
Krokový motor (např. 28BYJ-48)
Driver pro krokový motor (např. A4988)
Pájení:
ESP8266 a driver A4988:
ESP8266 PIN D1 --> STEP_PIN na driveru
ESP8266 PIN D2 --> DIR_PIN na driveru
ESP8266 PIN D3 --> ENABLE_PIN na driveru
Ceny:
ESP8266 Wi-Fi modul: [59,54 Kč]
Krokový motor (28BYJ-48): [95 Kč]
Driver A4988: [21,53 Kč]
Celková cena [176,07 Kč]



Funkce:
Webové rozhraní: Uživatel může ovládat rolety pomocí tlačítek "Nahoru" a "Dolů" ve webovém prohlížeči.
Krokový motor: Kód řídí krokový motor tak, aby provedl určitý počet kroků po přijetí příkazu z webového rozhraní.

Výhody:
Jednoduché ovládání: Možnost ovládání rolet přes webové rozhraní, což je snadné a pohodlné.
Možnost automatizace: Umožňuje nastavit automatické ovládání rolet podle časového plánu nebo podle externích podmínek (např. světelné senzory).

Nevýhody:
Potřeba napájení: Nutnost připojení k elektrické síti pro napájení motoru a Wi-Fi modulu.
Přesnost motoru: Přesnost krokových motorů může být omezená a může se lišit v závislosti na konkrétním modelu.
Problémy řešené v rámci projektu:
Časová neaktivita: Uspání motoru po 30 sekundách neaktivity pro úsporu energie.
Webové ovládání: Implementace ovládání rolet pomocí tlačítek "Nahoru" a "Dolů" na webovém rozhraní.
Pohyb motoru: Řízení krokového motoru na základě požadavků z webového serveru.

Závěr:
Tento projekt umožňuje uživatelům ovládat rolety pomocí webového rozhraní přes Wi-Fi, což poskytuje pohodlí a možnost automatizace. Přesnost pohybu motoru a spotřeba energie jsou faktory, které je třeba zvážit při použití tohoto řešení.
Tato dokumentace slouží jako základní informace a popis projektu automatického ovládání rolet s ESP8266 a krokovým motorem.



Součástky a cíl projektu:
Součástky:
 ESP8266, krokový motor 28BYJ-48, driver pro krokový motor  A4988.

cíl projektu: 
vytvoření systému pro ovládání rolet pomocí ESP8266 a krokového motoru.




Připojení a zapojení součástek:
Připojoval jsem prvně na breadboard ESP8266 s krokovým motorem a driverem A4988.
po odzkoušení že vše funguje jsem začal pájení potřebných spojů pro správnou funkci projektu.

Experimentování s Home Assistant a ESPHome
Zpočátku jsem zkoušel implementovat ovládání rolet přes Home Assistant a ESPHome pro automatizaci.
Snažil jsem se integrovat systém přes tyto platformy, ale narazil jsem na problémy s nastavením a kompatibilitou, které mi komplikovaly proces a neumožnily plně funkční řešení.


Úspěch pomocí Arduino IDE
Po neúspěšných pokusech s Home Assistant a ESPHome jsem se rozhodl pro ověřenou cestu pomocí Arduino IDE.
S implementací pomocí Arduino IDE jsem dosáhl úspěchu a vytvořil funkční systém pro ovládání rolet přes webové rozhraní, což umožnilo uživatelům snadnější a spolehlivější ovládání.

potřebné knihovny a začátek kódování:
Zvolil jsem knihovny ESP8266WiFi a ESP8266WebServer pro komunikaci a vytvoření webového rozhraní.
Začal jsem kódovat základní funkcionalitu pro ovládání krokového motoru přes ESP8266.

Implementace webového serveru:
Vytvořil jsem jednoduché webové rozhraní pro ovládání rolet pomocí HTML a JavaScriptu.
Implementoval jsem funkcionalitu tlačítek "Nahoru" a "Dolů" pro ovládání motoru.

Řízení krokového motoru a jeho pohyb
hledal jsem inspiraci v kódu pro pohyb krokového motoru na základě příkazů z webového serveru.
Ladil jsem rychlost a směr otáčení motoru.



Uspání motoru po nečinnosti a jeho probuzení:
Přidal jsem funkcionalitu uspání motoru po určité době nečinnosti.
Implementoval jsem kód pro probuzení motoru při novém požadavku z webového serveru.

3D tisk komponentů
Vytiskl jsem si držák motoru s malou převodovkou, aby motor měl dostatečnou sílu na vytahování rolet.
Vytiskl jsem:
držák motoru, kryt motoru , a zvlášť krabičku na esp8266 a driver krokového motoru A4988.

Dokumentace projektu
Sepsali jsem dokumentaci projektu obsahující informace o součástkách, jejich cenách, zapojení, funkci, výhody, nevýhody a problémy řešené během vývoje.
Toto je stručný přehled kroků, které jsem provedl během vývoje projektu automatického ovládání rolet s ESP8266 a krokovým motorem.

