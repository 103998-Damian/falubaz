# Falubaz – Symulacja Żużlowa

Projekt symulacji żużlowej Falubaz w **Unreal Engine 5 + C++**, z modelami 3D przygotowanymi w Blenderze.

## Struktura projektu

```
falubaz/
├── unreal/falubaz-simulation/  # Projekt UE5 (aktywny)
│   └── Source/falubaz/
│       ├── Vehicles/           # SpeedwayMotorcycle, SpeedwayMovementComponent
│       ├── Track/              # SpeedwayTrack
│       └── Player/             # SpeedwayPlayerController
├── godot/falubaz-simulation/   # Projekt Godot 4 (archiwum)
└── blender/                    # Pliki Blender (nieśledzone przez git)
```

## Wymagania

- **Unreal Engine 5.5** (pobierz przez Epic Games Launcher)
- **Visual Studio 2022** z workloadem **"Game development with C++"**
  - Podczas instalacji VS zaznacz: `MSVC v143`, `Windows 10/11 SDK`, `C++ CMake tools`
- Git

## Pierwsze uruchomienie

### 1. Sklonuj repozytorium

```bash
git clone https://github.com/falubaz/falubaz.git
cd falubaz
git checkout dev
```

### 2. Skompiluj projekt

Zamknij Unreal Engine jeśli jest otwarty, następnie uruchom:

```
unreal/falubaz-simulation/GenerateVS.bat
```

Poczekaj na komunikat `Build succeeded` (kilka minut przy pierwszym uruchomieniu).
Log z kompilacji zapisuje się do `unreal/falubaz-simulation/build_log.txt`.

### 3. Otwórz projekt w Unreal Engine

1. W **Epic Games Launcher** uruchom Unreal Engine 5.5
2. Otwórz plik: `unreal/falubaz-simulation/FalubazSimulation.uproject`
3. Jeśli pojawi się pytanie "Rebuild now?" – kliknij **Yes**

### 4. Skonfiguruj Blueprint motocykla

Po otwarciu projektu w UE5:

1. W **Content Browser** otwórz `Blueprints/BP_SpeedwayMotorcycle`
2. W panelu **Details** uzupełnij:
   - `Default Mapping Context` → `IMC_Motorcycle`
   - `Throttle Action` → `IA_Throttle`
   - `Steer Action` → `IA_Steer`
   - `HUD Class` → `WBP_HUD`
   - `Motorcycle Mesh` → wybierz model motocykla z `Content/Models/`
3. Kliknij **Compile** i **Save**

### 5. Uruchom symulację

- Naciśnij **Play** w edytorze
- Sterowanie:
  - **W** – gaz
  - **A / D** – skręt w lewo / prawo

### Parametry fizyki (edytowalne w BP)

| Parametr | Wartość domyślna | Opis |
|----------|-----------------|------|
| `Engine Force` | 5000 | Siła napędowa silnika |
| `Steer Torque` | 3000 | Moment skrętu |
| `Drag Coefficient` | 0.5 | Opór powietrza |

## Struktura kodu

```
Source/falubaz/
├── Vehicles/
│   └── SpeedwayMotorcycle.h/.cpp   # Pawn motocykla, fizyka, input
├── UI/
│   └── SpeedwayHUD.h/.cpp          # Widget HUD (prędkość, RPM)
└── Track/
    └── SpeedwayTrack.h/.cpp        # Proceduralny tor żużlowy
```

## Git – zasady pracy z branchami

### Struktura branchy

```
feature/nazwa  ──┐
                 ├──► dev ──► prod
feature/nazwa  ──┘
```

| Branch | Przeznaczenie |
|--------|---------------|
| `prod` | Stabilny, działający kod – tylko merge z `dev` |
| `dev` | Integracja – tu trafiają gotowe feature'y przez Pull Request |
| `feature/nazwa` | Bieżąca praca – jeden branch = jedna funkcjonalność |

### Workflow

```bash
# 1. Zacznij od aktualnego dev
git checkout dev
git pull origin dev

# 2. Utwórz branch dla nowej funkcjonalności
git checkout -b feature/nazwa-funkcji

# 3. Pracuj, commituj lokalnie
git add .
git commit -m "Opis zmian"

# 4. Wypchnij branch
git push origin feature/nazwa-funkcji

# 5. Utwórz Pull Request: feature/nazwa → dev (na GitHubie)
```

### Zasady ochrony brancha `dev`

- Zmiany tylko przez **Pull Request** – bezpośredni push zablokowany
- **Force push** zablokowany
- Historia liniowa – brak merge commitów (wymagany rebase lub squash)
- Usuwanie brancha zablokowane

### Zasady ochrony brancha `prod`

- Zmiany tylko przez **Pull Request** z `dev`
- **Force push** zablokowany
- Bezpośredni push zablokowany

## Zasoby

- [Dokumentacja Blender – Confluence](https://falubaz.atlassian.net/wiki/spaces/Falubaz/pages/edit-v2/4456451?draftShareId=a2f041e6-101e-4031-9d34-bf004aa56c94)
