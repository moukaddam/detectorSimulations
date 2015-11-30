/*****************************************************************************
 * Original Author: N. de Sereville  contact address: deserevi@ipno.in2p3.fr *
 * Modified by    : Ryan Dunlop  contact address: rdunlop@uoguelph.ca        *
 *---------------------------------------------------------------------------*
 * Decription: This class stores the results of the G4 simulation for the    *
 *             Griffin detector. And was adapted from S1 detector Class.     *
 *             in th NPTOOL project                                          *
 *             This class derives from TObject (ROOT) and its aim is to be   *
 *             stored in the output TTree of the G4 simulation               *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/

#include <iostream>
using namespace std;

#include "TGriffinData.h"


ClassImp(TGriffinData)

TGriffinData::TGriffinData()
{
        // Default constructor
        ClearVariables();
}

TGriffinData::~TGriffinData() {}


void TGriffinData::ClearVariables()
{

        fDetNbr.clear();
        fCrystalNbr.clear(); 
        fEnergy.clear();
        fPositionFirstHit.clear();
        
        fPrimaryEnergy.clear();
        fPrimaryPdg.clear();

        fEventNumber = -1;
}


void TGriffinData::Dump() const
{
   cout << "XXXXXXXXXXXXXXXXXXXXXXXX Griffin Event : " << fEventNumber <<  "XXXXXXXXXXXXXXXXXXXXXXXX" << endl;

   // Griffin
   // (E)
   cout << "GriffinMult = " << fDetNbr.size() << endl;
   for (UShort_t i = 0; i < fDetNbr.size(); i++)
      cout << "DetE: " << fDetNbr[i] << " CrystalE: " << fCrystalNbr[i] 
      		 << " Energy: " << fEnergy[i] <<  endl;
   // First hit
   cout << "Position of First Hit Mult = " << fPositionFirstHit.size() << endl;
   for (UShort_t i = 0; i < fPositionFirstHit.size(); i++)   
   cout << "    X - " << fPositionFirstHit.at(i).X() << "  Y - " <<fPositionFirstHit.at(i).Y() << " Z - " << fPositionFirstHit.at(i).Z() << endl;
   
   // Primary Pdg
   cout << "Primary Particle Pdg Mult = " << fPrimaryPdg.size() << endl;
   for (UShort_t i = 0; i < fPrimaryPdg.size(); i++)   
   cout << "   Pdg - " << fPrimaryPdg.at(i) << endl;
   // Primary energy
   cout << "Primary Particle Energy Mult = " << fPrimaryEnergy.size() << endl;
   for (UShort_t i = 0; i < fPrimaryEnergy.size(); i++)   
   cout << "   Energy - " << fPrimaryEnergy.at(i) << endl;
   
   
}
