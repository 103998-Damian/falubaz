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

- Unreal Engine 5.4 lub 5.5
- Visual Studio 2022 z workloadem **"Game development with C++"**
- Blender 3.x+ (do edycji modeli)

## Pierwsze uruchomienie

1. Otwórz Unreal Editor i utwórz nowy projekt C++ w `unreal/`:
   - `New Project → C++ → Vehicle (2-Wheel) → falubaz-simulation`
2. Skopiuj pliki z `Source/falubaz/` do nowego projektu
3. Skompiluj: `Tools → Compile` lub `Build` w Visual Studio
4. Modele z Blendera eksportuj jako `.fbx` do `Content/Models/`

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
