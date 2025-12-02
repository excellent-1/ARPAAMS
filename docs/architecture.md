# ARPAAMS System Architecture

## 1. Overview

The ARPAAMS project implements a modular radar beamforming engine using the **Strategy Pattern**.
This allows different beamforming algorithms (Monopulse, Phased Array, Adaptive, etc.) to be swapped
at runtime without modifying the engine itself.

---

## 2. Architecture Diagram (UML)

```plantuml
@startuml
interface IBeamformingStrategy {
    +applyBeamforming(AntennaArray, TargetInfo)
}

class MonopulseStrategy
class PhasedArrayStrategy
class BeamformingEngine {
    -strategy: IBeamformingStrategy
    +setStrategy()
    +process()
}

IBeamformingStrategy <|.. MonopulseStrategy
IBeamformingStrategy <|.. PhasedArrayStrategy
BeamformingEngine --> IBeamformingStrategy
BeamformingEngine --> AntennaArray
BeamformingEngine --> TargetInfo
@enduml
