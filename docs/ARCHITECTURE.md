# Architektura LoRa Scope ADV

## Warstwy

```text
Application
  ├─ InputController
  ├─ RadioEngine
  ├─ ScanEngine
  ├─ PacketInspector
  ├─ UiRenderer
  └─ LogWriter
```

## RadioEngine

Odpowiada wyłącznie za SX1262:

- inicjalizacja SPI,
- ustawianie profilu radia,
- ustawianie częstotliwości,
- odczyt RSSI,
- CAD,
- odbiór pakietu RAW.

## ScanEngine

Odpowiada za budowę linii waterfall:

- wylicza zakres częstotliwości na podstawie `centerFrequencyMHz`, `spanKHz`, `stepKHz`,
- dla każdego punktu woła `RadioEngine`,
- zwraca linię intensywności 0..255 do UI.

## UiRenderer

Nie zna szczegółów radia. Dostaje stan aplikacji i dane do narysowania.

## PacketInspector

Na razie klasyfikuje pakiety jako `Unknown/Raw`. Docelowo:

- Meshtastic: rozpoznanie nagłówka, channel hash, decrypt default/public PSK opcjonalnie,
- MeshCore: rozpoznanie typów frame/payload,
- LoRaWAN: heurystyka MHDR/MType i payload encrypted.

## Zasada bezpieczeństwa

Aplikacja ma pokazywać publiczne/autoryzowane wiadomości i metadane. Prywatne/zaszyfrowane ramki mają być oznaczane jako `encrypted/no key`, bez prób obchodzenia zabezpieczeń.
