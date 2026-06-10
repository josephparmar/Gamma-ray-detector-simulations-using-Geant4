#include "PMDetectorConstruction.hh"

PMDetectorConstruction::PMDetectorConstruction()
{

}

PMDetectorConstruction::~PMDetectorConstruction()
{
    
}

G4VPhysicalVolume *PMDetectorConstruction::Construct()
{
    G4bool check0verlaps = true ;
    G4NistManager *nist = G4NistManager::Instance();
    G4Material *worldMat = nist->FindOrBuildMaterial("G4_AIR");
    G4Material *leadMat = nist->FindOrBuildMaterial("G4_Pb");
    G4Material *detMat = nist ->FindOrBuildMaterial("G4_SODIUM_IODIDE");

    G4double xWorld = 1. *m;
    G4double yWorld = 1. *m;
    G4double zWorld = 1. *m;

    G4Box *solidWorld = new G4Box("solidWorld", 0.5 * xWorld, 0.5 * yWorld, 0.5 * zWorld);
    G4LogicalVolume *logicWorld = new G4LogicalVolume(solidWorld, worldMat, "logicalWorld");
    G4VPhysicalVolume *physWorld = new G4PVPlacement(0, G4ThreeVector(0., 0., 0.), logicWorld, "physworld", 0, false, 0, check0verlaps);

    /*
    G4double leadThickness = 2. *mm;
    G4double leadSize = 10. *cm;
    G4Box *solidLead = new G4Box("solidLead", 0.5 * leadSize, 0.5 * leadSize, 0.5 * leadThickness);
    G4LogicalVolume *logicLead = new G4LogicalVolume(solidLead, leadMat, "logicLead");
    G4VPhysicalVolume *physLead = new G4PVPlacement(0, G4ThreeVector(0, 0, 5 * cm), logicLead, "physLead", logicWorld, false, check0verlaps);

    G4VisAttributes *leadVisAtt = new G4VisAttributes(G4Color(1.0, 0.0, 0.0, 0.5));
    leadVisAtt->SetForceSolid(true);
    logicLead->SetVisAttributes(leadVisAtt);
    */




    
    G4double detectorWidth = 5 * cm;
    G4double detectorLength = 100 *cm;
    G4Box *solidDetector = new G4Box("solidDetector", detectorWidth * .5, detectorWidth * .5, detectorLength* .5);

    logicDetector = new G4LogicalVolume(solidDetector, detMat, "logicDetector");
    G4VPhysicalVolume *physDetector = new G4PVPlacement(0, G4ThreeVector(0, 0, 60.5 * cm), logicDetector, "physDetector", logicWorld, false, check0verlaps);


    G4VisAttributes *detVisAtt = new G4VisAttributes(G4Color(1.0, 1.0, 0.0, 0.5));
    detVisAtt->SetForceSolid(true);
    logicDetector->SetVisAttributes(detVisAtt);

    return physWorld;
}

void PMDetectorConstruction::ConstructSDandField()
{
    PMSensitiveDetector *sensDet = new PMSensitiveDetector("SensitveDetector");
    logicDetector->SetSensitiveDetector(sensDet);
    G4SDManager::GetSDMpointer()->AddNewDetector(sensDet);
}