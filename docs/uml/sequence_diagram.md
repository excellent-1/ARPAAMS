@startuml
actor Operator
Operator -> BeamformingEngine: setStrategy(strategy)
Operator -> BeamformingEngine: process(array, target)
BeamformingEngine -> IBeamformingStrategy: applyBeamforming(array, target)
IBeamformingStrategy --> BeamformingEngine: return result
@enduml
