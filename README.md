# LoRa Scope ADV

Kieszonkowy **sejsmograf LoRa / RF scope** dla **M5Stack Cardputer ADV + Cap LoRa-1262/SX1262**.

Cel MVP: nie udawać pełnego SDR-a, tylko zrobić realnie działający skaner LoRa na SX1262:

- kolorowy waterfall RSSI,
- przesuwanie częstotliwości klawiszami,
- sweep po paśmie 868 MHz,
- tryb lock/tune na konkretną częstotliwość,
- marker aktywności CAD,
- lista ostatnich pakietów/raw HEX,
- log CSV na microSD,
- przejrzysta architektura pod późniejsze dekodery Meshtastic/MeshCore/TTN.

## Ważne ograniczenie

Cap LoRa-1262/SX1262 **nie jest SDR-em**. Nie widzi całego pasma naraz. Aplikacja robi szybkie skanowanie krokowe:

```text
ustaw częstotliwość -> zmierz RSSI/CAD -> narysuj piksel -> następna częstotliwość
```

Dlatego są dwa podstawowe tryby:

- **SWEEP** — ładny waterfall i obserwacja pasma, ale można przegapić krótkie pakiety.
- **TUNE/LOCK** — radio stoi na jednej częstotliwości, większa szansa na realny odbiór pakietu.

## Sterowanie MVP

Domyślnie aplikacja obsługuje zarówno strzałki, jak i fallback klawiszami literowymi, bo firmware/wersje biblioteki M5Cardputer mogą różnie mapować klawiaturę.

```text
← / → albo A / D      przesuwanie częstotliwości
↑ / ↓ albo W / S      zoom / span zakresu
Q / E                 większy skok częstotliwości
1                     Scope
2                     Packets
3                     Antenna Lab
Space                 pauza waterfall
Enter                 lock/tune na środku zakresu
L                     logowanie CSV ON/OFF
M                     zmiana SWEEP/TUNE
P                     następny preset
```

Jeżeli strzałki nie działają w Pana wersji biblioteki, trzeba dopasować mapowanie w `src/input/InputController.cpp`.

## Build lokalny

```bash
pio run
```

Upload:

```bash
pio run -t upload
pio device monitor
```

## Struktura

```text
src/app/        aplikacja, stan, orkiestracja
src/radio/      RadioLib/SX1262, profile, sweep, pakiety
src/ui/         renderer UI, waterfall, kolory
src/input/      klawiatura Cardputera
src/storage/    logowanie CSV na microSD
src/util/       małe struktury pomocnicze
.github/        GitHub Actions build firmware.bin
```

## Roadmap

1. MVP waterfall RSSI + częstotliwość klawiszami.
2. CAD marker i lock-on-signal.
3. Packet inspector RAW HEX.
4. Antenna Lab — scoring miejsca/anteny.
5. Meshtastic public/default decoder.
6. MeshCore packet recognizer.
7. LoRaWAN/TTN test mode.
