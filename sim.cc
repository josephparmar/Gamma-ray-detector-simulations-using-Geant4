#include <iostream>


//Geant4 specific headers

/*run managers - responsible for
-initializing the detector
-initializing the physics list
-initializing particle generation
-controlling event loops
-managing simulation execution
*/
#include "G4RunManager.hh"
#include "G4MTRunManager.hh"

//Interface manager
#include "G4UImanager.hh"

//Visualisation (OpenGL etc)
#include "G4VisManager.hh"
#include "G4VisExecutive.hh"

//interactive UI manager
#include "G4UIExecutive.hh"

#include "PMPhysicsList.hh"
#include "PMDetectorConstruction.hh"
#include "PMActionInitialization.hh"

int main(int argc, char** argv) //argc argv let command line params be passed

{

    G4UIExecutive *ui = new G4UIExecutive(argc, argv); //creates the UI. argc and argv are added so geant4 can process command line 

    //create object of run manager. If multithreaded then use multithreaded run manager, else single core.
    #ifdef G4MULTITHREADED
        G4MTRunManager *runManager = new G4MTRunManager;
    #else
        G4RunManager *runManager = new G4RunManager;
    #endif

    //physics list
    runManager->SetUserInitialization(new PMPhysicsList());

    //Detector construction
    runManager->SetUserInitialization(new PMDetectorConstruction());

    //Action Init
    runManager->SetUserInitialization(new PMActionInitialization());

    //initializes graphics drivers and such
    G4VisManager *visManager = new G4VisExecutive();
    visManager ->Initialize();

    
    G4UImanager *UImanager = G4UImanager::GetUIpointer();

    UImanager->ApplyCommand("/control/execute vis.mac");

    ui -> SessionStart();

    return 0;
}
