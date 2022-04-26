# CAN IDs — Seat Ibiza (2013), comfort bus

Decoded by sniffing the bus with [`tools/canbus_finder.py`](../tools/canbus_finder.py) and
[`tools/canbus_monitor.py`](../tools/canbus_monitor.py) while pressing buttons, opening doors and so on.

Byte indexes are **0-based**, values are **decimal** unless written as hex.
Entries marked *(?)* were observed but not fully confirmed.

| ID | Byte | Meaning | Values |
|---|---|---|---|
| `0x151` | 1 | Seat belts | 160 = none fastened, 176 = driver, 224 = passenger, 240 = both |
| `0x35B` | 4 | Pedals | 40 = none, 43 = brake, 32 = clutch, 35 = clutch + brake |
| `0x381` | 0 | Driver door | 0 = closed, 1 = open, 2 = locked |
| `0x381` | 2 | Driver window | Window position |
| `0x3B5` | 0 | Passenger door | 0 = closed, 1 = open, 2 = locked |
| `0x3B5` | 2 | Passenger window | Window position |
| `0x3C3` | 0 | Steering wheel position | 0–128 = turned left, 128–255 = turned right |
| `0x3C3` | 1–2 | *(?)* Changes with acceleration | |
| `0x3E1` | 0 | *(?)* Climate temperature | 32 = fully cold, 0 = slightly warmer |
| `0x3E1` | 4 | Climate fan speed | |
| `0x3E1` | 6 | Air conditioning | 132 = off, 134 = on |
| `0x3E3` | 4 | Recirculation | 0 = off, 128 = on |
| `0x470` | 0 | Reverse gear | 192 = not in reverse, 224 = reverse |
| `0x47A` | 1 | Dashboard scroll knob | |
| `0x531` | 1, bits 0–4 | Turn signals | 0 = off, 17 = left, 18 = right, 27 = hazard lights |
| `0x531` | 1, bits 6–7 | Brake lights | 64 = on |
| `0x5C1` | 0 | Steering wheel buttons | 1 = mode, 2 = scroll up, 3 = scroll down, 4 = next, 5 = previous, 6 = volume up, 7 = volume down |
| `0x621` | 0 | Handbrake | 0 = released, 32 = applied |
| `0x621` | 4 | High beam | 1 = off, `0x21` = on |
| `0x621` | 5 | Low beam | 0 = off, >1 = on |
| `0x621` | 6–7 | Dashboard illumination level | 16-bit, big-endian |

The IDs used by the firmware are in
[`firmware/src/carcanbus/messages/`](../firmware/src/carcanbus/messages/).
